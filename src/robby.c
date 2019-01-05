#include "robby.h"
#include "utils.h"
#include <string.h>

robby* create_population(void){
  size_t pop_bytes = sizeof(robby)*POP_SIZE;
  robby *pop = NULL;

  // Allocate memory for the population
  if((pop=(robby*)malloc(pop_bytes))==NULL){
      perror("malloc");
      return NULL;
    }
  memset(pop, 0, pop_bytes);
  // Create a random strategy for each individual
  for(int i=0;i<POP_SIZE;i++){
      for(int j=0;j<S_SIZE;j++)
        pop[i].strategy[j] = gsl_rng_uniform_int(prng, S_MAX_OPTIONS);
    }
  return pop;
}

void destroy_population(robby *pop){
  if(pop==NULL) return;
  free(pop);
}
