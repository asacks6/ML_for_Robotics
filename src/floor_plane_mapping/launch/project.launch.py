import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration

import launch_ros.actions


def include(package, launch_file):
    return IncludeLaunchDescription(PythonLaunchDescriptionSource(
        [get_package_share_directory(package), '/', launch_file]))


def generate_launch_description():
    rviz_config = os.path.join(get_package_share_directory('floor_plane_mapping'), 'rviz', 'project.rviz')
    return LaunchDescription([
        DeclareLaunchArgument('graph_launch', default_value='floor_graph.launch.py',
            description='Launch file of floor_graph, floor_graph-test.launch.py for the test scene'),
        include('vrep4_helpers', 'kinect_pc.launch.py'),
        include('floor_nav', 'launch_server.launch.py'),
        include('floor_graph', LaunchConfiguration('graph_launch')),
        include('vrep_ros_teleop', 'teleop_mux.launch.py'),
        include('floor_plane_mapping', 'floor_plane_mapping.launch.py'),
        include('cylinder_detector', 'cylinder_detector.launch.py'),
        launch_ros.actions.Node(
            package='rviz2', executable='rviz2', name='rviz2',
            arguments=['-d', rviz_config],
            output='screen'),
    ])
