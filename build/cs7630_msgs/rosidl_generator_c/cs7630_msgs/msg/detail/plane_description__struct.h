// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cs7630_msgs:msg/PlaneDescription.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cs7630_msgs/msg/plane_description.h"


#ifndef CS7630_MSGS__MSG__DETAIL__PLANE_DESCRIPTION__STRUCT_H_
#define CS7630_MSGS__MSG__DETAIL__PLANE_DESCRIPTION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/PlaneDescription in the package cs7630_msgs.
/**
  * Describe a plane with a generic equation
  * a x + b y + c z + d = 0
  * fitness can be used to output a regression score (R^2 or other fitness)
 */
typedef struct cs7630_msgs__msg__PlaneDescription
{
  double a;
  double b;
  double c;
  double d;
  double fitness;
} cs7630_msgs__msg__PlaneDescription;

// Struct for a sequence of cs7630_msgs__msg__PlaneDescription.
typedef struct cs7630_msgs__msg__PlaneDescription__Sequence
{
  cs7630_msgs__msg__PlaneDescription * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cs7630_msgs__msg__PlaneDescription__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CS7630_MSGS__MSG__DETAIL__PLANE_DESCRIPTION__STRUCT_H_
