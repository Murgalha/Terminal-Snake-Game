#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <time.h>
#include "utils.h"
#include "window.h"

void draw_borders(WINDOW *w) {
	int x, y, i;

	getmaxyx(w, y, x);

	wattron(w, COLOR_PAIR(4));

	/* draw side border */
	for (i = 0; i < y; i++) {
		mvwprintw(w, i, 0, " ");
		mvwprintw(w, i, x - 1, " ");
	}
	/* draw bottom and top border */
	for(i = 0; i < x; i++) {
		mvwprintw(w, 0, i, " ");
		mvwprintw(w, y-1, i, " ");
	}
	wattroff(w, COLOR_PAIR(4));
}

POINT *generate_fruit(WINDOW *w) {
	int border_x, border_y;
	POINT *random = (POINT *) malloc (sizeof(POINT));

	srand(time(NULL));

	getmaxyx(w, border_y, border_x);

	/* generate two random numbers inside
	the window's limits */
	random->x = (rand()%(border_x-2))+1;
	random->y = (rand()%(border_y-2))+1;

	wattron(w, COLOR_PAIR(5));

	mvwprintw(w, random->y, random->x, FRUIT);
	wrefresh(w);

	wattroff(w, COLOR_PAIR(5));

	return random;
}

char *score2str(int score) {
	char *str;
	/* saving 'score' value on char* */
	asprintf(&str, "%d", score);
	return str;
}

void update_score(WINDOW *w, int score) {
	int x, y;
	char *str;

	getmaxyx(w, y, x);
	/* get current score as char* */
	str = score2str(score);
	/* update score window */
	mvwprintw(w, 0, (x/2)-((strlen("Score: ")+strlen(str))/2), "Score: %s", str);
	wrefresh(w);
	free(str);
}

void print_gameover(WINDOW *w, int score) {
	int x, y;
	char *str;
	/* saving message on a char* */
	asprintf(&str, "You scored: %d. Press 'Q' to quit or 'R' to play again", score);
	getmaxyx(w, y, x);

	/* print game over message */
	wattron(w, COLOR_PAIR(4));
	mvwprintw(w, y-1, (x/2)-(strlen(str)/2), str);
	wrefresh(w);
	wattroff(w, COLOR_PAIR(4));
}
