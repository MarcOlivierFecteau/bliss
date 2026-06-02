# Configuration Notes

## Game Controller Mappings

**Axes**:

| **Index** | **Button** |
| --------- | ---------- |
| 0         | LJH (LX)   |
| 1         | LJV (LY)   |
| 2         | RJH (RX)   |
| 3         | RJV (RY)   |
| 4         | LT         |
| 5         | RT         |

**Buttons:**

| **Index** | **Button**                                |
| --------- | ----------------------------------------- |
| 0         | A (CROSS)                                 |
| 1         | B (CIRCLE)                                |
| 2         | X (SQUARE)                                |
| 3         | Y (TRIANGLE)                              |
| 4         | BACK (SELECT)                             |
| 5         | HOME                                      |
| 6         | START                                     |
| 7         | LJP                                       |
| 8         | RJP                                       |
| 9         | LB                                        |
| 10        | RB                                        |
| 11        | DPAD UP                                   |
| 12        | DPAD DOWN                                 |
| 13        | DPAD LEFT                                 |
| 14        | DPAD RIGHT                                |
| 15        | MISC1 (SHARE)\*                           |
| 16        | PADDLE1 (upper left)                      |
| 17        | PADDLE2 (upper right)                     |
| 18        | PADDLE3 (lower left)                      |
| 19        | PADDLE4 (lower right)                     |
| 20        | TOUCHPAD (if present, button status only) |

## Xbox Controller Mappings

Compatible with Xbox 360 controllers and Xbox Series S/X controllers.

**Axes:**

| **Index** | **Button** |
| --------- | ---------- |
| 0         | LJH (LX)   |
| 1         | LJV (LY)   |
| 2         | LT         |
| 3         | RJH (RX)   |
| 4         | RJV (RY)   |
| 5         | RT         |
| 6         | DPH (DX)   |
| 7         | DPV (DY)   |

**Buttons:**

| **Index** | **Button** |
| --------- | ---------- |
| 0         | A          |
| 1         | B          |
| 2         | X          |
| 3         | Y          |
| 4         | LB         |
| 5         | RB         |
| 6         | BACK       |
| 7         | START      |
| 8         | HOME       |
| 9         | LJP        |
| 10        | RJP        |
| 11        | SHARE\*    |

> \* Not all controllers have this button.

## Logitech F710 Contoller Mappings

### X-Mode

**Axes:**

| **Index** | **Button** |
| --------- | ---------- |
| 0         | LJH        |
| 1         | LJV        |
| 2         | LT         |
| 3         | RJH        |
| 4         | RJV        |
| 5         | RT         |
| 6         | DPH        |
| 7         | DPV        |

**Buttons:**

| **Index** | **Button** |
| --------- | ---------- |
| 0         | A          |
| 1         | B          |
| 2         | X          |
| 3         | Y          |
| 4         | LB         |
| 5         | RB         |
| 6         | BACK       |
| 7         | START      |
| 8         | HOME       |
| 9         | LJP        |
| 10        | RJP        |

### D-Mode

**Axes:**

| **Index** | **Button** |
| --------- | ---------- |
| 0         | LJH        |
| 1         | LJV        |
| 2         | RJH        |
| 3         | RJV        |
| 4         | DPH        |
| 5         | DPV        |

**Buttons:**

| **Index** | **Button**   |
| --------- | ------------ |
| 0         | X (square)   |
| 1         | A (cross)    |
| 2         | B (circle)   |
| 3         | Y (triangle) |
| 4         | LB           |
| 5         | RB           |
| 6         | LT           |
| 7         | RT           |
| 8         | BACK         |
| 9         | START        |
| 10        | LJP          |
| 11        | RJP          |

### `Mode` button

The `Mode` toggle button swaps the left joystick and the D-Pad's indices. In other words:

- LJH <---> DPH;
- LJV <---> DPV.

Additionally, the left joystick now behaves as a D-Pad.

This feature works the same for both X-Mode and D-Mode.
