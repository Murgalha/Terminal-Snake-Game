#ifndef _FRUIT_H_
#define _FRUIT_H_

/* Function that verifies if the pseudo-random generated
fruit position is a valid one, that is, if the position given
is not the player current position.
Returns 1 if the position is valid, and 0 otherwise */
int vfp(PLAYER *, POINT *);

/* This function verifies if the snake player ate the fruit,
that is, if the 'snake head' position is the same as the fruit.
Returns 1 if the position is the same, 0 otherwise */
int get_fruit(PLAYER *, POINT *);

#endif
