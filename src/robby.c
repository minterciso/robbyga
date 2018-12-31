#include "robby.h"

void place_robby(world *w, size_t x, size_t y){
  if(w->tiles[x][y] != wall)
    w->tiles[x][y] = robby;
}

int move_robby(world *w, size_t x0, size_t y0, size_t x1, size_t y1){
  e_tile original_tile = w->tiles[y0][x0];
  if(w->tiles[y1][x1] != wall){
      // Set original tile back on the x0,y0 position
      if(original_tile == dirt || original_tile == robby_dirt)
        w->tiles[y0][x0] = dirt;
      else if(original_tile == clean)
        w->tiles[y0][x0] = clean;
      else
        w->tiles[y0][x0] = clean;
      //Put robby on the new x1,y1 position
      if(w->tiles[y1][x1] == clean)
        w->tiles[y1][x1] = robby;
      else if(w->tiles[x1][x1] == dirt)
        w->tiles[y1][x1] = robby_dirt;
      return 0;
    }
  return -5;
}

void get_robby_position(world *w, size_t *x, size_t *y){
  for(int i=0;i<w->x;i++){
      for(int j=0;j<w->y;j++){
          if(w->tiles[i][j] == robby || w->tiles[i][j] == robby_dirt){
              *y=i;
              *x=j;
            }
        }
    }
}
