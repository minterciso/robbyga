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

/**
 * @brief create_population Create a non repeating random initial population
 * @return A pointer to an array of POP_SIZE individuals
 */
individual *create_population(void);

/**
 * @brief get_strategy Return a strategy based on the neighbours and the individual
 * @param ind A pointer to the individual with the strategy
 * @param neighbours A pointer with the 5 sized array with the neighbours
 * @return The strategy movement id [0,7[
 */
unsigned int get_strategy(individual *ind, unsigned int *neighbours);

/**
 * @brief execute_strategy Execute a strategy
 * @param w The world were to execute the strategy
 * @param strategy The strategy movement id
 * @return The fitness result of the strategy execution (-5,-1,0 or 10 for wall hit, cleaning a cleaned tile, movement ok, cleaned a dirty tile)
 */
float execute_strategy(world *w, int strategy);

/**
 * @brief fitness Calculate the fitness of the population
 * @param pop The population to calculate a new fitness
 * @param cols The amount of cols of the world size
 * @param rows The amount of rows of the world size
 */
void fitness(individual *pop, int cols, int rows);

/**
 * @brief select_individual Select an individual id based on the selection type passed
 * @param pop The population to look for fitness or weights
 * @param sel_type The selection type
 * @return The individual id selected.
 */
int select_individual(individual *pop, e_selection sel_type);

/**
 * @brief crossover_and_mutate Crossover and mutate until creating a new population
 * @param pop The old population
 * @param sel_type The selection type
 */
void crossover_and_mutate(individual *pop, e_selection sel_type);

#endif // GA_H
