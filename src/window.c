#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>
#include "utils.h"
#include "window.h"


void draw_borders(WINDOW *screen) {
	int x, y, i;

	getmaxyx(screen, y, x);

	// drawing side border
	for (i = 1; i < y-1; i++) {
		mvwprintw(screen, i, 0, "|");
		mvwprintw(screen, i, x - 1, "|");
	}

	// top and bottom border
	for(i = 1; i < x-1; i++) {
		mvwprintw(screen, 0, i, "-");
		mvwprintw(screen, y-1, i, "-");
	}
}

POINT *generate_fruit(WINDOW *w) {
	int border_x, border_y;
	POINT *random = (POINT *) malloc (sizeof(POINT));

	srand(time(NULL));

	random->x = rand();
	random->y = rand();

	getmaxyx(w, border_y, border_x);

	random->x = (rand()%(border_x-2))+1;
	random->y = (rand()%(border_y-2))+1;

	mvwprintw(w, random->y, random->x, FRUIT);
	wrefresh(w);

	return random;
}

bool vfp(PLAYER *p, POINT *fruit) {
	int i;

	if(!fruit) return false;

	for(i = 0; i < p->body_size; i++) {
		if(fruit->x == p->body[i].x && fruit->y == p->body[i].y)
			return false;
	}
	return true;
}
bool get_fruit(PLAYER *p, POINT *fruit) {
	if(!fruit) return false;

	if(p->body[0].x == fruit->x && p->body[0].y == fruit->y)
		return true;
	return false;
}

char *score2str(int score) {
	char *str;
	asprintf(&str, "%d", score);
	return str;
}

void update_score(WINDOW *w, int score) {
	int x, y;
	char *str;

	getmaxyx(w, y, x);
	y++;
	str = score2str(score);

	mvwprintw(w, 0, (x/2)-((strlen("Score: ")+strlen(str))/2), "Score: %s", str);
	wrefresh(w);
	free(str);
}
