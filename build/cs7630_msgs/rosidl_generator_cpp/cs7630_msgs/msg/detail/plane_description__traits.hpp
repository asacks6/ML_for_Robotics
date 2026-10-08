// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cs7630_msgs:msg/PlaneDescription.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cs7630_msgs/msg/plane_description.hpp"


#ifndef CS7630_MSGS__MSG__DETAIL__PLANE_DESCRIPTION__TRAITS_HPP_
#define CS7630_MSGS__MSG__DETAIL__PLANE_DESCRIPTION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cs7630_msgs/msg/detail/plane_description__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace cs7630_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const PlaneDescription & msg,
  std::ostream & out)
{
  out << "{";
  // member: a
  {
    out << "a: ";
    rosidl_generator_traits::value_to_yaml(msg.a, out);
    out << ", ";
  }

  // member: b
  {
    out << "b: ";
    rosidl_generator_traits::value_to_yaml(msg.b, out);
    out << ", ";
  }

  // member: c
  {
    out << "c: ";
    rosidl_generator_traits::value_to_yaml(msg.c, out);
    out << ", ";
  }

  // member: d
  {
    out << "d: ";
    rosidl_generator_traits::value_to_yaml(msg.d, out);
    out << ", ";
  }

  // member: fitness
  {
    out << "fitness: ";
    rosidl_generator_traits::value_to_yaml(msg.fitness, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PlaneDescription & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: a
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "a: ";
    rosidl_generator_traits::value_to_yaml(msg.a, out);
    out << "\n";
  }

  // member: b
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "b: ";
    rosidl_generator_traits::value_to_yaml(msg.b, out);
    out << "\n";
  }

  // member: c
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "c: ";
    rosidl_generator_traits::value_to_yaml(msg.c, out);
    out << "\n";
  }

  // member: d
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "d: ";
    rosidl_generator_traits::value_to_yaml(msg.d, out);
    out << "\n";
  }

  // member: fitness
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fitness: ";
    rosidl_generator_traits::value_to_yaml(msg.fitness, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PlaneDescription & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace cs7630_msgs

namespace rosidl_generator_traits
{

[[deprecated("use cs7630_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const cs7630_msgs::msg::PlaneDescription & msg,
  std::ostream & out, size_t indentation = 0)
{
  cs7630_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cs7630_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const cs7630_msgs::msg::PlaneDescription & msg)
{
  return cs7630_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cs7630_msgs::msg::PlaneDescription>()
{
  return "cs7630_msgs::msg::PlaneDescription";
}

template<>
inline const char * name<cs7630_msgs::msg::PlaneDescription>()
{
  return "cs7630_msgs/msg/PlaneDescription";
}

template<>
struct has_fixed_size<cs7630_msgs::msg::PlaneDescription>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<cs7630_msgs::msg::PlaneDescription>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<cs7630_msgs::msg::PlaneDescription>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // CS7630_MSGS__MSG__DETAIL__PLANE_DESCRIPTION__TRAITS_HPP_
