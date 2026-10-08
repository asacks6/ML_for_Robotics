// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from task_manager_msgs:srv/StopTask.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "task_manager_msgs/srv/stop_task.hpp"


#ifndef TASK_MANAGER_MSGS__SRV__DETAIL__STOP_TASK__BUILDER_HPP_
#define TASK_MANAGER_MSGS__SRV__DETAIL__STOP_TASK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "task_manager_msgs/srv/detail/stop_task__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace task_manager_msgs
{

namespace srv
{

namespace builder
{

class Init_StopTask_Request_id
{
public:
  Init_StopTask_Request_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::task_manager_msgs::srv::StopTask_Request id(::task_manager_msgs::srv::StopTask_Request::_id_type arg)
  {
    msg_.id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::task_manager_msgs::srv::StopTask_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::task_manager_msgs::srv::StopTask_Request>()
{
  return task_manager_msgs::srv::builder::Init_StopTask_Request_id();
}

}  // namespace task_manager_msgs


namespace task_manager_msgs
{

namespace srv
{

namespace builder
{

class Init_StopTask_Response_id
{
public:
  Init_StopTask_Response_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::task_manager_msgs::srv::StopTask_Response id(::task_manager_msgs::srv::StopTask_Response::_id_type arg)
  {
    msg_.id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::task_manager_msgs::srv::StopTask_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::task_manager_msgs::srv::StopTask_Response>()
{
  return task_manager_msgs::srv::builder::Init_StopTask_Response_id();
}

}  // namespace task_manager_msgs


namespace task_manager_msgs
{

namespace srv
{

namespace builder
{

class Init_StopTask_Event_response
{
public:
  explicit Init_StopTask_Event_response(::task_manager_msgs::srv::StopTask_Event & msg)
  : msg_(msg)
  {}
  ::task_manager_msgs::srv::StopTask_Event response(::task_manager_msgs::srv::StopTask_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::task_manager_msgs::srv::StopTask_Event msg_;
};

class Init_StopTask_Event_request
{
public:
  explicit Init_StopTask_Event_request(::task_manager_msgs::srv::StopTask_Event & msg)
  : msg_(msg)
  {}
  Init_StopTask_Event_response request(::task_manager_msgs::srv::StopTask_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_StopTask_Event_response(msg_);
  }

private:
  ::task_manager_msgs::srv::StopTask_Event msg_;
};

class Init_StopTask_Event_info
{
public:
  Init_StopTask_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_StopTask_Event_request info(::task_manager_msgs::srv::StopTask_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_StopTask_Event_request(msg_);
  }

private:
  ::task_manager_msgs::srv::StopTask_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::task_manager_msgs::srv::StopTask_Event>()
{
  return task_manager_msgs::srv::builder::Init_StopTask_Event_info();
}

}  // namespace task_manager_msgs

#endif  // TASK_MANAGER_MSGS__SRV__DETAIL__STOP_TASK__BUILDER_HPP_
