#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include "utils.h"
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
	int max_x, max_y, old_score;
	PLAYER *p;
	char c;
    POINT *fruit = NULL;

	initscr();
	noecho();
	curs_set(FALSE);

	getmaxyx(stdscr, max_y, max_x);

    WINDOW *win = newwin(max_y - SCORE_SIZE, max_x, SCORE_SIZE, 0);
	WINDOW *score = newwin(SCORE_SIZE, max_x, 0, 0);

    p = create_player(max_y/2, max_x/2);

	draw_borders(win);
    update_score(score, p->score);

	while(1) {

		move_player(p);
		draw_player(win, p);
        old_score = get_score(p);

        if(get_fruit(p, fruit)) {
            score_up(p);
            grow_up(p);
        }

        while(!vfp(p, fruit))
            fruit = generate_fruit(win);

        wrefresh(win);
        wrefresh(score);

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
			change_direction(p, direction);
		}

        if(old_score != get_score(p)) {
            update_score(score, p->score);
            old_score = get_score(p);
        }

        if(border_collision(win, p)) break;

        usleep(100000);
	}

	delwin(win);
	delwin(score);
    destroy_player(p);

	endwin();
	return 0;
}
