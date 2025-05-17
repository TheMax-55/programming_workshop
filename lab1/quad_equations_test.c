#include "quad_equations.h"
#include <assert.h>
#include <math.h>

void a_is_zero() {
  double roots[2];
  int result = quadratic(0, 2, 3, 10E-14, roots);
  assert(result == NOT_QUADRATIC);
}

void positive_discr() {
  double roots[2];
  int result = quadratic(1, 0, -1, 10E-14, roots);
  assert(result == TWO_ROOTS);
  assert(fabs(roots[0] - (-1)) < 1E-14 && fabs(roots[1] - 1) < 1E-14);
}

void zero_discr() {
  double roots[2];
  int result = quadratic(1, 0, 0, 10E-14, roots);
  assert(result == ONE_ROOT);
  assert(fabs(roots[0] - 0) < 1E-14);
}

void negative_discr() {
  double roots[2];
  int result = quadratic(1, 0, 1, 10E-14, roots);
  assert(result == NO_ROOTS);
}

void c_is_minus_one_e_minus_seven() {
  double roots[2];
  int result = quadratic(1, 0, -1E-7, 1E-14, roots);
  assert(result == TWO_ROOTS);
  assert(fabs(roots[0] - (-3E-4)) < 1E-4 && fabs(roots[1] - 3E-4) < 1E-4);
}

void b_is_minus_one_e_plus_ten() {
  double roots[2];
  int result = quadratic(1, -1E+10, -1, 1E-11, roots);
  assert(result == TWO_ROOTS);
  assert(fabs(roots[0] - (-1E-10)) < 1E-11 && fabs(roots[1] - 1E+10) < 1E-11);
}

void c_is_minus_one_e_minus_eight() {
  double roots[2];
  int result = quadratic(1, 0, -1E-8, 1E-7, roots);
  assert(result == ONE_ROOT);
  assert(fabs(roots[0] - 0) < 1E-7);
}

int main() {
  a_is_zero();
  positive_discr();
  zero_discr();
  negative_discr();
  c_is_minus_one_e_minus_seven();
  b_is_minus_one_e_plus_ten();
  c_is_minus_one_e_minus_eight();
  return 0;
}
