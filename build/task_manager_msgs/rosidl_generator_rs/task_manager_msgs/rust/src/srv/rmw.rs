#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "task_manager_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__srv__GetAllTaskStatus_Request() -> *const std::ffi::c_void;
}

#[link(name = "task_manager_msgs__rosidl_generator_c")]
extern "C" {
    fn task_manager_msgs__srv__GetAllTaskStatus_Request__init(msg: *mut GetAllTaskStatus_Request) -> bool;
    fn task_manager_msgs__srv__GetAllTaskStatus_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetAllTaskStatus_Request>, size: usize) -> bool;
    fn task_manager_msgs__srv__GetAllTaskStatus_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetAllTaskStatus_Request>);
    fn task_manager_msgs__srv__GetAllTaskStatus_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetAllTaskStatus_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<GetAllTaskStatus_Request>) -> bool;
}

// Corresponds to task_manager_msgs__srv__GetAllTaskStatus_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetAllTaskStatus_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub structure_needs_at_least_one_member: u8,

}



impl Default for GetAllTaskStatus_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !task_manager_msgs__srv__GetAllTaskStatus_Request__init(&mut msg as *mut _) {
        panic!("Call to task_manager_msgs__srv__GetAllTaskStatus_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetAllTaskStatus_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__srv__GetAllTaskStatus_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__srv__GetAllTaskStatus_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__srv__GetAllTaskStatus_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetAllTaskStatus_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetAllTaskStatus_Request where Self: Sized {
  const TYPE_NAME: &'static str = "task_manager_msgs/srv/GetAllTaskStatus_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__srv__GetAllTaskStatus_Request() }
  }
}


#[link(name = "task_manager_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__srv__GetAllTaskStatus_Response() -> *const std::ffi::c_void;
}

#[link(name = "task_manager_msgs__rosidl_generator_c")]
extern "C" {
    fn task_manager_msgs__srv__GetAllTaskStatus_Response__init(msg: *mut GetAllTaskStatus_Response) -> bool;
    fn task_manager_msgs__srv__GetAllTaskStatus_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetAllTaskStatus_Response>, size: usize) -> bool;
    fn task_manager_msgs__srv__GetAllTaskStatus_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetAllTaskStatus_Response>);
    fn task_manager_msgs__srv__GetAllTaskStatus_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetAllTaskStatus_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<GetAllTaskStatus_Response>) -> bool;
}

// Corresponds to task_manager_msgs__srv__GetAllTaskStatus_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetAllTaskStatus_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub running_tasks: rosidl_runtime_rs::Sequence<super::super::msg::rmw::TaskStatus>,


    // This member is not documented.
    #[allow(missing_docs)]
    pub zombie_tasks: rosidl_runtime_rs::Sequence<super::super::msg::rmw::TaskStatus>,

}



impl Default for GetAllTaskStatus_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !task_manager_msgs__srv__GetAllTaskStatus_Response__init(&mut msg as *mut _) {
        panic!("Call to task_manager_msgs__srv__GetAllTaskStatus_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetAllTaskStatus_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__srv__GetAllTaskStatus_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__srv__GetAllTaskStatus_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__srv__GetAllTaskStatus_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetAllTaskStatus_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetAllTaskStatus_Response where Self: Sized {
  const TYPE_NAME: &'static str = "task_manager_msgs/srv/GetAllTaskStatus_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__srv__GetAllTaskStatus_Response() }
  }
}


#[link(name = "task_manager_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__srv__StartTask_Request() -> *const std::ffi::c_void;
}

#[link(name = "task_manager_msgs__rosidl_generator_c")]
extern "C" {
    fn task_manager_msgs__srv__StartTask_Request__init(msg: *mut StartTask_Request) -> bool;
    fn task_manager_msgs__srv__StartTask_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<StartTask_Request>, size: usize) -> bool;
    fn task_manager_msgs__srv__StartTask_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<StartTask_Request>);
    fn task_manager_msgs__srv__StartTask_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<StartTask_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<StartTask_Request>) -> bool;
}

// Corresponds to task_manager_msgs__srv__StartTask_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct StartTask_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub name: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub config: rosidl_runtime_rs::Sequence<rcl_interfaces::msg::rmw::Parameter>,

}



impl Default for StartTask_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !task_manager_msgs__srv__StartTask_Request__init(&mut msg as *mut _) {
        panic!("Call to task_manager_msgs__srv__StartTask_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for StartTask_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__srv__StartTask_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__srv__StartTask_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__srv__StartTask_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for StartTask_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for StartTask_Request where Self: Sized {
  const TYPE_NAME: &'static str = "task_manager_msgs/srv/StartTask_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__srv__StartTask_Request() }
  }
}


#[link(name = "task_manager_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__srv__StartTask_Response() -> *const std::ffi::c_void;
}

#[link(name = "task_manager_msgs__rosidl_generator_c")]
extern "C" {
    fn task_manager_msgs__srv__StartTask_Response__init(msg: *mut StartTask_Response) -> bool;
    fn task_manager_msgs__srv__StartTask_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<StartTask_Response>, size: usize) -> bool;
    fn task_manager_msgs__srv__StartTask_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<StartTask_Response>);
    fn task_manager_msgs__srv__StartTask_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<StartTask_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<StartTask_Response>) -> bool;
}

// Corresponds to task_manager_msgs__srv__StartTask_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct StartTask_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub id: i32,

}



