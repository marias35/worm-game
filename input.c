#include "input.h"

direction read_direction(){
    volatile int *gpio_data = (volatile int*) GPIO_BASE;

    int all_pins = *gpio_data;

    int up    = !(all_pins & 1);
    int down  = !((all_pins >> 1) & 1);
    int right = !((all_pins >> 2) & 1);
    int left  = !((all_pins >> 3) & 1);

    if (up)    return UP;
    if (down)  return DOWN;
    if (right) return RIGHT;
    if (left)  return LEFT;
    return NONE;
}

void handle_interrupt(unsigned int cause){}

// int main(){
//     volatile int *leds = (volatile int*) LED_BASE;

//     while (1) {
//         direction state = read_direction();
 
//         switch (state){
//             case UP: 
//                 *leds = 0b0001; 
//                 break;
//             case DOWN: 
//                 *leds = 0b0010; 
//                 break;
//             case RIGHT: 
//                 *leds = 0b0100; 
//                 break;
//             case LEFT: 
//                 *leds = 0b1000; 
//                 break;
//             default: 
//                 *leds = 0b0000; 
//                 break;
//         }
//     }
// }
