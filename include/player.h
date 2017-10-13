#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <ncurses.h>
#include <stdbool.h>
#include "utils.h"

typedef struct {
	char going;
	POINT *body;
	int body_size;
	int score;
	POINT last_pos;
} PLAYER;

PLAYER *create_player(int, int);
void destroy_player(PLAYER *);
void move_player(PLAYER *);
void change_direction(PLAYER *, char);
void draw_player(WINDOW *, PLAYER *);
bool border_collision(WINDOW *, PLAYER *);
void score_up(PLAYER *);
int get_score(PLAYER *);

#endif
