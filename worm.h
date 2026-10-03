#ifndef WORM_H
#define WORM_H

#include "input.h"

#define MAX_WORM_LENGTH 100
#define WORM_START_LENGTH 4
#define WORM_COLOR 0xF3

typedef enum WormFace{
    FACE_HAPPY,
    FACE_SAD
} WormFace;

extern int worm_body[MAX_WORM_LENGTH][2];
extern int worm_length;
extern WormFace face;

extern direction worm_direction;
extern direction next_direction;

void draw_worm();
void draw_face();
void init_worm();

#endif