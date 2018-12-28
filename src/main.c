#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "world.h"
#include "utils.h"

const char *program_name;

void usage(FILE *stream, int exit_code){
  fprintf(stream, "Usage: %s options\n", program_name);
  fprintf(stream, "    -h        --help             This help message\n");
  fprintf(stream, "    -x size   --x_size size      Width size\n");
  fprintf(stream, "    -y size   --y_size size      Height size\n");
  exit(exit_code);
}

int main(int argc, char *argv[]){
  // get opt and program setup
  program_name = argv[0];
  int next_option;
  const char* const short_options = "x:y:h";
  const struct option long_option[] ={
    {"help",   0, NULL, 'h'},
    {"x_size", 1, NULL, 'x'},
    {"y_size", 1, NULL, 'y'},
    {NULL,     0, NULL, 0}
  };
  size_t x, y;
  x=10;
  y=10;
  do{
      next_option = getopt_long(argc, argv, short_options, long_option, NULL);
      switch (next_option) {
        case 'h': usage(stdout, EXIT_SUCCESS); break;
        case 'x': x=atoi(optarg); break;
        case 'y': y=atoi(optarg); break;
        case '?': usage(stderr,EXIT_FAILURE);
        case -1: break;
        default:abort();
        }
    } while(next_option != -1);

  start_prng();
  // Start the program
  world *w = NULL;


  if((w=create_world(x,y))==NULL){
      fprintf(stderr,"[*] Unable to create world\n");
      return EXIT_FAILURE;
    }
  print_world(stdout,w);
  destroy_world(w);

  return EXIT_SUCCESS;
}
