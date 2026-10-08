#include <stdint.h>

#ifndef SPRITES_H
#define SPRITES_H

#include <stdint.h>

 // the sprite size is 10x10 pixels
#define SPRITE_SIZE 10
// 227 = magenta, is the flag color for not setting that pixel, 
// magenta was chosen as that color because it is not going to be used anywhere else
#define SPRITE_TRANSPARENT 227 

extern const uint8_t sprite_apple[100];
extern const uint8_t sprite_grapes[100];
extern const uint8_t sprite_watermelon[100];
extern const uint8_t sprite_strawberry[100];
extern const uint8_t sprite_smile[100];
extern const uint8_t sprite_sad[100];
extern const uint8_t worm_smile[100];
extern const uint8_t worm_sad[100];

#endif