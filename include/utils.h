#ifndef _UTILS_H_
#define _UTILS_H_

#define DEAD "X"
#define FRUIT "#"
#define COLOR_GREY 8

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

int kbhit();
int is_valid(char);
void init_colors();
void init_pairs();

#endif
