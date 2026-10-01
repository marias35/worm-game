#include <stdint.h>
#ifndef GRAPHICS_H
#define GRAPHICS_H

#define VGA_DMA_BASE 0x04000100
#define VGA_DMA_BUFFER VGA_DMA_BASE
#define VGA_DMA_BACKBUFFER (VGA_DMA_BASE + 0x4)
#define VGA_DMA_RESOLUTION (VGA_DMA_BASE + 0x8)
#define VGA_DMA_STATUS (VGA_DMA_BASE + 0xC)

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define VGA_FRAMEBUFFER_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT)
#define VGA_FRAMEBUFFER 0x08000000
#define VGA_FRAMEBUFFER_2 (0x08000000 + VGA_FRAMEBUFFER_SIZE)

#define WHITE 0xFF
#define BLACK 0x00

#define BORDER_THICKENSS 1
#define BORDER_COLOR WHITE

void init_vga();
void set_pixel(int x, int y, uint8_t color);
void clear_screen(uint8_t color);
void draw_rect(int x, int y, int width, int height, uint8_t color);
void draw_border();
void draw_char(int x, int y, char c, uint8_t color);
void draw_text(int x, int y, char *text, uint8_t color);

#endif