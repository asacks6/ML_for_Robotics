from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration


def generate_launch_description():
    # Mismo sistema que auto.launch.py pero sin red: la persona mueve la punta del
    # brazo de lado con el joystick mientras se graba la demostracion
    return LaunchDescription([
        DeclareLaunchArgument('rviz', default_value='true', description='open RViz'),
        DeclareLaunchArgument('linear_vel', default_value='0.4', description='truck speed (m/s)'),
        DeclareLaunchArgument('target_distance', default_value='2.5',
            description='lateral distance kept between the truck and the shore (m)'),
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource([get_package_share_directory('vsv_treasure'), '/auto.launch.py']),
            launch_arguments={
                'teach': 'true',
                'rviz': LaunchConfiguration('rviz'),
                'linear_vel': LaunchConfiguration('linear_vel'),
                'target_distance': LaunchConfiguration('target_distance'),
                }.items()),
    ])
