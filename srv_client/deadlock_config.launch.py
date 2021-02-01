from launch import LaunchDescription
from launch_ros.actions import ComposableNodeContainer, Node
from launch_ros.descriptions import ComposableNode
import numpy as np


def generate_launch_description():
    return LaunchDescription(
        [
            ComposableNodeContainer(
                name="client_container",
                namespace="",
                package="rclcpp_components",
                executable="component_container",
                output="screen",
                composable_node_descriptions=[
                    ComposableNode(
                        package="srv_client",
                        plugin="srv_client::SrvClient",
                        name="srv_client",
                    ),
                    ComposableNode(
                        package="srv_service",
                        plugin="srv_service::SrvService",
                        name="srv_service",
                    ),

                ],
            )
        ]
    )
