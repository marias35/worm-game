#ifndef GAME_H
#define GAME_H

void game_init(void);
void game_start(void);
void game_update(void);
int game_is_over(void);
int game_get_score(void);
void game_add_score(int points);
void game_end(void);

#endif