#ifndef ROBBY_H
#define ROBBY_H

#include <stdio.h>

typedef struct robby{
  int neighbours[5];
  int strategy[5][243];
  float fitness;
} robby;

#endif // ROBBY_H
