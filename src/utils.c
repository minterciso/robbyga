#include "utils.h"

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
  int power = 1; // Initialize power of base
  int num = 0;  // Initialize result
  int i;

  // Decimal equivalent is str[len-1]*1 +
  // str[len-1]*base + str[len-1]*(base^2) + ...
  for (i = len - 1; i >= 0; i--){
      // A digit in input number must be
      // less than number's base
      if (str[i] >= base){
          printf("Invalid Number");
          return -1;
        }

      num += str[i] * power;
      power = power * base;
    }

  return num;

}

void stop_prng(void){
  gsl_rng_free(prng);
}
