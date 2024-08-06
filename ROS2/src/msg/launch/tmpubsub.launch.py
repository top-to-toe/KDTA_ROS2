import os

from ament_index_python import get_package_share_directory
from launch import LaunchDescription
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    param_dir = LaunchConfiguration('param_dir', default=os.path.join(
        get_package_share_directory('msg'), 
        'param', 
        'turtlesim.yaml'
        ))
    
    return LaunchDescription([
        Node(package='msg',
             executable='message_publisher_class',
             output='screen',
             ),
        Node(package='msg',
             executable='message_subscriber_class',
             output='screen',
             ),
        Node(package='msg',
             executable='message2_subscriber_class',
             output='screen',
             ),
        Node(package='msg',
             executable='message_time_subscriber_class',
             output='screen',
             ),
        Node(package='msg',
             executable='time_publisher_class',
             output='screen',
             ),
        Node(package='turtlesim',
             executable='turtlesim_node',
             output='screen',
             parameters=[param_dir])
        ])