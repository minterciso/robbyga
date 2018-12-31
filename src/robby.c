#include "robby.h"

void place_robby(world *w, int col, int row){
  if(w->tiles[row][col] != wall)
    w->tiles[row][col] = robby;
}

float move_robby(world *w, int col0, int row0, int col1, int row1){
  e_tile original_tile = w->tiles[row0][col0];
  if(col1 < 0 || col1 > w->cols-1)
    return -5.0;
  if(row1 < 0 || row1 > w->rows-1)
    return -5.0;
  if(w->tiles[row1][col1] != wall){
      // Set original tile back on the x0,y0 position
      if(original_tile == dirt || original_tile == robby_dirt)
        w->tiles[row0][col0] = dirt;
      else if(original_tile == clean)
        w->tiles[row0][col0] = clean;
      else
        w->tiles[row0][col0] = clean;
      //Put robby on the new x1,y1 position
      if(w->tiles[row1][col1] == clean)
        w->tiles[row1][col1] = robby;
      else if(w->tiles[row1][col1] == dirt)
        w->tiles[row1][col1] = robby_dirt;
      return 0.0;
    }
  return -5.0;
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
  int r_col,r_row;

  get_robby_position(w, &r_col, &r_row);
  if(r_row-1 >= 0) // North
      n[0] = (unsigned int)w->tiles[r_row-1][r_col];
  else
    n[0] = (unsigned int)wall;
  if(r_row+1 < w->cols) // South
    n[1] = (unsigned int)w->tiles[r_row+1][r_col];
  else
    n[1] = (unsigned int)wall;
  if(r_col + 1 < w->rows) // East
    n[2] = (unsigned int)w->tiles[r_row][r_col+1];
  else
    n[2] = (unsigned int)wall;
  if(r_col - 1 >= 0) // West
    n[3] = (unsigned int)w->tiles[r_row][r_col-1];
  else
    n[3] = (unsigned int)wall;
  if(w->tiles[r_row][r_col] == robby_dirt)
    n[4] = (unsigned int)dirt;
  else
    n[4] = (unsigned int)clean;
}
