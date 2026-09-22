from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess, Shutdown
from launch.substitutions import LaunchConfiguration

import launch_ros.actions


def generate_launch_description():
    seed = LaunchConfiguration('seed')
    rate = LaunchConfiguration('rate')
    bag = LaunchConfiguration('bag')

    return LaunchDescription([
        DeclareLaunchArgument('seed', default_value='1'),
        DeclareLaunchArgument('rate', default_value='50.0'),
        DeclareLaunchArgument('bag', default_value='bags/train'),

        launch_ros.actions.Node(
            package='model_prediction', executable='backandforth', name='backandforth',
            parameters=[
                {'seed': seed},
                {'rate': rate},
                {'loop': False},
                ],
            on_exit=Shutdown(),
            output='screen'),

        ExecuteProcess(
            cmd=['ros2', 'bag', 'record', '-o', bag,
                 '/vrep/commandTwist', '/vrep/localTwist'],
            output='screen'),

    ])
