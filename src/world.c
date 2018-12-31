#include "world.h"

#include <string.h>

world * copy_world(world *w){
  world *nw = NULL;
  size_t len_row = sizeof(e_tile**)*w->cols;
  size_t len_col = sizeof(e_tile*)*w->rows;

  if((nw=(world*)malloc(sizeof(world)))==NULL){
      perror("malloc");
      return NULL;
    }
  memset(nw,'\0',sizeof(world));
  nw->cols = w->cols;
  nw->rows = w->rows;
  if((nw->tiles=(e_tile**)malloc(len_row))==NULL){
      perror("malloc");
      destroy_world(w);
    }
  for(int i=0;i<nw->rows;i++){
      if((nw->tiles[i] = (e_tile*)malloc(len_col))==NULL){
          perror("malloc");
          destroy_world(nw);
          return NULL;
        }
      for(int j=0;j<nw->cols;j++)
        nw->tiles[i][j] = w->tiles[i][j];
    }
  return nw;
}

world * create_world(int cols, int rows){
  world *w = NULL;
  size_t len_row = sizeof(e_tile**)*rows;
  size_t len_col = sizeof(e_tile*)*cols;

  if((w=(world*)malloc(sizeof(world)))==NULL){
      perror("malloc");
      return NULL;
    }
  memset(w, '\0', sizeof(world));
  w->cols = cols;
  w->rows = rows;
  if((w->tiles=(e_tile**)malloc(len_row))==NULL){
      perror("malloc");
      destroy_world(w);
    }
  for(int i=0;i<rows;i++){
      if((w->tiles[i] = (e_tile*)malloc(len_col))==NULL){
          perror("malloc");
          destroy_world(w);
          return NULL;
        }
      for(int j=0;j<cols;j++)
        if(rand() % 2 == 1)
          w->tiles[i][j] = dirt;
    }

  return w;
}

void destroy_world(world *w){
  for(int i=0;i<w->rows;i++)
    free(w->tiles[i]);
  free(w->tiles);
  free(w);
}

void print_world(FILE *stream, world *w){
  if(w == NULL)
    return;
  for(int j=0;j<w->cols+2;j++)
    fprintf(stream,"-");
  fprintf(stream,"\n");
  for(int i=0;i<w->rows; i++){
      fprintf(stream, "|");
      for(int j=0;j<w->cols;j++){
          char ch = ' ';
          if(w->tiles[i][j] == clean)
            ch = ' ';
          else if(w->tiles[i][j] == dirt)
            ch = '*';
          else if(w->tiles[i][j] == robby  || w->tiles[i][j] == robby_dirt)
            ch = 'R';
          fprintf(stream,"%c", ch);
        }
      fprintf(stream, "|");
      fprintf(stream, "\n");
    }
  fprintf(stream,"\n");
}

e_tile get_tile(world *w, int col, int row){
  return w->tiles[row][col];
}

int clean_tile(world *w, int col, int row){
  if(w->tiles[row][col] == dirt){
      w->tiles[row][col] = clean;
      return 1;
    }
  return 0;
}

void clear_world(world *w){
  for(int i=0;i<w->rows;i++){
      for(int j=0;j<w->cols;j++)
        w->tiles[i][j] = clean;
    }
}

void fill_world(world *w){
  for(int i=0;i<w->rows;i++){
      for(int j=0;j<w->cols;j++){
          if(rand() % 2 == 1)
            w->tiles[i][j] = dirt;
        }
    }
}
