#ifndef GA_H
#define GA_H

#include <stdio.h>
#include <stdlib.h>

#define STRATEGY_SIZE 243
#define STRATEGY_OPTIONS 7

#define POP_SIZE 100

typedef struct individual{
  unsigned int strategy[STRATEGY_SIZE];
  float fitness;
} individual;

individual *create_population(void);
unsigned int get_strategy(individual *ind, unsigned int *neighbours);

#endif // GA_H
