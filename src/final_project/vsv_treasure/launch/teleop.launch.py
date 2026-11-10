# Adapted from vrep_vsv_driver/launch/vsv_geom_mux.launch.py: same nodes, with the
# joystick axes and buttons as arguments (defaults for the SHANWAN gamepad).

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration

import launch_ros.actions
import launch_ros.descriptions

# Botones del mando SHANWAN: A=0 B=1 X=3 Y=4 LB=6 RB=7 LT=8 RT=9
ARGUMENTS = [
    ('joy', 'true', 'start the joystick driver'),
    ('axis_arm_x', '2', 'right stick left/right: arm tip lateral velocity'),
    ('axis_arm_y', '6', 'cross left/right: arm tip forward velocity'),
    ('axis_arm_z', '3', 'right stick up/down: arm tip vertical velocity'),
    ('arm_velocity', '0.4', 'arm tip velocity at full stick (m/s)'),
    ('ready_button', '0', 'A: deploy the arm'),
    ('home_button', '1', 'B: park the arm'),
    ('move_button', '3', 'X: control the arm tip with the stick'),
    ('base_joystick_button', '6', 'LB: the joystick drives the truck'),
    ('base_auto_button', '7', 'RB: the truck drives itself'),
    ('arm_joystick_button', '8', 'LT: the joystick moves the arm'),
    ('arm_auto_button', '9', 'RT: the arm moves itself'),
]


def launch_setup(context):
    def arg(name):
        return LaunchConfiguration(name).perform(context)

    return [
        launch_ros.actions.Node(
            package='joy', executable='joy_node', name='joy',
            parameters=[
                {'autorepeat_rate': 10.},
                ],
            condition=IfCondition(LaunchConfiguration('joy')),
            output='screen'),

        launch_ros.actions.Node(
            package='topic_tools', executable='mux', name='base_mux',
            arguments=['/vsv_driver/twistCommand','/teleop_base/twistCommand','/base_mux/autoCommand'],
            parameters=[
                {'output_topic': '/vsv_driver/twistCommand'},
                {'input_topics': ['/teleop_base/twistCommand','/base_mux/autoCommand']},
                ],
            remappings=[
                ('/mux', '/base_mux'),
                ],
            output='screen'),

        launch_ros.actions.Node(
            package='topic_tools', executable='mux', name='arm_mux',
            arguments=['/arm_ik/twist','/teleop_arm/twistCommand','/arm_mux/autoCommand'],
            parameters=[
                {'output_topic': '/arm_ik/twist'},
                {'input_topics': ['/teleop_arm/twistCommand','/arm_mux/autoCommand']},
                ],
            remappings=[
                ('/mux', '/arm_mux'),
                ],
            output='screen'),

        launch_ros.actions.Node(
            package='vrep_ros_teleop', executable='teleop_mux_node', name='teleop_base_mux',
            parameters=[
                {'~/joystick_button': int(arg('base_joystick_button'))},
                {'~/joystick_topic': '/teleop_base/twistCommand'},
                {'~/auto_button': int(arg('base_auto_button'))},
                {'~/auto_topic': '/base_mux/autoCommand'},
                ],
            remappings=[
                ('select', '/base_mux/select'),
                ],
            output='screen'),

        launch_ros.actions.Node(
            package='vrep_ros_teleop', executable='teleop_mux_node', name='teleop_arm_mux',
            parameters=[
                {'~/joystick_button': int(arg('arm_joystick_button'))},
                {'~/joystick_topic': '/teleop_arm/twistCommand'},
                {'~/auto_button': int(arg('arm_auto_button'))},
                {'~/auto_topic': '/arm_mux/autoCommand'},
                ],
            remappings=[
                ('select', '/arm_mux/select'),
                ],
            output='screen'),

        launch_ros.actions.Node(
            package='vrep_ros_teleop', executable='teleop_node', name='teleop_base',
            parameters=[
                {'~/axis_linear_x': 1},
                {'~/axis_angular': 0},
                {'~/scale_linear_x': 1.0},
                {'~/scale_angular': 1.},
                {'~/timeout': 1.0}
                ],
            output='screen'),

        launch_ros.actions.Node(
            package='vrep_vsv_driver', executable='vsv_arm_ik', name='arm_ik',
            parameters=[
                {'~/max_velocity': 0.5},
                ],
            remappings=[
                ('~/joint_command', '/VSV/aggregated/command'),
                ('~/joint_state', '/VSV/aggregated/state'),
                ],
            output='screen'),

        launch_ros.actions.Node(
            package='vrep_vsv_driver', executable='teleop_geom', name='teleop_geom',
            parameters=[
                {'~/axis_arm_x': int(arg('axis_arm_x'))},
                {'~/axis_arm_y': int(arg('axis_arm_y'))},
                {'~/axis_arm_z': int(arg('axis_arm_z'))},
                {'~/arm_velocity': float(arg('arm_velocity'))},
                {'~/home_button': int(arg('home_button'))},
                {'~/ready_button': int(arg('ready_button'))},
                {'~/move_button': int(arg('move_button'))},
                ],
            remappings=[
                ('~/position_command', '/arm_ik/position'),
                ('~/twist_command', '/teleop_arm/twistCommand'),
                ('~/tool_command', '/arm_ik/tool_orientation'),
                ],
            output='screen'),

        launch_ros.actions.Node(
            package='vrep_vsv_driver', executable='vsv_arm', name='vsv_arm',
            output='screen'),

        launch_ros.actions.Node(
            package='vrep_vsv_driver', executable='vsv_driver', name='vsv_driver',
            parameters=[
                {'~/min_radius': 5.0},
                ],
            output='screen'),
    ]


def generate_launch_description():
    return LaunchDescription(
        [DeclareLaunchArgument(name, default_value=default, description=description)
         for name, default, description in ARGUMENTS]
        + [OpaqueFunction(function=launch_setup)])
