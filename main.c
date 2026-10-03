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

void start(){
    init_vga();
    init_timer();
    game_init();
    enable_interrupt();
}

int main()
{
    start();
    game_start();
    while (1) {
        if(!game_is_over()){
            update_game();
            if(get_time_left() == 0){
                game_end();
            }
        render_frame();
        show_time();
        swap_buffers();

        }
        else{
            clear_screen(BLACK);
            draw_border();
            show_game_over();
            swap_buffers();
        }
    }
    return 0;
}