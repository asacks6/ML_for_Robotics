#include <cstdio>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <pcl/point_types.h>
#include <pcl_conversions/pcl_conversions.h>
#include <visualization_msgs/msg/marker.hpp>
// #include <cs7630_msgs/msg/plane_description.hpp>
#include <tf2/utils.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <tf2_sensor_msgs/tf2_sensor_msgs.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>

#include <Eigen/Core>
#include <Eigen/Cholesky>

#include <chrono>  // Permite medir el tiempo de cálculo del solver

class FloorPlaneRegression: public rclcpp::Node {
    protected:
        rclcpp::Subscription<sensor_msgs::msg::PointCloud2>::SharedPtr scan_sub_;
        rclcpp::Publisher<visualization_msgs::msg::Marker>::SharedPtr marker_pub_;
        // rclcpp::Client<topic_tools::srv::MuxSelect>::SharedPtr muxClt;
        std::shared_ptr<tf2_ros::TransformListener> tf_listener{nullptr};
        std::unique_ptr<tf2_ros::Buffer> tf_buffer;


        std::string base_frame_;
        double max_range_;


    protected: // ROS Callbacks

        void pointCloudCallback(sensor_msgs::msg::PointCloud2::SharedPtr msg) {
            pcl::PointCloud<pcl::PointXYZ> pc_sensor, pc_baseframe;
            pcl::PCLPointCloud2 cloud2;
            pcl_conversions::toPCL(*msg,cloud2);    
            pcl::fromPCLPointCloud2(cloud2,pc_sensor);

            if (msg->header.frame_id != base_frame_) {
                geometry_msgs::msg::TransformStamped transformStamped;
                try {
                    std::string errStr;
                    // This converts target in the grid frame.
                    if (!tf_buffer->canTransform(base_frame_, msg->header.frame_id, msg->header.stamp,
                                rclcpp::Duration(std::chrono::duration<double>(1.0)),&errStr)) {
                        RCLCPP_ERROR(this->get_logger(),"Cannot transform target: %s",errStr.c_str());
                        return;
                    }
                    transformStamped = tf_buffer->lookupTransform(base_frame_, msg->header.frame_id, msg->header.stamp);
                    sensor_msgs::msg::PointCloud2 pc;
                    tf2::doTransform(*msg,pc,transformStamped);

                    // ROS2 Pointcloud2 to PCL Pointcloud2
                    pcl_conversions::toPCL(pc,cloud2);    
                } catch (const tf2::TransformException & ex){
                    RCLCPP_ERROR(this->get_logger(),"%s",ex.what());
                }
            } else {
                // ROS2 Pointcloud2 to PCL Pointcloud2
                pcl_conversions::toPCL(*msg,cloud2);    
            }
            // PCL Pointcloud2 to templated form
            pcl::fromPCLPointCloud2(cloud2,pc_baseframe);

            //
            unsigned int n = pc_sensor.size();
            std::vector<size_t> pidx;
            // First count the useful points
            for (unsigned int i=0;i<n;i++) {
                float x = pc_sensor[i].x;
                float y = pc_sensor[i].y;
                float d = hypot(x,y);
                if (d < 1e-2) {
                    // Bogus point, ignore
                    continue;
                }
                x = pc_baseframe[i].x;
                y = pc_baseframe[i].y;
                d = hypot(x,y);
                if (d > max_range_) {
                    // too far, ignore
                    continue;
                }
                pidx.push_back(i);
            }
            
            //
            //
            //
            // TODO START
            // 
            // Linear regression: z = a*x + b*y + c
            // Update the code below to use Eigen to find the parameters of the
            // linear regression above. 
            //
            // n is the number of useful point in the point cloud
            n = pidx.size();
            // Eigen is a matrix library. The line below create a 3x3 matrix A,
            // and a 3x1 vector B
            
            // Predecimos un plano ax + by + c = z  =>  AX = B. Entonces matriz A son los (xi yi 1), tiene tamano n x 3. B son los (zi), tiene tamano n x 1. X son los parametros (a, b, c), tiene tamano 3 x 1. 
             
            Eigen::MatrixXf A(n,3);
            Eigen::MatrixXf B(n,1);
            
            for (unsigned int i=0;i<n;i++) {
                // Assign x,y,z to the coordinates of the point we are
                // considering.
                double x = pc_baseframe[pidx[i]].x;
                double y = pc_baseframe[pidx[i]].y;
                double z = pc_baseframe[pidx[i]].z;

                // Cada fila representa la ecuación z_i = a*x_i + b*y_i + c de un punto i
                A(i,0) = x;
                A(i,1) = y;
                A(i,2) = 1.0;
                
                B(i,0) = z;
            }
            
            
            // Medimos solo el tiempo que tarda Eigen en resolver la regresión
			auto start = std::chrono::steady_clock::now();

            // Lo siguiente resuelve el problema de mínimos cuadrados sin calcular explícitamente la inversa. No calculamos la inversa pq puede no ser cuadrada. Por eso ponemos AT*A a ambos lados (que si es cuadrada) y Eigen lo resuelve  para encontrar los minimos cuadrados. No calcula necesariamente la inversa de AT*A ya que cuesta mas y no es necesario para encontrar X. 
            //La exppresion quiere decir resuelve AT*A*X=AT*B
            
            Eigen::MatrixXf X = (A.transpose() * A).ldlt().solve(A.transpose() * B);
            
            
            auto end = std::chrono::steady_clock::now();
            // Convertimos el tiempo transcurrido a milisegundos para comparar con CERES
			double time_ms =
				std::chrono::duration<double, std::milli>(end - start).count();

			RCLCPP_INFO(this->get_logger(),
						"Eigen computation time: %.3f ms", time_ms);
            
            // Details on linear solver can be found on 
            // http://eigen.tuxfamily.org/dox-devel/group__TutorialLinearAlgebra.html
            
            // Assuming the result is computed in vector X
            RCLCPP_INFO(this->get_logger(),"Extracted floor plane: z = %.2fx + %.2fy + %.2f",
                    X(0),X(1),X(2));

            // ---------------------------------------------------------------
            // Modelo cubico: z = a*x^3 + b*x^2*y + c*x*y^2 + d*y^3
            //                  + e*x^2 + f*x*y + g*y^2 + h
            //
            // No hay terminos lineales en x ni en y, de modo que el gradiente
            // (dz/dx, dz/dy) se anula en el origen: la normal de la superficie
            // en el origen del frame de bubbleRob es vertical, tal y como pide
            // el enunciado.
            //
            // Usamos matrices nuevas (Ac, Bc, Xc) para no tocar A, B y X, que
            // siguen describiendo el plano usado para dibujar el disco morado.
            // Este modelo no se dibuja en rviz.
            //
            // Ac es n x 8 (una fila por punto, una columna por monomio),
            // Bc es n x 1 (las z medidas) y Xc es 8 x 1 (los parametros).
            Eigen::MatrixXf Ac(n,8);
            Eigen::MatrixXf Bc(n,1);

            for (unsigned int i=0;i<n;i++) {
                double x = pc_baseframe[pidx[i]].x;
                double y = pc_baseframe[pidx[i]].y;
                double z = pc_baseframe[pidx[i]].z;

                Ac(i,0) = x*x*x;    // a
                Ac(i,1) = x*x*y;    // b
                Ac(i,2) = x*y*y;    // c
                Ac(i,3) = y*y*y;    // d
                Ac(i,4) = x*x;      // e
                Ac(i,5) = x*y;      // f
                Ac(i,6) = y*y;      // g
                Ac(i,7) = 1.0;      // h

                Bc(i,0) = z;
            }

            // Hacen falta al menos 8 puntos para que Ac^T*Ac no sea singular.
            if (n < 8) {
                RCLCPP_WARN(this->get_logger(),
                        "Not enough points (%u) to fit the cubic surface, skipping it",n);
                // Sin el modelo cubico solo publicamos el plano de siempre.
            } else {
                // Mismo esquema que antes: resolvemos Ac^T*Ac*Xc = Ac^T*Bc
                auto start_cubic = std::chrono::steady_clock::now();

                Eigen::MatrixXf Xc = (Ac.transpose() * Ac).ldlt().solve(Ac.transpose() * Bc);

                auto end_cubic = std::chrono::steady_clock::now();
                double time_cubic_ms =
                    std::chrono::duration<double, std::milli>(end_cubic - start_cubic).count();

                RCLCPP_INFO(this->get_logger(),
                        "Eigen computation time (cubic): %.3f ms", time_cubic_ms);

                RCLCPP_INFO(this->get_logger(),
                        "Extracted floor surface: z = %.3fx^3 + %.3fx^2y + %.3fxy^2 + %.3fy^3 "
                        "+ %.3fx^2 + %.3fxy + %.3fy^2 + %.3f",
                        Xc(0),Xc(1),Xc(2),Xc(3),Xc(4),Xc(5),Xc(6),Xc(7));

                // Vector de parametros completo, tal y como lo imprime Eigen
                RCLCPP_INFO_STREAM(this->get_logger(), "Cubic parameters Xc:\n" << Xc.transpose());

                // Error medio en z de cada modelo: media de los residuos
                // (A*X - B), es decir de (z_estimada - z_medida).
                // Es un error con signo, asi que los residuos positivos y
                // negativos se compensan entre si; anadimos tambien la media de
                // los valores absolutos, que es mas informativa para comparar.
                double mean_err_plane = (A * X - B).sum() / n;
                double mean_err_cubic = (Ac * Xc - Bc).sum() / n;
                double mean_abs_err_plane = (A * X - B).cwiseAbs().sum() / n;
                double mean_abs_err_cubic = (Ac * Xc - Bc).cwiseAbs().sum() / n;

                RCLCPP_INFO(this->get_logger(),
                        "Average z error over %u points: plane %.5f (abs %.5f) | cubic %.5f (abs %.5f)",
                        n, mean_err_plane, mean_abs_err_plane, mean_err_cubic, mean_abs_err_cubic);
            }

            // END OF TODO

            // Now build an orientation vector to display a marker in rviz
            // First we build a basis of the plane normal to its normal vector
            Eigen::Vector3f O,u,v,w;
            w << X(0), X(1), -1.0;
            w /= w.norm();
            O << 1.0, 0.0, 1.0*X(0)+0.0*X(1)+X(2);
            u << 2.0, 0.0, 2.0*X(0)+0.0*X(1)+X(2);
            u -= O;
            u /= u.norm();
            v = w.cross(u);

            // Then we build a rotation matrix out of it
            tf2::Matrix3x3 R(u(0),v(0),w(0),
                    u(1),v(1),w(1),
                    u(2),v(2),w(2));
            // And convert it to a quaternion
            tf2::Quaternion Q;
            R.getRotation(Q);
            
            // Documentation on visualization markers can be found on:
            // http://www.ros.org/wiki/rviz/DisplayTypes/Marker
            visualization_msgs::msg::Marker m;
            m.header.stamp = msg->header.stamp;
            m.header.frame_id = base_frame_;
            m.ns = "floor_plane";
            m.id = 1;
            m.type = visualization_msgs::msg::Marker::CYLINDER;
            m.action = visualization_msgs::msg::Marker::ADD;
            m.pose.position.x = O(0);
            m.pose.position.y = O(1);
            m.pose.position.z = O(2);
            m.pose.orientation = tf2::toMsg(Q);
            m.scale.x = 1.0;
            m.scale.y = 1.0;
            m.scale.z = 0.01;
            m.color.a = 0.5;
            m.color.r = 1.0;
            m.color.g = 0.0;
            m.color.b = 1.0;

            // Finally publish the marker
            marker_pub_->publish(m);
            
        }

