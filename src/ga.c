#include "ga.h"

#include "world.h"
#include "utils.h"

#include <string.h>

static int cmp_robby(const void *p1, const void *p2){
  robby *r1 = (robby*)p1;
  robby *r2 = (robby*)p2;
  if(r1->fitness > r2->fitness) return -1;
  if(r1->fitness < r2->fitness) return 1;
  return 0;
}

int select_individual(robby *pop, double weighted_sum, int selection_type){
  if(selection_type == SELECTION_ROULETTE){
      float rnd = 0.0;
      float sum = 0.0;
      int index = -1;

      // Now select a random value from 0 to weighted_sum
      rnd = gsl_rng_uniform(prng) * weighted_sum;
      // Now find the index corresponding to the rnd probability
      while(sum < rnd){
          index++;
          sum += pop[index].weight;
        }
      return index;
    }
  if(selection_type == SELECTION_ELITE){
      return gsl_rng_uniform_int(prng, POP_ELITE);
    }
  if(selection_type == SELECTION_TOURNAMENT){
      // Select at random 2 individuals and return the one with the best fitness
      int idx1, idx2;
      idx1 = gsl_rng_uniform_int(prng, POP_SIZE);
      idx2 = gsl_rng_uniform_int(prng, POP_SIZE);
      if(pop[idx1].fitness > pop[idx2].fitness) return idx1;
      return idx2;
    }
  return -1;
}

int crossover_and_mutate(robby *pop, int selection_type){
  robby *old_pop = NULL;
  size_t pop_bytes = sizeof(robby) * POP_SIZE;

  // Calculate the weighted_sum
  double weighted_sum = 0;
  if(selection_type == SELECTION_ROULETTE){
      // We rank the weights based on the sorting of the individual, due to the negative fitness values.
      for(int i=0;i<POP_SIZE;i++){
          pop[i].weight = (float)(POP_SIZE-i);
          weighted_sum += pop[i].weight;
      }
    }

  // Allocate memory for the old population
  if((old_pop=(robby*)malloc(pop_bytes))==NULL){
      perror("malloc");
      return -1;
    }
  memcpy(old_pop, pop, pop_bytes); // Copy the current population on the old population
  memset(pop, 0, pop_bytes); // Clear the current population
 
  // Now create a new population
  for(int i=0;i<POP_SIZE;i++){
      int p1_idx, p2_idx;
      int xp;
      // Select 2 parents
      p1_idx = select_individual(old_pop, weighted_sum, selection_type);
      p2_idx = select_individual(old_pop, weighted_sum, selection_type);
      // If we have to crossover...
      if(gsl_rng_uniform(prng) < PROB_XOVER){
          // Select a random xover point
          xp = gsl_rng_uniform_int(prng, S_SIZE);
          // Create 1 sons
          for(int j=0;j<xp;j++)
              pop[i].strategy[j] = old_pop[p1_idx].strategy[j];
          for(int j=xp;j<S_SIZE;j++)
              pop[i].strategy[j] = old_pop[p2_idx].strategy[j];
        }
      else // If we don't need to crossover, just copy the strategy
          memcpy(&pop[i].strategy, &old_pop[p1_idx].strategy, sizeof(int)*S_SIZE);
      pop[i].fitness = -99.99;
      pop[i].weight = -99.99;
      // Now check for mutation
      for(int j=0;j<S_SIZE;j++){
          if(gsl_rng_uniform(prng) < PROB_MUTATION)
            pop[i].strategy[j] = gsl_rng_uniform_int(prng, S_MAX_OPTIONS);
        }
    }
  free(old_pop);
  return 0;
}

void fitness(robby *pop){
  for(int i=0;i<POP_SIZE;i++){
      session *s = create_sessions();
      for(int j=0;j<CLEANING_SESSIONS;j++){
          int score = 0;
          for(int k=0;k<200;k++)
            score += execute_strategy(&s[j], &pop[i]);
          pop[i].fitness += (float)score;
        }
      pop[i].fitness /= CLEANING_SESSIONS;
      destroy_sessions(s);
    }
}

int execute_ga(const char *fname, int selection_type){
  robby *pop = NULL;
  robby *best = NULL;
  FILE *fp = NULL;

  fprintf(stdout,"[*] Creating initial population...");
  fflush(stdout);
  if((pop = create_population())==NULL){
      fprintf(stderr,"[E] Unable to create population\n");
      stop_prng();
      return -1;
    }
  fprintf(stdout,"[OK]\n");
  fprintf(stdout,"[*] Creating output file '%s'...", fname);
  fflush(stdout);
  if((fp=fopen(fname, "w"))==NULL){
      perror("fopen");
      return -1;
    }
  fprintf(fp, "generation, fitness, rule\n");
  fflush(fp);
  fprintf(stdout,"[OK]\n");
  fflush(stdout);

  for(int g=0;g<GA_RUNS;g++){
      // Execute the fitness
      fitness(pop);
      // Sort
      qsort(pop, POP_SIZE, sizeof(robby), cmp_robby);
      best = &pop[0];
      fprintf(fp, "%d, %f, ", g, best->fitness);
      for(int j=0;j<S_SIZE;j++) fprintf(fp, "%d", best->strategy[j]);
      fprintf(fp, "\n");
      fflush(fp);
      fprintf(stdout,"[*] %04d: %.5f\n", g, best->fitness);
      fflush(stdout);
      if(g != GA_RUNS)
        if(crossover_and_mutate(pop, selection_type) < 0){
            fprintf(stderr,"[E] Unable to crossover!\n");
            return -1;
          }
    }
  destroy_population(pop);
  return 0;
}
