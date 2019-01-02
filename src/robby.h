#ifndef ROBBY_H
#define ROBBY_H

#include "world.h"

/**
 * @brief place_robby Place Robby into the world
 * @param w The world to place robby
 * @param col The column robby is
 * @param row The row robby is
 */
void place_robby(world *w, int col, int row);

/**
 * @brief move_robby Move robby to one cell and return a value if there was a wall hit
 * @param w The world
 * @param col0 The original robby column
 * @param row0 The original robby row
 * @param col1 The destination robby column
 * @param row1 The destination robby row
 * @return -5.0 if robby hitted a wall, 0.0 otherwise
 */
float move_robby(world *w, int col0, int row0, int col1, int row1);

/**
 * @brief get_robby_position Return robby position in the pointer col and row
 * @param w The world
 * @param col Robby column position
 * @param row Robby row position
 */
void get_robby_position(world *w, int *col, int *row);

/**
 * @brief get_neighbours Get the neighbours of the robby and store in the n array, initialized with size 5
 * @param w The world
 * @param n An already initialized unsigned int array with 5 positions
 */
void get_neighbours(world *w, unsigned int *n);

#endif // ROBBY_H
