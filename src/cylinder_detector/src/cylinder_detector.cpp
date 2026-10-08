#include <cstdio>
#include <cmath>
#include <random>
#include <limits>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <visualization_msgs/msg/marker_array.hpp>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <tf2_sensor_msgs/tf2_sensor_msgs.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <opencv2/opencv.hpp>

#include <Eigen/Core>
#include <Eigen/Cholesky>

class CylinderDetector : public rclcpp::Node {
    protected:
        struct Detection {
            Eigen::Vector2d center;
            double radius;
            double zmin, zmax;
            double range;
        };

        // Fusion de todas las observaciones de un mismo cilindro, ponderadas
        // por la inversa de la varianza, que crece con la distancia.
        struct Cylinder {
            double sw = 0.0;
            Eigen::Vector2d sc = Eigen::Vector2d::Zero();
            double sr = 0.0;
            double zmin = std::numeric_limits<double>::max();
            double zmax = -std::numeric_limits<double>::max();
            int count = 0;

            Eigen::Vector2d center() const {return sc / sw;}
            double radius() const {return sr / sw;}
            void add(const Detection & d, double w) {
                sw += w;
                sc += w * d.center;
                sr += w * d.radius;
                zmin = std::min(zmin,d.zmin);
                zmax = std::max(zmax,d.zmax);
                count += 1;
            }
        };

        rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr scan_sub_;
        rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr vertical_pub_;
        rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr marker_pub_;
        std::shared_ptr<tf2_ros::TransformListener> tf_listener{nullptr};
        std::unique_ptr<tf2_ros::Buffer> tf_buffer;

        std::string map_frame_;
        double min_range_, max_range_;
        double grid_resolution_;
        double min_vertical_extent_;
        double floor_margin_;
        int min_cluster_points_;
        int ransac_iterations_;
        double tolerance_;
        double min_radius_, max_radius_;
        double min_inlier_ratio_;
        double min_arc_;
        double min_height_;
        double association_margin_;
        int min_detections_;

        std::vector<Cylinder> cylinders_;

        std::random_device rd;
        std::mt19937 gen;

    protected:

        void pointCloudCallback(sensor_msgs::msg::PointCloud2::SharedPtr msg) {
            geometry_msgs::msg::TransformStamped transformStamped;
            sensor_msgs::msg::PointCloud2 pc_msg;
            try {
                std::string errStr;
                if (!tf_buffer->canTransform(map_frame_, msg->header.frame_id, msg->header.stamp,
                            rclcpp::Duration(std::chrono::duration<double>(1.0)),&errStr)) {
                    RCLCPP_ERROR(this->get_logger(),"Cannot transform cloud: %s",errStr.c_str());
                    return;
                }
                transformStamped = tf_buffer->lookupTransform(map_frame_, msg->header.frame_id, msg->header.stamp);
                tf2::doTransform(*msg,pc_msg,transformStamped);
            } catch (const tf2::TransformException & ex){
                RCLCPP_ERROR(this->get_logger(),"%s",ex.what());
                return;
            }
            pcl::PointCloud<pcl::PointXYZ> pc;
            pcl::fromROSMsg(pc_msg,pc);
            Eigen::Vector3d sensor(transformStamped.transform.translation.x,
                    transformStamped.transform.translation.y,
                    transformStamped.transform.translation.z);

            // Rejilla horizontal local alrededor del sensor. Una superficie vertical
            // apila en la misma celda puntos de alturas muy distintas, el suelo no.
            int N = ceil(2 * max_range_ / grid_resolution_);
            double x0 = sensor.x() - max_range_;
            double y0 = sensor.y() - max_range_;
            cv::Mat_<float> zmin(N,N,std::numeric_limits<float>::max());
            cv::Mat_<float> zmax(N,N,-std::numeric_limits<float>::max());
            std::vector<cv::Point> cell(pc.size(),cv::Point(-1,-1));
            for (size_t k=0;k<pc.size();k++) {
                const pcl::PointXYZ & P = pc[k];
                if (!std::isfinite(P.x) || !std::isfinite(P.y) || !std::isfinite(P.z)) {
                    continue;
                }
                double r = (Eigen::Vector3d(P.x,P.y,P.z) - sensor).norm();
                if ((r < min_range_) || (r > max_range_)) {
                    continue;
                }
                int u = floor((P.x - x0) / grid_resolution_);
                int v = floor((P.y - y0) / grid_resolution_);
                if ((u < 0) || (v < 0) || (u >= N) || (v >= N)) {
                    continue;
                }
                cell[k] = cv::Point(u,v);
                zmin(v,u) = std::min(zmin(v,u),P.z);
                zmax(v,u) = std::max(zmax(v,u),P.z);
            }
            cv::Mat_<uint8_t> vertical(N,N,uint8_t(0));
            for (int v=0;v<N;v++) {
                for (int u=0;u<N;u++) {
                    if (zmax(v,u) - zmin(v,u) > min_vertical_extent_) {
                        vertical(v,u) = 255;
                    }
                }
            }
            cv::Mat_<int> label;
            int n_labels = cv::connectedComponents(vertical,label,8,CV_32S);

            // Se quitan los puntos del suelo que comparten celda con el objeto
            std::vector< std::vector<Eigen::Vector3d> > clusters(n_labels);
            pcl::PointCloud<pcl::PointXYZ> pc_vertical;
            for (size_t k=0;k<pc.size();k++) {
                const cv::Point & c = cell[k];
                if ((c.x < 0) || !vertical(c) || (pc[k].z < zmin(c) + floor_margin_)) {
                    continue;
                }
                clusters[label(c)].push_back(Eigen::Vector3d(pc[k].x,pc[k].y,pc[k].z));
                pc_vertical.push_back(pc[k]);
            }

            int n_detections = 0;
            for (int l=1;l<n_labels;l++) {
                Detection d;
                if (((int)clusters[l].size() >= min_cluster_points_) && fitCylinder(clusters[l],sensor,d)) {
                    integrate(d);
                    n_detections += 1;
                }
            }
            RCLCPP_INFO_THROTTLE(this->get_logger(),*this->get_clock(),5000,
                    "%d clusters, %d cylinders detected, %d in map",n_labels-1,n_detections,(int)cylinders_.size());

            sensor_msgs::msg::PointCloud2 vertical_msg;
            pcl::toROSMsg(pc_vertical,vertical_msg);
            vertical_msg.header.stamp = msg->header.stamp;
            vertical_msg.header.frame_id = map_frame_;
            vertical_pub_->publish(vertical_msg);
            publishMarkers();
        }

