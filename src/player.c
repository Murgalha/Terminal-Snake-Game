#include <stdlib.h>
#include <ncurses.h>
#include "player.h"
#include "utils.h"

int border_collision(WINDOW *w, PLAYER *p) {
	int border_x, border_y;

	getmaxyx(w, border_y, border_x);

	if(p->body[0].x == border_x-1 || p->body[0].x == 0)
		return 1;
	if(p->body[0].y == border_y-1 || p->body[0].y == 0)
		return 1;
	return 0;
}

int self_collision(PLAYER *p) {
	int i;

	for(i = 1; i < p->body_size; i++) {
		if(p->body[0].x == p->body[i].x && p->body[0].y== p->body[i].y)
			return 1;
	}
	return 0;
}

PLAYER *create_player(int y, int x) {
	PLAYER *p = (PLAYER *) malloc (sizeof(PLAYER));
	int i;

	p->going = 'r';
	p->score = 0;
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
	free(p->body);
	free(p);
}

void move_player(PLAYER *p) {
	int i;

	p->last_pos.x = p->body[(p->body_size)-1].x;
	p->last_pos.y = p->body[(p->body_size)-1].y;

	for(i = (p->body_size)-1; i > 0; i--)
		p->body[i] = p->body[i-1];

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

	mvwprintw(w, p->last_pos.y, p->last_pos.x, " ");
	wrefresh(w);
	wattron(w, COLOR_PAIR(2));
	for(i = 0; i < p->body_size; i++) {
		mvwprintw(w, p->body[i].y, p->body[i].x, "o");
		wrefresh(w);
	}
	wattroff(w, COLOR_PAIR(2));
}

void score_up(PLAYER *p) {
	(p->score)++;
}

int get_score(PLAYER *p) {
	return p->score;
}

void grow_up(PLAYER *p) {
	int aux;

	p->body = (POINT *) realloc (p->body, sizeof(POINT)*((p->body_size)+1));

	if(p->body[p->body_size-1].x == p->body[p->body_size-2].x && p->body[p->body_size-1].y == (p->body[p->body_size-2].y)+1) {
		// must place down
		p->body[p->body_size].x = p->body[(p->body_size)-1].x;
		p->body[p->body_size].y = (p->body[(p->body_size)-1].y)+1;
	}
	else if(p->body[p->body_size-1].x == p->body[p->body_size-2].x && p->body[p->body_size-1].y == (p->body[p->body_size-2].y)-1) {
		// must place up
		p->body[p->body_size].x = p->body[(p->body_size)-1].x;
		p->body[p->body_size].y = (p->body[(p->body_size)-1].y)-1;
	}
	else if(p->body[p->body_size-1].y == p->body[p->body_size-2].y && p->body[p->body_size-1].x == (p->body[p->body_size-2].x)+1) {
		// must place right
		p->body[p->body_size].x = (p->body[(p->body_size)-1].x)+1;
		p->body[p->body_size].y = p->body[(p->body_size)-1].y;
	}
	else {
		// must place left
		p->body[p->body_size].x = (p->body[(p->body_size)-1].x)-1;
		p->body[p->body_size].y = p->body[(p->body_size)-1].y;
	}
	(p->body_size)++;
}

void print_dead(WINDOW *w, PLAYER *p) {
	if(border_collision(w, p)) {
		wattron(w, COLOR_PAIR(4));
		mvwprintw(w, p->body[0].y, p->body[0].x, DEAD);
		wrefresh(w);
		wattroff(w, COLOR_PAIR(4));
	}
	else {
		wattron(w, COLOR_PAIR(3));
		mvwprintw(w, p->body[0].y, p->body[0].x, DEAD);
		wrefresh(w);
		wattroff(w, COLOR_PAIR(3));
	}
}
