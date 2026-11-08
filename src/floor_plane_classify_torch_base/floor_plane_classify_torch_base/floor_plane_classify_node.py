#!/usr/bin/env python3

import pytorch_models_base.venv_hack
from pytorch_models_base.model import CNNModel

import sys
import os

import rclpy
from rclpy.node import Node
from rclpy.time import Time

from sensor_msgs.msg import Image

import torch
import numpy as np

from sensor_msgs.msg import Image

import cv2
# cv_bridge2 is a local version of cv_bridge compiled with numpy 2
from cv_bridge2 import CvBridge, CvBridgeError


class FloorPlaneClassify(Node):
    def __init__(self):
        super().__init__("classify")

        self.declare_parameter('~/model', ".")
        self.declare_parameter('~/thumb_size', 32)
        self.declare_parameter('~/mean', "")
        self.declare_parameter('~/std', "")
        self.declare_parameter('~/dropout', 0.2)
        self.model_ = self.get_parameter('~/model').get_parameter_value().string_value
        self.ts_ = self.get_parameter('~/thumb_size').get_parameter_value().integer_value
        self.mean_str = self.get_parameter('~/mean').get_parameter_value().string_value
        self.std_str = self.get_parameter('~/std').get_parameter_value().string_value
        self.mean = [float(x) for x in self.mean_str.split(",") if len(x) > 0]
        self.std = [float(x) for x in self.std_str.split(",") if len(x) > 0]
        self.dropout = self.get_parameter('~/dropout').get_parameter_value().double_value

        self.load_model()

        self.br = CvBridge()
        self.image_pub_ = self.create_publisher(Image,"~/image_label",1)
        self.image_sub_ = self.create_subscription(Image,"~/image", self.image_callback, 1)

    def load_model(self):
        # Loads the model
        self.get_logger().info("Loding pytorch model")
        # TODO: Fix the model loading parameters
        # Mismos argumentos que en train.py: imagen BGR de 3 canales, 2 clases
        num_channels = 3
        num_classes = 2
        self.model = CNNModel(num_channels, num_classes, self.dropout)
        # El modelo se entrena en GPU, aqui corre en CPU
        self.model.load_state_dict(torch.load(self.model_, weights_only=True, map_location='cpu'))
        self.model.eval()
        self.get_logger().info("Model loaded, ready to run")

    def reshape_split(self, image, kernel_size):
        img_height, img_width, channels = image.shape
        tile_heigth, tile_width = kernel_size
        tiled_array = image.reshape(img_height // tile_heigth,
                                    tile_heigth,
                                    img_width // tile_width,
                                    tile_width,
                                    channels)
        tiled_array = tiled_array.swapaxes(1, 2)
        return tiled_array.reshape(-1, self.ts_, self.ts_, 3)

    def image_callback(self, data):
        # Gets the image, check that it is square and divisible by the thumbnail size
        assert(data.height == data.width)
        assert(data.height%self.ts_ == 0)
        # Convert to np array
        img = self.br.imgmsg_to_cv2(data,"bgr8")
        # Reshape the image as a batch of thumbnails (faster processing when using batches)
        batch = self.reshape_split(img, (self.ts_, self.ts_))
        # Calls the network
        checked = self.check_thumb(batch)
        # Transforms the array into low resolution image (one pixel per thumbnail)
        low_res = np.reshape(checked,[data.height//self.ts_,data.width//self.ts_,3])
        # Upsamples the predictions so they have the same size as the input image
        classified = cv2.resize(low_res,(0,0),fx=self.ts_,fy=self.ts_, interpolation=cv2.INTER_NEAREST).astype(np.uint8)
        overlay = cv2.addWeighted(img, 0.5, classified, 0.5, 0)
        # Publish the result
        enc = self.br.cv2_to_imgmsg(overlay,"passthrough")
        self.image_pub_.publish(enc)


    def check_thumb(self, batch):
        # Run the network
        batch = np.rollaxis(batch, 3, 1)
        # reader.py entrena con pixeles en [0,1]
        batch = torch.from_numpy(batch.astype(np.float32)/255.)
        res = self.model(batch).detach().numpy()
        # Makes sure that the output has the proper shape
        # Returns a numpy array of dimension (res.shape[0],3)
        #TODO : Use network output to determine traversability (idealy levaraging vector-wise operation in numpy)
        # Etiqueta 1 = transitable (verde), 0 = intransitable (rojo), colores en BGR
        colors = np.array([[0, 0, 255], [0, 255, 0]], dtype=np.uint8)
        return colors[np.argmax(res, axis=1)]

def main(args=None):
    rclpy.init(args=args)

    classify = FloorPlaneClassify()

    rclpy.spin(classify)

    classify.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
