#include "objects_functions.h"
#include "sprites.h"
#include "graphics.h"
#include "game.h"
#include "worm.h"
//Maria
static Object objects[MAX_OBJECTS]; //array with the 3 objects currently used in the game

//we implement a linear congruential pseudo-random generator to replace the rand()
//an LCG formula: X(n+1) = (a * X(n) + c) mod m
// a= 1103515245 and c = 12345;
// the seed stores the current X(n), since random_seed is unsigned int 
//it wraps around when excedes the max value of this type; with 32-bit unsigned int it gives modulo 2^32 

static unsigned int random_seed = 12345;

static unsigned int random_number(){
    random_seed = random_seed * 1103515245 + 12345;
    return random_seed;
}

//we initialize all objects.
//at the beginning all objects are marked inactive
//then we spawn the 3 objects and those become active
// we start the game with 3 objects on the screen


void init_objects(){
    for(int i = 0; i < MAX_OBJECTS; i++){
        objects[i].active = 0;
    }
    for(int i = 0; i < MAX_OBJECTS; i++){
        spawn_object();
    }
}

void spawn_object(){
    for(int i = 0; i < MAX_OBJECTS; i++){

        if(!objects[i].active){    // //we look for the first inactive object 

            objects[i].type = random_number() % 6; //we choose the fruit type using random_number and %6 to select one of the 6 object options (0-5)
            random_free_position( &objects[i].x, &objects[i].y ); //find a random position diff than the position of the already active objects
            objects[i].active = 1;
            return; // only one object is spawned each call

        }

    }

}

void random_free_position(int *x, int *y){

int free_position = 0; // we generate positions until a free one is found

while(!free_position){

    *x = 1 + random_number() % (SCREEN_WIDTH - SPRITE_SIZE - 1); // we start from 1 to leave room for the 1 pixel border
    *y = 1 + random_number() % (SCREEN_HEIGHT - SPRITE_SIZE - 1); //we must make sure to have enough space for the sprite so we substract the size of it and 1
    free_position = 1;

    for(int i = 0; i < MAX_OBJECTS; i++){
        if(objects[i].active){  // only compare with objects that currently exist
            if((*x < (objects[i].x + SPRITE_SIZE)) && // new object's left side < active object right side
               ((*x + SPRITE_SIZE) > objects[i].x) &&  // new right side > active left side
               (*y < (objects[i].y + SPRITE_SIZE)) &&  // new object top is above active object bottom
               ((*y + SPRITE_SIZE) > objects[i].y)){   //new object bottom is under active object top
                free_position = 0;
                break;
            }
        }
    }
}
}

//respawns an object after it has been collected

void respawn_object(int index){
    objects[index].active = 0; 
    objects[index].type = random_number() % 6; // the object gets a new object type
    random_free_position(&objects[index].x, &objects[index].y); // it gets a new available position 
    objects[index].active = 1;
}

//we apply effects to collected fruits
// APPLE - adds 1 point;
// GRAPES - adds 5 points;
// WATERMELON - increases worm speed by decreasing the movement interval;
// STRAWBERRY - decreases worm speed by increasing the movement interval;

void apply_fruit_effect(ObjectType type){
    switch(type){
        case APPLE:
            update_score(1);
            break;
        case GRAPES:
            update_score(5);
            break;
        case WATERMELON:
            change_speed(-1);
            break;
        case STRAWBERRY:
            change_speed(1);
            break;
        case HAPPY_FACE:
            face = FACE_HAPPY;
            break;
        case SAD_FACE:
            face = FACE_SAD;
            break;
    }
}

// this function decides which sprite belongs to which object
// we use draw_sprite() to actually draw the 10*10 pixels to the frame

void draw_objects(){
    for(int i = 0; i < MAX_OBJECTS; i++){
        if(objects[i].active){
            switch(objects[i].type){
                case APPLE:
                    draw_sprite(objects[i].x, objects[i].y, sprite_apple);
                    break;
                case GRAPES:
                    draw_sprite(objects[i].x, objects[i].y, sprite_grapes);
                    break;
                case WATERMELON:
                    draw_sprite(objects[i].x, objects[i].y, sprite_watermelon);
                    break;
                case STRAWBERRY:
                    draw_sprite(objects[i].x, objects[i].y, sprite_strawberry);
                    break;
                case HAPPY_FACE:
                     draw_sprite(objects[i].x, objects[i].y, sprite_smile);
                     break;
                case SAD_FACE:
                    draw_sprite(objects[i].x, objects[i].y, sprite_sad);
                    break;
            }
        }
    }
}
int find_object_collision(int x, int y){
    for(int i = 0; i < MAX_OBJECTS; i++){
        if(objects[i].active){
            if( (x < (objects[i].x + SPRITE_SIZE)) &&
                ((x + SPRITE_SIZE > objects[i].x)) &&
                (y < (objects[i].y + SPRITE_SIZE)) &&
                ((y + SPRITE_SIZE) > objects[i].y)){
                    return i;
                }
        }
    }
    return -1; // no object was hit
}

ObjectType get_object_type(int index){
    return objects[index].type;
}