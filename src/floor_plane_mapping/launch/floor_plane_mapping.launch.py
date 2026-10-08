import launch_ros.actions
from launch import LaunchDescription


def generate_launch_description():
    return LaunchDescription([
        launch_ros.actions.Node(
            package='floor_plane_mapping', executable='floor_plane_mapping', name='floor_plane_mapping',
            parameters=[
                {'~/map_frame': 'world'},
                {'~/resolution': 0.1},
                {'~/width': 11.0},
                {'~/height': 11.0},
                {'~/origin_x': -5.5},
                {'~/origin_y': -5.5},
                {'~/min_range': 0.3},
                {'~/max_range': 3.0},
                {'~/min_points': 6},
                {'~/min_spread': 0.015},
                {'~/max_slope_deg': 20.0},
                {'~/max_roughness': 0.02},
                {'~/max_step': 0.05},
                {'~/p_near': 0.9},
                {'~/p_far': 0.6},
                {'~/p_max': 0.99},
                {'~/threshold': 0.7},
                {'~/publish_period': 1.0},
                {'~/save_prefix': 'floor_map'},
                ],
            remappings=[
                ('~/scans', '/points'),
                ],
            output='screen'),
    ])
