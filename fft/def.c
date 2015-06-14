#include "def.h"

mycomplex add(mycomplex a, mycomplex b) {
  mycomplex c;
  c.real = a.real + b.real;
  c.imag = a.imag + b.imag;
  return c;
}

mycomplex sub(mycomplex a, mycomplex b) {
  mycomplex c;
  c.real = a.real - b.real;
  c.imag = a.imag - b.imag;
  return c;
}

mycomplex mul(mycomplex a, mycomplex b) {
  mycomplex c;
  c.real = a.real * b.real;
  c.imag = a.imag * b.imag;
  c.real = a.real * b.real - a.imag * b.imag;
  c.imag = a.imag * b.real + a.real * b.imag;
  return c;
}
