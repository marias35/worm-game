#ifndef TIMER_H // if not defined, so we don't define it by mistake
#define TIMER_H

#define TIMER_STATUS 0x04000020 //tells whether a timeout happened
#define TIMER_CONTROL 0x04000024 //tells the timer what to do
#define TIMER_PERIODL 0x04000028 // tells how long the timer counts
#define TIMER_PERIODH 0x0400002C
// for a 1 second interval we need 30,00,00 clock cycles = 30 MHz
// 3,000,000 decimal = 0x002DC6C0
//3,000,000/ 30,000,000 = 0.1 seconds
//after 10 interrupts, 1 second has passed
// BUT WE HAVE two 16-bit registers
//TIMER_PERIODH is the 16 upper bits
//TIMER_PERIODL is the 16 lower bits
//so we split it in init_timer
void show_time();
void init_timer();
void timer_interrupt();
int get_movement_counter();
void reset_movement_counter();
void start_timer();
void stop_timer();
int get_time_left();
void set_displays(int display_number, int value);

#endif