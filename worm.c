#include "graphics.h"
#include "worm.h"
#include "sprites.h"
#include "game.h"

int worm_body[MAX_WORM_LENGTH][2];
int worm_length;
static int worm_speed = WORM_START_SPEED; //determine how many 0.1 seconds time ticks must pass before the woerm moves
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
    worm_speed = WORM_START_SPEED;
    face = FACE_HAPPY;

    for(int i = 0; i < worm_length; i++){
        worm_body[i][0] = SCREEN_WIDTH/2 - SPRITE_SIZE/2; // we divide the width and height to get the horizontal/vertical center of the screen;
        worm_body[i][1] = SCREEN_HEIGHT/2 - SPRITE_SIZE/2 + i*SPRITE_SIZE; // we substract half of sprite size to center it around the middle;
        //We add i*SPRITE_SIZE to the y-coordinate so each following
        // segment is placed one segment below the previous one
    }
    //initially the worm moves up
    worm_direction = UP;
    next_direction = UP;
}

void set_direction(){
    direction requested = read_direction();
    next_direction = current_direction(worm_direction, requested);
}

void move_worm(){
    // we first move every body segment to the position of the segment in front of it;
    // we start from tail and move towards the head so we don't lose the old position of the segments
    for(int i = worm_length - 1; i > 0; i--){
        worm_body[i][0] = worm_body[i-1][0];
        worm_body[i][1] = worm_body[i-1][1];
    }

    worm_direction = next_direction;
    //we move only the head by sprite_size pixels because one worm segment is sprite_size pixels wide/tall;
    //the body was already moved to follow the position of the previous segments;
    switch(worm_direction){
        case UP:
                worm_body[0][1] -= SPRITE_SIZE;
                break;
        case DOWN: 
                worm_body[0][1] += SPRITE_SIZE;
                break;
        case RIGHT: 
                worm_body[0][0] += SPRITE_SIZE;
                break;
        case LEFT:
                worm_body[0][0] -= SPRITE_SIZE;
                break;
        default: // if the direction is none, the head does not move;
             break;
    }
}

void grow_worm(){
    if(worm_length < MAX_WORM_LENGTH){
        int tail = worm_length - 1;
     // direction x and y tell us the direction in which the tail is pointing
     //so the new segment points to the same direction

        int direction_x = worm_body[tail][0] - worm_body[tail - 1][0];
        int direction_y = worm_body[tail][1] - worm_body[tail - 1][1];
     // we add direction_x and direction_y to the tail's position so the new segment continues in the same direction as the worm;
        worm_body[worm_length][0] = worm_body[tail][0] + direction_x;
        worm_body[worm_length][1] = worm_body[tail][1] + direction_y;
        worm_length++;
    }
}

void change_speed(int amount){
    //changes the movement speed by the amount givent by a fruit
    //a negative amount = faster and a positive amount = slower
    worm_speed += amount;
    
    if(worm_speed < 1){
        worm_speed = 1; // prevent the worm from becoming too fast
    }
    if(worm_speed > 10){
        worm_speed = 10; //prevent the worm from becoming too slow
    }
}

void check_wall_collision(){
    int x = worm_body[0][0]; // we get the position of the head;
    int y = worm_body[0][1];
    //we check the right/left & top/bottom borders;
    // x is the left side of the head, while x + sprite_size is the right side;
    if( (x < BORDER_THICKENSS) || ( ( x + SPRITE_SIZE ) > ( SCREEN_WIDTH - BORDER_THICKENSS) ) ){
        game_end();
    }
    if( (y < BORDER_THICKENSS) || ( (y + SPRITE_SIZE) > (SCREEN_HEIGHT - BORDER_THICKENSS) ) ){
        game_end();
    }
}

void check_self_collision(){
    int head_x = worm_body[0][0]; 
    int head_y = worm_body[0][1];

    for(int i = 1; i < worm_length; i++){ // we start from 1 because worm_body[0] is the head and we do not want to compare the head with itself
        if( (head_x < (worm_body[i][0] + SPRITE_SIZE) ) && 
            ( (head_x + SPRITE_SIZE) > worm_body[i][0]) &&
            (head_y < (worm_body[i][1] + SPRITE_SIZE) ) &&
            ( (head_y + SPRITE_SIZE) > worm_body[i][1]) ){
                
                face = FACE_SAD;
                game_end();
                return;
            }
    }
}
int worm_should_move(){
    if(get_movement_counter() >= worm_speed){
        reset_movement_counter();
        return 1; // the worm is going to move
    }
    return 0; // not enough time passed yet so the worm stays in place
}