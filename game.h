#ifndef GAME_H 
#define GAME_H
  
void render_frame(); 
void draw_score();
void show_game_over();

void game_init();
void game_start();
void update_game();
void check_fruit_collision();
void update_score(int points);
int get_score();
int game_is_over();
void game_end();

#endif 