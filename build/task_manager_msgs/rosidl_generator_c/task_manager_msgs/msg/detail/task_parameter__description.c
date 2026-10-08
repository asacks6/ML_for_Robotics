// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from task_manager_msgs:msg/TaskParameter.idl
// generated code does not contain a copyright notice

#include "task_manager_msgs/msg/detail/task_parameter__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_type_hash_t *
task_manager_msgs__msg__TaskParameter__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xeb, 0xf1, 0x93, 0xb2, 0xab, 0x56, 0x76, 0x11,
      0x3d, 0xec, 0x8c, 0x3c, 0xe2, 0xf1, 0x0b, 0xec,
      0x0c, 0x5a, 0x54, 0x3e, 0x18, 0x1c, 0x68, 0xa8,
      0x94, 0x7e, 0x3f, 0xe1, 0x1f, 0xa1, 0x89, 0x18,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char task_manager_msgs__msg__TaskParameter__TYPE_NAME[] = "task_manager_msgs/msg/TaskParameter";

// Define type names, field names, and default values
static char task_manager_msgs__msg__TaskParameter__FIELD_NAME__name[] = "name";
static char task_manager_msgs__msg__TaskParameter__FIELD_NAME__description[] = "description";
static char task_manager_msgs__msg__TaskParameter__FIELD_NAME__type[] = "type";
static char task_manager_msgs__msg__TaskParameter__FIELD_NAME__min[] = "min";
static char task_manager_msgs__msg__TaskParameter__FIELD_NAME__max[] = "max";
static char task_manager_msgs__msg__TaskParameter__FIELD_NAME__dflt[] = "dflt";
static char task_manager_msgs__msg__TaskParameter__FIELD_NAME__value[] = "value";

static rosidl_runtime_c__type_description__Field task_manager_msgs__msg__TaskParameter__FIELDS[] = {
  {
    {task_manager_msgs__msg__TaskParameter__FIELD_NAME__name, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__msg__TaskParameter__FIELD_NAME__description, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__msg__TaskParameter__FIELD_NAME__type, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__msg__TaskParameter__FIELD_NAME__min, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__msg__TaskParameter__FIELD_NAME__max, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__msg__TaskParameter__FIELD_NAME__dflt, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__msg__TaskParameter__FIELD_NAME__value, 5, 5},
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
task_manager_msgs__msg__TaskParameter__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {task_manager_msgs__msg__TaskParameter__TYPE_NAME, 35, 35},
      {task_manager_msgs__msg__TaskParameter__FIELDS, 7, 7},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "string name\n"
  "string description\n"
  "string type\n"
  "string min\n"
  "string max\n"
  "string dflt\n"
  "string value\n"
  "\n"
  "";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
task_manager_msgs__msg__TaskParameter__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {task_manager_msgs__msg__TaskParameter__TYPE_NAME, 35, 35},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 92, 92},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
task_manager_msgs__msg__TaskParameter__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *task_manager_msgs__msg__TaskParameter__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
