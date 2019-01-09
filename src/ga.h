#ifndef GA_H
#define GA_H

#include <stdio.h>

#include "robby.h"

/**
 * @brief select_individual Select an individual based on a Roulete selection
 * @param pop A pointer to the population
 * @param selection_type The type of selection we want to select the individuals on the population
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
 * @param selection_type The type of selection we want to select the individuals on the population
 * @return -1 in case of failure, 0 otherwise
 */
int execute_ga(const char *fname, int selection_type);

/**
 * @brief crossover_and_mutate Single point crossover between 2 parents selected by selection_type parameter on the population pop
 * @param pop The population in witch to crossover and mutate, it'll update it with the new population
 * @param selection_type The type of selection we want to select the individuals on the population
 * @return 0 on success, -1 on error
 */
int crossover_and_mutate(robby *pop, int selection_type);

#endif // GA_H
