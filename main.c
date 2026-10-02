//Wiktoria

#include "graphics.h"
#include "sprites.h"
#include "timer.h"
#include <stdint.h>

extern void enable_interrupt(void);

void handle_interrupt(unsigned int cause){
    if (cause == 0x10){
        timer_interrupt();
    }
}

void gameinit(void){
    init_timer();
    init_vga();
    draw_border();
    enable_interrupt();
}

int main(){
    gameinit();

    start_timer();
    

    while (1){
        show_time();
        // Happy Worm game will go here
    }
    return 0;
}

int main(){
    
    draw_text(200, 200, "HELLO!", WHITE);
    draw_sprite(100, 100, sprite_watermelon);
    draw_sprite(150,150, sprite_strawberry);
    draw_sprite(160,160, sprite_apple);
    draw_sprite(170,170, sprite_grapes);
    draw_sprite(180,180, sprite_sad);
    draw_sprite(190,190, sprite_smile);

    swap_buffers();

}