#include <stdint.h>
#ifndef GRAPHICS_H
#define GRAPHICS_H

#define VGA_DMA_BASE 0x04000100
// holds adress of the start of the memory buffer, is the first pixel of the frame currently being output
#define VGA_DMA_BUFFER VGA_DMA_BASE 
// points to the first pixel of the next frame
#define VGA_DMA_BACKBUFFER (VGA_DMA_BASE + 0x4)
// bits 15-0 = x-resolution, bits 31-16 = y-resolution
#define VGA_DMA_RESOLUTION (VGA_DMA_BASE + 0x8)
// LSB of status equals 0 when the swap is done, 1 otherwise
#define VGA_DMA_STATUS (VGA_DMA_BASE + 0xC)


// the preset resolution of the screen
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define VGA_FRAMEBUFFER_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)
#define VGA_FRAMEBUFFER 0x08000000
#define VGA_FRAMEBUFFER_2 (0x08000000 + VGA_FRAMEBUFFER_SIZE)

#define WHITE 0xFF
#define BLACK 0x00f

#define BORDER_THICKENSS 1
#define BORDER_COLOR WHITE

void init_vga();
void swap_buffers();
void set_pixel(int x, int y, uint8_t color);
void clear_screen(uint8_t color);
void draw_rect(int x, int y, int width, int height, uint8_t color);
void draw_border();
void draw_char(int x, int y, char c, uint8_t color);
void draw_text(int x, int y, char *text, uint8_t color);
void draw_sprite(int x, int y, const uint8_t *sprite);

#endif