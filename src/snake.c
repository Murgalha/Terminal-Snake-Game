#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include "window.h"
#include "player.h"

int kbhit() {
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
    return ch;

  return 0;
}

int main(int argc, char *argv[]){
	int max_x, max_y, new_x, new_y;
	int i = 1, j = 1;
	PLAYER *p;
	char c;

	initscr();
	noecho();
	curs_set(0);

	getmaxyx(stdscr, max_y, max_x);

	p = create_player(max_x/2, max_y/2);

    WINDOW *win = newwin(max_y - SCORE_SIZE, max_x, SCORE_SIZE, 0);
	WINDOW *score = newwin(SCORE_SIZE, max_x, 0, 0);

	//draw_borders(win);

	while(1) {
		/*getmaxyx(stdscr, new_y, new_x);

		if (new_y != max_y || new_x != max_x)
			resize_window(win, score, &max_x, &max_y, &new_x, &new_y);
        */
		move_player(p);
		draw_player(win, p);
		mvwprintw(score, 0, (max_x)/2-((strlen("Score: ")+4)/2), "Score: ");

		wrefresh(win);
		wrefresh(score);
		usleep(100000);

		c = kbhit();

		if(c) {
			char direction;
			if(c == 'w')
				direction = 'u';
			else if(c == 's')
				direction = 'd';
			else if(c == 'a')
				direction = 'l';
			else if(c == 'd')
				direction = 'r';
			else if(c == 'k')
				break;
			change_direction(p, direction);
		}

		//j = (j%(max_x-2))+1;
		//if(j == 1) i = (i%(max_y-3))+1;
	}

	delwin(win);
	delwin(score);
    destroy_player(p);

	endwin();
	return 0;
}
