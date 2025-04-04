# Bliss (*noun*): heavenly joy

This ROS package takes inputs from `joy_node`, and adds features such as rising/falling edge detecion, ans toggle support. The motivation for this package is to bring more advanced controls to joystick controller in ROS.

> *N.B.* The documentation for this package uses 'ROS' to refer to 'ROS 2'.

## How to use this repository

Clone this repository into your ROS workspace's `src` directory:

```bash
git clone git@ssh.dev.azure.com:v3/CTA-BRP-UdeS/SCoPe2.0/bliss path/to/ros2_ws/src/
```

Build the package (from the ROS workspace's root directory):

```bash
colcon build [--packages-select bliss]
source install/local_setup.bash
```

The package comes with both an executable and a launch file that includes `joy_node`:

```bash
ros2 run bliss bliss_node           # `bliss_node` only
ros2 launch bliss bliss.launch.py   # Includes `joy_node`
```

## Feature support

As of: 2025-04-03

| **Feature** | **Buttons** | **D-Pad** | **Analog** |
|---|---|---|---|
| Raw value | ✔ | ✔ | ✔ |
| Rising edge | ✔ | ✔ | - |
| Falling edge | ✔ | ✔ | - |
| Toggle | ✔ | - | - |
| Counter | ✔ | ✔\* | - |
| Time held | - | - | - |
| Double click | - | - | - |
| Lock value | - | - | - |

> \* Supports "delta-counter" (e.g. +1 for 'up', -1 for 'down').

### Other features

Interesting features that MIGHT be added ulteriorly:

- Parameters + configuration file: *N/A*
- Parameter server (dynamic reconfigure): *N/A*
  - Services for resetting values (e.g. counters, lock values)
- Auto-detect controller (automatic remappings): *N/A*
  - Implicitly: hot-swap support
  - NOTE: though `joy_node` supports automatic remappings, `bliss_node` crashes due to OOB access error.
- Modifier "keys": *N/A*
- Layers | Profiles: *N/A*
- Runtime feature customization: *N/A*
