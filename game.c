//Wiktoria 

#include "graphics.h"
#include "sprites.h"
#include "objects_functions.h"
#include "worm.h"
#include "game.h"
#include "timer.h"
#include <stdint.h>

static int score = 0; 
static int game_over = 0;
void render_frame(){
    // add a condition for checking if game is over
    clear_screen(BLACK);
    draw_border();
    draw_objects();
    draw_worm();
   // draw_face();
    draw_score();
}

void draw_score(){
    int score = get_score();
    // the x value we reach after printing SCORE: + space 4 pixels away from the end of the screen
    // 4 + 6*8 + 8 = 60
    int x = 60; 

    draw_text(4, 4, "SCORE: ", WHITE);

    if(score >= 100){
        // we add the digit to '0' as this way we obtain the ascii code for it 
        draw_char(x, 4, (char) ('0' + (score / 100) % 10), WHITE); 
        x += 8;
    }
    if(score >= 10){
        draw_char(x, 4, (char) ('0' + (score / 10) % 10), WHITE);
        x += 8;
    }
    draw_char(x, 4, (char) ('0' + score % 10), WHITE);
}

void show_game_over(){
    draw_text(129, 116, "GAME OVER", WHITE);
}

//Maria 

void game_init(){
    score = 0;
    game_over = 0;
    init_worm();
    init_objects();
}

void game_start(){
    game_over = 0;
    start_timer();
}

void update_game(){
    if(game_is_over()) return;
    set_direction();
    if(worm_should_move()){
        move_worm();
        check_wall_collision();
        check_self_collision();
        check_fruit_collision();
    }
}

void check_fruit_collision(){
    int head_x = worm_body[0][0];
    int head_y = worm_body[0][1];
    int index = find_object_collision(head_x, head_y);
    if(index != -1){
        ObjectType type = get_object_type(index);

        apply_fruit_effect(type);
        grow_worm();
        respawn_object(index);
    }
}

void update_score(int points){
    score += points;
}

int get_score(){
    return score;
}

int game_is_over(){
    return game_over;
}

void game_end(){
    game_over = 1;
}