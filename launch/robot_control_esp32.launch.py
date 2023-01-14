from launch import LaunchDescription
import launch_ros.actions


def generate_launch_description():
    return LaunchDescription([
        launch_ros.actions.Node(
            package='esp32_serial', node_executable='esp32_serial_exe', output='screen'),
    ])