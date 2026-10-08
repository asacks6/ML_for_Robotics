#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "task_manager_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__msg__TaskDescription() -> *const std::ffi::c_void;
}

#[link(name = "task_manager_msgs__rosidl_generator_c")]
extern "C" {
    fn task_manager_msgs__msg__TaskDescription__init(msg: *mut TaskDescription) -> bool;
    fn task_manager_msgs__msg__TaskDescription__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<TaskDescription>, size: usize) -> bool;
    fn task_manager_msgs__msg__TaskDescription__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<TaskDescription>);
    fn task_manager_msgs__msg__TaskDescription__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<TaskDescription>, out_seq: *mut rosidl_runtime_rs::Sequence<TaskDescription>) -> bool;
}

// Corresponds to task_manager_msgs__msg__TaskDescription
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct TaskDescription {

    // This member is not documented.
    #[allow(missing_docs)]
    pub name: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub description: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub periodic: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub config: rosidl_runtime_rs::Sequence<rcl_interfaces::msg::rmw::ParameterDescriptor>,

}



impl Default for TaskDescription {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !task_manager_msgs__msg__TaskDescription__init(&mut msg as *mut _) {
        panic!("Call to task_manager_msgs__msg__TaskDescription__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for TaskDescription {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__msg__TaskDescription__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__msg__TaskDescription__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__msg__TaskDescription__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for TaskDescription {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for TaskDescription where Self: Sized {
  const TYPE_NAME: &'static str = "task_manager_msgs/msg/TaskDescription";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__msg__TaskDescription() }
  }
}


#[link(name = "task_manager_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__msg__TaskParameter() -> *const std::ffi::c_void;
}

#[link(name = "task_manager_msgs__rosidl_generator_c")]
extern "C" {
    fn task_manager_msgs__msg__TaskParameter__init(msg: *mut TaskParameter) -> bool;
    fn task_manager_msgs__msg__TaskParameter__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<TaskParameter>, size: usize) -> bool;
    fn task_manager_msgs__msg__TaskParameter__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<TaskParameter>);
    fn task_manager_msgs__msg__TaskParameter__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<TaskParameter>, out_seq: *mut rosidl_runtime_rs::Sequence<TaskParameter>) -> bool;
}

// Corresponds to task_manager_msgs__msg__TaskParameter
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct TaskParameter {

    // This member is not documented.
    #[allow(missing_docs)]
    pub name: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub description: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub type_: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub min: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub max: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub dflt: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub value: rosidl_runtime_rs::String,

}



impl Default for TaskParameter {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !task_manager_msgs__msg__TaskParameter__init(&mut msg as *mut _) {
        panic!("Call to task_manager_msgs__msg__TaskParameter__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for TaskParameter {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__msg__TaskParameter__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__msg__TaskParameter__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__msg__TaskParameter__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for TaskParameter {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for TaskParameter where Self: Sized {
  const TYPE_NAME: &'static str = "task_manager_msgs/msg/TaskParameter";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__msg__TaskParameter() }
  }
}


#[link(name = "task_manager_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__msg__TaskStatus() -> *const std::ffi::c_void;
}

#[link(name = "task_manager_msgs__rosidl_generator_c")]
extern "C" {
    fn task_manager_msgs__msg__TaskStatus__init(msg: *mut TaskStatus) -> bool;
    fn task_manager_msgs__msg__TaskStatus__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<TaskStatus>, size: usize) -> bool;
    fn task_manager_msgs__msg__TaskStatus__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<TaskStatus>);
    fn task_manager_msgs__msg__TaskStatus__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<TaskStatus>, out_seq: *mut rosidl_runtime_rs::Sequence<TaskStatus>) -> bool;
}

// Corresponds to task_manager_msgs__msg__TaskStatus
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct TaskStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub id: u32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub name: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub status: u8,


    // This member is not documented.
    #[allow(missing_docs)]
    pub status_string: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub status_time: builtin_interfaces::msg::rmw::Time,


    // This member is not documented.
    #[allow(missing_docs)]
    pub plist: rosidl_runtime_rs::Sequence<rcl_interfaces::msg::rmw::Parameter>,

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
    unsafe {
      let mut msg = std::mem::zeroed();
      if !task_manager_msgs__msg__TaskStatus__init(&mut msg as *mut _) {
        panic!("Call to task_manager_msgs__msg__TaskStatus__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for TaskStatus {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__msg__TaskStatus__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__msg__TaskStatus__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__msg__TaskStatus__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for TaskStatus {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for TaskStatus where Self: Sized {
  const TYPE_NAME: &'static str = "task_manager_msgs/msg/TaskStatus";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__msg__TaskStatus() }
  }
}


#[link(name = "task_manager_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__msg__TaskConfig() -> *const std::ffi::c_void;
}

