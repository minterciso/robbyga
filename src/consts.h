#ifndef CONSTS_H
#define CONSTS_H

// GA Params
#define POP_SIZE 200
#define POP_ELITE POP_SIZE * 0.2
#define PROB_XOVER 1
#define PROB_MUTATION 0.001
#define GA_RUNS 500
#define CLEANING_SESSIONS 100
#define SELECTION_ROULETTE 0
#define SELECTION_ELITE 1
#define SELECTION_MODE SELECTION_ROULETTE

// Robby Strategy params
#define S_MOVE_NORTH 0
#define S_MOVE_SOUTH 1
#define S_MOVE_EAST  2
#define S_MOVE_WEST  3
#define S_STAY_PUT   4
#define S_PICK_UP    5
#define S_RANDOM     6
#define S_MAX_OPTIONS  7
#define S_SIZE 243

// World params
#define W_COLS 10
#define W_ROWS 10
#define W_TILE_EMPTY 0
#define W_TILE_CAN   1
#define W_TILE_WALL  2

#endif // CONSTS_H
