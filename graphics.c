//Wiktoria

#include "graphics.h"
#include "font8x8_basic.h"
#include "sprites.h"
#include <stdint.h>

static volatile uint8_t *frame_buffer = (volatile uint8_t *) VGA_FRAMEBUFFER;

void swap_buffers(){
    volatile int *dma_buffer = (volatile int*) VGA_DMA_BUFFER;
    volatile int *dma_backbuffer = (volatile int*) VGA_DMA_BACKBUFFER;
    volatile int *dma_status = (volatile int*) VGA_DMA_STATUS;

    *dma_buffer = 0;

    while(*dma_status & 1){}

    frame_buffer = (volatile int*) dma_backbuffer;
}

void init_vga(){
    volatile int *dma_buffer = (volatile int*) VGA_DMA_BUFFER;
    volatile int *dma_backbuffer = (volatile int*) VGA_DMA_BACKBUFFER;
    volatile int *dma_status = (volatile int*) VGA_DMA_STATUS;

    int frame1 = VGA_FRAMEBUFFER;
    int frame2 = VGA_FRAMEBUFFER_2;

    *dma_backbuffer = frame1;
    *dma_buffer = 0;
    while(*dma_status & 1){}

    frame_buffer = (volatile int*) frame1;
    clear_screen(BLACK);

    *dma_backbuffer = frame2;
    frame_buffer = (volatile int*) frame1;
    clear_screen(BLACK);
}

void set_pixel(int x, int y, uint8_t color){
    if(x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_WIDTH) 
        return; 
    frame_buffer[y * SCREEN_WIDTH + x] = color;  
}

void clear_screen(uint8_t color){
    for(int i = 0; i < VGA_FRAMEBUFFER_SIZE; i++){
        frame_buffer[i] = color;
    }
}

void draw_rect(int x, int y, int width, int height, uint8_t color){
    int x1, y1, x2, y2;
    if(x < 0)
        x1 = 0;
    else
        x1 = x;
    
    if(y < 0)
        y1 = 0;
    else
        y1 = y;

    if((x + width) > SCREEN_WIDTH)
        x2 = SCREEN_WIDTH;
    else
        x2 = x + width;

    if((y + height) > SCREEN_HEIGHT)
        y2 = SCREEN_HEIGHT;
    else
        y2 = y + height;

    for(int row = y1; row < y2; row++){
        for(int col = x1; col < x2; col++){
            set_pixel(col, row, color);
        }
    }
}  

void draw_border(){
    draw_rect(0, 0, SCREEN_WIDTH, BORDER_THICKENSS, BORDER_COLOR); //top
    draw_rect(0, SCREEN_HEIGHT - BORDER_THICKENSS, SCREEN_WIDTH, BORDER_THICKENSS, BORDER_COLOR); //bottom
    draw_rect(0, 0, BORDER_THICKENSS, SCREEN_HEIGHT, BORDER_COLOR); // left
    draw_rect(SCREEN_WIDTH - BORDER_THICKENSS, 0, BORDER_THICKENSS, SCREEN_HEIGHT, BORDER_COLOR); // right
}

void draw_char(int x, int y, char c, uint8_t color){
    uint8_t line;

    if(c < 0 || c > 127){
        return;
    }

    for(int row = 0; row < 8; row++){
        line = font8x8_basic[(int) c][row];
        for(int col = 0; col < 8; col++){
            if((line >> col) & 1)
                set_pixel(x + col, y + row, color);
        }
    }
}

void draw_text(int x, int y, char *text, uint8_t color){
    for(int i = 0; text[i] != 0; i++){
        draw_char(x + i * 8, y, text[i], color);
    }
}

void draw_sprite(int x, int y, const uint8_t *sprite){
    for(int row = 0; row < SPRITE_SIZE; row++){
        for(int col = 0; col < SPRITE_SIZE; col++){
            uint8_t color = sprite[row * SPRITE_SIZE + col];
            if(color != SPRITE_TRANSPARENT){
                set_pixel(x + row, y + col, color);
            }
        }
    }
}