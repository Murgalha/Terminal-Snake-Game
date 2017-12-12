#include "utils.h"

int vfp(PLAYER *p, POINT *fruit) {
	int i;

	if(!fruit) return 0;

	/* check for every body point if has the same position
	as the generated fruit */
	for(i = 0; i < p->body_size; i++) {
		if(fruit->x == p->body[i].x && fruit->y == p->body[i].y)
			return 0;
	}
	return 1;
}
int get_fruit(PLAYER *p, POINT *fruit) {
	if(!fruit) return 0;

	/* return 1 if the player head got the fruit
	return 0 otherwise */
	if(p->body[0].x == fruit->x && p->body[0].y == fruit->y)
		return 1;
	return 0;
}
