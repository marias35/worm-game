//Wiktoria + Maria

#include "timer.h"
#include "graphics.h"
#include "game.h"
#include "worm.h"
#include "input.h"
#include "objects_functions.h"
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

    // we count loop iterations while the player doesn't move the joystick
    // that number is going to be different every time which allows us to obtain a different seed for the LCG formula
    // resulting in pseudo random positions and objects for each new game
    unsigned int count = 0;
    while(read_direction() == NONE){
        count++;
        clear_screen(BLACK);
        draw_border();
        draw_text(78, 116, "MOVE JOYSTICK TO START", WHITE);
        swap_buffers();

    }

    set_seed(count);
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