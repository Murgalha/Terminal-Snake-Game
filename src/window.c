#include <ncurses.h>
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
