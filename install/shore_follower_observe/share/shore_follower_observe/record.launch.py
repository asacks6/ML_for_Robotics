# Copyright (c) 2008, Willow Garage, Inc.
# All rights reserved.
#
# Software License Agreement (BSD License 2.0)
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above
#    copyright notice, this list of conditions and the following
#    disclaimer in the documentation and/or other materials provided
#    with the distribution.
#  * Neither the name of the Willow Garage nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

import os
import time

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription, DeclareLaunchArgument, OpaqueFunction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration

import launch_ros.actions
import launch_ros.descriptions


def launch_setup(context):
    # El nodo reinicia labels.txt al arrancar: cada sesion va en su propia carpeta
    out_dir = os.path.expanduser(LaunchConfiguration('out_dir').perform(context))
    os.makedirs(out_dir, exist_ok=True)
    return [
        launch_ros.actions.Node(
            package='shore_follower_observe', executable='shore_follower_observe', name='shore_follower_observe',
            parameters=[
                {'~/base_frame': 'bubbleRob'},
                {'~/world_frame': 'world'},
                {'~/out_dir': out_dir},
                {'~/rotation_threshold': 0.2},
                {'~/min_displacement': 0.1},
                {'~/min_rotation': 0.1},
                {'~/max_image_per_type': 1000},
                {'~/joystick_button': 3},
                ],
            remappings=[
                ('~/joy', '/joy'),
                ('~/image', '/vrep/kision/image'),
                ('~/twist', '/vrep/twistCommand'),
                ],
            output='screen'),
    ]


def generate_launch_description():
    default_dir = '~/data/shore_follower/raw_' + time.strftime('%Y%m%d_%H%M%S')
    return LaunchDescription([
        DeclareLaunchArgument('out_dir', default_value=default_dir,
            description='output folder for images and labels.txt'),
        OpaqueFunction(function=launch_setup),
    ])
