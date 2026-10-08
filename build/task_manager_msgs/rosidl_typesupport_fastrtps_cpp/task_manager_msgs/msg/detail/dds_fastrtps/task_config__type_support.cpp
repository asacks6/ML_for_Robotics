// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from task_manager_msgs:msg/TaskConfig.idl
// generated code does not contain a copyright notice
#include "task_manager_msgs/msg/detail/task_config__rosidl_typesupport_fastrtps_cpp.hpp"
#include "task_manager_msgs/msg/detail/task_config__functions.h"
#include "task_manager_msgs/msg/detail/task_config__struct.hpp"

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions
namespace rcl_interfaces
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const rcl_interfaces::msg::Parameter &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  rcl_interfaces::msg::Parameter &);
size_t get_serialized_size(
  const rcl_interfaces::msg::Parameter &,
  size_t current_alignment);
size_t
max_serialized_size_Parameter(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
bool cdr_serialize_key(
  const rcl_interfaces::msg::Parameter &,
  eprosima::fastcdr::Cdr &);
size_t get_serialized_size_key(
  const rcl_interfaces::msg::Parameter &,
  size_t current_alignment);
size_t
max_serialized_size_key_Parameter(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace rcl_interfaces


namespace task_manager_msgs
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{


bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_task_manager_msgs
cdr_serialize(
  const task_manager_msgs::msg::TaskConfig & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: plist
  {
    size_t size = ros_message.plist.size();
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; i++) {
      rcl_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize(
        ros_message.plist[i],
        cdr);
    }
  }

  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_task_manager_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  task_manager_msgs::msg::TaskConfig & ros_message)
{
  // Member: plist
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);

    // Check there are at least 'size' remaining bytes in the CDR stream before resizing
    auto old_state = cdr.get_state();
    bool correct_size = cdr.jump(size);
    cdr.set_state(old_state);
    if (!correct_size) {
      fprintf(stderr, "sequence size exceeds remaining buffer\n");
      return false;
    }

    ros_message.plist.resize(size);
    for (size_t i = 0; i < size; i++) {
      rcl_interfaces::msg::typesupport_fastrtps_cpp::cdr_deserialize(
        cdr, ros_message.plist[i]);
    }
  }

  return true;
}  // NOLINT(readability/fn_size)


size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_task_manager_msgs
get_serialized_size(
  const task_manager_msgs::msg::TaskConfig & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: plist
  {
    size_t array_size = ros_message.plist.size();
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        rcl_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size(
        ros_message.plist[index], current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}


size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_task_manager_msgs
max_serialized_size_TaskConfig(
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

  // Member: plist
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        rcl_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_Parameter(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = task_manager_msgs::msg::TaskConfig;
    is_plain =
      (
      offsetof(DataType, plist) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_task_manager_msgs
cdr_serialize_key(
  const task_manager_msgs::msg::TaskConfig & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: plist
  {
    size_t size = ros_message.plist.size();
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; i++) {
      rcl_interfaces::msg::typesupport_fastrtps_cpp::cdr_serialize_key(
        ros_message.plist[i],
        cdr);
    }
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_task_manager_msgs
get_serialized_size_key(
  const task_manager_msgs::msg::TaskConfig & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: plist
  {
    size_t array_size = ros_message.plist.size();
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        rcl_interfaces::msg::typesupport_fastrtps_cpp::get_serialized_size_key(
        ros_message.plist[index], current_alignment);
    }
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_task_manager_msgs
max_serialized_size_key_TaskConfig(
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

  // Member: plist
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size =
        rcl_interfaces::msg::typesupport_fastrtps_cpp::max_serialized_size_key_Parameter(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = task_manager_msgs::msg::TaskConfig;
    is_plain =
      (
      offsetof(DataType, plist) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}


static bool _TaskConfig__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const task_manager_msgs::msg::TaskConfig *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _TaskConfig__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<task_manager_msgs::msg::TaskConfig *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _TaskConfig__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const task_manager_msgs::msg::TaskConfig *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _TaskConfig__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_TaskConfig(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _TaskConfig__callbacks = {
  "task_manager_msgs::msg",
  "TaskConfig",
  _TaskConfig__cdr_serialize,
  _TaskConfig__cdr_deserialize,
  _TaskConfig__get_serialized_size,
  _TaskConfig__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _TaskConfig__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_TaskConfig__callbacks,
  get_message_typesupport_handle_function,
  &task_manager_msgs__msg__TaskConfig__get_type_hash,
  &task_manager_msgs__msg__TaskConfig__get_type_description,
  &task_manager_msgs__msg__TaskConfig__get_type_description_sources,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace task_manager_msgs

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_task_manager_msgs
const rosidl_message_type_support_t *
get_message_type_support_handle<task_manager_msgs::msg::TaskConfig>()
{
  return &task_manager_msgs::msg::typesupport_fastrtps_cpp::_TaskConfig__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, task_manager_msgs, msg, TaskConfig)() {
  return &task_manager_msgs::msg::typesupport_fastrtps_cpp::_TaskConfig__handle;
}

#ifdef __cplusplus
}
#endif
