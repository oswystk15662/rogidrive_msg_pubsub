#include <memory>
#include <functional>
#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "rogidrive_msg/msg/rogidrive_multi_array.hpp"

using std::placeholders::_1;

class Pub_Multi : public rclcpp::Node
{
public:
    Pub_Multi();
private:
    float a;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<rogidrive_msg::msg::RogidriveMultiArray>::SharedPtr publisher_;
};

Pub_Multi::Pub_Multi()
: Node("pub_multi")
{
    this->publisher_ = this->create_publisher<rogidrive_msg::msg::RogidriveMultiArray>("rogidrive_msg_multi", 10);
    timer_ = this->create_wall_timer(
        std::chrono::milliseconds(500),
        [this]() -> void {
            rogidrive_msg::msg::RogidriveMultiArray message;
            message.data[0].pos = a;
            message.data[1].pos = a - 0.1;
            RCLCPP_INFO(this->get_logger(), "Publishing: '%f', '%f'", message.data[0].pos, message.data[1].pos);
            publisher_->publish(message);

            a+=0.1;
        });
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Pub_Multi>());
    rclcpp::shutdown();
    return 0;
}