#ifndef GAME_H // header guard - used in .h files to prevent contents of the header to be included twice
#define GAME_H

void game_init(void); // sets to initial state
void game_start(void); //starts a new game 
void game_update(void); // updates the game state each game loop
int game_is_over(void); // tells main if the game ended
int game_get_score(void); //returns the current score 
void game_add_score(int points); //adds point if object is collected 
void game_end(void); // changes the game to game-over state 

#endif 