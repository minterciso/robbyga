#ifndef ROBBY_H
#define ROBBY_H

#include "world.h"

void place_robby(world *w, int col, int row);
float move_robby(world *w, int col0, int row0, int col1, int row1);
void get_robby_position(world *w, int *col, int *row);
void get_neighbours(world *w, unsigned int *n);

#endif // ROBBY_H
