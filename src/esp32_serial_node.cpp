#include <cstdio>
#include "esp32_serial/SimpleSerial.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/u_int32.hpp"

using std::placeholders::_1;



class RobotControlNode : public rclcpp::Node
{
public:
  RobotControlNode()
      : Node("robot_cmd_node")
  {
    cmd_subscriber = this->create_subscription<std_msgs::msg::UInt32>(
        "/robot_cmd", 10, std::bind(&RobotControlNode::cmd_received, this, _1));

    // try
    // {

    //   serial = std::make_shared<SimpleSerial>("/dev/ttyUSB0", 115200);
    //   serial->writeString("f");
    // }
    // catch (boost::system::system_error &e)
    // {
    //   std::cout << "Error: " << e.what() << std::endl;
    // }
  }

private:
  void cmd_received(const std_msgs::msg::UInt32::SharedPtr cmd) const
  {
    if (cmd->data == 1)
    {
      serial->writeString("f");
    }

    if (cmd->data == 2)
    {
      serial->writeString("c");
    }
    
  }

  rclcpp::Subscription<std_msgs::msg::UInt32>::SharedPtr cmd_subscriber;
  std::shared_ptr<SimpleSerial> serial;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<RobotControlNode>());
  rclcpp::shutdown();
  return 0;
}
