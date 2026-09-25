#include "input.h"

direction read_direction(){
    volatile int *gpio_data = (volatile int*) GPIO_BASE;

    int all_pins = *gpio_data;

    if (!(all_pins & (1 << 0)))
        return UP;

    else if (!(all_pins & (1 << 1)))
        return DOWN;

    else if (!(all_pins & (1 << 2)))
        return RIGHT;

    else if (!(all_pins & (1 << 3)))
        return LEFT;

    else
        return NONE;
}

void handle_interrupt(unsigned int cause){}

int main(){
    volatile int *leds = (volatile int*) LED_BASE;
    while(1){
        direction state = read_direction();

        *leds = 0;

        if(state == UP){
            *leds = 0b0001;
        }
        if(state == DOWN){
            *leds = 0b0010;
        }
        if(state == RIGHT){
            *leds = 0b0100;
        }
        if(state == LEFT){
            *leds = 0b1000;
        }
    }
}
