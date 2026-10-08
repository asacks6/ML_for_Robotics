// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from cs7630_msgs:msg/PlaneDescription.idl
// generated code does not contain a copyright notice
#include "cs7630_msgs/msg/detail/plane_description__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "cs7630_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "cs7630_msgs/msg/detail/plane_description__struct.h"
#include "cs7630_msgs/msg/detail/plane_description__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _PlaneDescription__ros_msg_type = cs7630_msgs__msg__PlaneDescription;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cs7630_msgs
bool cdr_serialize_cs7630_msgs__msg__PlaneDescription(
  const cs7630_msgs__msg__PlaneDescription * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: a
  {
    cdr << ros_message->a;
  }

  // Field name: b
  {
    cdr << ros_message->b;
  }

  // Field name: c
  {
    cdr << ros_message->c;
  }

  // Field name: d
  {
    cdr << ros_message->d;
  }

  // Field name: fitness
  {
    cdr << ros_message->fitness;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cs7630_msgs
bool cdr_deserialize_cs7630_msgs__msg__PlaneDescription(
  eprosima::fastcdr::Cdr & cdr,
  cs7630_msgs__msg__PlaneDescription * ros_message)
{
  // Field name: a
  {
    cdr >> ros_message->a;
  }

  // Field name: b
  {
    cdr >> ros_message->b;
  }

  // Field name: c
  {
    cdr >> ros_message->c;
  }

  // Field name: d
  {
    cdr >> ros_message->d;
  }

  // Field name: fitness
  {
    cdr >> ros_message->fitness;
  }

  return true;
}  // NOLINT(readability/fn_size)


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cs7630_msgs
size_t get_serialized_size_cs7630_msgs__msg__PlaneDescription(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _PlaneDescription__ros_msg_type * ros_message = static_cast<const _PlaneDescription__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: a
  {
    size_t item_size = sizeof(ros_message->a);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: b
  {
    size_t item_size = sizeof(ros_message->b);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: c
  {
    size_t item_size = sizeof(ros_message->c);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: d
  {
    size_t item_size = sizeof(ros_message->d);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: fitness
  {
    size_t item_size = sizeof(ros_message->fitness);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cs7630_msgs
size_t max_serialized_size_cs7630_msgs__msg__PlaneDescription(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Field name: a
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: b
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: c
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: d
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: fitness
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }


  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = cs7630_msgs__msg__PlaneDescription;
    is_plain =
      (
      offsetof(DataType, fitness) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cs7630_msgs
bool cdr_serialize_key_cs7630_msgs__msg__PlaneDescription(
  const cs7630_msgs__msg__PlaneDescription * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: a
  {
    cdr << ros_message->a;
  }

  // Field name: b
  {
    cdr << ros_message->b;
  }

  // Field name: c
  {
    cdr << ros_message->c;
  }

  // Field name: d
  {
    cdr << ros_message->d;
  }

  // Field name: fitness
  {
    cdr << ros_message->fitness;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cs7630_msgs
size_t get_serialized_size_key_cs7630_msgs__msg__PlaneDescription(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _PlaneDescription__ros_msg_type * ros_message = static_cast<const _PlaneDescription__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;

  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: a
  {
    size_t item_size = sizeof(ros_message->a);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: b
  {
    size_t item_size = sizeof(ros_message->b);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: c
  {
    size_t item_size = sizeof(ros_message->c);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: d
  {
    size_t item_size = sizeof(ros_message->d);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: fitness
  {
    size_t item_size = sizeof(ros_message->fitness);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cs7630_msgs
size_t max_serialized_size_key_cs7630_msgs__msg__PlaneDescription(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;
  // Field name: a
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: b
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: c
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: d
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: fitness
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = cs7630_msgs__msg__PlaneDescription;
    is_plain =
      (
      offsetof(DataType, fitness) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _PlaneDescription__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const cs7630_msgs__msg__PlaneDescription * ros_message = static_cast<const cs7630_msgs__msg__PlaneDescription *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_cs7630_msgs__msg__PlaneDescription(ros_message, cdr);
}

static bool _PlaneDescription__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  cs7630_msgs__msg__PlaneDescription * ros_message = static_cast<cs7630_msgs__msg__PlaneDescription *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_cs7630_msgs__msg__PlaneDescription(cdr, ros_message);
}

static uint32_t _PlaneDescription__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_cs7630_msgs__msg__PlaneDescription(
      untyped_ros_message, 0));
}

static size_t _PlaneDescription__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_cs7630_msgs__msg__PlaneDescription(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_PlaneDescription = {
  "cs7630_msgs::msg",
  "PlaneDescription",
  _PlaneDescription__cdr_serialize,
  _PlaneDescription__cdr_deserialize,
  _PlaneDescription__get_serialized_size,
  _PlaneDescription__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _PlaneDescription__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_PlaneDescription,
  get_message_typesupport_handle_function,
  &cs7630_msgs__msg__PlaneDescription__get_type_hash,
  &cs7630_msgs__msg__PlaneDescription__get_type_description,
  &cs7630_msgs__msg__PlaneDescription__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cs7630_msgs, msg, PlaneDescription)() {
  return &_PlaneDescription__type_support;
}

#if defined(__cplusplus)
}
#endif
