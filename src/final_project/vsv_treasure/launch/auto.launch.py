import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction, LogInfo
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration

import launch_ros.actions
import launch_ros.descriptions

# La red necesita pytorch, que solo esta en este entorno virtual
VENV = '/cs-share/pradalier/venv/torch-cpu-ros2'


def launch_setup(context):
    model = ''
    if LaunchConfiguration('teach').perform(context).lower() != 'true':
        model = os.path.realpath(os.path.expanduser(LaunchConfiguration('model').perform(context)))
        if not os.path.exists(model):
            return [LogInfo(msg='Model not found: ' + model + '. Train it first with: ros2 run vsv_treasure train_arm.sh')]

    arm_remappings = [
        ('~/depth', '/vrep/kision/depth'),
        ('~/sim_time', '/vrep/simTime'),
        ('~/twist', '/arm_mux/autoCommand'),
    ]
    if model == '':
        arm_remappings.append(('~/teleop_twist', '/teleop_arm/twistCommand'))
    else:
        arm_remappings.append(('~/image', '/vrep/kision/image'))

    return [
        LogInfo(msg='Arm model: ' + (model if model != '' else 'none, teaching mode')),

        # Objetivos 2a y 2b: la punta del brazo sigue la orilla a la altura fijada
        launch_ros.actions.Node(
            package='vsv_treasure', executable='arm_follower', name='arm_follower',
            parameters=[
                {'~/model': model},
                {'~/lateral_vel': 0.5},
                {'~/target_height': 0.35},
                {'~/height_gain': 1.0},
                {'~/vertical_vel': 0.3},
                {'~/max_reach': 3.9},
                ],
            remappings=arm_remappings,
            additional_env={'VIRTUAL_ENV': VENV},
            output='screen'),

        # Objetivo 3: el camion mantiene la distancia a la orilla que ve el laser de linea
        launch_ros.actions.Node(
            package='vsv_treasure', executable='truck_follower', name='truck_follower',
            parameters=[
                {'~/linear_vel': float(LaunchConfiguration('linear_vel').perform(context))},
                {'~/target_distance': float(LaunchConfiguration('target_distance').perform(context))},
                {'~/k_distance': 0.375},
                {'~/k_angle': 0.75},
                {'~/shore_percentile': 50.0},
                ],
            remappings=[
                ('~/image', '/vrep/line/image'),
                ('~/depth', '/vrep/line/depth'),
                ('~/camera_info', '/vrep/line/camera_info'),
                ('~/twist', '/base_mux/autoCommand'),
                ],
            output='screen'),

        # Objetivo 1: localiza los objetos con el detector de metales
        launch_ros.actions.Node(
            package='vsv_treasure', executable='treasure_detector', name='treasure_detector',
            parameters=[
                {'~/threshold': 0.3},
                {'~/merge_distance': 3.0},
                ],
            remappings=[
                ('~/detector', '/vrep/metalDetector'),
                ],
            output='screen'),

        launch_ros.actions.Node(
            package='rviz2', executable='rviz2', name='rviz2',
            arguments=['-d', os.path.join(get_package_share_directory('vsv_treasure'), 'treasure.rviz')],
            condition=IfCondition(LaunchConfiguration('rviz')),
            output='log'),
    ]


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument('model',
            default_value='~/ros_workspace/src/final_project/data/arm/model.pt',
            description='pytorch checkpoint of the arm network'),
        DeclareLaunchArgument('teach', default_value='false',
            description='true: no network, the arm lateral motion comes from the joystick'),
        DeclareLaunchArgument('rviz', default_value='true',
            description='open RViz'),
        DeclareLaunchArgument('linear_vel', default_value='0.25',
            description='truck speed (m/s)'),
        DeclareLaunchArgument('target_distance', default_value='2.7',
            description='lateral distance kept between the truck and the shore (m)'),
        OpaqueFunction(function=launch_setup),
    ])
