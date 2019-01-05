#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "utils.h"
#include "robby.h"

const char *prog_name;

void usage(FILE *stream, int exit_code){
  fprintf(stream, "Usage: %s options\n", prog_name);
  fprintf(stream, "Options:\n");
  fprintf(stream, " -h        --help          This help message\n");
  fprintf(stream, " -o file   --output file   The output result file (CSV format)\n");
  fprintf(stream, "Defaults: -o output.csv\n");
  exit(exit_code);
}

int main(int argc, char **argv){
  // Program options (getpot)
  prog_name = argv[0];
  const char* const short_options = "ho:";
  const struct option long_options[] = {
  {"help",   0, NULL, 'h'},
  {"output", 1, NULL, 'o'},
  {NULL,     0, NULL, 0}
  };
  int next_option;
  char *fname = NULL;
  do{
      next_option = getopt_long(argc, argv, short_options, long_options, NULL);
      switch (next_option) {
        case 'h': usage(stdout, EXIT_SUCCESS); break;
        case 'o': fname=optarg; break;
        case '?': usage(stderr, EXIT_FAILURE); break;
        case -1: break;
        default: abort();
        }
    }while(next_option != -1);
  if(fname == NULL)
    fname = "output.csv";
  // Show options
  fprintf(stdout,"[*] Starting %s\n", prog_name);
  fprintf(stdout,"[*] Options: \n");
  fprintf(stdout,"[*] - Output file: '%s'\n", fname);
  // GA variables
  robby *pop = NULL;

  fprintf(stdout,"[*] Starting PRNG...");
  fflush(stdout);
  if(start_prng() < 0){
      fprintf(stderr,"[E] Unable to start PRNG\n");
      return EXIT_FAILURE;
    }
  fprintf(stdout,"[OK]\n");
  fprintf(stdout,"[*] Creating initial population...");
  fflush(stdout);
  if((pop = create_population())==NULL){
      fprintf(stderr,"[E] Unable to create population\n");
      stop_prng();
      return EXIT_FAILURE;
    }
  fprintf(stdout,"[OK]\n");

  fprintf(stdout,"[*] Cleaning up...");
  fflush(stdout);
  stop_prng();
  destroy_population(pop);
  fprintf(stdout,"[OK]\n");

  fprintf(stdout,"[*] Done!\n");
  return EXIT_SUCCESS;
}
