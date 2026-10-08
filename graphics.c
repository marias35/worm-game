//Wiktoria 

#include "graphics.h"
#include "font8x8_basic.h"
#include "sprites.h"
#include <stdint.h>


// we define the frame buffer as uint8_t because it points to the first pixel in the frame
// pixels are defined as 8-bit non-negative values each bit corresponing to a color value in a pattern of RRRGGGBB
static volatile uint8_t *frame_buffer = (volatile uint8_t *) VGA_FRAMEBUFFER;  

void swap_buffers(){
    *(volatile int*) VGA_DMA_BUFFER = 0; //any write to the buffer requests a swap

    while(*(volatile int *)VGA_DMA_STATUS & 1){} //wait until the swap is done (lsb of status turns 0 when the swap is complete)

    frame_buffer = (volatile uint8_t*) *(volatile int *)VGA_DMA_BACKBUFFER; //set the frame buffer to whatever is at the back buffer
                                                    // we don't have to keep track of which frame is which 
                                                    // we just swap them when required 
}

void init_vga(){

    int frame1 = VGA_FRAMEBUFFER;
    int frame2 = VGA_FRAMEBUFFER_2;

    *(volatile int *)VGA_DMA_BACKBUFFER = frame1; // we make frame1 the next frame, so after the swap we know which frame is displayed
    *(volatile int *)VGA_DMA_BUFFER = 0; // any write to that variable requests a swap of buffers meaning that 
                                        // first frame is going to be in the frame buffer
    while(*(volatile int *)VGA_DMA_STATUS & 1){} // we wait until the swap is done

    frame_buffer = (volatile uint8_t*) frame1; // we set the frame buffer to frame1 beacause that's our current frame
    clear_screen(BLACK);

    *(volatile int *)VGA_DMA_BACKBUFFER = frame2; // we set back buffer to frame2 so that the next swap will show that frame
    frame_buffer = (volatile uint8_t*) frame2; // we set frame_buffer to frame2 so all drawing goes there
    clear_screen(BLACK); // we clear that frame too
}

void set_pixel(int x, int y, uint8_t color){
    if(x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) // checks if (x,y) is in the range 
        return; 
    frame_buffer[y * SCREEN_WIDTH + x] = color; // if it is we set that pixel to the chosen color 
}

void clear_screen(uint8_t color){
    for(int i = 0; i < VGA_FRAMEBUFFER_SIZE; i++){ // sets all pixels one by one to the choosen color
        frame_buffer[i] = color; 
    }
}

void draw_rect(int x, int y, int width, int height, uint8_t color){
    int x1, y1; // upper left corner of the rectangle
    int x2, y2; // bottom right corner of the rectangle


    // the following if ... else ... statements check if the (x,y) values are in the range of our screen
    // if they are outside we set the x and y values to minimum or maximum accordingly
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

    if(c < 0 || c > 127){ // if the character is not in the avaiable range of characters we return
        return;
    }

    for(int row = 0; row < 8; row++){
        line = font8x8_basic[(int) c][row]; //line of pixels that needs to be printed to show the character
        for(int col = 0; col < 8; col++){
            if((line >> col) & 1) // we shift by column to obtain the next pixel
                set_pixel(x + col, y + row, color);
        }
    }
}

void draw_text(int x, int y, char *text, uint8_t color){
    for(int i = 0; text[i] != 0; i++){
        draw_char(x + i * 8, y, text[i], color); // we add to x, 8*i to shift where we want to print the character
    }
}

void draw_sprite(int x, int y, const uint8_t *sprite){
    for(int row = 0; row < SPRITE_SIZE; row++){ 
        for(int col = 0; col < SPRITE_SIZE; col++){
            // gets the pixel from the sprite we want to show at that postion
            uint8_t color = sprite[row * SPRITE_SIZE + col]; 
            // if the color is not set to the flag transparent color we set that pixel
            if(color != SPRITE_TRANSPARENT){ 
                set_pixel(x + col, y + row, color);
            }
        }
    }
}