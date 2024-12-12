#include <memory>
#include <functional>
#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include "rogidrive_msg/msg/rogidrive_message.hpp"

using std::placeholders::_1;

class Pub : public rclcpp::Node
{
public:
    Pub();
private:
    float a;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<rogidrive_msg::msg::RogidriveMessage>::SharedPtr publisher_;
};

Pub::Pub()
: Node("pub")
{
    this->publisher_ = this->create_publisher<rogidrive_msg::msg::RogidriveMessage>("rogidrive_msg", 10);
    timer_ = this->create_wall_timer(
        std::chrono::milliseconds(500),
        [this]() -> void {
            auto message = rogidrive_msg::msg::RogidriveMessage();
            message.pos = a;
            RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", message.pos);
            publisher_->publish(message);

            a+=0.1;
        });
}

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Pub>());
    rclcpp::shutdown();
    return 0;
}