        bool fitCylinder(const std::vector<Eigen::Vector3d> & pts, const Eigen::Vector3d & sensor, Detection & d) {
            // RANSAC sobre el circulo que forman los puntos proyectados en el suelo
            std::uniform_int_distribution<size_t> dsample(0,pts.size()-1);
            size_t best = 0;
            Eigen::Vector2d center = Eigen::Vector2d::Zero();
            double radius = 0;
            for (int it=0;it<ransac_iterations_;it++) {
                Eigen::Vector2d a = pts[dsample(gen)].head<2>();
                Eigen::Vector2d b = pts[dsample(gen)].head<2>() - a;
                Eigen::Vector2d c = pts[dsample(gen)].head<2>() - a;
                // Circulo circunscrito; den es nulo si los puntos estan alineados
                double den = 2 * (b.x()*c.y() - b.y()*c.x());
                if (fabs(den) < 1e-9) {
                    continue;
                }
                Eigen::Vector2d u((c.y()*b.squaredNorm() - b.y()*c.squaredNorm()) / den,
                        (b.x()*c.squaredNorm() - c.x()*b.squaredNorm()) / den);
                double r = u.norm();
                if ((r < min_radius_) || (r > max_radius_)) {
                    continue;
                }
                size_t count = countInliers(pts,a+u,r);
                if (count > best) {
                    best = count;
                    center = a + u;
                    radius = r;
                }
            }
            if (best < (size_t)min_cluster_points_) {
                return false;
            }

            // Ajuste algebraico x^2+y^2+Dx+Ey+F = 0 por minimos cuadrados sobre
            // los inliers, en coordenadas centradas para que este bien condicionado
            std::vector<Eigen::Vector3d> inliers;
            for (const Eigen::Vector3d & p : pts) {
                if (fabs((p.head<2>() - center).norm() - radius) < tolerance_) {
                    inliers.push_back(p);
                }
            }
            Eigen::Vector2d m = Eigen::Vector2d::Zero();
            for (const Eigen::Vector3d & p : inliers) {
                m += p.head<2>();
            }
            m /= inliers.size();
            Eigen::MatrixXd A(inliers.size(),3);
            Eigen::VectorXd B(inliers.size());
            for (size_t k=0;k<inliers.size();k++) {
                Eigen::Vector2d q = inliers[k].head<2>() - m;
                A(k,0) = q.x();
                A(k,1) = q.y();
                A(k,2) = 1.0;
                B(k) = -q.squaredNorm();
            }
            Eigen::Vector3d S = (A.transpose() * A).ldlt().solve(A.transpose() * B);
            center = m - S.head<2>() / 2;
            radius = sqrt(S.head<2>().squaredNorm() / 4 - S(2));
            if (!std::isfinite(radius) || (radius < min_radius_) || (radius > max_radius_)) {
                return false;
            }

            // Cerca del circulo casi todos los puntos deben estar sobre el. Rechaza
            // las esquinas de las cajas y los trozos de pared.
            size_t near = 0, on = 0;
            double z_lo = std::numeric_limits<double>::max(), z_hi = -z_lo;
            std::vector<double> angles;
            for (const Eigen::Vector3d & p : pts) {
                Eigen::Vector2d q = p.head<2>() - center;
                double dist = q.norm();
                if (dist > radius + 5 * tolerance_) {
                    continue;
                }
                near += 1;
                if (fabs(dist - radius) < tolerance_) {
                    on += 1;
                    angles.push_back(atan2(q.y(),q.x()));
                    z_lo = std::min(z_lo,p.z());
                    z_hi = std::max(z_hi,p.z());
                }
            }
            if ((on < (size_t)min_cluster_points_) || (on < min_inlier_ratio_ * near)) {
                return false;
            }
            // Arco cubierto = 2pi menos el mayor hueco entre angulos consecutivos
            std::sort(angles.begin(),angles.end());
            double max_gap = angles.front() + 2*M_PI - angles.back();
            for (size_t k=1;k<angles.size();k++) {
                max_gap = std::max(max_gap,angles[k] - angles[k-1]);
            }
            if (2*M_PI - max_gap < min_arc_) {
                return false;
            }
            // Superficie convexa vista desde el sensor: el centro queda detras
            Eigen::Vector2d s = sensor.head<2>();
            if ((center - s).norm() < (m - s).norm()) {
                return false;
            }
            if (z_hi - z_lo < min_height_) {
                return false;
            }
            d.center = center;
            d.radius = radius;
            d.zmin = z_lo;
            d.zmax = z_hi;
            d.range = (center - s).norm();
            return true;
        }

