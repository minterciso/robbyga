#ifndef GA_H
#define GA_H

#include <stdio.h>

#include "robby.h"

/**
 * @brief select_individual Select an individual based on a Roulete selection
 * @param pop A pointer to the population
 * @return The id of the selected individual
 */
int select_individual(robby *pop, double weighted_sum, int selection_type);

/**
 * @brief fitness Calculate the fitness for one execution
 * @param pop A pointer to the current population
 */
void fitness(robby *pop);

/**
 * @brief execute_ga Execute the GA for GA_RUNS executions
 * @return -1 in case of failure, 0 otherwise
 */
int execute_ga(const char *fname, int selection_type);

int crossover_and_mutate(robby *pop, int selection_type);

#endif // GA_H
