#ifndef ROBBY_H
#define ROBBY_H

#include <stdio.h>

#include "consts.h"
#include "world.h"

typedef struct robby{
  int neighbours[5];
  int strategy[S_SIZE];
  float fitness;
  float weight;
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

/**
 * @brief execute_strategy Execute one step of a strategy and return the score of it
 * @param s The session to execute the strategy on
 * @param r The robby with the strategy to execute
 * @return The score of the strategy
 */
int execute_strategy(session *s, robby *r);

#endif // ROBBY_H
