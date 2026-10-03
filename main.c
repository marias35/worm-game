//Wiktoria

#include "timer.h"
#include "graphics.h"
#include "game.h"
#include "worm.h"
#include <stdint.h>

extern void enable_interrupt();

void handle_interrupt(unsigned int cause){
    if (cause == 0x10){
        timer_interrupt();
    }
}

void game_init(){
    init_vga();
    init_worm();

    init_timer();
    enable_interrupt();
    start_timer();
}

int main()
{
    game_init();
    while (1) {
        render_frame();
        show_time();
        swap_buffers();
    }
    return 0;
}