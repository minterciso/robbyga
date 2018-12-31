#ifndef WORLD_H
#define WORLD_H

#include <stdio.h>
#include <stdlib.h>

#include "consts.h"

typedef struct world
{
  int cols, rows;
  e_tile **tiles;
} world;

world * create_world(int cols, int rows);
world * copy_world(world *w);
void destroy_world(world *w);
void print_world(FILE *stream, world *w);
e_tile get_tile(world *w, int col, int row);
int clean_tile(world *w, int col, int row);
void clear_world(world *w);
void fill_world(world *w);

#endif // WORLD_H
