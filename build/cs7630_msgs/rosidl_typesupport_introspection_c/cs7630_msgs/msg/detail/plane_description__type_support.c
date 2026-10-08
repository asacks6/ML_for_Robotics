// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from cs7630_msgs:msg/PlaneDescription.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "cs7630_msgs/msg/detail/plane_description__rosidl_typesupport_introspection_c.h"
#include "cs7630_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "cs7630_msgs/msg/detail/plane_description__functions.h"
#include "cs7630_msgs/msg/detail/plane_description__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void cs7630_msgs__msg__PlaneDescription__rosidl_typesupport_introspection_c__PlaneDescription_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cs7630_msgs__msg__PlaneDescription__init(message_memory);
}

void cs7630_msgs__msg__PlaneDescription__rosidl_typesupport_introspection_c__PlaneDescription_fini_function(void * message_memory)
{
  cs7630_msgs__msg__PlaneDescription__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember cs7630_msgs__msg__PlaneDescription__rosidl_typesupport_introspection_c__PlaneDescription_message_member_array[5] = {
  {
    "a",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cs7630_msgs__msg__PlaneDescription, a),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "b",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cs7630_msgs__msg__PlaneDescription, b),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "c",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cs7630_msgs__msg__PlaneDescription, c),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "d",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cs7630_msgs__msg__PlaneDescription, d),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "fitness",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cs7630_msgs__msg__PlaneDescription, fitness),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cs7630_msgs__msg__PlaneDescription__rosidl_typesupport_introspection_c__PlaneDescription_message_members = {
  "cs7630_msgs__msg",  // message namespace
  "PlaneDescription",  // message name
  5,  // number of fields
  sizeof(cs7630_msgs__msg__PlaneDescription),
  false,  // has_any_key_member_
  cs7630_msgs__msg__PlaneDescription__rosidl_typesupport_introspection_c__PlaneDescription_message_member_array,  // message members
  cs7630_msgs__msg__PlaneDescription__rosidl_typesupport_introspection_c__PlaneDescription_init_function,  // function to initialize message memory (memory has to be allocated)
  cs7630_msgs__msg__PlaneDescription__rosidl_typesupport_introspection_c__PlaneDescription_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cs7630_msgs__msg__PlaneDescription__rosidl_typesupport_introspection_c__PlaneDescription_message_type_support_handle = {
  0,
  &cs7630_msgs__msg__PlaneDescription__rosidl_typesupport_introspection_c__PlaneDescription_message_members,
  get_message_typesupport_handle_function,
  &cs7630_msgs__msg__PlaneDescription__get_type_hash,
  &cs7630_msgs__msg__PlaneDescription__get_type_description,
  &cs7630_msgs__msg__PlaneDescription__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cs7630_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cs7630_msgs, msg, PlaneDescription)() {
  if (!cs7630_msgs__msg__PlaneDescription__rosidl_typesupport_introspection_c__PlaneDescription_message_type_support_handle.typesupport_identifier) {
    cs7630_msgs__msg__PlaneDescription__rosidl_typesupport_introspection_c__PlaneDescription_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cs7630_msgs__msg__PlaneDescription__rosidl_typesupport_introspection_c__PlaneDescription_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
