// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from task_manager_msgs:srv/GetTaskList.idl
// generated code does not contain a copyright notice

#include "task_manager_msgs/srv/detail/get_task_list__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_type_hash_t *
task_manager_msgs__srv__GetTaskList__get_type_hash(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x86, 0x41, 0x3f, 0xeb, 0x72, 0x4e, 0x12, 0xb8,
      0xa9, 0x54, 0x1a, 0x82, 0x06, 0x81, 0xc8, 0xb3,
      0x1f, 0x3d, 0x15, 0x26, 0xf6, 0xb1, 0xc5, 0xc9,
      0xec, 0xe8, 0x9a, 0xd3, 0xca, 0x09, 0x90, 0x14,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_type_hash_t *
task_manager_msgs__srv__GetTaskList_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x43, 0xf9, 0x7c, 0x68, 0x82, 0xce, 0x9a, 0x43,
      0xbd, 0x5f, 0x22, 0xa7, 0xcf, 0xc9, 0x11, 0x1b,
      0x3c, 0xf3, 0xe8, 0x50, 0xad, 0xe5, 0x90, 0x78,
      0x88, 0x6f, 0x0c, 0x34, 0xa4, 0xf1, 0x44, 0xca,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_type_hash_t *
task_manager_msgs__srv__GetTaskList_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x78, 0xdc, 0xfc, 0x50, 0xfc, 0x85, 0x83, 0x12,
      0x1a, 0x3e, 0x94, 0x02, 0xeb, 0x01, 0x60, 0xc6,
      0x94, 0xa7, 0x66, 0x37, 0x4b, 0x80, 0x19, 0xd4,
      0xac, 0xa8, 0xe0, 0xed, 0xe4, 0xfb, 0xc3, 0xfa,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_type_hash_t *
task_manager_msgs__srv__GetTaskList_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x9d, 0xa4, 0xd0, 0xa6, 0x6a, 0x13, 0x18, 0xc0,
      0x28, 0xf3, 0x98, 0x7d, 0x35, 0x30, 0x13, 0xa3,
      0xbe, 0x6c, 0x64, 0xec, 0xad, 0x10, 0x08, 0x04,
      0xf1, 0x45, 0xf3, 0x5e, 0xd0, 0xf1, 0x48, 0x73,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "rcl_interfaces/msg/detail/floating_point_range__functions.h"
#include "rcl_interfaces/msg/detail/integer_range__functions.h"
#include "rcl_interfaces/msg/detail/parameter_descriptor__functions.h"
#include "service_msgs/msg/detail/service_event_info__functions.h"
#include "task_manager_msgs/msg/detail/task_description__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t rcl_interfaces__msg__FloatingPointRange__EXPECTED_HASH = {1, {
    0xe6, 0xaf, 0x23, 0xa2, 0x3c, 0x17, 0x7f, 0xee,
    0x5f, 0x30, 0x75, 0xc8, 0xb1, 0xe4, 0x35, 0x16,
    0x2a, 0x9b, 0x63, 0xc8, 0x63, 0xd7, 0x8c, 0x06,
    0x01, 0x74, 0x60, 0xb4, 0x96, 0x84, 0x26, 0x2d,
  }};
static const rosidl_type_hash_t rcl_interfaces__msg__IntegerRange__EXPECTED_HASH = {1, {
    0xf7, 0xb7, 0xfd, 0xc0, 0xf6, 0x5f, 0x07, 0x70,
    0x2e, 0x09, 0x92, 0x18, 0xe1, 0x32, 0x88, 0xc3,
    0x96, 0x3b, 0xcb, 0x93, 0x45, 0xbd, 0xe7, 0x8b,
    0x56, 0x0e, 0x6c, 0xd1, 0x98, 0x00, 0xfc, 0x5a,
  }};
static const rosidl_type_hash_t rcl_interfaces__msg__ParameterDescriptor__EXPECTED_HASH = {1, {
    0x52, 0x17, 0x5d, 0xbf, 0xda, 0x6c, 0x51, 0x15,
    0x31, 0x01, 0xd3, 0x3d, 0x2a, 0x9d, 0xa0, 0x57,
    0x43, 0xf6, 0x6f, 0x02, 0xd5, 0xab, 0x2c, 0xa9,
    0xec, 0x47, 0x09, 0xb4, 0x6b, 0x73, 0xd7, 0x04,
  }};
static const rosidl_type_hash_t service_msgs__msg__ServiceEventInfo__EXPECTED_HASH = {1, {
    0x41, 0xbc, 0xbb, 0xe0, 0x7a, 0x75, 0xc9, 0xb5,
    0x2b, 0xc9, 0x6b, 0xfd, 0x5c, 0x24, 0xd7, 0xf0,
    0xfc, 0x0a, 0x08, 0xc0, 0xcb, 0x79, 0x21, 0xb3,
    0x37, 0x3c, 0x57, 0x32, 0x34, 0x5a, 0x6f, 0x45,
  }};
