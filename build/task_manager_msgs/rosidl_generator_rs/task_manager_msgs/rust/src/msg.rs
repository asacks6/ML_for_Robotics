#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to task_manager_msgs__msg__TaskDescription

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct TaskDescription {

    // This member is not documented.
    #[allow(missing_docs)]
    pub name: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub description: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub periodic: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub config: Vec<rcl_interfaces::msg::ParameterDescriptor>,

}



impl Default for TaskDescription {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::TaskDescription::default())
  }
}

impl rosidl_runtime_rs::Message for TaskDescription {
  type RmwMsg = super::msg::rmw::TaskDescription;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        name: msg.name.as_str().into(),
        description: msg.description.as_str().into(),
        periodic: msg.periodic,
        config: msg.config
          .into_iter()
          .map(|elem| rcl_interfaces::msg::ParameterDescriptor::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        name: msg.name.as_str().into(),
        description: msg.description.as_str().into(),
      periodic: msg.periodic,
        config: msg.config
          .iter()
          .map(|elem| rcl_interfaces::msg::ParameterDescriptor::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      name: msg.name.to_string(),
      description: msg.description.to_string(),
      periodic: msg.periodic,
      config: msg.config
          .into_iter()
          .map(rcl_interfaces::msg::ParameterDescriptor::from_rmw_message)
          .collect(),
    }
  }
}


// Corresponds to task_manager_msgs__msg__TaskParameter

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct TaskParameter {

    // This member is not documented.
    #[allow(missing_docs)]
    pub name: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub description: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub type_: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub min: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub max: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub dflt: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub value: std::string::String,

}



impl Default for TaskParameter {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::TaskParameter::default())
  }
}

impl rosidl_runtime_rs::Message for TaskParameter {
  type RmwMsg = super::msg::rmw::TaskParameter;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        name: msg.name.as_str().into(),
        description: msg.description.as_str().into(),
        type_: msg.type_.as_str().into(),
        min: msg.min.as_str().into(),
        max: msg.max.as_str().into(),
        dflt: msg.dflt.as_str().into(),
        value: msg.value.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        name: msg.name.as_str().into(),
        description: msg.description.as_str().into(),
        type_: msg.type_.as_str().into(),
        min: msg.min.as_str().into(),
        max: msg.max.as_str().into(),
        dflt: msg.dflt.as_str().into(),
        value: msg.value.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      name: msg.name.to_string(),
      description: msg.description.to_string(),
      type_: msg.type_.to_string(),
      min: msg.min.to_string(),
      max: msg.max.to_string(),
      dflt: msg.dflt.to_string(),
      value: msg.value.to_string(),
    }
  }
}


// Corresponds to task_manager_msgs__msg__TaskStatus

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct TaskStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub id: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub name: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub status: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub status_string: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub status_time: builtin_interfaces::msg::Time,


    // This member is not documented.
    #[allow(missing_docs)]
    pub plist: Vec<rcl_interfaces::msg::Parameter>,

}

impl TaskStatus {

    // This constant is not documented.
    #[allow(missing_docs)]
    pub const TASK_NEWBORN: u8 = 0;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const TASK_CONFIGURED: u8 = 1;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const TASK_INITIALISED: u8 = 2;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const TASK_RUNNING: u8 = 3;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const TASK_COMPLETED: u8 = 4;

    /// To be used as a bit mask
    pub const TASK_TERMINATED: u8 = 128;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const TASK_INTERRUPTED: u8 = 6;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const TASK_FAILED: u8 = 7;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const TASK_TIMEOUT: u8 = 8;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const TASK_CONFIGURATION_FAILED: u8 = 9;


    // This constant is not documented.
    #[allow(missing_docs)]
    pub const TASK_INITIALISATION_FAILED: u8 = 10;

}


impl Default for TaskStatus {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::TaskStatus::default())
  }
}

impl rosidl_runtime_rs::Message for TaskStatus {
  type RmwMsg = super::msg::rmw::TaskStatus;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        id: msg.id,
        name: msg.name.as_str().into(),
        status: msg.status,
        status_string: msg.status_string.as_str().into(),
        status_time: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Owned(msg.status_time)).into_owned(),
        plist: msg.plist
          .into_iter()
          .map(|elem| rcl_interfaces::msg::Parameter::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      id: msg.id,
        name: msg.name.as_str().into(),
      status: msg.status,
        status_string: msg.status_string.as_str().into(),
        status_time: builtin_interfaces::msg::Time::into_rmw_message(std::borrow::Cow::Borrowed(&msg.status_time)).into_owned(),
        plist: msg.plist
          .iter()
          .map(|elem| rcl_interfaces::msg::Parameter::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      id: msg.id,
      name: msg.name.to_string(),
      status: msg.status,
      status_string: msg.status_string.to_string(),
      status_time: builtin_interfaces::msg::Time::from_rmw_message(msg.status_time),
      plist: msg.plist
          .into_iter()
          .map(rcl_interfaces::msg::Parameter::from_rmw_message)
          .collect(),
    }
  }
}


// Corresponds to task_manager_msgs__msg__TaskConfig

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct TaskConfig {

    // This member is not documented.
    #[allow(missing_docs)]
    pub plist: Vec<rcl_interfaces::msg::Parameter>,

}



impl Default for TaskConfig {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::TaskConfig::default())
  }
}

impl rosidl_runtime_rs::Message for TaskConfig {
  type RmwMsg = super::msg::rmw::TaskConfig;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        plist: msg.plist
          .into_iter()
          .map(|elem| rcl_interfaces::msg::Parameter::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        plist: msg.plist
          .iter()
          .map(|elem| rcl_interfaces::msg::Parameter::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      plist: msg.plist
          .into_iter()
          .map(rcl_interfaces::msg::Parameter::from_rmw_message)
          .collect(),
    }
  }
}


// Corresponds to task_manager_msgs__msg__SyncStatus

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SyncStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i16,

}



impl Default for SyncStatus {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::SyncStatus::default())
  }
}

impl rosidl_runtime_rs::Message for SyncStatus {
  type RmwMsg = super::msg::rmw::SyncStatus;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        status: msg.status,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      status: msg.status,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      status: msg.status,
    }
  }
}


// Corresponds to task_manager_msgs__msg__EncapsulatedMessage

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct EncapsulatedMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub type_: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub md5sum: std::string::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub data: std::string::String,

}



impl Default for EncapsulatedMessage {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::EncapsulatedMessage::default())
  }
}

impl rosidl_runtime_rs::Message for EncapsulatedMessage {
  type RmwMsg = super::msg::rmw::EncapsulatedMessage;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        type_: msg.type_.as_str().into(),
        md5sum: msg.md5sum.as_str().into(),
        data: msg.data.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        type_: msg.type_.as_str().into(),
        md5sum: msg.md5sum.as_str().into(),
        data: msg.data.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      type_: msg.type_.to_string(),
      md5sum: msg.md5sum.to_string(),
      data: msg.data.to_string(),
    }
  }
}


