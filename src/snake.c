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

int is_valid(char c) {
    if(c == 'w' || c == 'a' || c == 's' || c == 'd')
        return 1;
    return 0;
}

int main(int argc, char *argv[]){
	int max_x, max_y, old_score, replay = 1;
    char c;
	PLAYER *p;
    POINT *fruit;
    WINDOW *win, *score;

	initscr();
	noecho();
	curs_set(FALSE);


    while (replay) {
        getmaxyx(stdscr, max_y, max_x);

        win = newwin(max_y - SCORE_SIZE, max_x, SCORE_SIZE, 0);
        score = newwin(SCORE_SIZE, max_x, 0, 0);

        p = create_player(max_y/2, max_x/2);

        draw_borders(win);
        update_score(score, p->score);
        replay = 0;
        fruit = NULL;
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

            if(old_score != get_score(p)) {
                update_score(score, p->score);
                old_score = get_score(p);
            }

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
                if(is_valid(c))
                    change_direction(p, direction);
    		}

            wrefresh(win);
            wrefresh(score);

            if(border_collision(win, p) || self_collision(p)) {
                print_dead(win, p);
                break;
            }

            usleep(100000);
    	}
        print_gameover(score, p->score);

        while(1) {
        c = wgetch(win);
        if(c == 'r') {
            replay = 1;
            break;
        }
        else if (c == 'q')
            break;
        }
        destroy_player(p);
        delwin(win);
        delwin(score);
    }

	endwin();
	return 0;
}
