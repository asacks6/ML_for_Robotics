// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from cs7630_msgs:msg/PlaneDescription.idl
// generated code does not contain a copyright notice

#include "cs7630_msgs/msg/detail/plane_description__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_cs7630_msgs
const rosidl_type_hash_t *
cs7630_msgs__msg__PlaneDescription__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xcd, 0x8c, 0xbe, 0x25, 0xe7, 0xa8, 0x1b, 0xf6,
      0x83, 0x1a, 0x7f, 0x2d, 0xab, 0xe0, 0x5e, 0x89,
      0x1d, 0x32, 0x44, 0xe9, 0x6a, 0xc4, 0xea, 0xc3,
      0x4c, 0xdb, 0xb9, 0x37, 0x91, 0xea, 0x67, 0x6c,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char cs7630_msgs__msg__PlaneDescription__TYPE_NAME[] = "cs7630_msgs/msg/PlaneDescription";

// Define type names, field names, and default values
static char cs7630_msgs__msg__PlaneDescription__FIELD_NAME__a[] = "a";
static char cs7630_msgs__msg__PlaneDescription__FIELD_NAME__b[] = "b";
static char cs7630_msgs__msg__PlaneDescription__FIELD_NAME__c[] = "c";
static char cs7630_msgs__msg__PlaneDescription__FIELD_NAME__d[] = "d";
static char cs7630_msgs__msg__PlaneDescription__FIELD_NAME__fitness[] = "fitness";

static rosidl_runtime_c__type_description__Field cs7630_msgs__msg__PlaneDescription__FIELDS[] = {
  {
    {cs7630_msgs__msg__PlaneDescription__FIELD_NAME__a, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {cs7630_msgs__msg__PlaneDescription__FIELD_NAME__b, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {cs7630_msgs__msg__PlaneDescription__FIELD_NAME__c, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {cs7630_msgs__msg__PlaneDescription__FIELD_NAME__d, 1, 1},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {cs7630_msgs__msg__PlaneDescription__FIELD_NAME__fitness, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
cs7630_msgs__msg__PlaneDescription__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {cs7630_msgs__msg__PlaneDescription__TYPE_NAME, 32, 32},
      {cs7630_msgs__msg__PlaneDescription__FIELDS, 5, 5},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# Describe a plane with a generic equation\n"
  "# a x + b y + c z + d = 0\n"
  "# fitness can be used to output a regression score (R^2 or other fitness)\n"
  "float64 a\n"
  "float64 b\n"
  "float64 c\n"
  "float64 d\n"
  "float64 fitness";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
cs7630_msgs__msg__PlaneDescription__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {cs7630_msgs__msg__PlaneDescription__TYPE_NAME, 32, 32},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 199, 199},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
cs7630_msgs__msg__PlaneDescription__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *cs7630_msgs__msg__PlaneDescription__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
