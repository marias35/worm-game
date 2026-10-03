// #include "objects_functions.h"
// #include "sprites.h"
// #include "graphics.h"
// #include "game.h"
// #include <stdlib.h>
// //Maria
// static Object objects[MAX_OBJECTS];
// void init_objects(){
//     for(int i = 0; i < MAX_OBJECTS; i++){
//         objects[i].active = 0;
//     }
//     for(int i = 0; i < MAX_OBJECTS; i++){
//         spawn_object();
//     }
// }

// void spawn_object(){
//     for(int i = 0; i < MAX_OBJECTS; i++){
//         if(!objects[i].active){
//             objects[i].type = rand() % 4;
//             random_free_position( &objects[i].x, &objects[i].y );
//             objects[i].active = 1;
//             return;
//         }
//     }

// }

// void random_free_position(int *x, int *y){
// int free_position = 0;
// while(!free_position){
//     *x = 1 + rand() % (SCREEN_WIDTH - SPRITE_SIZE - 1);
//     *y = 1 + rand() % (SCREEN_HEIGHT - SPRITE_SIZE - 1);
//     free_position = 1;
//     for(int i = 0; i < MAX_OBJECTS; i++){
//         if(objects[i].active){
//             if(*x < objects[i].x + SPRITE_SIZE && *x + SPRITE_SIZE > objects[i].x && *y < objects[i].y + SPRITE_SIZE && *y + SPRITE_SIZE > objects[i].y){
//                 free_position = 0;
//                 break;
//             }
//         }
//     }
// }
// }

// void respawn_object(int index){
//     objects[index].type = rand() % 4;
//     random_free_position(&objects[index].x, &objects[index].y);
//     objects[index].active = 1;
// }
// void draw_objects(){
//     for(int i = 0; i < MAX_OBJECTS; i++){
//         if(objects[i].active){

//             switch(objects[i].type){

//                 case APPLE:
//                     draw_sprite(objects[i].x, objects[i].y, sprite_apple);
//                     break;

//                 case GRAPES:
//                     draw_sprite(objects[i].x, objects[i].y, sprite_grapes);
//                     break;

//                 case WATERMELON:
//                     draw_sprite(objects[i].x, objects[i].y, sprite_watermelon);
//                     break;

//                 case STRAWBERRY:
//                     draw_sprite(objects[i].x, objects[i].y, sprite_strawberry);
//                     break;
//             }
//         }
//     }
// }

// void apply_fruit_effect(ObjectType type){
// }
