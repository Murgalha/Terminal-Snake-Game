#ifndef _UTILS_H_
#define _UTILS_H_

#define DEAD "X"
#define FRUIT "#"
#define COLOR_GREY 8

/* define a point on the screen, with its x and y coordinates */
typedef struct {
	int x, y;
} POINT;

/* define the player with a char representing where the snake is going,
the body points and size, the player's score and the 'snake tail' position */
typedef struct {
	char going;
	POINT *body;
	int body_size;
	int score;
	POINT last_pos;
} PLAYER;

/* Returns the character that was hit on the keyboard */
int kbhit();

/* Checks if the key hit is a valid one, that is, if is 'w', 'a', 's' or 'd'
to later change the player direction */
int is_valid(char);

/* Initialize all needed colors in the game */
void init_colors();

/* Initialize all color pairs (foreground and background) needed in the game */
void init_pairs();

#endif
