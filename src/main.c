#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "config.h"
#include <fft/fft.h>

#define MY_N 8

/**
 * Fileformat
 * ----------
 *
 *  n
 *  koeffizienten des ersten vectors
 *  koeffizienten des zweiten vectors
 */

typedef struct {
  int n;
  mycomplex* vec1;
  mycomplex* vec2;
} inputdata;

inputdata* open_file(char *filename) {
  FILE *fp = fopen(filename, "r");
  int i;
  
  if(fp == NULL) {
    fprintf(stderr, "%s\n", "Error while opening the file");
    exit(EXIT_FAILURE);
  }

  char line[128];
  inputdata *data = malloc(sizeof(inputdata));
  for(i = 0; fgets(line, sizeof(line), fp) != NULL; i++) {
    switch(i) {
    case 0: {
              data->n = atoi(line);
            break;
            }
    case 1: {
              int j;
              data->vec1 = malloc(sizeof(mycomplex)*data->n);
              char *token = strtok(line, " ");
              for(j = 0; token; j++, token = strtok(NULL, " ")) {
                data->vec1[j].real = atof(token);
                data->vec1[j].imag = 0.;
              }
            break;
            }
    case 2: {
              int j;
              data->vec2 = malloc(sizeof(mycomplex)*data->n);
              char *token = strtok(line, " ");
              for(j = 0; token; j++, token = strtok(NULL, " ")) {
                data->vec2[j].real = atof(token);
                data->vec2[j].imag = 0.;
              }
            break;
            }
    }
  }

  fclose(fp);
  return data;
}

int main(int argc, char *argv[]) {
  int i;
  if(argc != 2) {
    printf("Usage: %s inputdata\n", argv[0]);
    return EXIT_FAILURE;
  }

  inputdata* data = open_file(argv[1]);
  mycomplex *ret = malloc(sizeof(mycomplex) * data->n);
  mycomplex *ret2 = malloc(sizeof(mycomplex) * data->n);
  mycomplex *interm = malloc(sizeof(mycomplex) * data->n);
  recursive_fft(data->vec1, ret, data->n, 0);
  recursive_fft(data->vec2, ret2, data->n, 0);
  
  /* multiplikation der 2 vektoren */
  for (i = 0; i < data->n; ++i) {
    interm[i] = mul(ret[i], ret2[i]);
  }

  recursive_fft(interm, ret, data->n, 1);
#if DEBUG
  print_vector(ret, data->n);
#endif
  for (i = 0; i < data->n; ++i) {
    ret[i].real /= data->n;
  }
  
  print_vector(ret, data->n);

  free(data->vec1);
  free(data->vec2);
  free(data);
  free(ret);
  free(ret2);
  free(interm);

  return 0;
}

