#ifndef ROBBY_H
#define ROBBY_H

#include <stdio.h>

#include "consts.h"

typedef struct robby{
  int neighbours[5];
  int strategy[S_SIZE];
  float fitness;
} robby;

/**
 * @brief create_population Create a random population of POP_SIZE different robbys, sampled from a uniform distribution
 * @return A pointer to the created population
 */
robby* create_population(void);

/**
 * @brief destroy_population Destroy a previously allocated population
 * @param pop A pointer to the population
 */
void destroy_population(robby *pop);

#endif // ROBBY_H
