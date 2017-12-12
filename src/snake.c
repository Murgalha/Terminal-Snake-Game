#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include "utils.h"
#include "window.h"
#include "fruit.h"
#include "player.h"

int main(int argc, char *argv[]){
    int max_x, max_y, old_score, replay = 1;
    char c;
	PLAYER *p;
    POINT *fruit;
    WINDOW *win, *score;

    /* initialize colors */
	initscr();
    start_color();
    /* disable 'echo' command */
	noecho();
    /* disable cursor on window */
	curs_set(FALSE);

    init_colors();

    while (replay) {
        getmaxyx(stdscr, max_y, max_x);

        /* set window size */
        win = newwin(max_y - SCORE_SIZE, max_x, SCORE_SIZE, 0);
        score = newwin(SCORE_SIZE, max_x, 0, 0);

        init_pairs();

        /* set background color for main window
        and score */
        wbkgd(win, COLOR_PAIR(1));
        wbkgd(score, COLOR_PAIR(6));

        /* initializing, windows, variables and pointers */
        p = create_player(max_y/2, max_x/2);
        draw_borders(win);
        update_score(score, p->score);
        replay = 0;
        fruit = NULL;

        /* main game loop */
        while(1) {

            /* move and draw player */
    		move_player(p);
    		draw_player(win, p);
            old_score = get_score(p);

            /* if statement to check the fruit */
            if(get_fruit(p, fruit)) {
                score_up(p);
                grow_up(p);
            }

            /* while not a valid position for the fruit
            keep regenerating new position */
            while(!vfp(p, fruit))
                fruit = generate_fruit(win);

            /* if the score changes, the score window is updated */
            if(old_score != get_score(p)) {
                update_score(score, p->score);
                old_score = get_score(p);
            }

    		c = kbhit();

            /* check if the player has hit a key */
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

                /* check if pressed key is valid 
                       ('w', 'a', 's' or 'd') */
                if(is_valid(c))
                    change_direction(p, direction);
    		}

            wrefresh(win);
            wrefresh(score);

            /* check any type of collision */
            if(border_collision(win, p) || self_collision(p)) {
                print_dead(win, p);
                break;
            }

            /* reduce clock speed for the game */
            usleep(100000);
    	}
        /* game over screen */
        print_gameover(score, p->score);

        /* loop to see if the player wants to play again
        or quit the game */
        while(1) {
            c = wgetch(win);
            if(c == 'r') {
                replay = 1;
                break;
            }
            else if (c == 'q')
                break;
        }

        /* freeing memory */
        destroy_player(p);
        delwin(win);
        delwin(score);
    }

	endwin();
	return 0;
}
