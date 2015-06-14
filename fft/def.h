#ifndef DEF_H
#define DEF_H

typedef struct {
  double real;
  double imag;
} mycomplex;

mycomplex add(mycomplex a, mycomplex b);
mycomplex sub(mycomplex a, mycomplex b);
mycomplex mul(mycomplex a, mycomplex b);

#endif /* end of include guard: DEF_H */
