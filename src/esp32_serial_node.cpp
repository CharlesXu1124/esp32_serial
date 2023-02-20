#include <cstdio>
#include "esp32_serial/SimpleSerial.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

using std::placeholders::_1;

class RobotControlNode : public rclcpp::Node
{
public:
  RobotControlNode()
      : Node("robot_cmd_node")
  {
    cmd_subscriber = this->create_subscription<std_msgs::msg::Float32>(
        "/rotary_cmd", 10, std::bind(&RobotControlNode::cmd_received, this, _1));

    serial = std::make_shared<SimpleSerial>("/dev/ttyACM0", 115200);
    try
    {

      serial->writeString(" ");
    }
    catch (boost::system::system_error &e)
    {
      std::cout << "Error: " << e.what() << std::endl;
    }
  }

private:
  void cmd_received(const std_msgs::msg::Float32::SharedPtr cmd) const
  {

    if (cmd->data - 0.1f < 0.01)
    {
      RCLCPP_INFO(this->get_logger(), "command received");
      serial->writeString("a");
    }

    if (cmd->data - 0.2f < 0.01)
    {
      RCLCPP_INFO(this->get_logger(), "command received");
      serial->writeString("b");
    }

    if (cmd->data - 0.3f < 0.01)
    {
      RCLCPP_INFO(this->get_logger(), "command received");
      serial->writeString("c");
    }

    if (cmd->data - 0.4f < 0.01)
    {
      RCLCPP_INFO(this->get_logger(), "command received");
      serial->writeString("d");
    }
  }

  rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr cmd_subscriber;
  std::shared_ptr<SimpleSerial> serial;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<RobotControlNode>());
  rclcpp::shutdown();
  return 0;
}
