//Maria

#include "timer.h"
static volatile int time_left = 60; // we use volatile because we need to be able to hange those variables during interrupt handling
static volatile int timeout_counter = 0; 
static volatile int timer = 0; // if the timer runs or not


extern void set_displays(int display_number, int value);

void set_displays(int display_number, int value)
{
    volatile int *display = (volatile int *)(0x04000050 + display_number * 0x10); 

    int display_values[] = {
      //  decimal point + abcdefg are the led segments 
      // 0 means it's on 1 means it's off
        0b01000000, // 0
        0b01111001, // 1
        0b00100100, // 2
        0b00110000, // 3
        0b00011001, // 4
        0b00010010, // 5
        0b00000010, // 6
        0b01111000, // 7
        0b00000000, // 8
        0b00010000  // 9
    };

    *display = display_values[value];
}

void show_time(){
    int time = get_time_left();
    int minutes = time / 60;
    int seconds = time % 60;

    set_displays(0, seconds % 10);
    set_displays(1, seconds / 10);
    set_displays(2, minutes % 10);
    set_displays(3, minutes / 10);
}



// we set the time back to 60
void init_timer(){ 
    time_left = 60;
    timer = 0;
    timeout_counter = 0;
    *(volatile int *)TIMER_PERIODL = 0xC6C0;
    *(volatile int *)TIMER_PERIODH = 0x002D;
    *(volatile int *)TIMER_STATUS = 0;
}

void start_timer(){
    timer = 1;
    *(volatile int *)TIMER_CONTROL = 0b0111; //STOP START CONT ITO
}
void stop_timer(){
    timer = 0;
    *(volatile int*)TIMER_CONTROL = 0;
}
//called everytime the timer generates an interrupt
void timer_interrupt(){
    *(volatile int *)TIMER_STATUS = 0;

    if(timer){
        timeout_counter++;
        if(timeout_counter == 10){
            timeout_counter = 0;
            if(time_left > 0){
                time_left--;
            }
            if(time_left == 0){
                stop_timer();
            }
        }
    }
}

// we give the left time
int get_time_left(){ 
    return time_left;
}