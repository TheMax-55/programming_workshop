#include "quad_equations.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void a_is_zero() {
  double *result = quadratic(0, 2, 3, 10E-14);
  assert(result == NULL);
  free(result);
}

void positive_discr() {
  double *result = quadratic(1, 0, -1, 10E-14);
  assert(fabs(result[0] - (-1)) < 1E-14 && fabs(result[1] - 1) < 1E-14);
  free(result);
}

void zero_discr() {
  double *result = quadratic(1, 0, 0, 10E-14);
  assert(fabs(result[0] - 0) < 1E-14);
  free(result);
}

void negative_discr() {
  double *result = quadratic(1, 0, 1, 10E-14);
  assert(result == NULL);
  free(result);
}

void c_is_minus_one_e_minus_seven() {
  double *result = quadratic(1, 0, -1E-7, 1E-14);
  assert(fabs(result[0] - (-3E-4)) < 1E-4 && fabs(result[1] - 3E-4) < 1E-4);
  free(result);
}

void b_is_minus_one_e_plus_ten() {
  double *result = quadratic(1, -1E+10, -1, 1E-11);
  assert(fabs(result[0] - (-1E-10)) < 1E-11 && fabs(result[1] - 1E+10) < 1E-11);
  free(result);
}

void c_is_minus_one_e_minus_eight() {
  double *result = quadratic(1, 0, -1E-8, 1E-7);
  assert(fabs(result[0] - 0) < 1E-7);
  free(result);
}

double main() {
  a_is_zero();
  positive_discr();
  zero_discr();
  negative_discr();
  c_is_minus_one_e_minus_seven();
  b_is_minus_one_e_plus_ten();
  c_is_minus_one_e_minus_eight();
}
