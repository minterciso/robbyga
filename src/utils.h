#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>

gsl_rng *prng;

/**
 * @brief start_prng Start the PRNG based on the Mersenne Twister, this can be overriden with the GSL_RNG_TYPE variable at runtime
 * @return 0 if it was possible to start the PRNG, -1 otherwise
 */
int start_prng(void);

/**
 * @brief to_decimal Transform a array number on base 'base' on decimal
 * @param arr The number arrary on base 'base'
 * @param base The base we are working on
 * @param len The size of the array
 * @return -1 if unable to convert, or the decimal number
 */
int to_decimal(int *arr, int base, int len);

/**
 * @brief stop_prng Free the PRNG memory
 */
void stop_prng(void);

#endif // UTILS_H
