// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from task_manager_msgs:srv/GetTaskList.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "task_manager_msgs/srv/get_task_list.h"


#ifndef TASK_MANAGER_MSGS__SRV__DETAIL__GET_TASK_LIST__FUNCTIONS_H_
#define TASK_MANAGER_MSGS__SRV__DETAIL__GET_TASK_LIST__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/action_type_support_struct.h"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_runtime_c/type_description/type_description__struct.h"
#include "rosidl_runtime_c/type_description/type_source__struct.h"
#include "rosidl_runtime_c/type_hash.h"
#include "rosidl_runtime_c/visibility_control.h"
#include "task_manager_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "task_manager_msgs/srv/detail/get_task_list__struct.h"

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_type_hash_t *
task_manager_msgs__srv__GetTaskList__get_type_hash(
  const rosidl_service_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_runtime_c__type_description__TypeDescription *
task_manager_msgs__srv__GetTaskList__get_type_description(
  const rosidl_service_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_runtime_c__type_description__TypeSource *
task_manager_msgs__srv__GetTaskList__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_runtime_c__type_description__TypeSource__Sequence *
task_manager_msgs__srv__GetTaskList__get_type_description_sources(
  const rosidl_service_type_support_t * type_support);

/// Initialize srv/GetTaskList message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * task_manager_msgs__srv__GetTaskList_Request
 * )) before or use
 * task_manager_msgs__srv__GetTaskList_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
bool
task_manager_msgs__srv__GetTaskList_Request__init(task_manager_msgs__srv__GetTaskList_Request * msg);

/// Finalize srv/GetTaskList message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
void
task_manager_msgs__srv__GetTaskList_Request__fini(task_manager_msgs__srv__GetTaskList_Request * msg);

/// Create srv/GetTaskList message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * task_manager_msgs__srv__GetTaskList_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
task_manager_msgs__srv__GetTaskList_Request *
task_manager_msgs__srv__GetTaskList_Request__create(void);