        size_t countInliers(const std::vector<Eigen::Vector3d> & pts, const Eigen::Vector2d & center, double radius) const {
            size_t count = 0;
            for (const Eigen::Vector3d & p : pts) {
                if (fabs((p.head<2>() - center).norm() - radius) < tolerance_) {
                    count += 1;
                }
            }
            return count;
        }

        void integrate(const Detection & d) {
            int best = -1;
            double best_dist = 0;
            for (size_t k=0;k<cylinders_.size();k++) {
                double dist = (cylinders_[k].center() - d.center).norm();
                if ((dist < std::max(cylinders_[k].radius(),d.radius) + association_margin_)
                        && ((best < 0) || (dist < best_dist))) {
                    best = k;
                    best_dist = dist;
                }
            }
            if (best < 0) {
                best = cylinders_.size();
                cylinders_.push_back(Cylinder());
            }
            // El error lateral crece como la distancia (tamano del pixel), asi que
            // la varianza crece como su cuadrado
            double r = std::max(d.range,0.5);
            Cylinder & cyl = cylinders_[best];
            cyl.add(d,1.0 / (r*r));
            if (cyl.count == min_detections_) {
                RCLCPP_INFO(this->get_logger(),"New cylinder %d at (%.2f, %.2f), radius %.3f",
                        best,cyl.center().x(),cyl.center().y(),cyl.radius());
            }
        }

