#define GPIO_BASE 0x04000060 // check GPIO_BASE in system.h file 
#define LED_BASE 0x04000000

typedef enum direction{
    up,
    down,
    right, 
    left,
    none
} direction;