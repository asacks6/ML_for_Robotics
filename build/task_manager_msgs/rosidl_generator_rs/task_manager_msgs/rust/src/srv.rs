#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};




// Corresponds to task_manager_msgs__srv__GetAllTaskStatus_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetAllTaskStatus_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub structure_needs_at_least_one_member: u8,

}



impl Default for GetAllTaskStatus_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GetAllTaskStatus_Request::default())
  }
}

impl rosidl_runtime_rs::Message for GetAllTaskStatus_Request {
  type RmwMsg = super::srv::rmw::GetAllTaskStatus_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        structure_needs_at_least_one_member: msg.structure_needs_at_least_one_member,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      structure_needs_at_least_one_member: msg.structure_needs_at_least_one_member,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      structure_needs_at_least_one_member: msg.structure_needs_at_least_one_member,
    }
  }
}


// Corresponds to task_manager_msgs__srv__GetAllTaskStatus_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetAllTaskStatus_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub running_tasks: Vec<super::msg::TaskStatus>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub zombie_tasks: Vec<super::msg::TaskStatus>,

}



impl Default for GetAllTaskStatus_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GetAllTaskStatus_Response::default())
  }
}

impl rosidl_runtime_rs::Message for GetAllTaskStatus_Response {
  type RmwMsg = super::srv::rmw::GetAllTaskStatus_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        running_tasks: msg.running_tasks
          .into_iter()
          .map(|elem| super::msg::TaskStatus::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
        zombie_tasks: msg.zombie_tasks
          .into_iter()
          .map(|elem| super::msg::TaskStatus::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        running_tasks: msg.running_tasks
          .iter()
          .map(|elem| super::msg::TaskStatus::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
        zombie_tasks: msg.zombie_tasks
          .iter()
          .map(|elem| super::msg::TaskStatus::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      running_tasks: msg.running_tasks
          .into_iter()
          .map(super::msg::TaskStatus::from_rmw_message)
          .collect(),
      zombie_tasks: msg.zombie_tasks
          .into_iter()
          .map(super::msg::TaskStatus::from_rmw_message)
          .collect(),
    }
  }
}


// Corresponds to task_manager_msgs__srv__StartTask_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct StartTask_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub name: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub config: Vec<rcl_interfaces::msg::Parameter>,

}



impl Default for StartTask_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::StartTask_Request::default())
  }
}

impl rosidl_runtime_rs::Message for StartTask_Request {
  type RmwMsg = super::srv::rmw::StartTask_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        name: msg.name.as_str().into(),
        config: msg.config
          .into_iter()
          .map(|elem| rcl_interfaces::msg::Parameter::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        name: msg.name.as_str().into(),
        config: msg.config
          .iter()
          .map(|elem| rcl_interfaces::msg::Parameter::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      name: msg.name.to_string(),
      config: msg.config
          .into_iter()
          .map(rcl_interfaces::msg::Parameter::from_rmw_message)
          .collect(),
    }
  }
}


// Corresponds to task_manager_msgs__srv__StartTask_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct StartTask_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub id: i32,

}



impl Default for StartTask_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::StartTask_Response::default())
  }
}

impl rosidl_runtime_rs::Message for StartTask_Response {
  type RmwMsg = super::srv::rmw::StartTask_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        id: msg.id,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      id: msg.id,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      id: msg.id,
    }
  }
}


// Corresponds to task_manager_msgs__srv__StopTask_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct StopTask_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub id: i32,

}



impl Default for StopTask_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::StopTask_Request::default())
  }
}

impl rosidl_runtime_rs::Message for StopTask_Request {
  type RmwMsg = super::srv::rmw::StopTask_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        id: msg.id,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      id: msg.id,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      id: msg.id,
    }
  }
}


// Corresponds to task_manager_msgs__srv__StopTask_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct StopTask_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub id: i32,

}



impl Default for StopTask_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::StopTask_Response::default())
  }
}

impl rosidl_runtime_rs::Message for StopTask_Response {
  type RmwMsg = super::srv::rmw::StopTask_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        id: msg.id,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      id: msg.id,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      id: msg.id,
    }
  }
}


// Corresponds to task_manager_msgs__srv__GetTaskList_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetTaskList_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub structure_needs_at_least_one_member: u8,

}



impl Default for GetTaskList_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GetTaskList_Request::default())
  }
}

impl rosidl_runtime_rs::Message for GetTaskList_Request {
  type RmwMsg = super::srv::rmw::GetTaskList_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        structure_needs_at_least_one_member: msg.structure_needs_at_least_one_member,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      structure_needs_at_least_one_member: msg.structure_needs_at_least_one_member,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      structure_needs_at_least_one_member: msg.structure_needs_at_least_one_member,
    }
  }
}


// Corresponds to task_manager_msgs__srv__GetTaskList_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetTaskList_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub tlist: Vec<super::msg::TaskDescription>,

}



impl Default for GetTaskList_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::GetTaskList_Response::default())
  }
}

impl rosidl_runtime_rs::Message for GetTaskList_Response {
  type RmwMsg = super::srv::rmw::GetTaskList_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        tlist: msg.tlist
          .into_iter()
          .map(|elem| super::msg::TaskDescription::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        tlist: msg.tlist
          .iter()
          .map(|elem| super::msg::TaskDescription::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      tlist: msg.tlist
          .into_iter()
          .map(super::msg::TaskDescription::from_rmw_message)
          .collect(),
    }
  }
}






#[link(name = "task_manager_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__task_manager_msgs__srv__GetAllTaskStatus() -> *const std::ffi::c_void;
}

// Corresponds to task_manager_msgs__srv__GetAllTaskStatus
#[allow(missing_docs, non_camel_case_types)]
pub struct GetAllTaskStatus;

impl rosidl_runtime_rs::Service for GetAllTaskStatus {
    type Request = GetAllTaskStatus_Request;
    type Response = GetAllTaskStatus_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__task_manager_msgs__srv__GetAllTaskStatus() }
    }
}




#[link(name = "task_manager_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__task_manager_msgs__srv__StartTask() -> *const std::ffi::c_void;
}

// Corresponds to task_manager_msgs__srv__StartTask
#[allow(missing_docs, non_camel_case_types)]
pub struct StartTask;

impl rosidl_runtime_rs::Service for StartTask {
    type Request = StartTask_Request;
    type Response = StartTask_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__task_manager_msgs__srv__StartTask() }
    }
}




#[link(name = "task_manager_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__task_manager_msgs__srv__StopTask() -> *const std::ffi::c_void;
}

// Corresponds to task_manager_msgs__srv__StopTask
#[allow(missing_docs, non_camel_case_types)]
pub struct StopTask;

impl rosidl_runtime_rs::Service for StopTask {
    type Request = StopTask_Request;
    type Response = StopTask_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__task_manager_msgs__srv__StopTask() }
    }
}




#[link(name = "task_manager_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__task_manager_msgs__srv__GetTaskList() -> *const std::ffi::c_void;
}

// Corresponds to task_manager_msgs__srv__GetTaskList
#[allow(missing_docs, non_camel_case_types)]
pub struct GetTaskList;

impl rosidl_runtime_rs::Service for GetTaskList {
    type Request = GetTaskList_Request;
    type Response = GetTaskList_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__task_manager_msgs__srv__GetTaskList() }
    }
}


