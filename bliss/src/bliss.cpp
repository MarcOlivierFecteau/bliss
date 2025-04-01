#include <iostream>

#include "bliss/bliss.hpp"

void Bliss::init_msgs(void)
{
    msgin_ = sensor_msgs::msg::Joy();
    prev_msgin_ = sensor_msgs::msg::Joy();
    bliss_ = bliss_t();
    prev_bliss_ = bliss_t();
}

void Bliss::joy_callback(const sensor_msgs::msg::Joy::SharedPtr msgin)
{
    prev_msgin_.axes.clear();
    prev_msgin_.buttons.clear();
    prev_msgin_.axes = msgin_.axes;
    prev_msgin_.buttons = msgin_.buttons;
    if (prev_msgin_.buttons.empty()) {
        prev_msgin_.buttons.resize(msgin->buttons.size());
    }
    msgin_ = *msgin;

    prev_timestamp_ = timestamp_;
    timestamp_ = msgin_.header.stamp;

    prev_bliss_ = bliss_;
    if (prev_bliss_.buttons.empty()) {
        prev_bliss_.buttons.resize(msgin->buttons.size());
    }
    if (bliss_.buttons.empty()) {
        bliss_.buttons.resize(msgin->buttons.size());
    }

    for (size_t i = 0; i < msgin_.axes.size(); ++i) {
        bliss_.axes = msgin_.axes;
    }

    for (size_t i = 0; i < msgin_.buttons.size(); ++i) {
        int32_t raw = msgin_.buttons[i];
        int32_t prev_raw = prev_msgin_.buttons[i];
        int32_t count = prev_bliss_.buttons[i].count;

        bool rising_edge = (prev_raw == 0 && raw == 1);
        bool falling_edge = (prev_raw == 1 && raw == 0);
        bool toggle;
        if (rising_edge) {
            ++count;
            toggle = !prev_bliss_.buttons[i].toggle;
        } else {
            toggle = prev_bliss_.buttons[i].toggle;
        }

        bliss_.buttons[i].raw = raw;
        bliss_.buttons[i].count = count;
        bliss_.buttons[i].rising_edge = rising_edge;
        bliss_.buttons[i].falling_edge = falling_edge;
        bliss_.buttons[i].toggle = toggle;
    }
    publisher_->publish(bliss_);
}

Bliss::Bliss(name_t node_name) : Node(node_name)
{
    clock_ = rclcpp::Clock();
    prev_timestamp_ = clock_.now();
    timestamp_ = prev_timestamp_;

    init_msgs();

    publisher_ = this->create_publisher<bliss_t>("/bliss", 1);
    subscription_ = this->create_subscription<sensor_msgs::msg::Joy>(
        "/joy", 1, std::bind(&Bliss::joy_callback, this, std::placeholders::_1));

    RCLCPP_INFO(this->get_logger(), "Started %s node...", node_name.c_str());
}
