# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target cs7630_msgs::cs7630_msgs
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${cs7630_msgs_TARGETS}.
if(cs7630_msgs_TARGETS AND NOT TARGET cs7630_msgs::cs7630_msgs)
  add_library(cs7630_msgs::cs7630_msgs INTERFACE IMPORTED)
  set_target_properties(cs7630_msgs::cs7630_msgs PROPERTIES
    INTERFACE_LINK_LIBRARIES "${cs7630_msgs_TARGETS}")
endif()
