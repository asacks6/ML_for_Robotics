// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from task_manager_msgs:srv/StartTask.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "task_manager_msgs/srv/start_task.h"


#ifndef TASK_MANAGER_MSGS__SRV__DETAIL__START_TASK__STRUCT_H_
#define TASK_MANAGER_MSGS__SRV__DETAIL__START_TASK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'name'
#include "rosidl_runtime_c/string.h"
// Member 'config'
#include "rcl_interfaces/msg/detail/parameter__struct.h"

/// Struct defined in srv/StartTask in the package task_manager_msgs.
typedef struct task_manager_msgs__srv__StartTask_Request
{
  rosidl_runtime_c__String name;
  rcl_interfaces__msg__Parameter__Sequence config;
} task_manager_msgs__srv__StartTask_Request;

// Struct for a sequence of task_manager_msgs__srv__StartTask_Request.
typedef struct task_manager_msgs__srv__StartTask_Request__Sequence
{
  task_manager_msgs__srv__StartTask_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} task_manager_msgs__srv__StartTask_Request__Sequence;

// Constants defined in the message

/// Struct defined in srv/StartTask in the package task_manager_msgs.
typedef struct task_manager_msgs__srv__StartTask_Response
{
  int32_t id;
} task_manager_msgs__srv__StartTask_Response;

// Struct for a sequence of task_manager_msgs__srv__StartTask_Response.
typedef struct task_manager_msgs__srv__StartTask_Response__Sequence
{
  task_manager_msgs__srv__StartTask_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} task_manager_msgs__srv__StartTask_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  task_manager_msgs__srv__StartTask_Event__request__MAX_SIZE = 1
};
// response
enum
{
  task_manager_msgs__srv__StartTask_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/StartTask in the package task_manager_msgs.
typedef struct task_manager_msgs__srv__StartTask_Event
{
  service_msgs__msg__ServiceEventInfo info;
  task_manager_msgs__srv__StartTask_Request__Sequence request;
  task_manager_msgs__srv__StartTask_Response__Sequence response;
} task_manager_msgs__srv__StartTask_Event;

// Struct for a sequence of task_manager_msgs__srv__StartTask_Event.
typedef struct task_manager_msgs__srv__StartTask_Event__Sequence
{
  task_manager_msgs__srv__StartTask_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} task_manager_msgs__srv__StartTask_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TASK_MANAGER_MSGS__SRV__DETAIL__START_TASK__STRUCT_H_
