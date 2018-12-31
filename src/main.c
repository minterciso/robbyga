#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "world.h"
#include "utils.h"
#include "robby.h"
#include "ga.h"

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
  individual *pop = NULL;

  if((pop = create_population())==NULL){
      fprintf(stdout, "[E] Error creating population\n");
      destroy_world(w);
      return EXIT_FAILURE;
    }

  fitness(pop, cols, rows);
  for(int i=0;i<POP_SIZE;i++)
    fprintf(stdout,"%d: %0.10f\n", i, pop[i].fitness);


  free(pop);
  return EXIT_SUCCESS;
}
