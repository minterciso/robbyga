#include "world.h"

#include <string.h>

world * create_world(size_t x, size_t y){
  world *w = NULL;
  size_t len_row = sizeof(e_tile**)*y;
  size_t len_col = sizeof(e_tile*)*x;

  if((w=(world*)malloc(sizeof(world)))==NULL){
      perror("malloc");
      return NULL;
    }
  memset(w, '\0', sizeof(world));
  w->x = x;
  w->y = y;
  if((w->tiles=(e_tile**)malloc(len_row))==NULL){
      perror("malloc");
      destroy_world(w);
    }
  for(int i=0;i<y;i++){
      if((w->tiles[i] = (e_tile*)malloc(len_col))==NULL){
          perror("malloc");
          destroy_world(w);
          return NULL;
        }
      for(int j=0;j<x;j++)
        w->tiles[i][j] = rand() % (dirt + 1);
    }

  return w;
}

void destroy_world(world *w){
  if(w->tiles != NULL){
      for(int i=0;i<w->y;i++)
        free(w->tiles[i]);
      free(w->tiles);
    }
  free(w);
}

void print_world(FILE *stream, world *w){
  if(w == NULL)
    return;
  for(int i=0;i<w->y; i++){
      for(int j=0;j<w->x;j++)
        fprintf(stream,"%c", (w->tiles[i][j]==clean) ? ' ' : '*');
      fprintf(stream, "\n");
    }
}

e_tile get_tile(world *w, size_t x, size_t y){
  return w->tiles[x][y];
}

int clean_tile(world *w, size_t x, size_t y){
  if(w->tiles[x][y] == dirt){
      w->tiles[x][y] = clean;
      return 1;
    }
  return 0;
}
