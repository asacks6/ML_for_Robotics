import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/GTL/asacks/ros_workspace/install/shore_follower_drive_torch_base'
