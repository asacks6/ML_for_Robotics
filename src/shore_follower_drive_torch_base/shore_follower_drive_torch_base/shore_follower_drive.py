#!/usr/bin/env python3

import pytorch_models_base.venv_hack
from pytorch_models_base.model import CNNModel

import sys
import os

import rclpy
from rclpy.node import Node
from rclpy.time import Time

from sensor_msgs.msg import Image
from geometry_msgs.msg import Twist

import torch
import numpy as np

import cv2
# cv_bridge2 is a local version of cv_bridge compiled with numpy 2
from cv_bridge2 import CvBridge, CvBridgeError
from enum import Enum

class Direction(Enum):
    LEFT = 0
    STRAIGHT = 1
    RIGHT = 2


class ShoreFollowerDrive(Node):
    def __init__(self):
        super().__init__("classify")

        self.declare_parameter('~/model', "")
        self.declare_parameter('~/linear_vel', 1.0)
        self.declare_parameter('~/twist_factor', 1.0)
        self.declare_parameter('~/mean', "")
        self.declare_parameter('~/std', "")
        self.declare_parameter('~/dropout', 0.2)
        self.declare_parameter('~/regression', False)
        self.model_ = self.get_parameter('~/model').get_parameter_value().string_value
        self.regression_ = self.get_parameter('~/regression').get_parameter_value().bool_value
        self.linear_vel_ = self.get_parameter('~/linear_vel').get_parameter_value().double_value
        self.twist_factor_ = self.get_parameter('~/twist_factor').get_parameter_value().double_value
        self.mean_str = self.get_parameter('~/mean').get_parameter_value().string_value
        self.std_str = self.get_parameter('~/std').get_parameter_value().string_value
        self.mean = [float(x) for x in self.mean_str.split(",") if len(x) > 0]
        self.std = [float(x) for x in self.std_str.split(",") if len(x) > 0]
        self.dropout = self.get_parameter('~/dropout').get_parameter_value().double_value

        self.load_model()

        self.br = CvBridge()
        self.twist_pub_ = self.create_publisher(Twist,"~/twist",1)
        self.image_sub_ = self.create_subscription(Image,"~/image", self.image_callback, 1)

    def load_model(self):
        # Loads the model
        device = torch.device('cpu')
        self.get_logger().info("Loding pytorch model '"+self.model_+"'")
        # TODO: fix the model loading parameters
        # Mismos argumentos que en train.py
        if self.regression_:
            num_classes = 1
            self.model = CNNModel(3, num_classes, self.dropout)
        else:
            num_classes = 3
            self.model = CNNModel(3, num_classes, self.dropout)
        self.model.load_state_dict(torch.load(self.model_, weights_only=True, map_location=device))
        self.model.eval()
        self.get_logger().info("Model loaded, ready to run")

    def image_callback(self, data):
        # Image call back and resize to proper shape
        # Regularization is done directly inside the model so we don't have to do it.
        raw = self.br.imgmsg_to_cv2(data,"bgr8")
        processed_ = np.expand_dims(cv2.resize(raw, (0,0), fx = 32.0/data.height, fy=32.0/data.width, interpolation=cv2.INTER_AREA), axis=0)
        self.twist_pub_.publish(self.image_to_rot(processed_))

    def image_to_rot(self, img):
        # Reads the image, feed it to the network, get the predictions and act on it.
        out = Twist()
        # always move forward
        out.linear.x += self.linear_vel_
        # Runs the network
        img = np.rollaxis(img, 3, 1)
        img = torch.from_numpy(img.astype(np.float32)/255.)
        res = self.model(img).detach().numpy()
        if self.regression_:
            # TODO: compute the output command from z assuming the network is 
            # trained to perform a regression task
            out.angular.z = self.twist_factor_ * float(res[0, 0])
        else:
            # TODO: compute the output command from z assuming the network is 
            # a regression task
            # shore_follower_observe guarda 0 si angular.z < -umbral y 2 si > umbral.
            # Usamos la esperanza del giro en vez del argmax para suavizar el control
            out.angular.z = self.twist_factor_ * float(res[0, 2] - res[0, 0])
        return out


def main(args=None):
    rclpy.init(args=args)

    drive = ShoreFollowerDrive()

    rclpy.spin(drive)

    drive.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
