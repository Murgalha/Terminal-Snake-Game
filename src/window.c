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

int vfp(PLAYER *p, POINT *fruit) {
	int i;

	if(!fruit) return 0;

	for(i = 0; i < p->body_size; i++) {
		if(fruit->x == p->body[i].x && fruit->y == p->body[i].y)
			return 0;
	}
	return 1;
}
int get_fruit(PLAYER *p, POINT *fruit) {
	if(!fruit) return 0;

	if(p->body[0].x == fruit->x && p->body[0].y == fruit->y)
		return 1;
	return 0;
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
	str = score2str(score);

	mvwprintw(w, 0, (x/2)-((strlen("Score: ")+strlen(str))/2), "Score: %s", str);
	wrefresh(w);
	free(str);
}

void print_gameover(WINDOW *w, int score) {
	int x, y;
	char *str;

	asprintf(&str, "You scored: %d. Press 'Q' to quit or 'R' to play again", score);

	getmaxyx(w, y, x);

	mvwprintw(w, y-1, (x/2)-(strlen(str)/2), str);
	wrefresh(w);
}
