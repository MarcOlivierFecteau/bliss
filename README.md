# Bliss (_noun_): heavenly joy

This ROS package takes inputs from `joy_node`, and adds features such as rising/falling edge detecion, and toggle support. The motivation for this package is to bring more advanced controls to joystick controller in ROS.

> _N.B._ The documentation for this package uses 'ROS' to refer to 'ROS 2'.

## How to use this repository

Clone this repository into your ROS workspace's `src` directory:

```bash
git clone git@github.com:MarcOlivierFecteau/bliss.git path/to/ros2_ws/src/
```

Build the package (from the ROS workspace's root directory):

```bash
colcon build [--packages-select bliss bliss_msgs]
source install/local_setup.bash
```

The package comes with both an executable and a launch file that includes `joy_node`:

```bash
ros2 run bliss bliss_node           # `bliss_node` only
ros2 launch bliss bliss.launch.py   # Includes `joy_node`
```

> _N.B._ `game_controller_node` can be used instead with `--joy_node:=game_controller`.

## Feature support

As of: 2025-04-05

| **Feature**  | **Buttons** | **D-Pad** | **Analog** |
| ------------ | ----------- | --------- | ---------- |
| Raw value    | ✔           | ✔         | ✔          |
| Rising edge  | ✔           | ✔         | ✔          |
| Falling edge | ✔           | ✔         | ✔          |
| Toggle       | ✔           | -         | _N/A_      |
| Counter      | ✔           | ✔\*       | _N/A_      |
| Time held    | ✔           | ✔         | -          |
| Double click | ✔           | ✔         | _N/A_      |
| Lock value   | -           | -         | -          |

> \* Supports "delta-counter" (i.e. +1 for 'up', -1 for 'down').

### Other features

Interesting features that MIGHT be added ulteriorly:

- Parameters + configuration file: _N/A_
- Parameter server (dynamic reconfigure): _N/A_
  - Services for resetting values (e.g. counters, lock values)
- Auto-detect controller (automatic remappings): _N/A_
  - Implicitly: hot-swap support
  - NOTE: though `joy_node` supports automatic remappings, `bliss_node` crashes due to OOB access error.
- Modifier "keys": _N/A_
- Layers | Profiles: _N/A_
- Runtime feature customization: _N/A_

## Known issues

### D-Pad "ghost" input

This issue can be reproduced by following these steps:

1. Be buttons `n` from axis `N`, and `m` from axis `M != N`;
1. Hold `n`;
1. Hold `m`;
1. Release `n`;

**Result**: `n`'s `raw`, and implicitly its `time_held`, are NOT reset until either `m` is released, or the button opposite to `n` is pressed.

**Hypothesis**: the cause of this "ghost input" stems from the hardware itself, and therefore WILL NOT and CANNOT be fixed.