#[link(name = "task_manager_msgs__rosidl_generator_c")]
extern "C" {
    fn task_manager_msgs__msg__TaskConfig__init(msg: *mut TaskConfig) -> bool;
    fn task_manager_msgs__msg__TaskConfig__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<TaskConfig>, size: usize) -> bool;
    fn task_manager_msgs__msg__TaskConfig__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<TaskConfig>);
    fn task_manager_msgs__msg__TaskConfig__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<TaskConfig>, out_seq: *mut rosidl_runtime_rs::Sequence<TaskConfig>) -> bool;
}

// Corresponds to task_manager_msgs__msg__TaskConfig
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct TaskConfig {

    // This member is not documented.
    #[allow(missing_docs)]
    pub plist: rosidl_runtime_rs::Sequence<rcl_interfaces::msg::rmw::Parameter>,

}



impl Default for TaskConfig {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !task_manager_msgs__msg__TaskConfig__init(&mut msg as *mut _) {
        panic!("Call to task_manager_msgs__msg__TaskConfig__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for TaskConfig {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__msg__TaskConfig__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__msg__TaskConfig__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__msg__TaskConfig__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for TaskConfig {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for TaskConfig where Self: Sized {
  const TYPE_NAME: &'static str = "task_manager_msgs/msg/TaskConfig";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__msg__TaskConfig() }
  }
}


#[link(name = "task_manager_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__msg__SyncStatus() -> *const std::ffi::c_void;
}

#[link(name = "task_manager_msgs__rosidl_generator_c")]
extern "C" {
    fn task_manager_msgs__msg__SyncStatus__init(msg: *mut SyncStatus) -> bool;
    fn task_manager_msgs__msg__SyncStatus__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SyncStatus>, size: usize) -> bool;
    fn task_manager_msgs__msg__SyncStatus__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SyncStatus>);
    fn task_manager_msgs__msg__SyncStatus__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SyncStatus>, out_seq: *mut rosidl_runtime_rs::Sequence<SyncStatus>) -> bool;
}

// Corresponds to task_manager_msgs__msg__SyncStatus
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SyncStatus {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub status: i16,

}



impl Default for SyncStatus {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !task_manager_msgs__msg__SyncStatus__init(&mut msg as *mut _) {
        panic!("Call to task_manager_msgs__msg__SyncStatus__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SyncStatus {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__msg__SyncStatus__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__msg__SyncStatus__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__msg__SyncStatus__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SyncStatus {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SyncStatus where Self: Sized {
  const TYPE_NAME: &'static str = "task_manager_msgs/msg/SyncStatus";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__msg__SyncStatus() }
  }
}


#[link(name = "task_manager_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__msg__EncapsulatedMessage() -> *const std::ffi::c_void;
}

#[link(name = "task_manager_msgs__rosidl_generator_c")]
extern "C" {
    fn task_manager_msgs__msg__EncapsulatedMessage__init(msg: *mut EncapsulatedMessage) -> bool;
    fn task_manager_msgs__msg__EncapsulatedMessage__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<EncapsulatedMessage>, size: usize) -> bool;
    fn task_manager_msgs__msg__EncapsulatedMessage__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<EncapsulatedMessage>);
    fn task_manager_msgs__msg__EncapsulatedMessage__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<EncapsulatedMessage>, out_seq: *mut rosidl_runtime_rs::Sequence<EncapsulatedMessage>) -> bool;
}

// Corresponds to task_manager_msgs__msg__EncapsulatedMessage
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct EncapsulatedMessage {

    // This member is not documented.
    #[allow(missing_docs)]
    pub type_: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub md5sum: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub data: rosidl_runtime_rs::String,

}



impl Default for EncapsulatedMessage {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !task_manager_msgs__msg__EncapsulatedMessage__init(&mut msg as *mut _) {
        panic!("Call to task_manager_msgs__msg__EncapsulatedMessage__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for EncapsulatedMessage {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__msg__EncapsulatedMessage__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__msg__EncapsulatedMessage__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__msg__EncapsulatedMessage__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for EncapsulatedMessage {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for EncapsulatedMessage where Self: Sized {
  const TYPE_NAME: &'static str = "task_manager_msgs/msg/EncapsulatedMessage";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__msg__EncapsulatedMessage() }
  }
}


