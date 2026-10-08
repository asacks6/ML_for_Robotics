// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from task_manager_msgs:srv/StopTask.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "task_manager_msgs/srv/stop_task.hpp"


#ifndef TASK_MANAGER_MSGS__SRV__DETAIL__STOP_TASK__TRAITS_HPP_
#define TASK_MANAGER_MSGS__SRV__DETAIL__STOP_TASK__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "task_manager_msgs/srv/detail/stop_task__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace task_manager_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const StopTask_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const StopTask_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const StopTask_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace task_manager_msgs

namespace rosidl_generator_traits
{

[[deprecated("use task_manager_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const task_manager_msgs::srv::StopTask_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  task_manager_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use task_manager_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const task_manager_msgs::srv::StopTask_Request & msg)
{
  return task_manager_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<task_manager_msgs::srv::StopTask_Request>()
{
  return "task_manager_msgs::srv::StopTask_Request";
}

template<>
inline const char * name<task_manager_msgs::srv::StopTask_Request>()
{
  return "task_manager_msgs/srv/StopTask_Request";
}

template<>
struct has_fixed_size<task_manager_msgs::srv::StopTask_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<task_manager_msgs::srv::StopTask_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<task_manager_msgs::srv::StopTask_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace task_manager_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const StopTask_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: id
  {
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const StopTask_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "id: ";
    rosidl_generator_traits::value_to_yaml(msg.id, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const StopTask_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace task_manager_msgs

namespace rosidl_generator_traits
{

[[deprecated("use task_manager_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const task_manager_msgs::srv::StopTask_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  task_manager_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use task_manager_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const task_manager_msgs::srv::StopTask_Response & msg)
{
  return task_manager_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<task_manager_msgs::srv::StopTask_Response>()
{
  return "task_manager_msgs::srv::StopTask_Response";
}

template<>
inline const char * name<task_manager_msgs::srv::StopTask_Response>()
{
  return "task_manager_msgs/srv/StopTask_Response";
}

template<>
struct has_fixed_size<task_manager_msgs::srv::StopTask_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<task_manager_msgs::srv::StopTask_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<task_manager_msgs::srv::StopTask_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace task_manager_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const StopTask_Event & msg,
  std::ostream & out)
{
  out << "{";
  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: request
  {
    if (msg.request.size() == 0) {
      out << "request: []";
    } else {
      out << "request: [";
      size_t pending_items = msg.request.size();
      for (auto item : msg.request) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: response
  {
    if (msg.response.size() == 0) {
      out << "response: []";
    } else {
      out << "response: [";
      size_t pending_items = msg.response.size();
      for (auto item : msg.response) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const StopTask_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_block_style_yaml(msg.info, out, indentation + 2);
  }

  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.request.size() == 0) {
      out << "request: []\n";
    } else {
      out << "request:\n";
      for (auto item : msg.request) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.response.size() == 0) {
      out << "response: []\n";
    } else {
      out << "response:\n";
      for (auto item : msg.response) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const StopTask_Event & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace task_manager_msgs

namespace rosidl_generator_traits
{

[[deprecated("use task_manager_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const task_manager_msgs::srv::StopTask_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  task_manager_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use task_manager_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const task_manager_msgs::srv::StopTask_Event & msg)
{
  return task_manager_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<task_manager_msgs::srv::StopTask_Event>()
{
  return "task_manager_msgs::srv::StopTask_Event";
}

template<>
inline const char * name<task_manager_msgs::srv::StopTask_Event>()
{
  return "task_manager_msgs/srv/StopTask_Event";
}

template<>
struct has_fixed_size<task_manager_msgs::srv::StopTask_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<task_manager_msgs::srv::StopTask_Event>
  : std::integral_constant<bool, has_bounded_size<service_msgs::msg::ServiceEventInfo>::value && has_bounded_size<task_manager_msgs::srv::StopTask_Request>::value && has_bounded_size<task_manager_msgs::srv::StopTask_Response>::value> {};

template<>
struct is_message<task_manager_msgs::srv::StopTask_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<task_manager_msgs::srv::StopTask>()
{
  return "task_manager_msgs::srv::StopTask";
}

template<>
inline const char * name<task_manager_msgs::srv::StopTask>()
{
  return "task_manager_msgs/srv/StopTask";
}

template<>
struct has_fixed_size<task_manager_msgs::srv::StopTask>
  : std::integral_constant<
    bool,
    has_fixed_size<task_manager_msgs::srv::StopTask_Request>::value &&
    has_fixed_size<task_manager_msgs::srv::StopTask_Response>::value
  >
{
};

template<>
struct has_bounded_size<task_manager_msgs::srv::StopTask>
  : std::integral_constant<
    bool,
    has_bounded_size<task_manager_msgs::srv::StopTask_Request>::value &&
    has_bounded_size<task_manager_msgs::srv::StopTask_Response>::value
  >
{
};

template<>
struct is_service<task_manager_msgs::srv::StopTask>
  : std::true_type
{
};

template<>
struct is_service_request<task_manager_msgs::srv::StopTask_Request>
  : std::true_type
{
};

template<>
struct is_service_response<task_manager_msgs::srv::StopTask_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // TASK_MANAGER_MSGS__SRV__DETAIL__STOP_TASK__TRAITS_HPP_
