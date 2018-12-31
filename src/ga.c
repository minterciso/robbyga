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
      pop[i].fitness = -99.99;
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
  world *session = create_world(cols, rows);
  clear_world(session);
  for(int p=0;p<POP_SIZE;p++){
      // Create random sessions for each individual
      for(int i=0;i<AMOUNT_OF_SESSIONS;i++){
          fill_world(session);
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
          clear_world(session);
        }
      pop[p].fitness /= AMOUNT_OF_SESSIONS;
    }
}

int select_individual(individual *pop, e_selection sel_type){
  if(sel_type == elite_only){
      return rand() % KEEP_POP;
    }
  if(sel_type == tournament){
      int p1_idx = rand() % POP_SIZE;
      int p2_idx = rand() % POP_SIZE;
      if(pop[p1_idx].fitness > pop[p2_idx].fitness)
        return p1_idx;
      return p2_idx;
    }
  if(sel_type == roulette){
      /*
      float f_sum = 0.0;
      for(int i=0;i<POP_SIZE;i++)
        f_sum += pop[i].fitness;
      float rnd = (float)rand()/(float)RAND_MAX;
      */
    }
  return -1;
}

void crossover_and_mutate(individual *pop, e_selection sel_type){
  if(sel_type == tournament){
      individual *old_pop = NULL;
      int p1_idx, p2_idx, s1_idx, s2_idx;
      // Copy population on old_pop
      if((old_pop=(individual*)malloc(sizeof(individual)*POP_SIZE))==NULL){
          perror("malloc");
          return;
        }
      memcpy(old_pop, pop, sizeof(individual)*POP_SIZE);
      // Clear population
      memset(pop, '\0', sizeof(individual)*POP_SIZE);
      // Create the new population
      for(int p=0;p<POP_SIZE;p+=2){
          // Get 2 random parents from old population
          do{
              p1_idx = select_individual(pop, sel_type);
              p2_idx = select_individual(pop, sel_type);
            }while(p1_idx == p2_idx);
          s1_idx = p;
          s2_idx = p+1;
          unsigned int xp = rand() % STRATEGY_SIZE;
          memcpy(&pop[s1_idx].strategy, &old_pop[p1_idx].strategy, sizeof(unsigned int)*xp);
          memcpy(&pop[s2_idx].strategy, &old_pop[p2_idx].strategy, sizeof(unsigned int)*xp);
          memcpy(&pop[s1_idx].strategy[xp], &old_pop[p2_idx].strategy[xp], sizeof(unsigned int)*(STRATEGY_SIZE-xp));
          memcpy(&pop[s2_idx].strategy[xp], &old_pop[p1_idx].strategy[xp], sizeof(unsigned int)*(STRATEGY_SIZE-xp));
          float rnd = 0.0;
          for(int s=0;s<STRATEGY_SIZE;s++){
              rnd = (float)rand()/(float)RAND_MAX;
              if(rnd < PROB_MUTATION)
                pop[s1_idx].strategy[s] = rand() % STRATEGY_OPTIONS;

              rnd = (float)rand()/(float)RAND_MAX;
              if(rnd < PROB_MUTATION)
                pop[s2_idx].strategy[s] = rand() % STRATEGY_OPTIONS;
            }
        }
    }
}
