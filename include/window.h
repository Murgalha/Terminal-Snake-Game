#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "utils.h"
#include "player.h"

/* define the size of the score screen */
#define SCORE_SIZE 1

/* draw the borders of the playing window */
void draw_borders(WINDOW *);

/* generates a pseudo-random fruit position on the playing window */
POINT *generate_fruit(WINDOW *);

/* update the score window */
void update_score(WINDOW *, int);

/* print the game over message on the score screen */
void print_gameover(WINDOW *, int);

#endif
