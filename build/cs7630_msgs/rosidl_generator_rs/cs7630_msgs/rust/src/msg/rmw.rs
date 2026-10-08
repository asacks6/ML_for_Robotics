#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "cs7630_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cs7630_msgs__msg__ROIArray() -> *const std::ffi::c_void;
}

#[link(name = "cs7630_msgs__rosidl_generator_c")]
extern "C" {
    fn cs7630_msgs__msg__ROIArray__init(msg: *mut ROIArray) -> bool;
    fn cs7630_msgs__msg__ROIArray__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<ROIArray>, size: usize) -> bool;
    fn cs7630_msgs__msg__ROIArray__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<ROIArray>);
    fn cs7630_msgs__msg__ROIArray__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<ROIArray>, out_seq: *mut rosidl_runtime_rs::Sequence<ROIArray>) -> bool;
}

// Corresponds to cs7630_msgs__msg__ROIArray
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ROIArray {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub rois: rosidl_runtime_rs::Sequence<sensor_msgs::msg::rmw::RegionOfInterest>,

}



impl Default for ROIArray {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cs7630_msgs__msg__ROIArray__init(&mut msg as *mut _) {
        panic!("Call to cs7630_msgs__msg__ROIArray__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for ROIArray {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cs7630_msgs__msg__ROIArray__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cs7630_msgs__msg__ROIArray__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cs7630_msgs__msg__ROIArray__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for ROIArray {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for ROIArray where Self: Sized {
  const TYPE_NAME: &'static str = "cs7630_msgs/msg/ROIArray";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cs7630_msgs__msg__ROIArray() }
  }
}


#[link(name = "cs7630_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cs7630_msgs__msg__Trajectory() -> *const std::ffi::c_void;
}

#[link(name = "cs7630_msgs__rosidl_generator_c")]
extern "C" {
    fn cs7630_msgs__msg__Trajectory__init(msg: *mut Trajectory) -> bool;
    fn cs7630_msgs__msg__Trajectory__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Trajectory>, size: usize) -> bool;
    fn cs7630_msgs__msg__Trajectory__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Trajectory>);
    fn cs7630_msgs__msg__Trajectory__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Trajectory>, out_seq: *mut rosidl_runtime_rs::Sequence<Trajectory>) -> bool;
}

// Corresponds to cs7630_msgs__msg__Trajectory
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Trajectory {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub ts: rosidl_runtime_rs::Sequence<super::super::msg::rmw::TrajectoryElement>,

}



impl Default for Trajectory {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cs7630_msgs__msg__Trajectory__init(&mut msg as *mut _) {
        panic!("Call to cs7630_msgs__msg__Trajectory__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Trajectory {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cs7630_msgs__msg__Trajectory__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cs7630_msgs__msg__Trajectory__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cs7630_msgs__msg__Trajectory__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Trajectory {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Trajectory where Self: Sized {
  const TYPE_NAME: &'static str = "cs7630_msgs/msg/Trajectory";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cs7630_msgs__msg__Trajectory() }
  }
}


#[link(name = "cs7630_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cs7630_msgs__msg__TrajectoryElement() -> *const std::ffi::c_void;
}

#[link(name = "cs7630_msgs__rosidl_generator_c")]
extern "C" {
    fn cs7630_msgs__msg__TrajectoryElement__init(msg: *mut TrajectoryElement) -> bool;
    fn cs7630_msgs__msg__TrajectoryElement__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<TrajectoryElement>, size: usize) -> bool;
    fn cs7630_msgs__msg__TrajectoryElement__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<TrajectoryElement>);
    fn cs7630_msgs__msg__TrajectoryElement__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<TrajectoryElement>, out_seq: *mut rosidl_runtime_rs::Sequence<TrajectoryElement>) -> bool;
}

// Corresponds to cs7630_msgs__msg__TrajectoryElement
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct TrajectoryElement {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pose: geometry_msgs::msg::rmw::Pose,


    // This member is not documented.
    #[allow(missing_docs)]
    pub twist: geometry_msgs::msg::rmw::Twist,

}



impl Default for TrajectoryElement {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cs7630_msgs__msg__TrajectoryElement__init(&mut msg as *mut _) {
        panic!("Call to cs7630_msgs__msg__TrajectoryElement__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for TrajectoryElement {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cs7630_msgs__msg__TrajectoryElement__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cs7630_msgs__msg__TrajectoryElement__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cs7630_msgs__msg__TrajectoryElement__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for TrajectoryElement {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for TrajectoryElement where Self: Sized {
  const TYPE_NAME: &'static str = "cs7630_msgs/msg/TrajectoryElement";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cs7630_msgs__msg__TrajectoryElement() }
  }
}


#[link(name = "cs7630_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__cs7630_msgs__msg__PlaneDescription() -> *const std::ffi::c_void;
}

#[link(name = "cs7630_msgs__rosidl_generator_c")]
extern "C" {
    fn cs7630_msgs__msg__PlaneDescription__init(msg: *mut PlaneDescription) -> bool;
    fn cs7630_msgs__msg__PlaneDescription__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<PlaneDescription>, size: usize) -> bool;
    fn cs7630_msgs__msg__PlaneDescription__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<PlaneDescription>);
    fn cs7630_msgs__msg__PlaneDescription__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<PlaneDescription>, out_seq: *mut rosidl_runtime_rs::Sequence<PlaneDescription>) -> bool;
}

// Corresponds to cs7630_msgs__msg__PlaneDescription
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]

/// Describe a plane with a generic equation
/// a x + b y + c z + d = 0
/// fitness can be used to output a regression score (R^2 or other fitness)

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct PlaneDescription {

    // This member is not documented.
    #[allow(missing_docs)]
    pub a: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub b: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub c: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub d: f64,


    // This member is not documented.
    #[allow(missing_docs)]
    pub fitness: f64,

}



impl Default for PlaneDescription {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !cs7630_msgs__msg__PlaneDescription__init(&mut msg as *mut _) {
        panic!("Call to cs7630_msgs__msg__PlaneDescription__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for PlaneDescription {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cs7630_msgs__msg__PlaneDescription__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cs7630_msgs__msg__PlaneDescription__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { cs7630_msgs__msg__PlaneDescription__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for PlaneDescription {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for PlaneDescription where Self: Sized {
  const TYPE_NAME: &'static str = "cs7630_msgs/msg/PlaneDescription";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__cs7630_msgs__msg__PlaneDescription() }
  }
}


