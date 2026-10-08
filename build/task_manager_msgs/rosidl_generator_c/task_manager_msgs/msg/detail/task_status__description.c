// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from task_manager_msgs:msg/TaskStatus.idl
// generated code does not contain a copyright notice

#include "task_manager_msgs/msg/detail/task_status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_type_hash_t *
task_manager_msgs__msg__TaskStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xce, 0x8e, 0x5b, 0x11, 0x56, 0x8a, 0x7b, 0x1d,
      0xf8, 0x58, 0x27, 0x2a, 0xc7, 0xa6, 0x01, 0xa9,
      0x7a, 0x83, 0x5f, 0x0d, 0x6e, 0x84, 0xce, 0xa7,
      0xaf, 0xd3, 0x4b, 0xad, 0x5e, 0x0f, 0x5d, 0x00,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "rcl_interfaces/msg/detail/parameter__functions.h"
#include "rcl_interfaces/msg/detail/parameter_value__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
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

static char task_manager_msgs__msg__TaskStatus__TYPE_NAME[] = "task_manager_msgs/msg/TaskStatus";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char rcl_interfaces__msg__Parameter__TYPE_NAME[] = "rcl_interfaces/msg/Parameter";
static char rcl_interfaces__msg__ParameterValue__TYPE_NAME[] = "rcl_interfaces/msg/ParameterValue";

// Define type names, field names, and default values
static char task_manager_msgs__msg__TaskStatus__FIELD_NAME__id[] = "id";
static char task_manager_msgs__msg__TaskStatus__FIELD_NAME__name[] = "name";
static char task_manager_msgs__msg__TaskStatus__FIELD_NAME__status[] = "status";
static char task_manager_msgs__msg__TaskStatus__FIELD_NAME__status_string[] = "status_string";
static char task_manager_msgs__msg__TaskStatus__FIELD_NAME__status_time[] = "status_time";
static char task_manager_msgs__msg__TaskStatus__FIELD_NAME__plist[] = "plist";

static rosidl_runtime_c__type_description__Field task_manager_msgs__msg__TaskStatus__FIELDS[] = {
  {
    {task_manager_msgs__msg__TaskStatus__FIELD_NAME__id, 2, 2},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__msg__TaskStatus__FIELD_NAME__name, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__msg__TaskStatus__FIELD_NAME__status, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__msg__TaskStatus__FIELD_NAME__status_string, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__msg__TaskStatus__FIELD_NAME__status_time, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    },
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__msg__TaskStatus__FIELD_NAME__plist, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE,
      0,
      0,
      {rcl_interfaces__msg__Parameter__TYPE_NAME, 28, 28},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription task_manager_msgs__msg__TaskStatus__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
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
task_manager_msgs__msg__TaskStatus__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {task_manager_msgs__msg__TaskStatus__TYPE_NAME, 32, 32},
      {task_manager_msgs__msg__TaskStatus__FIELDS, 6, 6},
    },
    {task_manager_msgs__msg__TaskStatus__REFERENCED_TYPE_DESCRIPTIONS, 3, 3},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&rcl_interfaces__msg__Parameter__EXPECTED_HASH, rcl_interfaces__msg__Parameter__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = rcl_interfaces__msg__Parameter__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&rcl_interfaces__msg__ParameterValue__EXPECTED_HASH, rcl_interfaces__msg__ParameterValue__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = rcl_interfaces__msg__ParameterValue__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "uint8 TASK_NEWBORN = 0 \n"
  "uint8 TASK_CONFIGURED = 1\n"
  "uint8 TASK_INITIALISED = 2\n"
  "uint8 TASK_RUNNING = 3\n"
  "uint8 TASK_COMPLETED = 4\n"
  "\n"
  "# To be used as a bit mask\n"
  "uint8 TASK_TERMINATED = 128\n"
  "\n"
  "uint8 TASK_INTERRUPTED = 6\n"
  "uint8 TASK_FAILED = 7\n"
  "uint8 TASK_TIMEOUT = 8\n"
  "uint8 TASK_CONFIGURATION_FAILED = 9\n"
  "uint8 TASK_INITIALISATION_FAILED = 10\n"
  "\n"
  "uint32 id\n"
  "string name\n"
  "uint8 status\n"
  "string status_string\n"
  "builtin_interfaces/Time status_time\n"
  "rcl_interfaces/Parameter[] plist";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
task_manager_msgs__msg__TaskStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {task_manager_msgs__msg__TaskStatus__TYPE_NAME, 32, 32},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 454, 454},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
task_manager_msgs__msg__TaskStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[4];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 4, 4};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *task_manager_msgs__msg__TaskStatus__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *rcl_interfaces__msg__Parameter__get_individual_type_description_source(NULL);
    sources[3] = *rcl_interfaces__msg__ParameterValue__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
