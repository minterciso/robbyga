#include "ga.h"
#include "utils.h"
#include <string.h>

individual *create_population(){
  individual *pop = NULL;
  size_t pop_bytes = sizeof(individual)*POP_SIZE;

  if((pop=(individual*)malloc(pop_bytes))==NULL){
      perror("malloc");
      return NULL;
    }
  memset(pop, '\0', pop_bytes);
  for(int i=0;i<POP_SIZE;i++){
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
