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

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction, LogInfo
from launch.substitutions import LaunchConfiguration

import launch_ros.actions
import launch_ros.descriptions


def launch_setup(context):
    # El nodo reinicia labels.txt al arrancar: cada sesion va en su propia carpeta
    out_dir = LaunchConfiguration('out_dir').perform(context)
    if out_dir == '':
        out_dir = '~/ros_workspace/src/final_project/data/%s/raw_%s' % (
                LaunchConfiguration('name').perform(context), time.strftime('%Y%m%d_%H%M%S'))
    out_dir = os.path.expanduser(out_dir)
    os.makedirs(out_dir, exist_ok=True)
    return [
        LogInfo(msg='Recording into ' + out_dir),
        launch_ros.actions.Node(
            package='vsv_shore_observe', executable='vsv_shore_observe', name='vsv_shore_observe',
            parameters=[
                # El nodo mira cuanto se ha movido world_frame visto desde base_frame. Asi es la
                # posicion de la herramienta en el mundo: cambia con el camion y con el brazo
                {'~/base_frame': 'world'},
                {'~/world_frame': 'VSV/Tool'},
                {'~/out_dir': out_dir},
                # Etiqueta: velocidad lateral del brazo (m/s), 0 hacia el camion, 1 quieto, 2 hacia fuera
                {'~/command_field': 'linear.x'},
                {'~/rotation_threshold': 0.05},
                {'~/min_displacement': 0.05},
                {'~/min_rotation': 0.05},
                {'~/max_image_per_type': 1500},
                {'~/joystick_button': int(LaunchConfiguration('pause_button').perform(context))},
                ],
            remappings=[
                ('~/joy', '/joy'),
                ('~/image', '/vrep/kision/image'),
                # Orden de la persona en modo ensenanza, antes del limite de alcance del brazo
                ('~/twist', '/arm_follower/demo_twist'),
                ],
            output='screen'),
    ]


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument('name', default_value='arm',
            description='dataset name: images go to final_project/data/<name>/raw_<date>'),
        DeclareLaunchArgument('out_dir', default_value='',
            description='output folder for images and labels.txt (overrides name)'),
        DeclareLaunchArgument('pause_button', default_value='4',
            description='joystick button that pauses and resumes the recording (Y on the SHANWAN pad)'),
        OpaqueFunction(function=launch_setup),
    ])
