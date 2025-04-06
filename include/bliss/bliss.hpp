#ifndef BLISS_HPP
#define BLISS_HPP

#include <rclcpp/rclcpp.hpp>

#include "bliss/msg/bliss.hpp"
#include "bliss/msg/button.hpp"
#include <sensor_msgs/msg/joy.hpp>

typedef std::string name_t;
typedef uint64_t delay_t;
typedef bliss::msg::Bliss bliss_t;

class Bliss : public rclcpp::Node
{
  public:
    Bliss(name_t node_name);
    ~Bliss() {};

  private:
    sensor_msgs::msg::Joy msgin_, prev_msgin_;
    bliss_t bliss_, prev_bliss_;
    delay_t double_click_threshold_ = (delay_t)(500 * 1000000); // ns
    delay_t double_click_cooldown_ = (delay_t)(500 * 1000000);  // ns

    rclcpp::Clock clock_;
    rclcpp::Time timestamp_, prev_timestamp_;
    rclcpp::Publisher<bliss_t>::SharedPtr publisher_;
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscription_;

    void init_msgs(void);
    void joy_callback(const sensor_msgs::msg::Joy::SharedPtr msgin);
};

#endif // BLISS_HPP
