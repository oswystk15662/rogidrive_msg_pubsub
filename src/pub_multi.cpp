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

    float a = 0.0;
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
            RCLCPP_INFO(this->get_logger(), "Publishing: '%f', '%f'", a, a-0.1);

            rogidrive_msg::msg::RogidriveMessage msg1, msg2;
            msg1.pos = a;
            msg2.pos = a - 0.1;

            // メッセージ配列の作成
            rogidrive_msg::msg::RogidriveMultiArray message;
            message.data.push_back(msg1);  // std::vectorに追加
            message.data.push_back(msg2);

            // メッセージの公開
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