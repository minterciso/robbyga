#include "robby.h"
#include "utils.h"
#include <string.h>

robby* create_population(void){
  size_t pop_bytes = sizeof(robby)*POP_SIZE;
  robby *pop = NULL;

  // Allocate memory for the population
  if((pop=(robby*)malloc(pop_bytes))==NULL){
      perror("malloc");
      return NULL;
    }
  memset(pop, 0, pop_bytes);
  // Create a random strategy for each individual
  for(int i=0;i<POP_SIZE;i++){
      for(int j=0;j<S_SIZE;j++)
        pop[i].strategy[j] = gsl_rng_uniform_int(prng, S_MAX_OPTIONS);
      pop[i].fitness = -99.99;
      pop[i].weight = -99.99;
    }
  return pop;
}

void destroy_population(robby *pop){
  if(pop==NULL) return;
  free(pop);
}

int execute_strategy(session *s, robby *r){
  // This function needs to get the robby neighbours, translate it to a decimal index for the strategy, get the strategy and execute it
  int n[5]; // Neighbours
  int r_row, r_col; // Robby position
  int strategy_id; // Strategy ID based on the neighbours
  int strategy_step;
  int movement; // Robby movement
  int score = 0;

  // Get robby current position
  r_row = s->robby_row;
  r_col = s->robby_col;

  // Get neighbours
  if(r_row == 0) // If this is the first row, north is wall
    n[0] = W_TILE_WALL;
  else // Otherwise get the r_row - 1 tile
    n[0] = s->tiles[r_row-1][r_col];
  if(r_row == W_ROWS-1) // If this is the last row, sowth is wall
    n[1] = W_TILE_WALL;
  else // Otherwise get the r_row + 1 tile
    n[1] = s->tiles[r_row+1][r_col];
  if(r_col == 0) // If this is the first column, west is wall
    n[2] = W_TILE_WALL;
  else // Otherwise get r_col-1 tile
    n[2] = s->tiles[r_row][r_col-1];
  if(r_col == W_COLS-1) // If this is the last column, east is wall
    n[3] = W_TILE_WALL;
  else // Otherwise get r_col+1 tile
    n[3] = s->tiles[r_row][r_col+1];
  n[4] = s->tiles[r_row][r_col]; // Current robby position

  // Now get the id of the strategy and the strategy
  strategy_id = to_decimal(n, 3, 5);
  strategy_step = r->strategy[strategy_id];
  // Select strategy execution
  if(strategy_step==S_RANDOM)
    movement = gsl_rng_uniform_int(prng, 4);
  else
    movement = strategy_step;
  switch (movement) {
    case S_MOVE_NORTH:
      if(r_row == 0) // This is a wall
        score = -5;
      else
        s->robby_row--;
      break;
    case S_MOVE_SOUTH:
      if(r_row == W_ROWS-1) // This is a wall
        score = -5;
      else
        s->robby_row++;
      break;
    case S_MOVE_WEST:
      if(r_col == 0) // This is a wall
        score = -5;
      else
        s->robby_col--;
      break;
    case S_MOVE_EAST:
      if(r_col == W_COLS-1) // This is a wall
        score = -5;
      else
        s->robby_col++;
      break;
    case S_STAY_PUT:
      score = 0;
      break;
    case S_PICK_UP:
      if(s->tiles[r_row][r_col] == W_TILE_CAN){ // Got a can
          score = 10;
          s->tiles[r_row][r_col] = W_TILE_EMPTY;
          s->end_can_amount--;
        }
      else
        score = -1;
      break;
    }
  return score;
}
