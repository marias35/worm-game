// Maria + Wiktoria cd
#include "game.h"
static int score;
static int game_over;

void game_init(){
score = 0;
game_over = 0;
}

void game_start(){
    score = 0;
    game_over = 0;
}

void game_update(){
    // general updates
}

int game_is_over(){
    return game_over;
}

int game_get_score(){
    return score;
}

void game_add_score(int points){
    score += points;
}

void end_game(){
    game_over = 1;
}