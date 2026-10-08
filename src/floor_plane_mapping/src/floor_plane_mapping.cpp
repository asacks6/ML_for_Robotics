#include <cstdio>
#include <cmath>
#include <unordered_map>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <tf2_sensor_msgs/tf2_sensor_msgs.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <opencv2/opencv.hpp>

#include <Eigen/Core>
#include <Eigen/Eigenvalues>

// Valores de OccupancyGrid guardados en uint8: 0xFF se lee como -1 (desconocido)
#define TRAVERSABLE 0
#define OBSTACLE 100
#define UNKNOWN 0xFF

class FloorPlaneMapping : public rclcpp::Node {
    protected:
        struct Bucket {
            size_t n = 0;
            Eigen::Vector3d s = Eigen::Vector3d::Zero();
            Eigen::Matrix3d ss = Eigen::Matrix3d::Zero();
            double range = 0.0;
        };
        struct Observation {
            bool traversable;
            Eigen::Vector3d mean;
            Eigen::Vector3d normal;
            double range;
        };

        rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr scan_sub_;
        rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr labels_pub_;
        rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr proba_pub_;
        rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr trav_pub_;
        rclcpp::TimerBase::SharedPtr timer_;
        std::shared_ptr<tf2_ros::TransformListener> tf_listener{nullptr};
        std::unique_ptr<tf2_ros::Buffer> tf_buffer;

        std::string map_frame_;
        std::string save_prefix_;
        double resolution_;
        double min_range_, max_range_;
        int min_points_;
        double min_spread_;
        double max_slope_;
        double max_roughness_;
        double max_step_;
        double p_near_, p_far_;
        double l_max_;
        double threshold_;

        nav_msgs::msg::MapMetaData info_;
        // Objetivo 1: ultima etiqueta observada en cada celda
        cv::Mat_<uint8_t> labels_;
        // Objetivo 3: log(P(T)/P(N)) por celda, 0 equivale al prior P(T) = 0.5
        cv::Mat_<float> log_odds_;
        cv::Mat_<uint8_t> observed_;

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

            // Cada punto cae en el cubo de su celda; solo se guardan los momentos
            // de orden 1 y 2, que bastan para la media y la covarianza.
            std::unordered_map<int,Bucket> buckets;
            for (const pcl::PointXYZ & P : pc) {
                if (!std::isfinite(P.x) || !std::isfinite(P.y) || !std::isfinite(P.z)) {
                    continue;
                }
                Eigen::Vector3d p(P.x,P.y,P.z);
                double r = (p - sensor).norm();
                if ((r < min_range_) || (r > max_range_)) {
                    continue;
                }
                int i = floor((p.x() - info_.origin.position.x) / resolution_);
                int j = floor((p.y() - info_.origin.position.y) / resolution_);
                if ((i < 0) || (j < 0) || (i >= labels_.cols) || (j >= labels_.rows)) {
                    continue;
                }
                // Relativo al centro de la celda para no perder precision en ss
                Eigen::Vector3d q = p - cellCenter(i,j);
                Bucket & b = buckets[j*labels_.cols + i];
                b.n += 1;
                b.s += q;
                b.ss += q * q.transpose();
                b.range += r;
            }

            std::unordered_map<int,Observation> obs;
            for (const auto & [k,b] : buckets) {
                if (b.n < (size_t)min_points_) {
                    continue;
                }
                Eigen::Vector3d mean = b.s / b.n;
                Eigen::Matrix3d cov = b.ss / b.n - mean * mean.transpose();
                Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> es(cov);
                // Puntos casi alineados (una sola fila de la imagen a lo lejos):
                // el plano no esta definido y la celda no se observa.
                if (es.eigenvalues()(1) < min_spread_*min_spread_) {
                    continue;
                }
                Eigen::Vector3d normal = es.eigenvectors().col(0);
                double slope = acos(std::min(1.0,fabs(normal.z())));
                double roughness = sqrt(std::max(0.0,es.eigenvalues()(0)));
                Observation o;
                o.traversable = (slope < max_slope_) && (roughness < max_roughness_);
                o.mean = mean + cellCenter(k % labels_.cols, k / labels_.cols);
                o.normal = normal;
                o.range = b.range / b.n;
                obs[k] = o;
            }

