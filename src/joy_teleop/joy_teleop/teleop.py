import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Joy
from geometry_msgs.msg import Twist

class JoyTeleop(Node):
    def __init__(self):
        super().__init__('joy_teleop')
        self.declare_parameter('axis_linear', 1)
        self.declare_parameter('axis_angular', 3)
        self.declare_parameter('scale_linear', 0.5)
        self.declare_parameter('scale_angular', 1.0)
        self.declare_parameter('mode_factor', 3.0)
        self.declare_parameter('mode_button', 10)
        self.declare_parameter('dead_man_switch', 4)
        self.modes = [1.0, 1.0 / 3.0, 3.0]
        self.mode = 0
        self.prev = 0
        self.create_subscription(Joy, '/joy', self.joy_cb, 10)
        self.pub = self.create_publisher(Twist, '/vrep/twistCommand', 10)

    def joy_cb(self, joy):
        f = self.get_parameter('mode_factor').value
        self.modes = [1.0, 1.0 / f, f]
        btn = joy.buttons[self.get_parameter('mode_button').value]
        dead = joy.buttons[self.get_parameter('dead_man_switch').value]
        if btn == 1 and self.prev == 0:
            self.mode = (self.mode + 1) % 3
            self.get_logger().info(f'mode: {["normal", "precise", "fast"][self.mode]}')
        self.prev = btn

        ax_lin = self.get_parameter('axis_linear').value
        ax_ang = self.get_parameter('axis_angular').value
        sc_lin = self.get_parameter('scale_linear').value
        sc_ang = self.get_parameter('scale_angular').value

        msg = Twist()
        # msg.linear.x = joy.axes[ax_lin] * sc_lin
        # msg.angular.z = joy.axes[ax_ang] * sc_ang
        msg.linear.x = joy.axes[ax_lin] * sc_lin * self.modes[self.mode] * dead
        msg.angular.z = joy.axes[ax_ang] * sc_ang * self.modes[self.mode] * dead
        self.pub.publish(msg)
		

def main():
    rclpy.init()
    rclpy.spin(JoyTeleop())

if __name__ == '__main__':
    main()
