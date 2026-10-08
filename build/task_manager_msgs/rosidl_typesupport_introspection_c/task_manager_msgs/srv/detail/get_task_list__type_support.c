// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from task_manager_msgs:srv/GetTaskList.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "task_manager_msgs/srv/detail/get_task_list__rosidl_typesupport_introspection_c.h"
#include "task_manager_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "task_manager_msgs/srv/detail/get_task_list__functions.h"
#include "task_manager_msgs/srv/detail/get_task_list__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void task_manager_msgs__srv__GetTaskList_Request__rosidl_typesupport_introspection_c__GetTaskList_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  task_manager_msgs__srv__GetTaskList_Request__init(message_memory);
}

void task_manager_msgs__srv__GetTaskList_Request__rosidl_typesupport_introspection_c__GetTaskList_Request_fini_function(void * message_memory)
{
  task_manager_msgs__srv__GetTaskList_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember task_manager_msgs__srv__GetTaskList_Request__rosidl_typesupport_introspection_c__GetTaskList_Request_message_member_array[1] = {
  {
    "structure_needs_at_least_one_member",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(task_manager_msgs__srv__GetTaskList_Request, structure_needs_at_least_one_member),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers task_manager_msgs__srv__GetTaskList_Request__rosidl_typesupport_introspection_c__GetTaskList_Request_message_members = {
  "task_manager_msgs__srv",  // message namespace
  "GetTaskList_Request",  // message name
  1,  // number of fields
  sizeof(task_manager_msgs__srv__GetTaskList_Request),
  false,  // has_any_key_member_
  task_manager_msgs__srv__GetTaskList_Request__rosidl_typesupport_introspection_c__GetTaskList_Request_message_member_array,  // message members
  task_manager_msgs__srv__GetTaskList_Request__rosidl_typesupport_introspection_c__GetTaskList_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  task_manager_msgs__srv__GetTaskList_Request__rosidl_typesupport_introspection_c__GetTaskList_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t task_manager_msgs__srv__GetTaskList_Request__rosidl_typesupport_introspection_c__GetTaskList_Request_message_type_support_handle = {
  0,
  &task_manager_msgs__srv__GetTaskList_Request__rosidl_typesupport_introspection_c__GetTaskList_Request_message_members,
  get_message_typesupport_handle_function,
  &task_manager_msgs__srv__GetTaskList_Request__get_type_hash,
  &task_manager_msgs__srv__GetTaskList_Request__get_type_description,
  &task_manager_msgs__srv__GetTaskList_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_task_manager_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, task_manager_msgs, srv, GetTaskList_Request)() {
  if (!task_manager_msgs__srv__GetTaskList_Request__rosidl_typesupport_introspection_c__GetTaskList_Request_message_type_support_handle.typesupport_identifier) {
    task_manager_msgs__srv__GetTaskList_Request__rosidl_typesupport_introspection_c__GetTaskList_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &task_manager_msgs__srv__GetTaskList_Request__rosidl_typesupport_introspection_c__GetTaskList_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "task_manager_msgs/srv/detail/get_task_list__rosidl_typesupport_introspection_c.h"
// already included above
// #include "task_manager_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "task_manager_msgs/srv/detail/get_task_list__functions.h"
// already included above
// #include "task_manager_msgs/srv/detail/get_task_list__struct.h"


// Include directives for member types
// Member `tlist`
#include "task_manager_msgs/msg/task_description.h"
// Member `tlist`
#include "task_manager_msgs/msg/detail/task_description__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__GetTaskList_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  task_manager_msgs__srv__GetTaskList_Response__init(message_memory);
}

void task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__GetTaskList_Response_fini_function(void * message_memory)
{
  task_manager_msgs__srv__GetTaskList_Response__fini(message_memory);
}

size_t task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__size_function__GetTaskList_Response__tlist(
  const void * untyped_member)
{
  const task_manager_msgs__msg__TaskDescription__Sequence * member =
    (const task_manager_msgs__msg__TaskDescription__Sequence *)(untyped_member);
  return member->size;
}

const void * task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__get_const_function__GetTaskList_Response__tlist(
  const void * untyped_member, size_t index)
{
  const task_manager_msgs__msg__TaskDescription__Sequence * member =
    (const task_manager_msgs__msg__TaskDescription__Sequence *)(untyped_member);
  return &member->data[index];
}

void * task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__get_function__GetTaskList_Response__tlist(
  void * untyped_member, size_t index)
{
  task_manager_msgs__msg__TaskDescription__Sequence * member =
    (task_manager_msgs__msg__TaskDescription__Sequence *)(untyped_member);
  return &member->data[index];
}

void task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__fetch_function__GetTaskList_Response__tlist(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const task_manager_msgs__msg__TaskDescription * item =
    ((const task_manager_msgs__msg__TaskDescription *)
    task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__get_const_function__GetTaskList_Response__tlist(untyped_member, index));
  task_manager_msgs__msg__TaskDescription * value =
    (task_manager_msgs__msg__TaskDescription *)(untyped_value);
  *value = *item;
}

void task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__assign_function__GetTaskList_Response__tlist(
  void * untyped_member, size_t index, const void * untyped_value)
{
  task_manager_msgs__msg__TaskDescription * item =
    ((task_manager_msgs__msg__TaskDescription *)
    task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__get_function__GetTaskList_Response__tlist(untyped_member, index));
  const task_manager_msgs__msg__TaskDescription * value =
    (const task_manager_msgs__msg__TaskDescription *)(untyped_value);
  *item = *value;
}

bool task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__resize_function__GetTaskList_Response__tlist(
  void * untyped_member, size_t size)
{
  task_manager_msgs__msg__TaskDescription__Sequence * member =
    (task_manager_msgs__msg__TaskDescription__Sequence *)(untyped_member);
  task_manager_msgs__msg__TaskDescription__Sequence__fini(member);
  return task_manager_msgs__msg__TaskDescription__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__GetTaskList_Response_message_member_array[1] = {
  {
    "tlist",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(task_manager_msgs__srv__GetTaskList_Response, tlist),  // bytes offset in struct
    NULL,  // default value
    task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__size_function__GetTaskList_Response__tlist,  // size() function pointer
    task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__get_const_function__GetTaskList_Response__tlist,  // get_const(index) function pointer
    task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__get_function__GetTaskList_Response__tlist,  // get(index) function pointer
    task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__fetch_function__GetTaskList_Response__tlist,  // fetch(index, &value) function pointer
    task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__assign_function__GetTaskList_Response__tlist,  // assign(index, value) function pointer
    task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__resize_function__GetTaskList_Response__tlist  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__GetTaskList_Response_message_members = {
  "task_manager_msgs__srv",  // message namespace
  "GetTaskList_Response",  // message name
  1,  // number of fields
  sizeof(task_manager_msgs__srv__GetTaskList_Response),
  false,  // has_any_key_member_
  task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__GetTaskList_Response_message_member_array,  // message members
  task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__GetTaskList_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__GetTaskList_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__GetTaskList_Response_message_type_support_handle = {
  0,
  &task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__GetTaskList_Response_message_members,
  get_message_typesupport_handle_function,
  &task_manager_msgs__srv__GetTaskList_Response__get_type_hash,
  &task_manager_msgs__srv__GetTaskList_Response__get_type_description,
  &task_manager_msgs__srv__GetTaskList_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_task_manager_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, task_manager_msgs, srv, GetTaskList_Response)() {
  task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__GetTaskList_Response_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, task_manager_msgs, msg, TaskDescription)();
  if (!task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__GetTaskList_Response_message_type_support_handle.typesupport_identifier) {
    task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__GetTaskList_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__GetTaskList_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "task_manager_msgs/srv/detail/get_task_list__rosidl_typesupport_introspection_c.h"
// already included above
// #include "task_manager_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "task_manager_msgs/srv/detail/get_task_list__functions.h"
// already included above
// #include "task_manager_msgs/srv/detail/get_task_list__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "task_manager_msgs/srv/get_task_list.h"
// Member `request`
// Member `response`
// already included above
// #include "task_manager_msgs/srv/detail/get_task_list__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__GetTaskList_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  task_manager_msgs__srv__GetTaskList_Event__init(message_memory);
}

void task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__GetTaskList_Event_fini_function(void * message_memory)
{
  task_manager_msgs__srv__GetTaskList_Event__fini(message_memory);
}

size_t task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__size_function__GetTaskList_Event__request(
  const void * untyped_member)
{
  const task_manager_msgs__srv__GetTaskList_Request__Sequence * member =
    (const task_manager_msgs__srv__GetTaskList_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__get_const_function__GetTaskList_Event__request(
  const void * untyped_member, size_t index)
{
  const task_manager_msgs__srv__GetTaskList_Request__Sequence * member =
    (const task_manager_msgs__srv__GetTaskList_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__get_function__GetTaskList_Event__request(
  void * untyped_member, size_t index)
{
  task_manager_msgs__srv__GetTaskList_Request__Sequence * member =
    (task_manager_msgs__srv__GetTaskList_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__fetch_function__GetTaskList_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const task_manager_msgs__srv__GetTaskList_Request * item =
    ((const task_manager_msgs__srv__GetTaskList_Request *)
    task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__get_const_function__GetTaskList_Event__request(untyped_member, index));
  task_manager_msgs__srv__GetTaskList_Request * value =
    (task_manager_msgs__srv__GetTaskList_Request *)(untyped_value);
  *value = *item;
}

void task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__assign_function__GetTaskList_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  task_manager_msgs__srv__GetTaskList_Request * item =
    ((task_manager_msgs__srv__GetTaskList_Request *)
    task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__get_function__GetTaskList_Event__request(untyped_member, index));
  const task_manager_msgs__srv__GetTaskList_Request * value =
    (const task_manager_msgs__srv__GetTaskList_Request *)(untyped_value);
  *item = *value;
}

bool task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__resize_function__GetTaskList_Event__request(
  void * untyped_member, size_t size)
{
  task_manager_msgs__srv__GetTaskList_Request__Sequence * member =
    (task_manager_msgs__srv__GetTaskList_Request__Sequence *)(untyped_member);
  task_manager_msgs__srv__GetTaskList_Request__Sequence__fini(member);
  return task_manager_msgs__srv__GetTaskList_Request__Sequence__init(member, size);
}

size_t task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__size_function__GetTaskList_Event__response(
  const void * untyped_member)
{
  const task_manager_msgs__srv__GetTaskList_Response__Sequence * member =
    (const task_manager_msgs__srv__GetTaskList_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__get_const_function__GetTaskList_Event__response(
  const void * untyped_member, size_t index)
{
  const task_manager_msgs__srv__GetTaskList_Response__Sequence * member =
    (const task_manager_msgs__srv__GetTaskList_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__get_function__GetTaskList_Event__response(
  void * untyped_member, size_t index)
{
  task_manager_msgs__srv__GetTaskList_Response__Sequence * member =
    (task_manager_msgs__srv__GetTaskList_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__fetch_function__GetTaskList_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const task_manager_msgs__srv__GetTaskList_Response * item =
    ((const task_manager_msgs__srv__GetTaskList_Response *)
    task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__get_const_function__GetTaskList_Event__response(untyped_member, index));
  task_manager_msgs__srv__GetTaskList_Response * value =
    (task_manager_msgs__srv__GetTaskList_Response *)(untyped_value);
  *value = *item;
}

void task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__assign_function__GetTaskList_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  task_manager_msgs__srv__GetTaskList_Response * item =
    ((task_manager_msgs__srv__GetTaskList_Response *)
    task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__get_function__GetTaskList_Event__response(untyped_member, index));
  const task_manager_msgs__srv__GetTaskList_Response * value =
    (const task_manager_msgs__srv__GetTaskList_Response *)(untyped_value);
  *item = *value;
}

bool task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__resize_function__GetTaskList_Event__response(
  void * untyped_member, size_t size)
{
  task_manager_msgs__srv__GetTaskList_Response__Sequence * member =
    (task_manager_msgs__srv__GetTaskList_Response__Sequence *)(untyped_member);
  task_manager_msgs__srv__GetTaskList_Response__Sequence__fini(member);
  return task_manager_msgs__srv__GetTaskList_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__GetTaskList_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(task_manager_msgs__srv__GetTaskList_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(task_manager_msgs__srv__GetTaskList_Event, request),  // bytes offset in struct
    NULL,  // default value
    task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__size_function__GetTaskList_Event__request,  // size() function pointer
    task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__get_const_function__GetTaskList_Event__request,  // get_const(index) function pointer
    task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__get_function__GetTaskList_Event__request,  // get(index) function pointer
    task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__fetch_function__GetTaskList_Event__request,  // fetch(index, &value) function pointer
    task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__assign_function__GetTaskList_Event__request,  // assign(index, value) function pointer
    task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__resize_function__GetTaskList_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(task_manager_msgs__srv__GetTaskList_Event, response),  // bytes offset in struct
    NULL,  // default value
    task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__size_function__GetTaskList_Event__response,  // size() function pointer
    task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__get_const_function__GetTaskList_Event__response,  // get_const(index) function pointer
    task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__get_function__GetTaskList_Event__response,  // get(index) function pointer
    task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__fetch_function__GetTaskList_Event__response,  // fetch(index, &value) function pointer
    task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__assign_function__GetTaskList_Event__response,  // assign(index, value) function pointer
    task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__resize_function__GetTaskList_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__GetTaskList_Event_message_members = {
  "task_manager_msgs__srv",  // message namespace
  "GetTaskList_Event",  // message name
  3,  // number of fields
  sizeof(task_manager_msgs__srv__GetTaskList_Event),
  false,  // has_any_key_member_
  task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__GetTaskList_Event_message_member_array,  // message members
  task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__GetTaskList_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__GetTaskList_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__GetTaskList_Event_message_type_support_handle = {
  0,
  &task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__GetTaskList_Event_message_members,
  get_message_typesupport_handle_function,
  &task_manager_msgs__srv__GetTaskList_Event__get_type_hash,
  &task_manager_msgs__srv__GetTaskList_Event__get_type_description,
  &task_manager_msgs__srv__GetTaskList_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_task_manager_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, task_manager_msgs, srv, GetTaskList_Event)() {
  task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__GetTaskList_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__GetTaskList_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, task_manager_msgs, srv, GetTaskList_Request)();
  task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__GetTaskList_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, task_manager_msgs, srv, GetTaskList_Response)();
  if (!task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__GetTaskList_Event_message_type_support_handle.typesupport_identifier) {
    task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__GetTaskList_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__GetTaskList_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "task_manager_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "task_manager_msgs/srv/detail/get_task_list__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers task_manager_msgs__srv__detail__get_task_list__rosidl_typesupport_introspection_c__GetTaskList_service_members = {
  "task_manager_msgs__srv",  // service namespace
  "GetTaskList",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // task_manager_msgs__srv__detail__get_task_list__rosidl_typesupport_introspection_c__GetTaskList_Request_message_type_support_handle,
  NULL,  // response message
  // task_manager_msgs__srv__detail__get_task_list__rosidl_typesupport_introspection_c__GetTaskList_Response_message_type_support_handle
  NULL  // event_message
  // task_manager_msgs__srv__detail__get_task_list__rosidl_typesupport_introspection_c__GetTaskList_Response_message_type_support_handle
};


static rosidl_service_type_support_t task_manager_msgs__srv__detail__get_task_list__rosidl_typesupport_introspection_c__GetTaskList_service_type_support_handle = {
  0,
  &task_manager_msgs__srv__detail__get_task_list__rosidl_typesupport_introspection_c__GetTaskList_service_members,
  get_service_typesupport_handle_function,
  &task_manager_msgs__srv__GetTaskList_Request__rosidl_typesupport_introspection_c__GetTaskList_Request_message_type_support_handle,
  &task_manager_msgs__srv__GetTaskList_Response__rosidl_typesupport_introspection_c__GetTaskList_Response_message_type_support_handle,
  &task_manager_msgs__srv__GetTaskList_Event__rosidl_typesupport_introspection_c__GetTaskList_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    task_manager_msgs,
    srv,
    GetTaskList
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    task_manager_msgs,
    srv,
    GetTaskList
  ),
  &task_manager_msgs__srv__GetTaskList__get_type_hash,
  &task_manager_msgs__srv__GetTaskList__get_type_description,
  &task_manager_msgs__srv__GetTaskList__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, task_manager_msgs, srv, GetTaskList_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, task_manager_msgs, srv, GetTaskList_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, task_manager_msgs, srv, GetTaskList_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_task_manager_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, task_manager_msgs, srv, GetTaskList)(void) {
  if (!task_manager_msgs__srv__detail__get_task_list__rosidl_typesupport_introspection_c__GetTaskList_service_type_support_handle.typesupport_identifier) {
    task_manager_msgs__srv__detail__get_task_list__rosidl_typesupport_introspection_c__GetTaskList_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)task_manager_msgs__srv__detail__get_task_list__rosidl_typesupport_introspection_c__GetTaskList_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, task_manager_msgs, srv, GetTaskList_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, task_manager_msgs, srv, GetTaskList_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, task_manager_msgs, srv, GetTaskList_Event)()->data;
  }

  return &task_manager_msgs__srv__detail__get_task_list__rosidl_typesupport_introspection_c__GetTaskList_service_type_support_handle;
}
