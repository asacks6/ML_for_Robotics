#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to cs7630_msgs__msg__ROIArray

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct ROIArray {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub rois: Vec<sensor_msgs::msg::RegionOfInterest>,

}



impl Default for ROIArray {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::ROIArray::default())
  }
}

impl rosidl_runtime_rs::Message for ROIArray {
  type RmwMsg = super::msg::rmw::ROIArray;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        rois: msg.rois
          .into_iter()
          .map(|elem| sensor_msgs::msg::RegionOfInterest::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        rois: msg.rois
          .iter()
          .map(|elem| sensor_msgs::msg::RegionOfInterest::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      rois: msg.rois
          .into_iter()
          .map(sensor_msgs::msg::RegionOfInterest::from_rmw_message)
          .collect(),
    }
  }
}


// Corresponds to cs7630_msgs__msg__Trajectory

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Trajectory {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub ts: Vec<super::msg::TrajectoryElement>,

}



impl Default for Trajectory {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::Trajectory::default())
  }
}

impl rosidl_runtime_rs::Message for Trajectory {
  type RmwMsg = super::msg::rmw::Trajectory;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        ts: msg.ts
          .into_iter()
          .map(|elem| super::msg::TrajectoryElement::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        ts: msg.ts
          .iter()
          .map(|elem| super::msg::TrajectoryElement::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      ts: msg.ts
          .into_iter()
          .map(super::msg::TrajectoryElement::from_rmw_message)
          .collect(),
    }
  }
}


// Corresponds to cs7630_msgs__msg__TrajectoryElement

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct TrajectoryElement {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub pose: geometry_msgs::msg::Pose,


    // This member is not documented.
    #[allow(missing_docs)]
    pub twist: geometry_msgs::msg::Twist,

}



impl Default for TrajectoryElement {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::TrajectoryElement::default())
  }
}

impl rosidl_runtime_rs::Message for TrajectoryElement {
  type RmwMsg = super::msg::rmw::TrajectoryElement;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        pose: geometry_msgs::msg::Pose::into_rmw_message(std::borrow::Cow::Owned(msg.pose)).into_owned(),
        twist: geometry_msgs::msg::Twist::into_rmw_message(std::borrow::Cow::Owned(msg.twist)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        pose: geometry_msgs::msg::Pose::into_rmw_message(std::borrow::Cow::Borrowed(&msg.pose)).into_owned(),
        twist: geometry_msgs::msg::Twist::into_rmw_message(std::borrow::Cow::Borrowed(&msg.twist)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      pose: geometry_msgs::msg::Pose::from_rmw_message(msg.pose),
      twist: geometry_msgs::msg::Twist::from_rmw_message(msg.twist),
    }
  }
}


// Corresponds to cs7630_msgs__msg__PlaneDescription
/// Describe a plane with a generic equation
/// a x + b y + c z + d = 0
/// fitness can be used to output a regression score (R^2 or other fitness)

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::PlaneDescription::default())
  }
}

impl rosidl_runtime_rs::Message for PlaneDescription {
  type RmwMsg = super::msg::rmw::PlaneDescription;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        a: msg.a,
        b: msg.b,
        c: msg.c,
        d: msg.d,
        fitness: msg.fitness,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      a: msg.a,
      b: msg.b,
      c: msg.c,
      d: msg.d,
      fitness: msg.fitness,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      a: msg.a,
      b: msg.b,
      c: msg.c,
      d: msg.d,
      fitness: msg.fitness,
    }
  }
}


