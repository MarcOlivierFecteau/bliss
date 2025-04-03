from launch import LaunchDescription
from launch_ros.actions import Node

bliss_node = Node(
    package="bliss",
    executable="bliss_node",
    name="bliss_node",
    output="screen",
)

joy_node = Node(
    package="joy",
    executable="joy_node",
    name="joy_node",
    output="screen",
    parameters=[{"deadzone": 0.05}],
)


def generate_launch_description():
    return LaunchDescription(
        [
            bliss_node,
            joy_node,
        ]
    )
