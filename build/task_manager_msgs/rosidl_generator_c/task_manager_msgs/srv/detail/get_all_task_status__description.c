// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from task_manager_msgs:srv/GetAllTaskStatus.idl
// generated code does not contain a copyright notice

#include "task_manager_msgs/srv/detail/get_all_task_status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_type_hash_t *
task_manager_msgs__srv__GetAllTaskStatus__get_type_hash(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x45, 0x78, 0x86, 0x1a, 0x6a, 0x47, 0x25, 0x7e,
      0xe4, 0x42, 0x1e, 0xb6, 0xdb, 0x37, 0x7c, 0x39,
      0x1f, 0x79, 0x22, 0xc9, 0xfd, 0x8b, 0xd9, 0x42,
      0x21, 0xde, 0xda, 0x95, 0x0c, 0x2d, 0x10, 0xc3,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_type_hash_t *
task_manager_msgs__srv__GetAllTaskStatus_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x63, 0xb7, 0xdb, 0x20, 0x3d, 0x59, 0x19, 0xed,
      0xa8, 0xe6, 0x10, 0x3b, 0x7b, 0x25, 0x54, 0x25,
      0x19, 0xa9, 0x5c, 0x91, 0x6e, 0xc0, 0x3f, 0x55,
      0xcc, 0xa2, 0xd1, 0xa9, 0x44, 0x6b, 0xa2, 0xee,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_type_hash_t *
task_manager_msgs__srv__GetAllTaskStatus_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xc5, 0xf1, 0x50, 0x62, 0xb3, 0x02, 0x34, 0x1f,
      0x07, 0x44, 0x4a, 0x36, 0x4d, 0xf6, 0x65, 0x82,
      0x32, 0xd6, 0xd2, 0x65, 0xd1, 0x6c, 0xac, 0x70,
      0xf3, 0x28, 0x7c, 0xb7, 0x69, 0xa1, 0xfe, 0xa9,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_task_manager_msgs
const rosidl_type_hash_t *
task_manager_msgs__srv__GetAllTaskStatus_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x7f, 0xd8, 0xb1, 0x04, 0x40, 0x66, 0xc7, 0x30,
      0x24, 0xe3, 0x19, 0x87, 0xf4, 0x59, 0xcd, 0x2f,
      0xd4, 0x62, 0x20, 0x2e, 0xf1, 0xf8, 0xe6, 0x48,
      0x70, 0xff, 0xc2, 0x16, 0x8c, 0x40, 0xe3, 0x9e,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "rcl_interfaces/msg/detail/parameter__functions.h"
#include "rcl_interfaces/msg/detail/parameter_value__functions.h"
#include "service_msgs/msg/detail/service_event_info__functions.h"
#include "task_manager_msgs/msg/detail/task_status__functions.h"

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
static const rosidl_type_hash_t service_msgs__msg__ServiceEventInfo__EXPECTED_HASH = {1, {
    0x41, 0xbc, 0xbb, 0xe0, 0x7a, 0x75, 0xc9, 0xb5,
    0x2b, 0xc9, 0x6b, 0xfd, 0x5c, 0x24, 0xd7, 0xf0,
    0xfc, 0x0a, 0x08, 0xc0, 0xcb, 0x79, 0x21, 0xb3,
    0x37, 0x3c, 0x57, 0x32, 0x34, 0x5a, 0x6f, 0x45,
  }};
static const rosidl_type_hash_t task_manager_msgs__msg__TaskStatus__EXPECTED_HASH = {1, {
    0xce, 0x8e, 0x5b, 0x11, 0x56, 0x8a, 0x7b, 0x1d,
    0xf8, 0x58, 0x27, 0x2a, 0xc7, 0xa6, 0x01, 0xa9,
    0x7a, 0x83, 0x5f, 0x0d, 0x6e, 0x84, 0xce, 0xa7,
    0xaf, 0xd3, 0x4b, 0xad, 0x5e, 0x0f, 0x5d, 0x00,
  }};
#endif

static char task_manager_msgs__srv__GetAllTaskStatus__TYPE_NAME[] = "task_manager_msgs/srv/GetAllTaskStatus";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char rcl_interfaces__msg__Parameter__TYPE_NAME[] = "rcl_interfaces/msg/Parameter";
static char rcl_interfaces__msg__ParameterValue__TYPE_NAME[] = "rcl_interfaces/msg/ParameterValue";
static char service_msgs__msg__ServiceEventInfo__TYPE_NAME[] = "service_msgs/msg/ServiceEventInfo";
static char task_manager_msgs__msg__TaskStatus__TYPE_NAME[] = "task_manager_msgs/msg/TaskStatus";
static char task_manager_msgs__srv__GetAllTaskStatus_Event__TYPE_NAME[] = "task_manager_msgs/srv/GetAllTaskStatus_Event";
static char task_manager_msgs__srv__GetAllTaskStatus_Request__TYPE_NAME[] = "task_manager_msgs/srv/GetAllTaskStatus_Request";
static char task_manager_msgs__srv__GetAllTaskStatus_Response__TYPE_NAME[] = "task_manager_msgs/srv/GetAllTaskStatus_Response";

// Define type names, field names, and default values
static char task_manager_msgs__srv__GetAllTaskStatus__FIELD_NAME__request_message[] = "request_message";
static char task_manager_msgs__srv__GetAllTaskStatus__FIELD_NAME__response_message[] = "response_message";
static char task_manager_msgs__srv__GetAllTaskStatus__FIELD_NAME__event_message[] = "event_message";

static rosidl_runtime_c__type_description__Field task_manager_msgs__srv__GetAllTaskStatus__FIELDS[] = {
  {
    {task_manager_msgs__srv__GetAllTaskStatus__FIELD_NAME__request_message, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {task_manager_msgs__srv__GetAllTaskStatus_Request__TYPE_NAME, 46, 46},
    },
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__srv__GetAllTaskStatus__FIELD_NAME__response_message, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {task_manager_msgs__srv__GetAllTaskStatus_Response__TYPE_NAME, 47, 47},
    },
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__srv__GetAllTaskStatus__FIELD_NAME__event_message, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {task_manager_msgs__srv__GetAllTaskStatus_Event__TYPE_NAME, 44, 44},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription task_manager_msgs__srv__GetAllTaskStatus__REFERENCED_TYPE_DESCRIPTIONS[] = {
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
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__msg__TaskStatus__TYPE_NAME, 32, 32},
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__srv__GetAllTaskStatus_Event__TYPE_NAME, 44, 44},
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__srv__GetAllTaskStatus_Request__TYPE_NAME, 46, 46},
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__srv__GetAllTaskStatus_Response__TYPE_NAME, 47, 47},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
task_manager_msgs__srv__GetAllTaskStatus__get_type_description(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {task_manager_msgs__srv__GetAllTaskStatus__TYPE_NAME, 38, 38},
      {task_manager_msgs__srv__GetAllTaskStatus__FIELDS, 3, 3},
    },
    {task_manager_msgs__srv__GetAllTaskStatus__REFERENCED_TYPE_DESCRIPTIONS, 8, 8},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&rcl_interfaces__msg__Parameter__EXPECTED_HASH, rcl_interfaces__msg__Parameter__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = rcl_interfaces__msg__Parameter__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&rcl_interfaces__msg__ParameterValue__EXPECTED_HASH, rcl_interfaces__msg__ParameterValue__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = rcl_interfaces__msg__ParameterValue__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[3].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&task_manager_msgs__msg__TaskStatus__EXPECTED_HASH, task_manager_msgs__msg__TaskStatus__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[4].fields = task_manager_msgs__msg__TaskStatus__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[5].fields = task_manager_msgs__srv__GetAllTaskStatus_Event__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[6].fields = task_manager_msgs__srv__GetAllTaskStatus_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[7].fields = task_manager_msgs__srv__GetAllTaskStatus_Response__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char task_manager_msgs__srv__GetAllTaskStatus_Request__FIELD_NAME__structure_needs_at_least_one_member[] = "structure_needs_at_least_one_member";

