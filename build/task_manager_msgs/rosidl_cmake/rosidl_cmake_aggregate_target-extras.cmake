# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target task_manager_msgs::task_manager_msgs
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${task_manager_msgs_TARGETS}.
if(task_manager_msgs_TARGETS AND NOT TARGET task_manager_msgs::task_manager_msgs)
  add_library(task_manager_msgs::task_manager_msgs INTERFACE IMPORTED)
  set_target_properties(task_manager_msgs::task_manager_msgs PROPERTIES
    INTERFACE_LINK_LIBRARIES "${task_manager_msgs_TARGETS}")
endif()
