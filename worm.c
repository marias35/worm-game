#include "graphics.h"
#include "worm.h"
#include "sprites.h"


int worm_body[MAX_WORM_LENGTH][2];
int worm_length;
WormFace face;

direction worm_direction;
direction next_direction;

//Wiktoria 

void draw_worm(){
    for(int i = 0; i < worm_length; i++){
        draw_rect(worm_body[i][0], worm_body[i][1], SPRITE_SIZE, SPRITE_SIZE, WORM_COLOR);
    }
    draw_face();
}

void draw_face(){
    if(face == FACE_HAPPY)
        draw_sprite(worm_body[0][0], worm_body[0][1], worm_smile);
    else{
        draw_sprite(worm_body[0][0], worm_body[0][1], worm_sad);
    }
    
}

//Maria

void init_worm(){
    worm_length = WORM_START_LENGTH;
    face = FACE_HAPPY;

    for(int i = 0; i < worm_length; i++){
        worm_body[i][0] = SCREEN_WIDTH/2 - SPRITE_SIZE/2; 
        worm_body[i][1] = SCREEN_HEIGHT/2 - SPRITE_SIZE/2 + i*SPRITE_SIZE;
    }

    worm_direction = UP;
    next_direction = UP;
}

void set_direction(){}

void move_worm(){}

void grow_worm(){}

void change_speed(){}

void check_wall_collision(){}

void check_self_collision(){}