from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

from launch import LaunchDescription


def generate_launch_description():
    joy_node_name = LaunchConfiguration("joy_node")

    joy_node_name_cmd = DeclareLaunchArgument(
        name="joy_node",
        default_value="joy",
        description="The joy node to spin.",
        choices=["joy", "game_controller"],
    )

    joy_node = Node(
        package="joy",
        executable=[joy_node_name, "_node"],
        name=[joy_node_name, "_node"],
        output="screen",
        parameters=[{"deadzone": 0.05}],
    )

    bliss_node = Node(
        package="bliss",
        executable="bliss_node",
        name="bliss_node",
        output="screen",
    )
    return LaunchDescription(
        [
            joy_node_name_cmd,
            joy_node,
            bliss_node,
        ]
    )
