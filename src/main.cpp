#include <rclcpp/rclcpp.hpp>

#include "bliss.cpp"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Bliss>("bliss"));
    rclcpp::shutdown();

    return 0;
}
