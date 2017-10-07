#include <ncurses.h>
#include "window.h"

void resize_window(WINDOW *win, WINDOW *score, int *parent_x, int *parent_y, int *new_x, int *new_y) {

	*parent_x = *new_x;
	*parent_y = *new_y;
	wresize(win, *new_y - SCORE_SIZE, *new_x);
	wresize(score, SCORE_SIZE, *new_x);

	mvwin(score, 0, 0);

	wclear(stdscr);
	wclear(win);
	wclear(score);

	//draw_borders(win);
}

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
