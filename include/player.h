#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <ncurses.h>
#include "utils.h"

PLAYER *create_player(int, int);
void destroy_player(PLAYER *);
void move_player(PLAYER *);
void change_direction(PLAYER *, char);
void draw_player(WINDOW *, PLAYER *);
int border_collision(WINDOW *, PLAYER *);
void score_up(PLAYER *);
int get_score(PLAYER *);
void grow_up(PLAYER *);
int self_collision(PLAYER *);
void print_dead(WINDOW *, PLAYER *);

#endif
