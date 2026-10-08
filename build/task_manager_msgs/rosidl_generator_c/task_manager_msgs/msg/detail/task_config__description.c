// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from task_manager_msgs:msg/TaskConfig.idl
// generated code does not contain a copyright notice

#include "task_manager_msgs/msg/detail/task_config__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_type_hash_t *
task_manager_msgs__msg__TaskConfig__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x6d, 0xde, 0x1c, 0xc4, 0x1b, 0x1b, 0xfb, 0x42,
      0x49, 0x23, 0x0b, 0xc0, 0xf2, 0x20, 0xb1, 0xef,
      0x7a, 0x13, 0xd2, 0xb8, 0xda, 0xaa, 0xad, 0x07,
      0x0a, 0x4d, 0x53, 0x18, 0x7e, 0x9d, 0xdc, 0x3c,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "rcl_interfaces/msg/detail/parameter__functions.h"
#include "rcl_interfaces/msg/detail/parameter_value__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t rcl_interfaces__msg__Parameter__EXPECTED_HASH = {1, {
    0xdd, 0xfe, 0x64, 0x42, 0xcf, 0xfc, 0x46, 0x23,
    0x17, 0xad, 0xb5, 0xc9, 0x25, 0x36, 0xa7, 0xb6,
    0xdd, 0x55, 0x85, 0x8c, 0x5c, 0x3e, 0x1e, 0x32,
    0x81, 0x65, 0xa6, 0xb7, 0x3c, 0x28, 0x31, 0xaf,
  }};
static const rosidl_type_hash_t rcl_interfaces__msg__ParameterValue__EXPECTED_HASH = {1, {
    0x11, 0x5f, 0xc0, 0x89, 0xa3, 0x87, 0xe2, 0x3c,
    0x7e, 0xcd, 0x35, 0x25, 0xc9, 0x18, 0x9c, 0x37,
    0x91, 0x09, 0x11, 0x9d, 0x6a, 0xb8, 0x2e, 0x8d,
    0xfb, 0xde, 0x0f, 0xdf, 0x6a, 0x7f, 0x9b, 0x68,
  }};
#endif

static char task_manager_msgs__msg__TaskConfig__TYPE_NAME[] = "task_manager_msgs/msg/TaskConfig";
static char rcl_interfaces__msg__Parameter__TYPE_NAME[] = "rcl_interfaces/msg/Parameter";
static char rcl_interfaces__msg__ParameterValue__TYPE_NAME[] = "rcl_interfaces/msg/ParameterValue";

// Define type names, field names, and default values
static char task_manager_msgs__msg__TaskConfig__FIELD_NAME__plist[] = "plist";

static rosidl_runtime_c__type_description__Field task_manager_msgs__msg__TaskConfig__FIELDS[] = {
  {
    {task_manager_msgs__msg__TaskConfig__FIELD_NAME__plist, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE,
      0,
      0,
      {rcl_interfaces__msg__Parameter__TYPE_NAME, 28, 28},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription task_manager_msgs__msg__TaskConfig__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {rcl_interfaces__msg__Parameter__TYPE_NAME, 28, 28},
    {NULL, 0, 0},
  },
  {
    {rcl_interfaces__msg__ParameterValue__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
task_manager_msgs__msg__TaskConfig__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {task_manager_msgs__msg__TaskConfig__TYPE_NAME, 32, 32},
      {task_manager_msgs__msg__TaskConfig__FIELDS, 1, 1},
    },
    {task_manager_msgs__msg__TaskConfig__REFERENCED_TYPE_DESCRIPTIONS, 2, 2},
  };
  if (!constructed) {
    assert(0 == memcmp(&rcl_interfaces__msg__Parameter__EXPECTED_HASH, rcl_interfaces__msg__Parameter__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = rcl_interfaces__msg__Parameter__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&rcl_interfaces__msg__ParameterValue__EXPECTED_HASH, rcl_interfaces__msg__ParameterValue__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = rcl_interfaces__msg__ParameterValue__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "rcl_interfaces/Parameter[] plist";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
task_manager_msgs__msg__TaskConfig__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {task_manager_msgs__msg__TaskConfig__TYPE_NAME, 32, 32},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 33, 33},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
task_manager_msgs__msg__TaskConfig__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[3];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 3, 3};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *task_manager_msgs__msg__TaskConfig__get_individual_type_description_source(NULL),
    sources[1] = *rcl_interfaces__msg__Parameter__get_individual_type_description_source(NULL);
    sources[2] = *rcl_interfaces__msg__ParameterValue__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
