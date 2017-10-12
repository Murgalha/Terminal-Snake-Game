#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <ncurses.h>
#include <stdbool.h>

typedef struct {
	int x, y;
} POINT;


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
bool collision(WINDOW *, PLAYER *);

#endif