            // Escalon: el centroide de una celda vecina esta lejos del plano de
            // esta celda. Detecta bordes de superficies planas elevadas.
            std::vector<int> steps;
            for (const auto & [k,o] : obs) {
                if (!o.traversable) {
                    continue;
                }
                int i = k % labels_.cols, j = k / labels_.cols;
                bool step = false;
                for (int dj=-1;(dj<=1) && !step;dj++) {
                    for (int di=-1;(di<=1) && !step;di++) {
                        if ((i+di < 0) || (i+di >= labels_.cols) || (j+dj < 0) || (j+dj >= labels_.rows)) {
                            continue;
                        }
                        auto it = obs.find((j+dj)*labels_.cols + i+di);
                        step = (it != obs.end()) && (fabs(o.normal.dot(it->second.mean - o.mean)) > max_step_);
                    }
                }
                if (step) {
                    steps.push_back(k);
                }
            }
            for (int k : steps) {
                obs[k].traversable = false;
            }

            for (const auto & [k,o] : obs) {
                int i = k % labels_.cols, j = k / labels_.cols;
                labels_(j,i) = o.traversable ? TRAVERSABLE : OBSTACLE;
                // Modelo de sensor simetrico P(z=t|T) = P(z=n|N) = p(r), que decrece
                // con la distancia porque las celdas lejanas reciben pocos puntos.
                double p = p_near_ + (p_far_ - p_near_) * std::min(1.0, o.range / max_range_);
                double dl = log(p / (1 - p));
                double l = log_odds_(j,i) + (o.traversable ? dl : -dl);
                log_odds_(j,i) = std::max(-l_max_, std::min(l_max_, l));
                observed_(j,i) = 1;
            }
            RCLCPP_INFO_THROTTLE(this->get_logger(),*this->get_clock(),5000,
                    "%d points, %d cells updated",(int)pc.size(),(int)obs.size());
        }

        Eigen::Vector3d cellCenter(int i, int j) const {
            return Eigen::Vector3d(info_.origin.position.x + (i+0.5)*resolution_,
                    info_.origin.position.y + (j+0.5)*resolution_, 0.0);
        }

        double probaTraversable(int j, int i) const {
            return 1.0 - 1.0 / (1.0 + exp(log_odds_(j,i)));
        }

        void mat_to_og(const cv::Mat_<uint8_t> & mat, nav_msgs::msg::OccupancyGrid & og) {
            og.info = info_;
            og.header.frame_id = map_frame_;
            og.header.stamp = this->get_clock()->now();
            og.data.resize(mat.cols*mat.rows);
            for (int j=0;j<mat.rows;j++) {
                for (int i=0;i<mat.cols;i++) {
                    og.data[j*mat.cols + i] = (int8_t)mat(j,i);
                }
            }
        }

        void computeBayesMaps(cv::Mat_<uint8_t> & proba, cv::Mat_<uint8_t> & trav) {
            proba = cv::Mat_<uint8_t>(labels_.size(),UNKNOWN);
            trav = cv::Mat_<uint8_t>(labels_.size(),UNKNOWN);
            for (int j=0;j<labels_.rows;j++) {
                for (int i=0;i<labels_.cols;i++) {
                    if (!observed_(j,i)) {
                        continue;
                    }
                    double pt = probaTraversable(j,i);
                    // La OccupancyGrid representa P(no transitable) en [0,100]
                    proba(j,i) = round(100 * (1 - pt));
                    if (pt > threshold_) {
                        trav(j,i) = TRAVERSABLE;
                    } else if (pt < 1 - threshold_) {
                        trav(j,i) = OBSTACLE;
                    }
                }
            }
        }

        void timerCallback() {
            cv::Mat_<uint8_t> proba, trav;
            computeBayesMaps(proba,trav);
            nav_msgs::msg::OccupancyGrid og;
            mat_to_og(labels_,og);
            labels_pub_->publish(og);
            mat_to_og(proba,og);
            proba_pub_->publish(og);
            mat_to_og(trav,og);
            trav_pub_->publish(og);
        }

        // Imagen con el norte hacia arriba: blanco transitable, negro no, gris desconocido
        cv::Mat_<uint8_t> toImage(const cv::Mat_<uint8_t> & mat) const {
            cv::Mat_<uint8_t> img(mat.size(),128);
            for (int j=0;j<mat.rows;j++) {
                for (int i=0;i<mat.cols;i++) {
                    if (mat(j,i) == UNKNOWN) {
                        continue;
                    }
                    img(j,i) = 255 - (255 * mat(j,i)) / 100;
                }
            }
            cv::flip(img,img,0);
            return img;
        }

    public:
        FloorPlaneMapping() : rclcpp::Node("floor_plane_mapping") {
            this->declare_parameter("~/map_frame",std::string("world"));
            this->declare_parameter("~/save_prefix",std::string(""));
            this->declare_parameter("~/resolution",0.1);
            this->declare_parameter("~/width",11.0);
            this->declare_parameter("~/height",11.0);
            this->declare_parameter("~/origin_x",-5.5);
            this->declare_parameter("~/origin_y",-5.5);
            this->declare_parameter("~/min_range",0.3);
            this->declare_parameter("~/max_range",3.0);
            this->declare_parameter("~/min_points",6);
            this->declare_parameter("~/min_spread",0.015);
            this->declare_parameter("~/max_slope_deg",20.0);
            this->declare_parameter("~/max_roughness",0.02);
            this->declare_parameter("~/max_step",0.05);
            this->declare_parameter("~/p_near",0.9);
            this->declare_parameter("~/p_far",0.6);
            this->declare_parameter("~/p_max",0.99);
            this->declare_parameter("~/threshold",0.7);
            this->declare_parameter("~/publish_period",1.0);
            map_frame_ = this->get_parameter("~/map_frame").as_string();
            save_prefix_ = this->get_parameter("~/save_prefix").as_string();
            resolution_ = this->get_parameter("~/resolution").as_double();
            min_range_ = this->get_parameter("~/min_range").as_double();
            max_range_ = this->get_parameter("~/max_range").as_double();
            min_points_ = this->get_parameter("~/min_points").as_int();
            min_spread_ = this->get_parameter("~/min_spread").as_double();
            max_slope_ = this->get_parameter("~/max_slope_deg").as_double() * M_PI / 180.;
            max_roughness_ = this->get_parameter("~/max_roughness").as_double();
            max_step_ = this->get_parameter("~/max_step").as_double();
            p_near_ = this->get_parameter("~/p_near").as_double();
            p_far_ = this->get_parameter("~/p_far").as_double();
            double p_max = this->get_parameter("~/p_max").as_double();
            l_max_ = log(p_max / (1 - p_max));
            threshold_ = this->get_parameter("~/threshold").as_double();

            info_.resolution = resolution_;
            info_.width = round(this->get_parameter("~/width").as_double() / resolution_);
            info_.height = round(this->get_parameter("~/height").as_double() / resolution_);
            info_.origin.position.x = this->get_parameter("~/origin_x").as_double();
            info_.origin.position.y = this->get_parameter("~/origin_y").as_double();
            info_.origin.orientation.w = 1.0;
            labels_ = cv::Mat_<uint8_t>(info_.height,info_.width,UNKNOWN);
            log_odds_ = cv::Mat_<float>(info_.height,info_.width,0.0f);
            observed_ = cv::Mat_<uint8_t>(info_.height,info_.width,uint8_t(0));

            RCLCPP_INFO(this->get_logger(),"Mapping %dx%d cells of %.2fm in frame %s, max slope %.1f deg",
                    info_.width,info_.height,resolution_,map_frame_.c_str(),max_slope_*180./M_PI);

            tf_buffer = std::make_unique<tf2_ros::Buffer>(this->get_clock());
            tf_listener = std::make_shared<tf2_ros::TransformListener>(*tf_buffer);

            auto qos = rclcpp::QoS(rclcpp::KeepLast(3)).best_effort().durability_volatile();
            scan_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>("~/scans",qos,
                    std::bind(&FloorPlaneMapping::pointCloudCallback,this,std::placeholders::_1));
            auto latched = rclcpp::QoS(rclcpp::KeepLast(1)).transient_local();
            labels_pub_ = this->create_publisher<nav_msgs::msg::OccupancyGrid>("~/labels",latched);
            proba_pub_ = this->create_publisher<nav_msgs::msg::OccupancyGrid>("~/probability",latched);
            trav_pub_ = this->create_publisher<nav_msgs::msg::OccupancyGrid>("~/traversability",latched);
            timer_ = this->create_wall_timer(std::chrono::duration<double>(this->get_parameter("~/publish_period").as_double()),
                    std::bind(&FloorPlaneMapping::timerCallback,this));
        }

        ~FloorPlaneMapping() {
            if (save_prefix_.empty()) {
                return;
            }
            cv::Mat_<uint8_t> proba, trav;
            computeBayesMaps(proba,trav);
            cv::imwrite(save_prefix_ + "_labels.png",toImage(labels_));
            cv::imwrite(save_prefix_ + "_probability.png",toImage(proba));
            cv::imwrite(save_prefix_ + "_traversability.png",toImage(trav));
        }
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<FloorPlaneMapping>());
    rclcpp::shutdown();
    return 0;
}
