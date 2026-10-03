#ifndef INPUT_H
#define INPUT_H

#define GPIO_BASE 0x040000e0
#define LED_BASE 0x04000000

typedef enum direction{
    NONE = 0,
    UP,
    DOWN,
    RIGHT, 
    LEFT
} direction;

direction read_direction();
direction current_direction(direction current, direction requested);

#endif