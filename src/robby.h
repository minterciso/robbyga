#ifndef ROBBY_H
#define ROBBY_H

#include "world.h"

void place_robby(world *w, size_t x, size_t y);
int move_robby(world *w, size_t x0, size_t y0, size_t x1, size_t y1);
void get_robby_position(world *w, size_t *x, size_t *y);


#endif // ROBBY_H