static rosidl_runtime_c__type_description__Field task_manager_msgs__srv__GetAllTaskStatus_Request__FIELDS[] = {
  {
    {task_manager_msgs__srv__GetAllTaskStatus_Request__FIELD_NAME__structure_needs_at_least_one_member, 35, 35},
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
task_manager_msgs__srv__GetAllTaskStatus_Request__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {task_manager_msgs__srv__GetAllTaskStatus_Request__TYPE_NAME, 46, 46},
      {task_manager_msgs__srv__GetAllTaskStatus_Request__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char task_manager_msgs__srv__GetAllTaskStatus_Response__FIELD_NAME__running_tasks[] = "running_tasks";
static char task_manager_msgs__srv__GetAllTaskStatus_Response__FIELD_NAME__zombie_tasks[] = "zombie_tasks";

static rosidl_runtime_c__type_description__Field task_manager_msgs__srv__GetAllTaskStatus_Response__FIELDS[] = {
  {
    {task_manager_msgs__srv__GetAllTaskStatus_Response__FIELD_NAME__running_tasks, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE,
      0,
      0,
      {task_manager_msgs__msg__TaskStatus__TYPE_NAME, 32, 32},
    },
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__srv__GetAllTaskStatus_Response__FIELD_NAME__zombie_tasks, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE,
      0,
      0,
      {task_manager_msgs__msg__TaskStatus__TYPE_NAME, 32, 32},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription task_manager_msgs__srv__GetAllTaskStatus_Response__REFERENCED_TYPE_DESCRIPTIONS[] = {
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
  {
    {task_manager_msgs__msg__TaskStatus__TYPE_NAME, 32, 32},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
task_manager_msgs__srv__GetAllTaskStatus_Response__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {task_manager_msgs__srv__GetAllTaskStatus_Response__TYPE_NAME, 47, 47},
      {task_manager_msgs__srv__GetAllTaskStatus_Response__FIELDS, 2, 2},
    },
    {task_manager_msgs__srv__GetAllTaskStatus_Response__REFERENCED_TYPE_DESCRIPTIONS, 4, 4},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&rcl_interfaces__msg__Parameter__EXPECTED_HASH, rcl_interfaces__msg__Parameter__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = rcl_interfaces__msg__Parameter__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&rcl_interfaces__msg__ParameterValue__EXPECTED_HASH, rcl_interfaces__msg__ParameterValue__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = rcl_interfaces__msg__ParameterValue__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&task_manager_msgs__msg__TaskStatus__EXPECTED_HASH, task_manager_msgs__msg__TaskStatus__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[3].fields = task_manager_msgs__msg__TaskStatus__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char task_manager_msgs__srv__GetAllTaskStatus_Event__FIELD_NAME__info[] = "info";
static char task_manager_msgs__srv__GetAllTaskStatus_Event__FIELD_NAME__request[] = "request";
static char task_manager_msgs__srv__GetAllTaskStatus_Event__FIELD_NAME__response[] = "response";

static rosidl_runtime_c__type_description__Field task_manager_msgs__srv__GetAllTaskStatus_Event__FIELDS[] = {
  {
    {task_manager_msgs__srv__GetAllTaskStatus_Event__FIELD_NAME__info, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    },
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__srv__GetAllTaskStatus_Event__FIELD_NAME__request, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {task_manager_msgs__srv__GetAllTaskStatus_Request__TYPE_NAME, 46, 46},
    },
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__srv__GetAllTaskStatus_Event__FIELD_NAME__response, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {task_manager_msgs__srv__GetAllTaskStatus_Response__TYPE_NAME, 47, 47},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription task_manager_msgs__srv__GetAllTaskStatus_Event__REFERENCED_TYPE_DESCRIPTIONS[] = {
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
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__msg__TaskStatus__TYPE_NAME, 32, 32},
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__srv__GetAllTaskStatus_Request__TYPE_NAME, 46, 46},
    {NULL, 0, 0},
  },
  {
    {task_manager_msgs__srv__GetAllTaskStatus_Response__TYPE_NAME, 47, 47},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
task_manager_msgs__srv__GetAllTaskStatus_Event__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {task_manager_msgs__srv__GetAllTaskStatus_Event__TYPE_NAME, 44, 44},
      {task_manager_msgs__srv__GetAllTaskStatus_Event__FIELDS, 3, 3},
    },
    {task_manager_msgs__srv__GetAllTaskStatus_Event__REFERENCED_TYPE_DESCRIPTIONS, 7, 7},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&rcl_interfaces__msg__Parameter__EXPECTED_HASH, rcl_interfaces__msg__Parameter__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = rcl_interfaces__msg__Parameter__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&rcl_interfaces__msg__ParameterValue__EXPECTED_HASH, rcl_interfaces__msg__ParameterValue__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = rcl_interfaces__msg__ParameterValue__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[3].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&task_manager_msgs__msg__TaskStatus__EXPECTED_HASH, task_manager_msgs__msg__TaskStatus__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[4].fields = task_manager_msgs__msg__TaskStatus__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[5].fields = task_manager_msgs__srv__GetAllTaskStatus_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[6].fields = task_manager_msgs__srv__GetAllTaskStatus_Response__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "---\n"
  "task_manager_msgs/TaskStatus[] running_tasks\n"
  "task_manager_msgs/TaskStatus[] zombie_tasks";

static char srv_encoding[] = "srv";
static char implicit_encoding[] = "implicit";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
task_manager_msgs__srv__GetAllTaskStatus__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {task_manager_msgs__srv__GetAllTaskStatus__TYPE_NAME, 38, 38},
    {srv_encoding, 3, 3},
    {toplevel_type_raw_source, 93, 93},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
task_manager_msgs__srv__GetAllTaskStatus_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {task_manager_msgs__srv__GetAllTaskStatus_Request__TYPE_NAME, 46, 46},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
task_manager_msgs__srv__GetAllTaskStatus_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {task_manager_msgs__srv__GetAllTaskStatus_Response__TYPE_NAME, 47, 47},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
task_manager_msgs__srv__GetAllTaskStatus_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {task_manager_msgs__srv__GetAllTaskStatus_Event__TYPE_NAME, 44, 44},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
task_manager_msgs__srv__GetAllTaskStatus__get_type_description_sources(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[9];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 9, 9};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *task_manager_msgs__srv__GetAllTaskStatus__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *rcl_interfaces__msg__Parameter__get_individual_type_description_source(NULL);
    sources[3] = *rcl_interfaces__msg__ParameterValue__get_individual_type_description_source(NULL);
    sources[4] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    sources[5] = *task_manager_msgs__msg__TaskStatus__get_individual_type_description_source(NULL);
    sources[6] = *task_manager_msgs__srv__GetAllTaskStatus_Event__get_individual_type_description_source(NULL);
    sources[7] = *task_manager_msgs__srv__GetAllTaskStatus_Request__get_individual_type_description_source(NULL);
    sources[8] = *task_manager_msgs__srv__GetAllTaskStatus_Response__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
task_manager_msgs__srv__GetAllTaskStatus_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *task_manager_msgs__srv__GetAllTaskStatus_Request__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
task_manager_msgs__srv__GetAllTaskStatus_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[5];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 5, 5};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *task_manager_msgs__srv__GetAllTaskStatus_Response__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *rcl_interfaces__msg__Parameter__get_individual_type_description_source(NULL);
    sources[3] = *rcl_interfaces__msg__ParameterValue__get_individual_type_description_source(NULL);
    sources[4] = *task_manager_msgs__msg__TaskStatus__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
task_manager_msgs__srv__GetAllTaskStatus_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[8];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 8, 8};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *task_manager_msgs__srv__GetAllTaskStatus_Event__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *rcl_interfaces__msg__Parameter__get_individual_type_description_source(NULL);
    sources[3] = *rcl_interfaces__msg__ParameterValue__get_individual_type_description_source(NULL);
    sources[4] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    sources[5] = *task_manager_msgs__msg__TaskStatus__get_individual_type_description_source(NULL);
    sources[6] = *task_manager_msgs__srv__GetAllTaskStatus_Request__get_individual_type_description_source(NULL);
    sources[7] = *task_manager_msgs__srv__GetAllTaskStatus_Response__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
