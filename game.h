#ifndef GAME_H // header guard - used in .h files to prevent contents of the header to be included twice
#define GAME_H

void game_init();  
void render_frame(); 
void draw_score();
void show_game_over();

void game_start();
void update_game();
void check_fruit_collision();
void update_score();
int get_score();
void game_is_over();
void game_end();

#endif 