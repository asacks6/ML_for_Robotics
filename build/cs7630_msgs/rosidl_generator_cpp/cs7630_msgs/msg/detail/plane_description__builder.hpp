// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cs7630_msgs:msg/PlaneDescription.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cs7630_msgs/msg/plane_description.hpp"


#ifndef CS7630_MSGS__MSG__DETAIL__PLANE_DESCRIPTION__BUILDER_HPP_
#define CS7630_MSGS__MSG__DETAIL__PLANE_DESCRIPTION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cs7630_msgs/msg/detail/plane_description__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cs7630_msgs
{

namespace msg
{

namespace builder
{

class Init_PlaneDescription_fitness
{
public:
  explicit Init_PlaneDescription_fitness(::cs7630_msgs::msg::PlaneDescription & msg)
  : msg_(msg)
  {}
  ::cs7630_msgs::msg::PlaneDescription fitness(::cs7630_msgs::msg::PlaneDescription::_fitness_type arg)
  {
    msg_.fitness = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cs7630_msgs::msg::PlaneDescription msg_;
};

class Init_PlaneDescription_d
{
public:
  explicit Init_PlaneDescription_d(::cs7630_msgs::msg::PlaneDescription & msg)
  : msg_(msg)
  {}
  Init_PlaneDescription_fitness d(::cs7630_msgs::msg::PlaneDescription::_d_type arg)
  {
    msg_.d = std::move(arg);
    return Init_PlaneDescription_fitness(msg_);
  }

private:
  ::cs7630_msgs::msg::PlaneDescription msg_;
};

class Init_PlaneDescription_c
{
public:
  explicit Init_PlaneDescription_c(::cs7630_msgs::msg::PlaneDescription & msg)
  : msg_(msg)
  {}
  Init_PlaneDescription_d c(::cs7630_msgs::msg::PlaneDescription::_c_type arg)
  {
    msg_.c = std::move(arg);
    return Init_PlaneDescription_d(msg_);
  }

private:
  ::cs7630_msgs::msg::PlaneDescription msg_;
};

class Init_PlaneDescription_b
{
public:
  explicit Init_PlaneDescription_b(::cs7630_msgs::msg::PlaneDescription & msg)
  : msg_(msg)
  {}
  Init_PlaneDescription_c b(::cs7630_msgs::msg::PlaneDescription::_b_type arg)
  {
    msg_.b = std::move(arg);
    return Init_PlaneDescription_c(msg_);
  }

private:
  ::cs7630_msgs::msg::PlaneDescription msg_;
};

class Init_PlaneDescription_a
{
public:
  Init_PlaneDescription_a()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PlaneDescription_b a(::cs7630_msgs::msg::PlaneDescription::_a_type arg)
  {
    msg_.a = std::move(arg);
    return Init_PlaneDescription_b(msg_);
  }

private:
  ::cs7630_msgs::msg::PlaneDescription msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cs7630_msgs::msg::PlaneDescription>()
{
  return cs7630_msgs::msg::builder::Init_PlaneDescription_a();
}

}  // namespace cs7630_msgs

#endif  // CS7630_MSGS__MSG__DETAIL__PLANE_DESCRIPTION__BUILDER_HPP_
