

#include "graphics.h"
#include "sprites.h"
#include "objects_functions.h"
#include "worm.h"
#include "game.h"
#include "timer.h"

static int score = 0; 
static int game_over = 0;

//Wiktoria 
void render_frame(){
    clear_screen(BLACK);
    draw_border();
    draw_objects();
    draw_worm();
    draw_score(4, 4);
}

void draw_score(int x, int y){
    int score = get_score();
    // the x value we reach after printing "SCORE: " + the x-position
    // x + 6*8 + 8 = 54 + x
    int space = 54 + x; 

    draw_text(x, y, "SCORE: ", WHITE);

    if(score >= 100){
        // we add the digit to '0' as this way we obtain the ascii code for it 
        draw_char(space, y, (char) ('0' + (score / 100) % 10), WHITE); 
        space += 8;
    }
    if(score >= 10){
        draw_char(space, y, (char) ('0' + (score / 10) % 10), WHITE);
        space += 8;
    }
    draw_char(space, y, (char) ('0' + score % 10), WHITE);
}

void show_game_over(){
    draw_text(129, 116, "GAME OVER", WHITE);
    draw_score(129 , 126);
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