static const rosidl_type_hash_t task_manager_msgs__msg__TaskDescription__EXPECTED_HASH = {1, {
    0xea, 0x48, 0x84, 0x29, 0x54, 0xcb, 0x2e, 0xed,
    0xe1, 0xed, 0x1e, 0xb6, 0x6a, 0xa7, 0xd3, 0xf7,
    0x78, 0xc9, 0x31, 0x16, 0xa8, 0x54, 0x4f, 0x85,
    0x4d, 0x1e, 0x16, 0x9c, 0xcd, 0xf1, 0x2a, 0x2d,
  }};
#endif

static char task_manager_msgs__srv__GetTaskList__TYPE_NAME[] = "task_manager_msgs/srv/GetTaskList";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char rcl_interfaces__msg__FloatingPointRange__TYPE_NAME[] = "rcl_interfaces/msg/FloatingPointRange";
static char rcl_interfaces__msg__IntegerRange__TYPE_NAME[] = "rcl_interfaces/msg/IntegerRange";
static char rcl_interfaces__msg__ParameterDescriptor__TYPE_NAME[] = "rcl_interfaces/msg/ParameterDescriptor";
static char service_msgs__msg__ServiceEventInfo__TYPE_NAME[] = "service_msgs/msg/ServiceEventInfo";
static char task_manager_msgs__msg__TaskDescription__TYPE_NAME[] = "task_manager_msgs/msg/TaskDescription";
static char task_manager_msgs__srv__GetTaskList_Event__TYPE_NAME[] = "task_manager_msgs/srv/GetTaskList_Event";
static char task_manager_msgs__srv__GetTaskList_Request__TYPE_NAME[] = "task_manager_msgs/srv/GetTaskList_Request";
static char task_manager_msgs__srv__GetTaskList_Response__TYPE_NAME[] = "task_manager_msgs/srv/GetTaskList_Response";

// Define type names, field names, and default values
static char task_manager_msgs__srv__GetTaskList__FIELD_NAME__request_message[] = "request_message";
static char task_manager_msgs__srv__GetTaskList__FIELD_NAME__response_message[] = "response_message";
static char task_manager_msgs__srv__GetTaskList__FIELD_NAME__event_message[] = "event_message";

static rosidl_runtime_c__type_description__Field task_manager_msgs__srv__GetTaskList__FIELDS[] = {
  {
    {task_manager_msgs__srv__GetTaskList__FIELD_NAME__request_message, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {task_manager_msgs__srv__GetTaskList_Request__TYPE_NAME, 41, 41},
    },
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__srv__GetTaskList__FIELD_NAME__response_message, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {task_manager_msgs__srv__GetTaskList_Response__TYPE_NAME, 42, 42},
    },
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__srv__GetTaskList__FIELD_NAME__event_message, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {task_manager_msgs__srv__GetTaskList_Event__TYPE_NAME, 39, 39},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription task_manager_msgs__srv__GetTaskList__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {rcl_interfaces__msg__FloatingPointRange__TYPE_NAME, 37, 37},
    {NULL, 0, 0},
  },
  {
    {rcl_interfaces__msg__IntegerRange__TYPE_NAME, 31, 31},
    {NULL, 0, 0},
  },
  {
    {rcl_interfaces__msg__ParameterDescriptor__TYPE_NAME, 38, 38},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__msg__TaskDescription__TYPE_NAME, 37, 37},
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__srv__GetTaskList_Event__TYPE_NAME, 39, 39},
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__srv__GetTaskList_Request__TYPE_NAME, 41, 41},
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__srv__GetTaskList_Response__TYPE_NAME, 42, 42},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
task_manager_msgs__srv__GetTaskList__get_type_description(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {task_manager_msgs__srv__GetTaskList__TYPE_NAME, 33, 33},
      {task_manager_msgs__srv__GetTaskList__FIELDS, 3, 3},
    },
    {task_manager_msgs__srv__GetTaskList__REFERENCED_TYPE_DESCRIPTIONS, 9, 9},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&rcl_interfaces__msg__FloatingPointRange__EXPECTED_HASH, rcl_interfaces__msg__FloatingPointRange__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = rcl_interfaces__msg__FloatingPointRange__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&rcl_interfaces__msg__IntegerRange__EXPECTED_HASH, rcl_interfaces__msg__IntegerRange__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = rcl_interfaces__msg__IntegerRange__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&rcl_interfaces__msg__ParameterDescriptor__EXPECTED_HASH, rcl_interfaces__msg__ParameterDescriptor__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[3].fields = rcl_interfaces__msg__ParameterDescriptor__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[4].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&task_manager_msgs__msg__TaskDescription__EXPECTED_HASH, task_manager_msgs__msg__TaskDescription__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[5].fields = task_manager_msgs__msg__TaskDescription__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[6].fields = task_manager_msgs__srv__GetTaskList_Event__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[7].fields = task_manager_msgs__srv__GetTaskList_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[8].fields = task_manager_msgs__srv__GetTaskList_Response__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char task_manager_msgs__srv__GetTaskList_Request__FIELD_NAME__structure_needs_at_least_one_member[] = "structure_needs_at_least_one_member";

