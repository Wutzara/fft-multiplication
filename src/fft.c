
#include <stdlib.h>
#include "fft.h"
#include <math.h>
#include <stdio.h>
#include "config.h"

#define PI M_PI

void recursive_fft(mycomplex *a, mycomplex *y, int n, int inv) {
  int k;
  mycomplex w, wn, tmp;
  mycomplex *a0, *a1;
  mycomplex *y0, *y1;
  /* rekursives Ende */
  if (n == 1) {
    y[0] = a[0];
    return;
  }

  a0 = malloc(sizeof(mycomplex) * n / 2);
  a1 = malloc(sizeof(mycomplex) * n / 2);
  y0 = malloc(sizeof(mycomplex) * n / 2);
  y1 = malloc(sizeof(mycomplex) * n / 2);
  /* extrahiere gerade und ungerade koeffizienten */
  for (int i = 0; i < n / 2; ++i) {
    a0[i] = a[i * 2];
    a1[i] = a[i * 2 + 1];
  }

  recursive_fft(a0, y0, n / 2, inv);
  recursive_fft(a1, y1, n / 2, inv);
  w.real = 1;
  w.imag = 0;
  if (inv) {
    wn.real = cos(-2 * PI / (double)n);
    wn.imag = sin(-2 * PI / (double)n);
  } else {
    wn.real = cos(2 * PI / (double)n);
    wn.imag = sin(2 * PI / (double)n);
  }

  for (k = 0; k < n / 2; ++k) {
    tmp = mul(w, y1[k]);
    y[k] = add(y0[k], tmp);
    y[k + n / 2] = sub(y0[k], tmp);
    w = mul(w, wn);
  }

#if DEBUG
  for (k = 0; k < n; ++k) {
    printf("[%.0f %.0f*i], ", y[k].real, y[k].imag);
  }
  printf("\n");
#endif

  free(a0);
  free(a1);
  free(y0);
  free(y1);
}
