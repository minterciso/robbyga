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
 * @brief to_decimal Transform an unsigned int array of base 'base' in decimal
 * @param str An unsigned int array
 * @param base The base of the str array
 * @param len The size of the str array
 * @return The decimal number
 */
int to_decimal(unsigned int *str, int base, int len);

/**
 * @brief stop_prng Free the PRNG memory
 */
void stop_prng(void);

#endif // UTILS_H
