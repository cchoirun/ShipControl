

#include <functional>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include <std_msgs/msg/float32_multi_array.hpp>

using std::placeholders::_1;

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("minimal_subscriber")
  {
    subscription_ = this->create_subscription<std_msgs::msg::Float32MultiArray>(
      "titik_data", 10, std::bind(&MinimalSubscriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const std_msgs::msg::Float32MultiArray & msg) const
  {
    float hijau = msg.data[0], hijau2 = msg.data[1];
    float merah = msg.data[2], merah2 = msg.data[2];

    RCLCPP_INFO(this -> get_logger(), "hijau: ['%.2f','%.2f' ]", hijau, hijau2);
    RCLCPP_INFO(this -> get_logger(), "merah: ['%.2f','%.2f' ]", merah, merah2);
  }
  rclcpp::Subscription<std_msgs::msg::Float32MultiArray>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}

