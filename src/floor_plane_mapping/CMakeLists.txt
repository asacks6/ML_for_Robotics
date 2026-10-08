cmake_minimum_required(VERSION 3.8)
project(floor_plane_mapping)
cmake_policy(SET CMP0074 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0144 NEW)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -O3)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_sensor_msgs REQUIRED)
find_package(pcl_conversions REQUIRED)
find_package(PCL REQUIRED QUIET COMPONENTS common io)
find_package(OpenCV REQUIRED)
include_directories(${PCL_COMMON_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS})

add_executable(floor_plane_mapping src/floor_plane_mapping.cpp)
target_compile_features(floor_plane_mapping PUBLIC c_std_99 cxx_std_17)
target_link_libraries(floor_plane_mapping PUBLIC
    ${geometry_msgs_TARGETS}
    ${sensor_msgs_TARGETS}
    ${nav_msgs_TARGETS}
    ${std_msgs_TARGETS}
    rclcpp::rclcpp
    pcl_conversions::pcl_conversions
    tf2_ros::tf2_ros
    tf2_sensor_msgs::tf2_sensor_msgs
    ${PCL_LIBRARIES}
    ${OpenCV_LIBRARIES}
)

install(TARGETS floor_plane_mapping
  DESTINATION lib/${PROJECT_NAME})

install(
  DIRECTORY launch/
  DESTINATION share/${PROJECT_NAME}
)

install(
  DIRECTORY rviz
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
