#ifndef WORLD_H
#define WORLD_H

#include <stdio.h>
#include <stdlib.h>

#include "consts.h"

typedef struct world
{
  size_t x, y;
  e_tile **tiles;
} world;

world * create_world(size_t x, size_t y);
void destroy_world(world *w);
void print_world(FILE *stream, world *w);

#endif // WORLD_H