    public:
        FloorPlaneRegression() : rclcpp::Node("floor_plane_regression") {
            // TODO START
            // The parameter below described the frame in which the point cloud
            // must be projected to be estimated. You need to understand TF
            // enough to find the correct value to update in the launch file
            
            this->declare_parameter("~/base_frame",std::string("body"));
            base_frame_ = this->get_parameter("~/base_frame").as_string();
            
            // This parameter defines the maximum range at which we want to
            // consider points. Experiment with the value in the launch file to
            // find something relevant.
            
            this->declare_parameter("~/max_range",5.0);
            max_range_ = this->get_parameter("~/max_range").as_double();
            
            // END OF TODO


            tf_buffer = std::make_unique<tf2_ros::Buffer>(this->get_clock());
            tf_listener = std::make_shared<tf2_ros::TransformListener>(*tf_buffer);

            // Subscribe to the point cloud and prepare the marker publisher
            auto qos = rclcpp::QoS(rclcpp::KeepLast(3)).best_effort().durability_volatile();
            scan_sub_ = this->create_subscription<sensor_msgs::msg::PointCloud2>("~/scans",qos,
                    std::bind(&FloorPlaneRegression::pointCloudCallback,this,std::placeholders::_1));
            marker_pub_ = this->create_publisher<visualization_msgs::msg::Marker>("~/floor_plane",1);

        }

};

int main(int argc, char * argv[]) 
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<FloorPlaneRegression>());
    rclcpp::shutdown();
    return 0;
}


