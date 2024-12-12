#include <memory>
#include <functional>
#include "rclcpp/rclcpp.hpp"
#include "rogidrive_msg/msg/rogidrive_message.hpp"

using std::placeholders::_1;

class Sub : public rclcpp::Node
{
public:
    Sub();
private:
    void callback(const rogidrive_msg::msg::RogidriveMessage::SharedPtr msg);
    rclcpp::Subscription<rogidrive_msg::msg::RogidriveMessage>::SharedPtr subscription_;
};

Sub::Sub()
: Node("sub")
{
    subscription_ = this->create_subscription<rogidrive_msg::msg::RogidriveMessage>(
        "rogidrive_msg", 10, std::bind(&Sub::callback, this, _1));
}

void Sub::callback(const rogidrive_msg::msg::RogidriveMessage::SharedPtr msg)
{
    RCLCPP_INFO(this->get_logger(), "I heard: '%f'", msg->pos);
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Sub>());
    rclcpp::shutdown();
    return 0;
}