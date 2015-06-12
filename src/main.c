#include <stdlib.h>
#include <stdio.h>
#include "config.h"
#include "def.h"
#include "fft.h"

#define MY_N 8

void print_vector(mycomplex *vec) {
  for (int i = 0; i < MY_N; ++i) {
    printf("[%.0f %.0f*i], ", vec[i].real, vec[i].imag);
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  int i;
  int n = MY_N;
  // Hier die Koeffizienten zur Berechnung eintragen und
  // anschließend die Größe des Zielvektors bei MY_N eintragen
  double realvec1[] = {-10., 1, -1., 7., 0., 0., 0., 0.};
  double realvec2[] = {3., -6., 0., 8., 0., 0., 0., 0.};
  mycomplex *vec = malloc(sizeof(mycomplex) * n);
  mycomplex *vec2 = malloc(sizeof(mycomplex) * n);
  mycomplex *ret = malloc(sizeof(mycomplex) * n);
  mycomplex *ret2 = malloc(sizeof(mycomplex) * n);
  mycomplex *interm = malloc(sizeof(mycomplex) * n);
  for (i = 0; i < MY_N; ++i) {
    vec[i].real = realvec1[i];
    vec[i].imag = 0;
    vec2[i].real = realvec2[i];
    vec2[i].imag = 0;
  }
  recursive_fft(vec, ret, n, 0);
  recursive_fft(vec2, ret2, n, 0);

  /* multiplikation der 2 vektoren */
  for (i = 0; i < n; ++i) {
    interm[i] = mul(ret[i], ret2[i]);
  }

  recursive_fft(interm, ret, n, 1);
#if DEBUG
  print_vector(ret);
#endif
  for (i = 0; i < n; ++i) {
    ret[i].real /= n;
  }
  
  print_vector(ret);

  free(vec);
  free(vec2);
  free(ret);
  free(ret2);
  free(interm);

  return 0;
}

