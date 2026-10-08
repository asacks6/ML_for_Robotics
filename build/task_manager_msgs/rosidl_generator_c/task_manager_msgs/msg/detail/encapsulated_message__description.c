// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from task_manager_msgs:msg/EncapsulatedMessage.idl
// generated code does not contain a copyright notice

#include "task_manager_msgs/msg/detail/encapsulated_message__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_type_hash_t *
task_manager_msgs__msg__EncapsulatedMessage__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xa6, 0x3c, 0x44, 0xee, 0xef, 0x3c, 0x0c, 0x3f,
      0xde, 0xca, 0x10, 0xc5, 0x5b, 0x7f, 0xcc, 0xb1,
      0x8d, 0xb7, 0x1c, 0x9c, 0x72, 0x69, 0x30, 0x6c,
      0x0f, 0x87, 0x23, 0xe3, 0x9b, 0xee, 0x9d, 0x9e,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char task_manager_msgs__msg__EncapsulatedMessage__TYPE_NAME[] = "task_manager_msgs/msg/EncapsulatedMessage";

// Define type names, field names, and default values
static char task_manager_msgs__msg__EncapsulatedMessage__FIELD_NAME__type[] = "type";
static char task_manager_msgs__msg__EncapsulatedMessage__FIELD_NAME__md5sum[] = "md5sum";
static char task_manager_msgs__msg__EncapsulatedMessage__FIELD_NAME__data[] = "data";

static rosidl_runtime_c__type_description__Field task_manager_msgs__msg__EncapsulatedMessage__FIELDS[] = {
  {
    {task_manager_msgs__msg__EncapsulatedMessage__FIELD_NAME__type, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__msg__EncapsulatedMessage__FIELD_NAME__md5sum, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__msg__EncapsulatedMessage__FIELD_NAME__data, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
task_manager_msgs__msg__EncapsulatedMessage__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {task_manager_msgs__msg__EncapsulatedMessage__TYPE_NAME, 41, 41},
      {task_manager_msgs__msg__EncapsulatedMessage__FIELDS, 3, 3},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "string type\n"
  "string md5sum\n"
  "string data";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
task_manager_msgs__msg__EncapsulatedMessage__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {task_manager_msgs__msg__EncapsulatedMessage__TYPE_NAME, 41, 41},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 38, 38},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
task_manager_msgs__msg__EncapsulatedMessage__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *task_manager_msgs__msg__EncapsulatedMessage__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
