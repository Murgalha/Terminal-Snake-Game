#include <stdlib.h>
#include <ncurses.h>
#include "player.h"
#include "utils.h"

int border_collision(WINDOW *w, PLAYER *p) {
	int border_x, border_y;

	getmaxyx(w, border_y, border_x);

	/* check if the snake head collided with any of
	the borders */
	if(p->body[0].x == border_x-1 || p->body[0].x == 0)
		return 1;
	if(p->body[0].y == border_y-1 || p->body[0].y == 0)
		return 1;
	return 0;
}

int self_collision(PLAYER *p) {
	int i;

	/* for every body point, check the
	collision with the head */
	for(i = 1; i < p->body_size; i++) {
		if(p->body[0].x == p->body[i].x && p->body[0].y== p->body[i].y)
			return 1;
	}
	return 0;
}

PLAYER *create_player(int y, int x) {
	PLAYER *p = (PLAYER *) malloc (sizeof(PLAYER));
	int i;

	/* set player going to the right, initial
	score to 0 */
	p->going = 'r';
	p->score = 0;

	/* set initial body size to 4 and set the body
	positions */
	p->body = (POINT *) malloc (sizeof(POINT)*4);
	for(i = 0; i < 4; i++) {
		p->body[i].x = x-i;
		p->body[i].y = y;
	}

	p->body_size = 4;
	p->last_pos.x = -1;
	p->last_pos.y = -1;

	return p;
}

void destroy_player(PLAYER *p) {
	/* free pointers */
	free(p->body);
	free(p);
}

void move_player(PLAYER *p) {
	int i;

	/* set the 'tail' position as the last */
	p->last_pos.x = p->body[(p->body_size)-1].x;
	p->last_pos.y = p->body[(p->body_size)-1].y;

	/* moving every body point */
	for(i = (p->body_size)-1; i > 0; i--)
		p->body[i] = p->body[i-1];

	/* moving the head based on the going position */
	if(p->going == 'u')
		(p->body[0].y)--;
	else if(p->going == 'd')
		(p->body[0].y)++;
	else if(p->going == 'l')
		(p->body[0].x)--;
	else
		(p->body[0].x)++;
}

void change_direction(PLAYER *p, char cmd) {
	/* change the player position based on the key pressed */
	/* if the key pressed is the exact or the opposite as the 
	going position, nothing change */
	if((p->going == 'u' && cmd == 'd') || (p->going == 'd' && cmd == 'u'))
		return;
	if((p->going == 'r' && cmd == 'l') || (p->going == 'l' && cmd == 'r'))
		return;
	if(p->going == cmd)
		return;
	p->going = cmd;
}

void draw_player(WINDOW *w, PLAYER *p) {
	int i;

	/* erase the tail position */
	mvwprintw(w, p->last_pos.y, p->last_pos.x, " ");
	wrefresh(w);
	wattron(w, COLOR_PAIR(2));
	/* for every body point, put an 'o' as a body part */
	for(i = 0; i < p->body_size; i++) {
		mvwprintw(w, p->body[i].y, p->body[i].x, "o");
		wrefresh(w);
	}
	wattroff(w, COLOR_PAIR(2));
}

void score_up(PLAYER *p) {
	/* increase 1 to score */
	(p->score)++;
}

int get_score(PLAYER *p) {
	return p->score;
}

void grow_up(PLAYER *p) {
	int aux;

	/* realloc the body point to increase the size */
	p->body = (POINT *) realloc (p->body, sizeof(POINT)*((p->body_size)+1));

	/* put the new body part got from the fruit on the end of the snake,
	based on the positions of the last and penultimate parts */

	/*                 penultimate > o
									 o < last
							                          */
	if(p->body[p->body_size-1].x == p->body[p->body_size-2].x && p->body[p->body_size-1].y == (p->body[p->body_size-2].y)+1) {
		/* place down */
		p->body[p->body_size].x = p->body[(p->body_size)-1].x;
		p->body[p->body_size].y = (p->body[(p->body_size)-1].y)+1;
	}

	/*                        last > o
									 o < penultimate         */
	else if(p->body[p->body_size-1].x == p->body[p->body_size-2].x && p->body[p->body_size-1].y == (p->body[p->body_size-2].y)-1) {
		/* place up */
		p->body[p->body_size].x = p->body[(p->body_size)-1].x;
		p->body[p->body_size].y = (p->body[(p->body_size)-1].y)-1;
	}

	/*                        penultimate > oo < last            */
	else if(p->body[p->body_size-1].y == p->body[p->body_size-2].y && p->body[p->body_size-1].x == (p->body[p->body_size-2].x)+1) {
		/* place right */
		p->body[p->body_size].x = (p->body[(p->body_size)-1].x)+1;
		p->body[p->body_size].y = p->body[(p->body_size)-1].y;
	}
		/*                        last > oo < penultimate            */
	else {
		/* place left */
		p->body[p->body_size].x = (p->body[(p->body_size)-1].x)-1;
		p->body[p->body_size].y = p->body[(p->body_size)-1].y;
	}
	(p->body_size)++;
}

void print_dead(WINDOW *w, PLAYER *p) {
	/* put a red 'X' on the border 
	with gray background*/
	if(border_collision(w, p)) {
		wattron(w, COLOR_PAIR(4));
		mvwprintw(w, p->body[0].y, p->body[0].x, DEAD);
		wrefresh(w);
		wattroff(w, COLOR_PAIR(4));
	}
	/* put a red 'X' on self 
	with white background */
	else {
		wattron(w, COLOR_PAIR(3));
		mvwprintw(w, p->body[0].y, p->body[0].x, DEAD);
		wrefresh(w);
		wattroff(w, COLOR_PAIR(3));
	}
}
