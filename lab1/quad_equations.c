#include "quad_equations.h"
#include <math.h>

int sign(double value) {
  if (value >= 0) {
    return 1;
  } else {
    return -1;
  }
}

int quadratic(double a, double b, double c, double eps, double *roots) {
  if (fabs(a) < eps) {
    return NOT_QUADRATIC;
  }
  double d = b * b - 4 * a * c;
  if (d > eps) {
    roots[0] = -(b + sign(b) * sqrt(d)) / 2;
    roots[1] = c / roots[0];
    if (roots[0] - roots[1] >= eps) {
      double temp = roots[0];
      roots[0] = roots[1];
      roots[1] = temp;
    }
    return TWO_ROOTS;
  } else if (d < -eps) {
    return NO_ROOTS;
  } else {
    roots[0] = -b / (2 * a);
    return ONE_ROOT;
  }
}
