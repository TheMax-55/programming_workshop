#include "integral.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>

double linear(double x) { return x; }

double quadratic(double x) { return x * x; }

void test_linear() {
  double lower_limit_of_integration = 0.0;
  double upper_limit_of_integration = 1.0;
  double result = integral(lower_limit_of_integration,
                           upper_limit_of_integration, 1000, linear);
  double expected = (upper_limit_of_integration * upper_limit_of_integration -
                     lower_limit_of_integration * lower_limit_of_integration) /
                    2.0; // Аналит решение с помощью формулы Ньютона-Лейбница

  assert(fabs(result - expected) < 1e-6);
}

void test_quadratic() {
  double lower_limit_of_integration = 1.0;
  double upper_limit_of_integration = 2.0;
  double result = integral(lower_limit_of_integration,
                           upper_limit_of_integration, 1000, quadratic);
  double expected =
      (upper_limit_of_integration * upper_limit_of_integration *
           upper_limit_of_integration -
       lower_limit_of_integration * lower_limit_of_integration *
           lower_limit_of_integration) /
      3.0; // Аналитическое решение с помощью формулы Ньютона-Лейбница

  assert(fabs(result - expected) < 1e-6);
}

int main() {
  test_linear();
  test_quadratic();
  return 0;
}
