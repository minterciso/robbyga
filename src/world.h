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

/**
 * @brief create_world Initialize a robby world with colsXrows size
 * @param cols The amount of cols of the world
 * @param rows The amount of rows of the world
 * @return A pointer to a world structure, initialized and with random dirt
 */
world * create_world(int cols, int rows);

/**
 * @brief copy_world Copy one world to a new one
 * @param w The original world to copy to
 * @return A pointer to a new world, with the exact size of the w world and the dirt on that world
 */
world * copy_world(world *w);

/**
 * @brief destroy_world Correctly free the world memory
 * @param w The world to free the memory
 */
void destroy_world(world *w);

/**
 * @brief print_world Print the world on the file stream
 * @param stream The file to print the world to
 * @param w The world to print
 */
void print_world(FILE *stream, world *w);

/**
 * @brief get_tile Return the tile on the row and col position of the world
 * @param w The world to look the tile into
 * @param col The column of the tile
 * @param row The row of the tile
 * @return The tile representation enum
 */
e_tile get_tile(world *w, int col, int row);

/**
 * @brief clean_tile Tries to clean the tile in the colum and row passed
 * @param w The world to clean the tile
 * @param col The column of the tile
 * @param row The row of the tile
 * @return 1 if success, 0 if the tile was already cleaned
 */
int clean_tile(world *w, int col, int row);

/**
 * @brief clear_world Remove all dirt from the world
 * @param w The world to clean
 */
void clear_world(world *w);

/**
 * @brief fill_world Randomly fill the world with dirt
 * @param w The world to fill with dirt
 */
void fill_world(world *w);

#endif // WORLD_H