impl Default for StartTask_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !task_manager_msgs__srv__StartTask_Response__init(&mut msg as *mut _) {
        panic!("Call to task_manager_msgs__srv__StartTask_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for StartTask_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__srv__StartTask_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__srv__StartTask_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__srv__StartTask_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for StartTask_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for StartTask_Response where Self: Sized {
  const TYPE_NAME: &'static str = "task_manager_msgs/srv/StartTask_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__srv__StartTask_Response() }
  }
}


#[link(name = "task_manager_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__srv__StopTask_Request() -> *const std::ffi::c_void;
}

#[link(name = "task_manager_msgs__rosidl_generator_c")]
extern "C" {
    fn task_manager_msgs__srv__StopTask_Request__init(msg: *mut StopTask_Request) -> bool;
    fn task_manager_msgs__srv__StopTask_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<StopTask_Request>, size: usize) -> bool;
    fn task_manager_msgs__srv__StopTask_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<StopTask_Request>);
    fn task_manager_msgs__srv__StopTask_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<StopTask_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<StopTask_Request>) -> bool;
}

// Corresponds to task_manager_msgs__srv__StopTask_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct StopTask_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub id: i32,

}



impl Default for StopTask_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !task_manager_msgs__srv__StopTask_Request__init(&mut msg as *mut _) {
        panic!("Call to task_manager_msgs__srv__StopTask_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for StopTask_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__srv__StopTask_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__srv__StopTask_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__srv__StopTask_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for StopTask_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for StopTask_Request where Self: Sized {
  const TYPE_NAME: &'static str = "task_manager_msgs/srv/StopTask_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__srv__StopTask_Request() }
  }
}


#[link(name = "task_manager_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__srv__StopTask_Response() -> *const std::ffi::c_void;
}

#[link(name = "task_manager_msgs__rosidl_generator_c")]
extern "C" {
    fn task_manager_msgs__srv__StopTask_Response__init(msg: *mut StopTask_Response) -> bool;
    fn task_manager_msgs__srv__StopTask_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<StopTask_Response>, size: usize) -> bool;
    fn task_manager_msgs__srv__StopTask_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<StopTask_Response>);
    fn task_manager_msgs__srv__StopTask_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<StopTask_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<StopTask_Response>) -> bool;
}

// Corresponds to task_manager_msgs__srv__StopTask_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct StopTask_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub id: i32,

}



impl Default for StopTask_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !task_manager_msgs__srv__StopTask_Response__init(&mut msg as *mut _) {
        panic!("Call to task_manager_msgs__srv__StopTask_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for StopTask_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__srv__StopTask_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__srv__StopTask_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__srv__StopTask_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for StopTask_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for StopTask_Response where Self: Sized {
  const TYPE_NAME: &'static str = "task_manager_msgs/srv/StopTask_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__srv__StopTask_Response() }
  }
}


#[link(name = "task_manager_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__srv__GetTaskList_Request() -> *const std::ffi::c_void;
}

#[link(name = "task_manager_msgs__rosidl_generator_c")]
extern "C" {
    fn task_manager_msgs__srv__GetTaskList_Request__init(msg: *mut GetTaskList_Request) -> bool;
    fn task_manager_msgs__srv__GetTaskList_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetTaskList_Request>, size: usize) -> bool;
    fn task_manager_msgs__srv__GetTaskList_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetTaskList_Request>);
    fn task_manager_msgs__srv__GetTaskList_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetTaskList_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<GetTaskList_Request>) -> bool;
}

// Corresponds to task_manager_msgs__srv__GetTaskList_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetTaskList_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub structure_needs_at_least_one_member: u8,

}



impl Default for GetTaskList_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !task_manager_msgs__srv__GetTaskList_Request__init(&mut msg as *mut _) {
        panic!("Call to task_manager_msgs__srv__GetTaskList_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetTaskList_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__srv__GetTaskList_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__srv__GetTaskList_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__srv__GetTaskList_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetTaskList_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetTaskList_Request where Self: Sized {
  const TYPE_NAME: &'static str = "task_manager_msgs/srv/GetTaskList_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__srv__GetTaskList_Request() }
  }
}


#[link(name = "task_manager_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__srv__GetTaskList_Response() -> *const std::ffi::c_void;
}

#[link(name = "task_manager_msgs__rosidl_generator_c")]
extern "C" {
    fn task_manager_msgs__srv__GetTaskList_Response__init(msg: *mut GetTaskList_Response) -> bool;
    fn task_manager_msgs__srv__GetTaskList_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<GetTaskList_Response>, size: usize) -> bool;
    fn task_manager_msgs__srv__GetTaskList_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<GetTaskList_Response>);
    fn task_manager_msgs__srv__GetTaskList_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<GetTaskList_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<GetTaskList_Response>) -> bool;
}

// Corresponds to task_manager_msgs__srv__GetTaskList_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct GetTaskList_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub tlist: rosidl_runtime_rs::Sequence<super::super::msg::rmw::TaskDescription>,

}



impl Default for GetTaskList_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !task_manager_msgs__srv__GetTaskList_Response__init(&mut msg as *mut _) {
        panic!("Call to task_manager_msgs__srv__GetTaskList_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for GetTaskList_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__srv__GetTaskList_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__srv__GetTaskList_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { task_manager_msgs__srv__GetTaskList_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for GetTaskList_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for GetTaskList_Response where Self: Sized {
  const TYPE_NAME: &'static str = "task_manager_msgs/srv/GetTaskList_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__task_manager_msgs__srv__GetTaskList_Response() }
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


