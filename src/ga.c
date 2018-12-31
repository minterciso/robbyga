#include "ga.h"
#include "utils.h"
#include "world.h"
#include "robby.h"
#include <string.h>

individual *create_population(void){
  individual *pop = NULL;
  size_t pop_bytes = sizeof(individual)*POP_SIZE;

  if((pop=(individual*)malloc(pop_bytes))==NULL){
      perror("malloc");
      return NULL;
    }
  memset(pop, '\0', pop_bytes);
  for(int i=0;i<POP_SIZE;i++){
      for(int j=0;j<STRATEGY_SIZE;j++)
        pop[i].strategy[j] = rand() % STRATEGY_OPTIONS;
    }
  return pop;
}

unsigned int get_strategy(individual *ind, unsigned int *neighbours){
  int id = to_decimal(neighbours, 3, 5);
  if(id >= 0 && id < STRATEGY_SIZE)
    return ind->strategy[id];
  return -1;
}

float execute_strategy(world *w, int strategy){
  int robby_col, robby_row;
  float fit = 0.0;
  int move_direction = 0;

  get_robby_position(w, &robby_col, &robby_row);
  // Execute strategy
  switch (strategy) {
    case 0: // Move North
      fit = move_robby(w, robby_col, robby_row, robby_col-1, robby_row);
      break;
    case 1: // Move South
      fit = move_robby(w, robby_col, robby_row, robby_col+1, robby_row);
      break;
    case 2: // Move East
      fit = move_robby(w, robby_col, robby_row, robby_col, robby_row+1);
      break;
    case 3: // Move West
      fit = move_robby(w, robby_col, robby_row, robby_col-1, robby_row);
      break;
    case 4: break; // Stay put
    case 5: // Pick Up
      if(clean_tile(w, robby_col, robby_row)==1) // Clean was successfull
        fit = 10.0;
      else
        fit = -1.0;
      break;
    case 6: // Random movement
      move_direction = rand() % 4;
      fit = execute_strategy(w, move_direction);
      break;
    default:
      break;
    }
  return fit;
}

void fitness(individual *pop, int cols, int rows){
  for(int p=0;p<POP_SIZE;p++){
      // Create random sessions for each individual
      for(int i=0;i<AMOUNT_OF_SESSIONS;i++){
          world *session = create_world(cols, rows);
          place_robby(session, 0, 0);
          unsigned int neighbours[5];
          int strategy = -1;
          float fit=0.0;
          for(int s=0;s<MAX_STEPS;s++){
              // Get neighbours
              get_neighbours(session, neighbours);
              // Get strategy based on neighbours
              strategy = get_strategy(&pop[p], neighbours);
              fit += execute_strategy(session, strategy);
            }
          pop[p].fitness += fit;
          destroy_world(session);
        }
      pop[p].fitness /= AMOUNT_OF_SESSIONS;
    }
}
