#include "utils.h"

#include <math.h>
#include <time.h>
#include <gsl/gsl_rng.h>

int start_prng(void){
  const gsl_rng_type *T = gsl_rng_ranlxs2;
  if((prng=gsl_rng_alloc(T))==NULL){
      fprintf(stderr,"[E] Error starting PRNG\n");
      return -1;
    }
  gsl_rng_set(prng, time(NULL));
  return 0;
}

int to_decimal(int *arr, int base, int len){
  int power = 1;
  int num = 0;
  int i;
  for(i=len - 1; i>= 0; i--){
      if(arr[i] >= base)
        return -1;
      num += (arr[i]*power);
      power *= base;
    }
  return num;
}

void stop_prng(void){
  gsl_rng_free(prng);
}