        void publishMarkers() {
            visualization_msgs::msg::MarkerArray ma;
            rclcpp::Time now = this->get_clock()->now();
            for (size_t k=0;k<cylinders_.size();k++) {
                const Cylinder & cyl = cylinders_[k];
                if (cyl.count < min_detections_) {
                    continue;
                }
                visualization_msgs::msg::Marker m;
                m.header.stamp = now;
                m.header.frame_id = map_frame_;
                m.ns = "cylinders";
                m.id = k;
                m.type = visualization_msgs::msg::Marker::CYLINDER;
                m.action = visualization_msgs::msg::Marker::ADD;
                m.pose.position.x = cyl.center().x();
                m.pose.position.y = cyl.center().y();
                m.pose.position.z = (cyl.zmin + cyl.zmax) / 2;
                m.pose.orientation.w = 1.0;
                m.scale.x = 2 * cyl.radius();
                m.scale.y = 2 * cyl.radius();
                m.scale.z = cyl.zmax - cyl.zmin;
                m.color.a = 0.8;
                m.color.r = 1.0;
                m.color.g = 0.5;
                m.color.b = 0.0;
                ma.markers.push_back(m);

                m.ns = "cylinder_labels";
                m.type = visualization_msgs::msg::Marker::TEXT_VIEW_FACING;
                m.pose.position.z = cyl.zmax + 0.2;
                m.scale.x = m.scale.y = 0.0;
                m.scale.z = 0.2;
                m.color.r = m.color.g = m.color.b = 1.0;
                char text[64];
                // RViz dibuja los espacios muy anchos, cada dato va en su linea
                snprintf(text,sizeof(text),"r=%.3f\nn=%d",cyl.radius(),cyl.count);
                m.text = text;
                ma.markers.push_back(m);
            }
            marker_pub_->publish(ma);
        }

    public:
        CylinderDetector() : rclcpp::Node("cylinder_detector"), gen(rd()) {
            this->declare_parameter("~/map_frame",std::string("world"));
            this->declare_parameter("~/min_range",0.3);
            this->declare_parameter("~/max_range",3.5);
            this->declare_parameter("~/grid_resolution",0.05);
            this->declare_parameter("~/min_vertical_extent",0.2);
            this->declare_parameter("~/floor_margin",0.03);
            this->declare_parameter("~/min_cluster_points",30);
            this->declare_parameter("~/ransac_iterations",200);
            this->declare_parameter("~/tolerance",0.01);
            this->declare_parameter("~/min_radius",0.07);
            this->declare_parameter("~/max_radius",0.3);
            this->declare_parameter("~/min_inlier_ratio",0.9);
            this->declare_parameter("~/min_arc_deg",90.0);
            this->declare_parameter("~/min_height",0.4);
            this->declare_parameter("~/association_margin",0.15);
            this->declare_parameter("~/min_detections",3);
            map_frame_ = this->get_parameter("~/map_frame").as_string();
            min_range_ = this->get_parameter("~/min_range").as_double();
            max_range_ = this->get_parameter("~/max_range").as_double();
            grid_resolution_ = this->get_parameter("~/grid_resolution").as_double();
            min_vertical_extent_ = this->get_parameter("~/min_vertical_extent").as_double();
            floor_margin_ = this->get_parameter("~/floor_margin").as_double();
            min_cluster_points_ = this->get_parameter("~/min_cluster_points").as_int();
            ransac_iterations_ = this->get_parameter("~/ransac_iterations").as_int();
            tolerance_ = this->get_parameter("~/tolerance").as_double();
            min_radius_ = this->get_parameter("~/min_radius").as_double();
            max_radius_ = this->get_parameter("~/max_radius").as_double();
            min_inlier_ratio_ = this->get_parameter("~/min_inlier_ratio").as_double();
            min_arc_ = this->get_parameter("~/min_arc_deg").as_double() * M_PI / 180.;
            min_height_ = this->get_parameter("~/min_height").as_double();
            association_margin_ = this->get_parameter("~/association_margin").as_double();
            min_detections_ = this->get_parameter("~/min_detections").as_int();

            tf_buffer = std::make_unique<tf2_ros::Buffer>(this->get_clock());
            tf_listener = std::make_shared<tf2_ros::TransformListener>(*tf_buffer);

            auto qos = rclcpp::QoS(rclcpp::KeepLast(3)).best_effort().durability_volatile();
            scan_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>("~/scans",qos,
                    std::bind(&CylinderDetector::pointCloudCallback,this,std::placeholders::_1));
            vertical_pub_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("~/vertical_points",1);
            marker_pub_ = this->create_publisher<visualization_msgs::msg::MarkerArray>("~/cylinders",1);
        }

        ~CylinderDetector() {
            for (size_t k=0;k<cylinders_.size();k++) {
                const Cylinder & cyl = cylinders_[k];
                if (cyl.count >= min_detections_) {
                    printf("Cylinder %d: x %.3f y %.3f r %.3f z [%.2f %.2f] n %d\n",(int)k,
                            cyl.center().x(),cyl.center().y(),cyl.radius(),cyl.zmin,cyl.zmax,cyl.count);
                }
            }
        }
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<CylinderDetector>());
    rclcpp::shutdown();
    return 0;
}
