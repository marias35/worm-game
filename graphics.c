
#include <stdint.h>
 
// Confirmed from board documentation: VGA Screen Buffer (320x240x2)
// occupies 0x08000000 - 0x080257ff (320*240*2 = 0x25800 bytes)
#define VGA_BASE      0x08000000
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240
// 2 bytes/pixel confirmed - assuming RGB565 (5-6-5 bit split), which is the
// standard 16-bit format on these boards. If colors come out wrong/swapped,
// check your lecture slides for the exact bit layout used.
 
typedef uint16_t pixel_t;
 
// RGB565: 5 bits red, 6 bits green, 5 bits blue
#define RGB565(r, g, b) (pixel_t)(((r & 0x1F) << 11) | ((g & 0x3F) << 5) | (b & 0x1F))
 
#define COLOR_RED    RGB565(31, 0, 0)
#define COLOR_GREEN  RGB565(0, 63, 0)
#define COLOR_BLUE   RGB565(0, 0, 31)
#define COLOR_WHITE  RGB565(31, 63, 31)
#define COLOR_BLACK  RGB565(0, 0, 0)
 
static void fill_screen(pixel_t color) {
    volatile pixel_t *fb = (volatile pixel_t *) VGA_BASE;
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        fb[i] = color;
    }
}
 
static void draw_color_bars(void) {
    volatile pixel_t *fb = (volatile pixel_t *) VGA_BASE;
    pixel_t bars[] = { COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_WHITE, COLOR_BLACK };
    int num_bars = sizeof(bars) / sizeof(bars[0]);
    int bar_width = SCREEN_WIDTH / num_bars;
 
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            int bar_index = x / bar_width;
            if (bar_index >= num_bars) bar_index = num_bars - 1;
            fb[y * SCREEN_WIDTH + x] = bars[bar_index];
        }
    }
}
 
// Crude busy-wait delay - replace with your board's real delay/timer if you have one
static void delay(volatile unsigned int cycles) {
    while (cycles--) { }
}
 
int main(void) {
    while (1) {
        fill_screen(COLOR_RED);
        delay(5000000);
 
        fill_screen(COLOR_GREEN);
        delay(5000000);
 
        fill_screen(COLOR_BLUE);
        delay(5000000);
 
        fill_screen(COLOR_WHITE);
        delay(5000000);
 
        draw_color_bars();
        delay(10000000);
    }
 
    return 0;
}