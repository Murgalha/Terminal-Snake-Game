#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include "player.h"

bool border_collision(WINDOW *w, PLAYER *p) {
	int border_x, border_y;

	getmaxyx(w, border_y, border_x);

	if(p->body[0].x == border_x-1 || p->body[0].x == 0)
		return true;
	if(p->body[0].y == border_y-1 || p->body[0].y == 0)
		return true;
	return false;
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

	for(i = 0; i < p->body_size; i++) {
		mvwprintw(w, p->body[i].y, p->body[i].x, "o");
		wrefresh(w);
	}
}

void score_up(PLAYER *p) {
	(p->score)++;
}

int get_score(PLAYER *p) {
	return p->score;
}
