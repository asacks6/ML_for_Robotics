// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from cs7630_msgs:msg/PlaneDescription.idl
// generated code does not contain a copyright notice
#include "cs7630_msgs/msg/detail/plane_description__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
cs7630_msgs__msg__PlaneDescription__init(cs7630_msgs__msg__PlaneDescription * msg)
{
  if (!msg) {
    return false;
  }
  // a
  // b
  // c
  // d
  // fitness
  return true;
}

void
cs7630_msgs__msg__PlaneDescription__fini(cs7630_msgs__msg__PlaneDescription * msg)
{
  if (!msg) {
    return;
  }
  // a
  // b
  // c
  // d
  // fitness
}

bool
cs7630_msgs__msg__PlaneDescription__are_equal(const cs7630_msgs__msg__PlaneDescription * lhs, const cs7630_msgs__msg__PlaneDescription * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // a
  if (lhs->a != rhs->a) {
    return false;
  }
  // b
  if (lhs->b != rhs->b) {
    return false;
  }
  // c
  if (lhs->c != rhs->c) {
    return false;
  }
  // d
  if (lhs->d != rhs->d) {
    return false;
  }
  // fitness
  if (lhs->fitness != rhs->fitness) {
    return false;
  }
  return true;
}

bool
cs7630_msgs__msg__PlaneDescription__copy(
  const cs7630_msgs__msg__PlaneDescription * input,
  cs7630_msgs__msg__PlaneDescription * output)
{
  if (!input || !output) {
    return false;
  }
  // a
  output->a = input->a;
  // b
  output->b = input->b;
  // c
  output->c = input->c;
  // d
  output->d = input->d;
  // fitness
  output->fitness = input->fitness;
  return true;
}

cs7630_msgs__msg__PlaneDescription *
cs7630_msgs__msg__PlaneDescription__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cs7630_msgs__msg__PlaneDescription * msg = (cs7630_msgs__msg__PlaneDescription *)allocator.allocate(sizeof(cs7630_msgs__msg__PlaneDescription), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cs7630_msgs__msg__PlaneDescription));
  bool success = cs7630_msgs__msg__PlaneDescription__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cs7630_msgs__msg__PlaneDescription__destroy(cs7630_msgs__msg__PlaneDescription * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cs7630_msgs__msg__PlaneDescription__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cs7630_msgs__msg__PlaneDescription__Sequence__init(cs7630_msgs__msg__PlaneDescription__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cs7630_msgs__msg__PlaneDescription * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(cs7630_msgs__msg__PlaneDescription)) {
      return false;
    }
    data = (cs7630_msgs__msg__PlaneDescription *)allocator.zero_allocate(size, sizeof(cs7630_msgs__msg__PlaneDescription), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cs7630_msgs__msg__PlaneDescription__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cs7630_msgs__msg__PlaneDescription__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
cs7630_msgs__msg__PlaneDescription__Sequence__fini(cs7630_msgs__msg__PlaneDescription__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      cs7630_msgs__msg__PlaneDescription__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

cs7630_msgs__msg__PlaneDescription__Sequence *
cs7630_msgs__msg__PlaneDescription__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cs7630_msgs__msg__PlaneDescription__Sequence * array = (cs7630_msgs__msg__PlaneDescription__Sequence *)allocator.allocate(sizeof(cs7630_msgs__msg__PlaneDescription__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cs7630_msgs__msg__PlaneDescription__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cs7630_msgs__msg__PlaneDescription__Sequence__destroy(cs7630_msgs__msg__PlaneDescription__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cs7630_msgs__msg__PlaneDescription__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cs7630_msgs__msg__PlaneDescription__Sequence__are_equal(const cs7630_msgs__msg__PlaneDescription__Sequence * lhs, const cs7630_msgs__msg__PlaneDescription__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cs7630_msgs__msg__PlaneDescription__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cs7630_msgs__msg__PlaneDescription__Sequence__copy(
  const cs7630_msgs__msg__PlaneDescription__Sequence * input,
  cs7630_msgs__msg__PlaneDescription__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(cs7630_msgs__msg__PlaneDescription)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(cs7630_msgs__msg__PlaneDescription);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cs7630_msgs__msg__PlaneDescription * data =
      (cs7630_msgs__msg__PlaneDescription *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cs7630_msgs__msg__PlaneDescription__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cs7630_msgs__msg__PlaneDescription__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cs7630_msgs__msg__PlaneDescription__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
