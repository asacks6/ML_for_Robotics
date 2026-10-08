// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from task_manager_msgs:srv/GetTaskList.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "task_manager_msgs/srv/get_task_list.hpp"


#ifndef TASK_MANAGER_MSGS__SRV__DETAIL__GET_TASK_LIST__BUILDER_HPP_
#define TASK_MANAGER_MSGS__SRV__DETAIL__GET_TASK_LIST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "task_manager_msgs/srv/detail/get_task_list__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace task_manager_msgs
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::task_manager_msgs::srv::GetTaskList_Request>()
{
  return ::task_manager_msgs::srv::GetTaskList_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace task_manager_msgs


namespace task_manager_msgs
{

namespace srv
{

namespace builder
{

class Init_GetTaskList_Response_tlist
{
public:
  Init_GetTaskList_Response_tlist()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::task_manager_msgs::srv::GetTaskList_Response tlist(::task_manager_msgs::srv::GetTaskList_Response::_tlist_type arg)
  {
    msg_.tlist = std::move(arg);
    return std::move(msg_);
  }

private:
  ::task_manager_msgs::srv::GetTaskList_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::task_manager_msgs::srv::GetTaskList_Response>()
{
  return task_manager_msgs::srv::builder::Init_GetTaskList_Response_tlist();
}

}  // namespace task_manager_msgs


namespace task_manager_msgs
{

namespace srv
{

namespace builder
{

class Init_GetTaskList_Event_response
{
public:
  explicit Init_GetTaskList_Event_response(::task_manager_msgs::srv::GetTaskList_Event & msg)
  : msg_(msg)
  {}
  ::task_manager_msgs::srv::GetTaskList_Event response(::task_manager_msgs::srv::GetTaskList_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::task_manager_msgs::srv::GetTaskList_Event msg_;
};

class Init_GetTaskList_Event_request
{
public:
  explicit Init_GetTaskList_Event_request(::task_manager_msgs::srv::GetTaskList_Event & msg)
  : msg_(msg)
  {}
  Init_GetTaskList_Event_response request(::task_manager_msgs::srv::GetTaskList_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_GetTaskList_Event_response(msg_);
  }

private:
  ::task_manager_msgs::srv::GetTaskList_Event msg_;
};

class Init_GetTaskList_Event_info
{
public:
  Init_GetTaskList_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetTaskList_Event_request info(::task_manager_msgs::srv::GetTaskList_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_GetTaskList_Event_request(msg_);
  }

private:
  ::task_manager_msgs::srv::GetTaskList_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::task_manager_msgs::srv::GetTaskList_Event>()
{
  return task_manager_msgs::srv::builder::Init_GetTaskList_Event_info();
}

}  // namespace task_manager_msgs

#endif  // TASK_MANAGER_MSGS__SRV__DETAIL__GET_TASK_LIST__BUILDER_HPP_
