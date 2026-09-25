#define GPIO_BASE 0x040000e0
#define LED_BASE 0x04000000

typedef enum direction{
    NONE = 0,
    UP,
    DOWN,
    RIGHT, 
    LEFT
} direction;