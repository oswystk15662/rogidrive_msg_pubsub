#include <memory>
#include <functional>
#include "rclcpp/rclcpp.hpp"
#include "rogidrive_msg/msg/rogidrive_multi_array.hpp"

using std::placeholders::_1;

class Sub_Multi : public rclcpp::Node
{
public:
    Sub_Multi();
private:
    void callback(const rogidrive_msg::msg::RogidriveMultiArray::UniquePtr msg);
    rclcpp::Subscription<rogidrive_msg::msg::RogidriveMultiArray>::SharedPtr subscription_;
};

Sub_Multi::Sub_Multi()
: Node("sub_multi")
{
    subscription_ = this->create_subscription<rogidrive_msg::msg::RogidriveMultiArray>(
        "rogidrive_msg_multi", 10, std::bind(&Sub_Multi::callback, this, _1));
}

void Sub_Multi::callback(rogidrive_msg::msg::RogidriveMultiArray::UniquePtr msg)
{
    RCLCPP_INFO(this->get_logger(), "I heard 1: '%f'", msg->data[0].pos);
    RCLCPP_INFO(this->get_logger(), "I heard 2: '%f'", msg->data[1].pos);
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Sub_Multi>());
    rclcpp::shutdown();
    return 0;
}