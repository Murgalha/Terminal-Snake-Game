#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "utils.h"
#include "player.h"

#define SCORE_SIZE 1

void draw_borders(WINDOW *);
POINT *generate_fruit(WINDOW *);
bool vfp(PLAYER *, POINT *);
bool get_fruit(PLAYER *, POINT *);
void update_score(WINDOW *, int);
void print_gameover(WINDOW *, int);

#endif
