//Wiktoria

#include "graphics.h"
#include <stdint.h>

void handle_interrupt(unsigned int cause){}

int main(){
    init_vga();
    draw_border();
    draw_text(200, 200, "HELLO!", WHITE);
}