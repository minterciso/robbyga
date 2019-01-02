#include "robby.h"
#include <assert.h>

void place_robby(world *w, int col, int row){
  if(w->tiles[row][col] != wall)
    w->tiles[row][col] = robby;
}

float move_robby(world *w, int col0, int row0, int col1, int row1){
  if(col1 < 0 || col1 >= w->cols)
    return -5.0;
  if(row1 < 0 || row1 >= w->rows)
    return -5.0;

  e_tile original_tile = w->tiles[row0][col0];
  // Set original tile back on the x0,y0 position
  if(original_tile == dirt || original_tile == robby_dirt)
    w->tiles[row0][col0] = dirt;
  else
    w->tiles[row0][col0] = clean;
  //Put robby on the new x1,y1 position
  if(w->tiles[row1][col1] == clean)
    w->tiles[row1][col1] = robby;
  else if(w->tiles[row1][col1] == dirt)
    w->tiles[row1][col1] = robby_dirt;

  return 0.0;
}

void get_robby_position(world *w, int *col, int *row){
  for(int i=0;i<w->rows;i++){
      for(int j=0;j<w->cols;j++){
          if(w->tiles[i][j] == robby || w->tiles[i][j] == robby_dirt){
              *col=j;
              *row=i;
            }
        }
    }
}

void get_neighbours(world *w, unsigned int *n){
  int r_col=0,r_row=0;

  get_robby_position(w, &r_col, &r_row);
  n[0] = (unsigned int)wall;
  n[1] = (unsigned int)wall;
  n[2] = (unsigned int)wall;
  n[3] = (unsigned int)wall;
  n[4] = (unsigned int)clean;
  if(r_col + 1 < w->rows) n[2] = (unsigned int)w->tiles[r_row][r_col+1];
  if(r_col - 1 >= 0) n[3] = (unsigned int)w->tiles[r_row][r_col-1];
  if(r_row - 1 >= 0) n[0] = (unsigned int)w->tiles[r_row-1][r_col];
  if(r_row +1 < w->cols) n[1] = (unsigned int)w->tiles[r_row+1][r_col];
  if(w->tiles[r_row][r_col] == robby_dirt) n[4] = (unsigned int)dirt;
}
