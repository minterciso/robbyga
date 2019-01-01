#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_rng.h>

gsl_rng *prng;

int start_prng(void);
int to_decimal(unsigned int *str, int base, int len);
void stop_prng(void);

#endif // UTILS_H
