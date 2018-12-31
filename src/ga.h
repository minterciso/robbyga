#ifndef GA_H
#define GA_H

#include <stdio.h>
#include <stdlib.h>
#include "world.h"

#define STRATEGY_SIZE 243
#define STRATEGY_OPTIONS 7

#define POP_SIZE 200
#define AMOUNT_OF_SESSIONS 100
#define MAX_STEPS 200

typedef struct individual{
  unsigned int strategy[STRATEGY_SIZE];
  float fitness;
} individual;

individual *create_population(void);
unsigned int get_strategy(individual *ind, unsigned int *neighbours);
float execute_strategy(world *w, int strategy);
void fitness(individual *pop, int cols, int rows);

#endif // GA_H
