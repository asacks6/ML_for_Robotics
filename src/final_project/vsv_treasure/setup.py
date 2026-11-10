from setuptools import find_packages, setup
import os
from glob import glob

package_name = 'vsv_treasure'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        (os.path.join('share', package_name), glob('launch/*.launch.py')),
        (os.path.join('share', package_name), glob('rviz/*.rviz')),
        (os.path.join('lib', package_name), glob('scripts/*')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='asacks',
    maintainer_email='asacks@todo.todo',
    description='Final project: treasure search with the VSV truck and its arm',
    license='Apache-2.0',
    entry_points={
        'console_scripts': [
            'arm_follower = vsv_treasure.arm_follower:main',
            'truck_follower = vsv_treasure.truck_follower:main',
            'treasure_detector = vsv_treasure.treasure_detector:main',
        ],
    },
)
