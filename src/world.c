#include "world.h"
#include "utils.h"

#include <string.h>
#include <gsl/gsl_randist.h>

session* create_sessions(void){
  size_t session_bytes = sizeof(session)*CLEANING_SESSIONS;
  session *s = NULL;
  // Allocate memory
  if((s=(session*)malloc(session_bytes))==NULL){
      perror("malloc");
      return NULL;
    }
  memset(s, 0, session_bytes);
  // Fill up each session with random cans, where each site has 50% of chance of having a can
  for(int i=0;i<CLEANING_SESSIONS;i++){
      s[i].robby_col=0;
      s[i].robby_row=0;
      for(int j=0;j<W_ROWS;j++){
          for(int k=0;k<W_COLS;k++){
              //if(gsl_ran_binomial(prng, 0.5, 1) == 1){
              if(gsl_rng_uniform(prng) <= 0.5){
                  s[i].tiles[j][k] = W_TILE_CAN;
                  s[i].start_can_amount++;
                }
            }
        }
      s[i].end_can_amount = s->start_can_amount;
    }
  return s;
}

void destroy_sessions(session* s){
  if(s == NULL) return;
  free(s);
}
