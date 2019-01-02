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
  fprintf(stream, "    -h           --help                       This help message\n");
  fprintf(stream, "    -r size      --rows size                  Rows of the world\n");
  fprintf(stream, "    -c size      --cols size                  Cols of the world\n");
  fprintf(stream, "    -s selection --selection selection_type   The selection type, valid values: 0:'tournament',1:'elite',2:'roulette'\n");
  fprintf(stream, "    -o file      --output file                Output csv file with results\n");
  exit(exit_code);
}

static int cmpind(const void *p1, const void *p2){
  individual *i1 = (individual*)p1;
  individual *i2 = (individual*)p2;
  //return i1->fitness - i2->fitness;
  if(i1->fitness > i2->fitness) return -1;
  if(i2->fitness > i1->fitness) return 1;
  return 0;
}

int main(int argc, char *argv[]){
  // get opt and program setup
  program_name = argv[0];
  int next_option;
  const char* const short_options = "r:c:hs:o:";
  const struct option long_option[] ={
  {"help",      0, NULL, 'h'},
  {"rows",      1, NULL, 'r'},
  {"cols",      1, NULL, 'c'},
  {"selection", 1, NULL, 's'},
  {"output",    1, NULL, 'o'},
  {NULL,        0, NULL, 0}
};
  int cols, rows;
  char *fname = NULL;
  e_selection selection_type = elite_only;
  cols=10;
  rows=10;
  do{
      next_option = getopt_long(argc, argv, short_options, long_option, NULL);
      switch (next_option) {
        case 'h': usage(stdout, EXIT_SUCCESS); break;
        case 'c': cols=atoi(optarg); break;
        case 'r': rows=atoi(optarg); break;
        case 's': switch (atoi(optarg)){
            case 0: selection_type=tournament; break;
            case 1: selection_type=elite_only; break;
            case 2: selection_type=roulette; break;
            }
          break;
        case 'o': fname = optarg; break;
        case '?': usage(stderr,EXIT_FAILURE);
        case -1: break;
        default:abort();
        }
    } while(next_option != -1);

  if(fname == NULL)
    fname="output.csv";

  if(start_prng() < 0){
      fprintf(stderr,"[E] No valid PRNG!\n");
      return EXIT_FAILURE;
    }
  // Start the program
  individual *pop = NULL;
  FILE *fp = NULL;

  fprintf(stdout,"[*] Creating population...");
  fflush(stdout);
  if((pop = create_population())==NULL){
      fprintf(stdout, "[E] Error creating population\n");
      return EXIT_FAILURE;
    }
  fprintf(stdout,"[OK]\n");
  fflush(stdout);
  if((fp=fopen(fname, "w"))==NULL){
      perror("fopen");
      free(pop);
      return EXIT_FAILURE;
    }
  fprintf(fp, "generation, fitness, strategy\n");
  fflush(fp);

  individual *best = NULL;
  for(int g=0;g<MAX_GENERATIONS;g++){
      fprintf(stdout,"[*] Generation %04d: ", g);
      fitness(pop, cols, rows);
      qsort(pop, POP_SIZE, sizeof(individual), cmpind);
      best=&pop[0];
      fprintf(fp, "%d,%0.10f,", g, best->fitness);
      for(int i=0;i<STRATEGY_SIZE;i++)
        fprintf(fp, "%d", best->strategy[i]);
      fprintf(fp,"\n");
      fflush(fp);
      fprintf(stdout,"%0.10f\n",best->fitness);
      fflush(stdout);
      if(g!=MAX_GENERATIONS)
        crossover_and_mutate(pop, selection_type);
    }

  fprintf(stdout,"[*] Best Strategy: ");
  for(int i=0;i<STRATEGY_SIZE;i++) fprintf(stdout,"%d", best->strategy[i]);
  fprintf(stdout,"\n");

  free(pop);
  fclose(fp);
  stop_prng();
  return EXIT_SUCCESS;
}
