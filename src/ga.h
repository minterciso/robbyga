#ifndef GA_H
#define GA_H

#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>
#include "world.h"

#define STRATEGY_SIZE 243
#define STRATEGY_OPTIONS 7

#define POP_SIZE 200
#define KEEP_POP POP_SIZE*0.2
#define AMOUNT_OF_SESSIONS 100
#define MAX_STEPS 200
#define PROB_MUTATION 0.02
#define MAX_GENERATIONS 1000

typedef enum e_selection{
  elite_only,
  tournament,
  roulette
} e_selection;

typedef struct individual{
  unsigned int strategy[STRATEGY_SIZE];
  float weight;
  float fitness;
} individual;

individual *create_population(void);
unsigned int get_strategy(individual *ind, unsigned int *neighbours);
float execute_strategy(world *w, int strategy);
void fitness(individual *pop, int cols, int rows);
int select_individual(individual *pop, e_selection sel_type);
void crossover_and_mutate(individual *pop, e_selection sel_type);

#endif // GA_H
