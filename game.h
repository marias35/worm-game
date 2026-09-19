#ifndef GAME_H // header guard - used in .h files to prevent contents of the header to be included twice
#define GAME_H

void game_init(); // sets to initial state
void game_start(); //starts a new game 
void game_update(); // updates the game state each game loop
int game_is_over(); // tells main if the game ended
int game_get_score(); //returns the current score 
void game_add_score(int points); //ads point if object is collected 
void game_end(); // changes the game to gave-ver state 

#endif 