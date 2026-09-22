from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration

import launch_ros.actions


def generate_launch_description():
    seed = LaunchConfiguration('seed')
    plot = LaunchConfiguration('plot')
    mode = LaunchConfiguration('mode')

    return LaunchDescription([
        DeclareLaunchArgument('seed', default_value='3'),
        DeclareLaunchArgument('plot', default_value='true'),
        DeclareLaunchArgument('mode', default_value='demo'),

        launch_ros.actions.Node(
            package='model_prediction', executable='backandforth', name='backandforth',
            parameters=[
                {'seed': seed},
                {'rate': 50.0},
                {'loop': True},
                {'mode': mode},
                ],
            output='screen'),

        launch_ros.actions.Node(
            package='model_prediction', executable='model_prediction_node', name='predict',
            parameters=[
                {'~/rate': 50.0},
                {'~/inverse_coef_list': True},
                {'~/command_type': "geometry_msgs/Twist"},
                {'~/command_field': "linear.x"},
                {'~/command_coef_csv': "0.003633,0.079007,0.038002"},
                {'~/state_type': "geometry_msgs/TwistStamped"},
                {'~/state_field': "twist.linear.x"},
                {'~/state_coef_csv': "-1.611503,0.728862"},
                ],
            remappings=[
                ('~/command', '/vrep/twistCommand'),
                ('~/state', '/vrep/localTwist'),
                ],
            output='screen'),

        launch_ros.actions.Node(
            package='rqt_plot', executable='rqt_plot', name='rqt_plot',
            arguments=[
                '/vrep/commandTwist/twist/linear/x',
                '/vrep/localTwist/twist/linear/x',
                '/predict/twist_prediction/twist/linear/x',
                ],
            condition=IfCondition(plot),
            output='screen'),

    ])
