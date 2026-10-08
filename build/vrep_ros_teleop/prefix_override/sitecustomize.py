import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/GTL/asacks/ros_workspace/install/vrep_ros_teleop'
