#include "integral.h"

#include <math.h>
#include <stdio.h>

double integral(double lower_limit_of_integration,
                double upper_limit_of_integration, int number_of_partitions,
                double (*f)(double)) {
  double height = (upper_limit_of_integration - lower_limit_of_integration) /
                  number_of_partitions;
  double sum = 0.0;

  sum +=
      ((f(lower_limit_of_integration) + f(upper_limit_of_integration)) / 2.0);
  for (int i = 1; i < number_of_partitions; i++) {
    sum += f(lower_limit_of_integration + i * height);
  }

  return sum * height;
}