static rosidl_runtime_c__type_description__Field task_manager_msgs__srv__GetTaskList_Request__FIELDS[] = {
  {
    {task_manager_msgs__srv__GetTaskList_Request__FIELD_NAME__structure_needs_at_least_one_member, 35, 35},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
task_manager_msgs__srv__GetTaskList_Request__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {task_manager_msgs__srv__GetTaskList_Request__TYPE_NAME, 41, 41},
      {task_manager_msgs__srv__GetTaskList_Request__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char task_manager_msgs__srv__GetTaskList_Response__FIELD_NAME__tlist[] = "tlist";

static rosidl_runtime_c__type_description__Field task_manager_msgs__srv__GetTaskList_Response__FIELDS[] = {
  {
    {task_manager_msgs__srv__GetTaskList_Response__FIELD_NAME__tlist, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE,
      0,
      0,
      {task_manager_msgs__msg__TaskDescription__TYPE_NAME, 37, 37},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription task_manager_msgs__srv__GetTaskList_Response__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {rcl_interfaces__msg__FloatingPointRange__TYPE_NAME, 37, 37},
    {NULL, 0, 0},
  },
  {
    {rcl_interfaces__msg__IntegerRange__TYPE_NAME, 31, 31},
    {NULL, 0, 0},
  },
  {
    {rcl_interfaces__msg__ParameterDescriptor__TYPE_NAME, 38, 38},
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__msg__TaskDescription__TYPE_NAME, 37, 37},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
task_manager_msgs__srv__GetTaskList_Response__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {task_manager_msgs__srv__GetTaskList_Response__TYPE_NAME, 42, 42},
      {task_manager_msgs__srv__GetTaskList_Response__FIELDS, 1, 1},
    },
    {task_manager_msgs__srv__GetTaskList_Response__REFERENCED_TYPE_DESCRIPTIONS, 4, 4},
  };
  if (!constructed) {
    assert(0 == memcmp(&rcl_interfaces__msg__FloatingPointRange__EXPECTED_HASH, rcl_interfaces__msg__FloatingPointRange__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = rcl_interfaces__msg__FloatingPointRange__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&rcl_interfaces__msg__IntegerRange__EXPECTED_HASH, rcl_interfaces__msg__IntegerRange__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = rcl_interfaces__msg__IntegerRange__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&rcl_interfaces__msg__ParameterDescriptor__EXPECTED_HASH, rcl_interfaces__msg__ParameterDescriptor__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = rcl_interfaces__msg__ParameterDescriptor__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&task_manager_msgs__msg__TaskDescription__EXPECTED_HASH, task_manager_msgs__msg__TaskDescription__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[3].fields = task_manager_msgs__msg__TaskDescription__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char task_manager_msgs__srv__GetTaskList_Event__FIELD_NAME__info[] = "info";
static char task_manager_msgs__srv__GetTaskList_Event__FIELD_NAME__request[] = "request";
static char task_manager_msgs__srv__GetTaskList_Event__FIELD_NAME__response[] = "response";

static rosidl_runtime_c__type_description__Field task_manager_msgs__srv__GetTaskList_Event__FIELDS[] = {
  {
    {task_manager_msgs__srv__GetTaskList_Event__FIELD_NAME__info, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    },
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__srv__GetTaskList_Event__FIELD_NAME__request, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {task_manager_msgs__srv__GetTaskList_Request__TYPE_NAME, 41, 41},
    },
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__srv__GetTaskList_Event__FIELD_NAME__response, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {task_manager_msgs__srv__GetTaskList_Response__TYPE_NAME, 42, 42},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription task_manager_msgs__srv__GetTaskList_Event__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {rcl_interfaces__msg__FloatingPointRange__TYPE_NAME, 37, 37},
    {NULL, 0, 0},
  },
  {
    {rcl_interfaces__msg__IntegerRange__TYPE_NAME, 31, 31},
    {NULL, 0, 0},
  },
  {
    {rcl_interfaces__msg__ParameterDescriptor__TYPE_NAME, 38, 38},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__msg__TaskDescription__TYPE_NAME, 37, 37},
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__srv__GetTaskList_Request__TYPE_NAME, 41, 41},
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__srv__GetTaskList_Response__TYPE_NAME, 42, 42},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
task_manager_msgs__srv__GetTaskList_Event__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {task_manager_msgs__srv__GetTaskList_Event__TYPE_NAME, 39, 39},
      {task_manager_msgs__srv__GetTaskList_Event__FIELDS, 3, 3},
    },
    {task_manager_msgs__srv__GetTaskList_Event__REFERENCED_TYPE_DESCRIPTIONS, 8, 8},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&rcl_interfaces__msg__FloatingPointRange__EXPECTED_HASH, rcl_interfaces__msg__FloatingPointRange__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = rcl_interfaces__msg__FloatingPointRange__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&rcl_interfaces__msg__IntegerRange__EXPECTED_HASH, rcl_interfaces__msg__IntegerRange__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = rcl_interfaces__msg__IntegerRange__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&rcl_interfaces__msg__ParameterDescriptor__EXPECTED_HASH, rcl_interfaces__msg__ParameterDescriptor__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[3].fields = rcl_interfaces__msg__ParameterDescriptor__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[4].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&task_manager_msgs__msg__TaskDescription__EXPECTED_HASH, task_manager_msgs__msg__TaskDescription__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[5].fields = task_manager_msgs__msg__TaskDescription__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[6].fields = task_manager_msgs__srv__GetTaskList_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[7].fields = task_manager_msgs__srv__GetTaskList_Response__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "---\n"
  "task_manager_msgs/TaskDescription[] tlist";

static char srv_encoding[] = "srv";
static char implicit_encoding[] = "implicit";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
task_manager_msgs__srv__GetTaskList__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {task_manager_msgs__srv__GetTaskList__TYPE_NAME, 33, 33},
    {srv_encoding, 3, 3},
    {toplevel_type_raw_source, 46, 46},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
task_manager_msgs__srv__GetTaskList_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {task_manager_msgs__srv__GetTaskList_Request__TYPE_NAME, 41, 41},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
task_manager_msgs__srv__GetTaskList_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {task_manager_msgs__srv__GetTaskList_Response__TYPE_NAME, 42, 42},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
task_manager_msgs__srv__GetTaskList_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {task_manager_msgs__srv__GetTaskList_Event__TYPE_NAME, 39, 39},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
task_manager_msgs__srv__GetTaskList__get_type_description_sources(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[10];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 10, 10};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *task_manager_msgs__srv__GetTaskList__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *rcl_interfaces__msg__FloatingPointRange__get_individual_type_description_source(NULL);
    sources[3] = *rcl_interfaces__msg__IntegerRange__get_individual_type_description_source(NULL);
    sources[4] = *rcl_interfaces__msg__ParameterDescriptor__get_individual_type_description_source(NULL);
    sources[5] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    sources[6] = *task_manager_msgs__msg__TaskDescription__get_individual_type_description_source(NULL);
    sources[7] = *task_manager_msgs__srv__GetTaskList_Event__get_individual_type_description_source(NULL);
    sources[8] = *task_manager_msgs__srv__GetTaskList_Request__get_individual_type_description_source(NULL);
    sources[9] = *task_manager_msgs__srv__GetTaskList_Response__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
task_manager_msgs__srv__GetTaskList_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *task_manager_msgs__srv__GetTaskList_Request__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
task_manager_msgs__srv__GetTaskList_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[5];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 5, 5};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *task_manager_msgs__srv__GetTaskList_Response__get_individual_type_description_source(NULL),
    sources[1] = *rcl_interfaces__msg__FloatingPointRange__get_individual_type_description_source(NULL);
    sources[2] = *rcl_interfaces__msg__IntegerRange__get_individual_type_description_source(NULL);
    sources[3] = *rcl_interfaces__msg__ParameterDescriptor__get_individual_type_description_source(NULL);
    sources[4] = *task_manager_msgs__msg__TaskDescription__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
task_manager_msgs__srv__GetTaskList_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[9];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 9, 9};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *task_manager_msgs__srv__GetTaskList_Event__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *rcl_interfaces__msg__FloatingPointRange__get_individual_type_description_source(NULL);
    sources[3] = *rcl_interfaces__msg__IntegerRange__get_individual_type_description_source(NULL);
    sources[4] = *rcl_interfaces__msg__ParameterDescriptor__get_individual_type_description_source(NULL);
    sources[5] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    sources[6] = *task_manager_msgs__msg__TaskDescription__get_individual_type_description_source(NULL);
    sources[7] = *task_manager_msgs__srv__GetTaskList_Request__get_individual_type_description_source(NULL);
    sources[8] = *task_manager_msgs__srv__GetTaskList_Response__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
