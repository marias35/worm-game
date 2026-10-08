//Wiktoria

#include "input.h"

direction read_direction(){
    int all_pins = *(volatile int*) GPIO_BASE;
    // 0 = pressed, 1 = not pressed -> that's why we reverse the input -> so int values are 1 when directions is pressed
    int up    = !(all_pins & 1);
    int down  = !((all_pins >> 1) & 1);
    int right = !((all_pins >> 2) & 1);
    int left  = !((all_pins >> 3) & 1);

    // if for example both UP and RIGHT are 1, RIGHT will be discarded as it's third if-statement
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
