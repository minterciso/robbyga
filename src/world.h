#ifndef WORLD_H
#define WORLD_H

#include <stdio.h>

#include "consts.h"

typedef struct session{
  int tiles[W_ROWS][W_COLS];
  int robby_row;
  int robby_col;
  int start_can_amount;
  int end_can_amount;
}session;

/**
 * @brief create_session Create CLEANING_SESSIONS sessions for cleaning up
 * @return A pointer to the cleaning session array
 */
session* create_sessions(void);

/**
 * @brief destroy_sessions Destroy a previously allocated array of cleaning sessions
 * @param s The session array
 */
void destroy_sessions(session* s);

#endif // WORLD_H