/// Destroy srv/GetTaskList message.
/**
 * It calls
 * task_manager_msgs__srv__GetTaskList_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
void
task_manager_msgs__srv__GetTaskList_Request__destroy(task_manager_msgs__srv__GetTaskList_Request * msg);

/// Check for srv/GetTaskList message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
bool
task_manager_msgs__srv__GetTaskList_Request__are_equal(const task_manager_msgs__srv__GetTaskList_Request * lhs, const task_manager_msgs__srv__GetTaskList_Request * rhs);

/// Copy a srv/GetTaskList message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
bool
task_manager_msgs__srv__GetTaskList_Request__copy(
  const task_manager_msgs__srv__GetTaskList_Request * input,
  task_manager_msgs__srv__GetTaskList_Request * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_type_hash_t *
task_manager_msgs__srv__GetTaskList_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_runtime_c__type_description__TypeDescription *
task_manager_msgs__srv__GetTaskList_Request__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_runtime_c__type_description__TypeSource *
task_manager_msgs__srv__GetTaskList_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_runtime_c__type_description__TypeSource__Sequence *
task_manager_msgs__srv__GetTaskList_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of srv/GetTaskList messages.
/**
 * It allocates the memory for the number of elements and calls
 * task_manager_msgs__srv__GetTaskList_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
bool
task_manager_msgs__srv__GetTaskList_Request__Sequence__init(task_manager_msgs__srv__GetTaskList_Request__Sequence * array, size_t size);

/// Finalize array of srv/GetTaskList messages.
/**
 * It calls
 * task_manager_msgs__srv__GetTaskList_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
void
task_manager_msgs__srv__GetTaskList_Request__Sequence__fini(task_manager_msgs__srv__GetTaskList_Request__Sequence * array);

/// Create array of srv/GetTaskList messages.
/**
 * It allocates the memory for the array and calls
 * task_manager_msgs__srv__GetTaskList_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
task_manager_msgs__srv__GetTaskList_Request__Sequence *
task_manager_msgs__srv__GetTaskList_Request__Sequence__create(size_t size);

/// Destroy array of srv/GetTaskList messages.
/**
 * It calls
 * task_manager_msgs__srv__GetTaskList_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
void
task_manager_msgs__srv__GetTaskList_Request__Sequence__destroy(task_manager_msgs__srv__GetTaskList_Request__Sequence * array);

/// Check for srv/GetTaskList message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
bool
task_manager_msgs__srv__GetTaskList_Request__Sequence__are_equal(const task_manager_msgs__srv__GetTaskList_Request__Sequence * lhs, const task_manager_msgs__srv__GetTaskList_Request__Sequence * rhs);

/// Copy an array of srv/GetTaskList messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
bool
task_manager_msgs__srv__GetTaskList_Request__Sequence__copy(
  const task_manager_msgs__srv__GetTaskList_Request__Sequence * input,
  task_manager_msgs__srv__GetTaskList_Request__Sequence * output);

/// Initialize srv/GetTaskList message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * task_manager_msgs__srv__GetTaskList_Response
 * )) before or use
 * task_manager_msgs__srv__GetTaskList_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
bool
task_manager_msgs__srv__GetTaskList_Response__init(task_manager_msgs__srv__GetTaskList_Response * msg);

/// Finalize srv/GetTaskList message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
void
task_manager_msgs__srv__GetTaskList_Response__fini(task_manager_msgs__srv__GetTaskList_Response * msg);

/// Create srv/GetTaskList message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * task_manager_msgs__srv__GetTaskList_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
task_manager_msgs__srv__GetTaskList_Response *
task_manager_msgs__srv__GetTaskList_Response__create(void);

/// Destroy srv/GetTaskList message.
/**
 * It calls
 * task_manager_msgs__srv__GetTaskList_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
void
task_manager_msgs__srv__GetTaskList_Response__destroy(task_manager_msgs__srv__GetTaskList_Response * msg);

/// Check for srv/GetTaskList message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
bool
task_manager_msgs__srv__GetTaskList_Response__are_equal(const task_manager_msgs__srv__GetTaskList_Response * lhs, const task_manager_msgs__srv__GetTaskList_Response * rhs);

/// Copy a srv/GetTaskList message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
bool
task_manager_msgs__srv__GetTaskList_Response__copy(
  const task_manager_msgs__srv__GetTaskList_Response * input,
  task_manager_msgs__srv__GetTaskList_Response * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_type_hash_t *
task_manager_msgs__srv__GetTaskList_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_runtime_c__type_description__TypeDescription *
task_manager_msgs__srv__GetTaskList_Response__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_runtime_c__type_description__TypeSource *
task_manager_msgs__srv__GetTaskList_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_runtime_c__type_description__TypeSource__Sequence *
task_manager_msgs__srv__GetTaskList_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of srv/GetTaskList messages.
/**
 * It allocates the memory for the number of elements and calls
 * task_manager_msgs__srv__GetTaskList_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
bool
task_manager_msgs__srv__GetTaskList_Response__Sequence__init(task_manager_msgs__srv__GetTaskList_Response__Sequence * array, size_t size);

/// Finalize array of srv/GetTaskList messages.
/**
 * It calls
 * task_manager_msgs__srv__GetTaskList_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
void
task_manager_msgs__srv__GetTaskList_Response__Sequence__fini(task_manager_msgs__srv__GetTaskList_Response__Sequence * array);

/// Create array of srv/GetTaskList messages.
/**
 * It allocates the memory for the array and calls
 * task_manager_msgs__srv__GetTaskList_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
task_manager_msgs__srv__GetTaskList_Response__Sequence *
task_manager_msgs__srv__GetTaskList_Response__Sequence__create(size_t size);

/// Destroy array of srv/GetTaskList messages.
/**
 * It calls
 * task_manager_msgs__srv__GetTaskList_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
void
task_manager_msgs__srv__GetTaskList_Response__Sequence__destroy(task_manager_msgs__srv__GetTaskList_Response__Sequence * array);

/// Check for srv/GetTaskList message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
bool
task_manager_msgs__srv__GetTaskList_Response__Sequence__are_equal(const task_manager_msgs__srv__GetTaskList_Response__Sequence * lhs, const task_manager_msgs__srv__GetTaskList_Response__Sequence * rhs);

/// Copy an array of srv/GetTaskList messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
bool
task_manager_msgs__srv__GetTaskList_Response__Sequence__copy(
  const task_manager_msgs__srv__GetTaskList_Response__Sequence * input,
  task_manager_msgs__srv__GetTaskList_Response__Sequence * output);

/// Initialize srv/GetTaskList message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * task_manager_msgs__srv__GetTaskList_Event
 * )) before or use
 * task_manager_msgs__srv__GetTaskList_Event__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
bool
task_manager_msgs__srv__GetTaskList_Event__init(task_manager_msgs__srv__GetTaskList_Event * msg);

/// Finalize srv/GetTaskList message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
void
task_manager_msgs__srv__GetTaskList_Event__fini(task_manager_msgs__srv__GetTaskList_Event * msg);

/// Create srv/GetTaskList message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * task_manager_msgs__srv__GetTaskList_Event__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
task_manager_msgs__srv__GetTaskList_Event *
task_manager_msgs__srv__GetTaskList_Event__create(void);

/// Destroy srv/GetTaskList message.
/**
 * It calls
 * task_manager_msgs__srv__GetTaskList_Event__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
void
task_manager_msgs__srv__GetTaskList_Event__destroy(task_manager_msgs__srv__GetTaskList_Event * msg);

/// Check for srv/GetTaskList message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
bool
task_manager_msgs__srv__GetTaskList_Event__are_equal(const task_manager_msgs__srv__GetTaskList_Event * lhs, const task_manager_msgs__srv__GetTaskList_Event * rhs);

/// Copy a srv/GetTaskList message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
bool
task_manager_msgs__srv__GetTaskList_Event__copy(
  const task_manager_msgs__srv__GetTaskList_Event * input,
  task_manager_msgs__srv__GetTaskList_Event * output);

/// Retrieve pointer to the hash of the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_type_hash_t *
task_manager_msgs__srv__GetTaskList_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_runtime_c__type_description__TypeDescription *
task_manager_msgs__srv__GetTaskList_Event__get_type_description(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the single raw source text that defined this type.
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_runtime_c__type_description__TypeSource *
task_manager_msgs__srv__GetTaskList_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support);

/// Retrieve pointer to the recursive raw sources that defined the description of this type.
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_runtime_c__type_description__TypeSource__Sequence *
task_manager_msgs__srv__GetTaskList_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support);

/// Initialize array of srv/GetTaskList messages.
/**
 * It allocates the memory for the number of elements and calls
 * task_manager_msgs__srv__GetTaskList_Event__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
bool
task_manager_msgs__srv__GetTaskList_Event__Sequence__init(task_manager_msgs__srv__GetTaskList_Event__Sequence * array, size_t size);

/// Finalize array of srv/GetTaskList messages.
/**
 * It calls
 * task_manager_msgs__srv__GetTaskList_Event__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
void
task_manager_msgs__srv__GetTaskList_Event__Sequence__fini(task_manager_msgs__srv__GetTaskList_Event__Sequence * array);

/// Create array of srv/GetTaskList messages.
/**
 * It allocates the memory for the array and calls
 * task_manager_msgs__srv__GetTaskList_Event__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
task_manager_msgs__srv__GetTaskList_Event__Sequence *
task_manager_msgs__srv__GetTaskList_Event__Sequence__create(size_t size);

/// Destroy array of srv/GetTaskList messages.
/**
 * It calls
 * task_manager_msgs__srv__GetTaskList_Event__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
void
task_manager_msgs__srv__GetTaskList_Event__Sequence__destroy(task_manager_msgs__srv__GetTaskList_Event__Sequence * array);

/// Check for srv/GetTaskList message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
bool
task_manager_msgs__srv__GetTaskList_Event__Sequence__are_equal(const task_manager_msgs__srv__GetTaskList_Event__Sequence * lhs, const task_manager_msgs__srv__GetTaskList_Event__Sequence * rhs);

/// Copy an array of srv/GetTaskList messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
bool
task_manager_msgs__srv__GetTaskList_Event__Sequence__copy(
  const task_manager_msgs__srv__GetTaskList_Event__Sequence * input,
  task_manager_msgs__srv__GetTaskList_Event__Sequence * output);
#ifdef __cplusplus
}
#endif

#endif  // TASK_MANAGER_MSGS__SRV__DETAIL__GET_TASK_LIST__FUNCTIONS_H_
