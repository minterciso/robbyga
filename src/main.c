#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "world.h"
#include "utils.h"
#include "robby.h"

const char *program_name;

void usage(FILE *stream, int exit_code){
  fprintf(stream, "Usage: %s options\n", program_name);
  fprintf(stream, "    -h        --help             This help message\n");
  fprintf(stream, "    -r size   --rows size        Rows of the world\n");
  fprintf(stream, "    -c size   --cols size        Cols of the world\n");
  exit(exit_code);
}

int main(int argc, char *argv[]){
  // get opt and program setup
  program_name = argv[0];
  int next_option;
  const char* const short_options = "r:c:h";
  const struct option long_option[] ={
    {"help",   0, NULL, 'h'},
    {"rows", 1, NULL, 'r'},
    {"cols", 1, NULL, 'c'},
    {NULL,     0, NULL, 0}
  };
  int cols, rows;
  cols=10;
  rows=10;
  do{
      next_option = getopt_long(argc, argv, short_options, long_option, NULL);
      switch (next_option) {
        case 'h': usage(stdout, EXIT_SUCCESS); break;
        case 'c': cols=atoi(optarg); break;
        case 'r': rows=atoi(optarg); break;
        case '?': usage(stderr,EXIT_FAILURE);
        case -1: break;
        default:abort();
        }
    } while(next_option != -1);

  start_prng();
  // Start the program
  world *w = NULL;


  if((w=create_world(cols,rows))==NULL){
      fprintf(stderr,"[*] Unable to create world\n");
      return EXIT_FAILURE;
    }
  int robby_row, robby_col;
  robby_col = robby_row = 0;
  place_robby(w, robby_col, robby_row);
  move_robby(w, robby_col, robby_row, robby_col+1, robby_row);
  move_robby(w, robby_col+1, robby_row, robby_col+2, robby_row);
  move_robby(w, robby_col+2, robby_row, robby_col+3, robby_row);
  move_robby(w, robby_col+3, robby_row, robby_col+3, robby_row+1);
  print_world(stdout,w);
  get_robby_position(w, &robby_col, &robby_row);
  fprintf(stdout,"Robby Position (Col:%d, Row:%d)\n", robby_col, robby_row);
  unsigned int neighbours[5];
  get_neighbours(w, neighbours);
  fprintf(stdout, "Neighbours:\n");
  fprintf(stdout,"N:%d\n", neighbours[0]);
  fprintf(stdout,"S:%d\n", neighbours[1]);
  fprintf(stdout,"E:%d\n", neighbours[2]);
  fprintf(stdout,"W:%d\n", neighbours[3]);
  fprintf(stdout,"C:%d\n", neighbours[4]);

  destroy_world(w);

  return EXIT_SUCCESS;
}
