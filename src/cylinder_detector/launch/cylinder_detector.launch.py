import launch_ros.actions
from launch import LaunchDescription


def generate_launch_description():
    return LaunchDescription([
        launch_ros.actions.Node(
            package='cylinder_detector', executable='cylinder_detector', name='cylinder_detector',
            parameters=[
                {'~/map_frame': 'world'},
                {'~/min_range': 0.3},
                {'~/max_range': 3.5},
                {'~/grid_resolution': 0.05},
                {'~/min_vertical_extent': 0.2},
                {'~/floor_margin': 0.03},
                {'~/min_cluster_points': 30},
                {'~/ransac_iterations': 200},
                {'~/tolerance': 0.01},
                {'~/min_radius': 0.07},
                {'~/max_radius': 0.3},
                {'~/min_inlier_ratio': 0.9},
                {'~/min_arc_deg': 90.0},
                {'~/min_height': 0.4},
                {'~/association_margin': 0.15},
                {'~/min_detections': 3},
                ],
            remappings=[
                ('~/scans', '/points'),
                ],
            output='screen'),
    ])
