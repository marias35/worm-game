//Wiktoria

#include "input.h"

direction read_direction(){
    int all_pins = *(volatile int*) GPIO_BASE;

    int up    = !(all_pins & 1);
    int down  = !((all_pins >> 1) & 1);
    int right = !((all_pins >> 2) & 1);
    int left  = !((all_pins >> 3) & 1);

    if (up) return UP;
    if (down) return DOWN;
    if (right) return RIGHT;
    if (left) return LEFT;
    return NONE;
}

direction current_direction(direction current, direction requested){
    if(requested == NONE)
        return current;
    
    // the worm can't turn on itself so we check if the requested direction is not oppposite to the current one
    if(current == UP && requested == DOWN)
        return current;
    if(current == DOWN && requested == UP)
        return current;
    if(current == RIGHT && requested == LEFT)
        return current;
    if(current == LEFT && requested == RIGHT)
        return current;
    
    return requested;
}

//For testing
//Lights up a corresponding led depending on the state of the joystick

/* int main(){
    volatile int *leds = (volatile int*) LED_BASE;

    while (1) {
        direction state = read_direction();
 
        switch (state){
            case UP: 
                *leds = 0b0001; 
                break;
            case DOWN: 
                *leds = 0b0010; 
                break;
            case RIGHT: 
                *leds = 0b0100; 
                break;
            case LEFT: 
                *leds = 0b1000; 
                break;
            default: 
                *leds = 0b0000; 
                break;
        }
    }
}
*/