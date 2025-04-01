#include "quad_equations.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int sign(double value) {
  if (value >= 0) {
    return 1;
  } else {
    return -1;
  }
}
double *quadratic(double a, double b, double c, double eps) {
  if (a < eps) {
    return NULL;
  }
  double *roots = malloc(sizeof(double) * 2);
  double d = b * b - 4 * a * c;
  if (d > eps) {
    roots[0] = -(b + sign(b) * sqrt(d)) / 2;
    roots[1] = c / roots[0];
    if (roots[0] > roots[1]) {
      double temp = roots[0];
      roots[0] = roots[1];
      roots[1] = temp;
    }
  } else if (d < -eps) {
    return NULL;
  } else {
    roots[0] = -b / (2 * a);
  }
  return roots;
}
