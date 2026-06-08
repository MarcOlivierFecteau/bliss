#include <iostream>

#include "bliss/bliss.hpp"

void Bliss::init_msgs(void)
{
    // Zero initialization to avoid undefined behavior on start
    msgin_ = prev_msgin_ = sensor_msgs::msg::Joy();
    bliss_ = prev_bliss_ = bliss_t();
}

void Bliss::joy_callback(const sensor_msgs::msg::Joy::SharedPtr msgin)
{
    // (Stupid) Memory management shenanigans to avoid segfaults
    prev_msgin_.axes.clear();
    prev_msgin_.buttons.clear();
    prev_msgin_.axes = msgin_.axes;
    prev_msgin_.buttons = msgin_.buttons;
    prev_bliss_ = bliss_;

    // SHOULD only trigger on the first call
    if (prev_msgin_.axes.empty()) {
        prev_msgin_.axes.resize(msgin->axes.size());
    }
    if (prev_msgin_.buttons.empty()) {
        prev_msgin_.buttons.resize(msgin->buttons.size());
    }
    if (prev_bliss_.axes.empty()) {
        prev_bliss_.axes.resize(msgin->axes.size());
    }
    if (prev_bliss_.dpad.empty()) {
        prev_bliss_.dpad.resize((size_t)2); // Assuming there is only one D-Pad
    }
    if (prev_bliss_.buttons.empty()) {
        prev_bliss_.buttons.resize(msgin->buttons.size());
    }
    if (bliss_.axes.empty()) {
        bliss_.axes.resize(msgin->axes.size());
    }
    if (bliss_.dpad.empty()) {
        bliss_.dpad.resize((size_t)2); // Assuming there is only one D-Pad
    }
    if (bliss_.buttons.empty()) {
        bliss_.buttons.resize(msgin->buttons.size());
    }
    // end: SHOULD only trigger on the first call

    msgin_ = *msgin;
    prev_timestamp_ = timestamp_;
    timestamp_ = msgin_.header.stamp;
    bliss_.header.stamp = timestamp_;

    uint64_t stamp_ns = timestamp_.nanoseconds();           // For convenience
    uint64_t prev_stamp_ns = prev_timestamp_.nanoseconds(); // For convenience
    delay_t dt = stamp_ns - prev_stamp_ns;

    for (size_t i = 0; i < msgin_.axes.size(); ++i) {
        float raw = msgin_.axes[i];
        float prev_raw = prev_msgin_.axes[i];

        bool on_press = (prev_raw == 0.0F && raw != 0.0F);
        bool on_release = (prev_raw != 0.0F && raw == 0.0F);

        if (i == 6 || i == 7) { // D-Pad
            size_t j = i - 6;

            int32_t i_raw = (int32_t)raw;
            int32_t count = prev_bliss_.dpad[j].count; // Delta counter
            uint64_t time_held = prev_bliss_.dpad[j].time_held;
            uint64_t last_click_timestamp = prev_bliss_.dpad[j].last_click_stamp;
            int64_t cooldown = prev_bliss_.dpad[j].cooldown;
            bool double_click = prev_bliss_.dpad[j].double_click;

            delay_t last_click_dt = stamp_ns - last_click_timestamp; // ns
            static const bool toggle = false;                        // Toggle not supported

            if (on_press) {
                if (cooldown == 0) {
                    double_click = last_click_dt < double_click_threshold_;
                }

                count += i_raw;
                last_click_timestamp = stamp_ns;
            }
            cooldown -= dt;
            if (cooldown <= 0) {
                cooldown = 0;
            }
            if (on_release) {
                if (double_click) {
                    cooldown = double_click_cooldown_;
                }
                double_click = false;
            }

            // Time held
            if (prev_bliss_.dpad[j].raw == i_raw && i_raw != 0) {
                time_held += (stamp_ns - prev_timestamp_.nanoseconds());
            } else {
                time_held = 0UL;
            }

            bliss_.dpad[j].last_click_stamp = last_click_timestamp;
            bliss_.dpad[j].time_held = time_held;
            bliss_.dpad[j].cooldown = cooldown;
            bliss_.dpad[j].raw = i_raw;
            bliss_.dpad[j].count = count;
            bliss_.dpad[j].on_press = on_press;
            bliss_.dpad[j].on_release = on_release;
            bliss_.dpad[j].toggle = toggle;
            bliss_.dpad[j].double_click = double_click;
        }

        bliss_.axes[i].raw = raw;
        bliss_.axes[i].on_press = on_press;
        bliss_.axes[i].on_release = on_release;
    }

    for (size_t i = 0; i < msgin_.buttons.size(); ++i) {
        int32_t raw = msgin_.buttons[i];
        int32_t prev_raw = prev_msgin_.buttons[i];
        int32_t count = prev_bliss_.buttons[i].count;
        uint64_t time_held = prev_bliss_.buttons[i].time_held;
        uint64_t last_click_timestamp = prev_bliss_.buttons[i].last_click_stamp;
        uint64_t cooldown = prev_bliss_.buttons[i].cooldown;
        bool toggle = prev_bliss_.buttons[i].toggle;
        bool double_click = prev_bliss_.buttons[i].double_click;

        uint64_t last_click_dt = stamp_ns - last_click_timestamp;
        bool on_press = (prev_raw == 0 && raw == 1);
        bool on_release = (prev_raw == 1 && raw == 0);

        if (on_press) {
            if (cooldown == 0) {
                double_click = last_click_dt < double_click_threshold_;
            } else {
                cooldown -= dt;
                if (cooldown <= 0) {
                    cooldown = 0;
                }
            }

            ++count;
            toggle = !toggle;
            last_click_timestamp = stamp_ns;
        }
        if (on_release) {
            if (double_click) {
                cooldown = double_click_cooldown_;
            }
            double_click = false;
        }

        // Property: time held
        if (prev_bliss_.buttons[i].raw == raw && raw == 1) {
            time_held += (stamp_ns - prev_timestamp_.nanoseconds());
        } else {
            time_held = 0UL;
        }

        bliss_.buttons[i].last_click_stamp = last_click_timestamp;
        bliss_.buttons[i].time_held = time_held;
        bliss_.buttons[i].cooldown = cooldown;
        bliss_.buttons[i].raw = raw;
        bliss_.buttons[i].count = count;
        bliss_.buttons[i].on_press = on_press;
        bliss_.buttons[i].on_release = on_release;
        bliss_.buttons[i].toggle = toggle;
        bliss_.buttons[i].double_click = double_click;
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
