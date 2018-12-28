#include "utils.h"

#include <time.h>

void start_prng(void)
{
    srand(time(NULL));
}
