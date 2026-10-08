// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from cs7630_msgs:msg/PlaneDescription.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "cs7630_msgs/msg/detail/plane_description__functions.h"
#include "cs7630_msgs/msg/detail/plane_description__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace cs7630_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void PlaneDescription_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) cs7630_msgs::msg::PlaneDescription(_init);
}

void PlaneDescription_fini_function(void * message_memory)
{
  auto typed_message = static_cast<cs7630_msgs::msg::PlaneDescription *>(message_memory);
  typed_message->~PlaneDescription();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember PlaneDescription_message_member_array[5] = {
  {
    "a",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cs7630_msgs::msg::PlaneDescription, a),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "b",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cs7630_msgs::msg::PlaneDescription, b),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "c",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cs7630_msgs::msg::PlaneDescription, c),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "d",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cs7630_msgs::msg::PlaneDescription, d),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "fitness",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cs7630_msgs::msg::PlaneDescription, fitness),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers PlaneDescription_message_members = {
  "cs7630_msgs::msg",  // message namespace
  "PlaneDescription",  // message name
  5,  // number of fields
  sizeof(cs7630_msgs::msg::PlaneDescription),
  false,  // has_any_key_member_
  PlaneDescription_message_member_array,  // message members
  PlaneDescription_init_function,  // function to initialize message memory (memory has to be allocated)
  PlaneDescription_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t PlaneDescription_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &PlaneDescription_message_members,
  get_message_typesupport_handle_function,
  &cs7630_msgs__msg__PlaneDescription__get_type_hash,
  &cs7630_msgs__msg__PlaneDescription__get_type_description,
  &cs7630_msgs__msg__PlaneDescription__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace cs7630_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<cs7630_msgs::msg::PlaneDescription>()
{
  return &::cs7630_msgs::msg::rosidl_typesupport_introspection_cpp::PlaneDescription_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, cs7630_msgs, msg, PlaneDescription)() {
  return &::cs7630_msgs::msg::rosidl_typesupport_introspection_cpp::PlaneDescription_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
