from setuptools import find_packages
from setuptools import setup

setup(
    name='cv_bridge2',
    version='4.1.0',
    packages=find_packages(
        include=('cv_bridge2', 'cv_bridge2.*')),
)
