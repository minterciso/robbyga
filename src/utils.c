#include "utils.h"

#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>

int start_prng(void){
  const gsl_rng_type *T = gsl_rng_mt19937;
  gsl_rng_env_setup();
  if((prng=gsl_rng_alloc(T))==NULL){
      fprintf(stderr,"[E] Error starting PRNG\n");
      return -1;
    }
  gsl_rng_set(prng, time(NULL));
  return 0;
}

int to_decimal(unsigned int *str, int base, int len){
  int power = len - 1;
  int num = 0;
  for(int x = 0;x<len;x++, power--){
      num += str[x]*pow(base,power);
    }
  return num;
}

void stop_prng(void){
  gsl_rng_free(prng);
}
