#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <ncurses.h>
#include "utils.h"

/* Creates a new PLAYER* that contains the body points and size
(initialized at 4), the current player score (0), the position of the
'snake tail' (initialized as (-1, -1)) and a char representing
the position the player is going (u, d, l, r for up, down, left, right respectively) */
PLAYER *create_player(int, int);

/* Deallocate every PLAYER* and its contents allocated memory */
void destroy_player(PLAYER *);

/* Moves the player on the screen based on which position the snake
is going (as described on 'create_player' function) */
void move_player(PLAYER *);

/* Changes the direction the player is going based on what letter was hit
on the keyboard ('w', 'a', 's', or 'd'). If the player tries to go backwards,
nothing happens */
void change_direction(PLAYER *, char);

/* Draw the player on the screen, using 'mvwprintf' and the player's body
POINT* to know the points to print */
void draw_player(WINDOW *, PLAYER *);

/* Check if the snake collided on any of the borders of the window.
Returns 1 if collided, 0 otherwise */
int border_collision(WINDOW *, PLAYER *);

/* Increases the player score */
void score_up(PLAYER *);

/* Returns player score */
int get_score(PLAYER *);

/* Increases the snake body and puts a new point on the tail of the snake
Needed variables are updated */
void grow_up(PLAYER *);

/* Checks if the snake has collided with its own body.
Returns 1 on collision, 0 otherwise */
int self_collision(PLAYER *);

/* Prints a red 'X' on the 'snake head' to symbolize it is dead */
void print_dead(WINDOW *, PLAYER *);

#endif
