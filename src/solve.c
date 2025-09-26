#include "../include/computor.h"


int get_polynomial_dergee(Polynomial *p){
  for (int i = MAX_DEGREE; i >= 0; --i) {
    if (!is_zero(p->coefs[i])) return i;
  }
  return 0;
}

void solve_zero(double a, Options *opt) {
  if (is_zero(a)){
    printf("All real numbers are solutions.\n");
  } else {
    printf("No solution.\n");
  }
}

void solve_linear(double a, double b, Options *opt) {
  if (is_zero(a)) {
    if (is_zero(b)) {
      printf("All real numbers are solutions.\n");
    } else {
      printf("No solution.\n");
    }
    return;
  }

  double x = -b / a;
  printf("The solution is:\n");
  // print_number_or_fraction(x);
  printf("\n");
}

void solve_quadratic(double a, double b, double c, Options *opt) {
  double disc = b * b - 4 * a * c;
  printf("Discriminant Δ = b^2 - 4ac = %.6g\n", disc);

  if(disc > EPSILON){
    printf("Discriminant strictly positive, two real solutions:\n");
    double sqrt_disc = sr_sqrt(disc);
    double x1 = (-b + sqrt_disc) / (2.0 * a);
    double x2 = (-b - sqrt_disc) / (2.0 * a);

  } else if(is_zero(disc)){
      printf("Discriminant zero, one real solution:\n");
      double x = -b / (2.0 * a);

  } else {
    printf("Discriminant strictly negative, two complex solutions:\n");
    double sqrt_disc = sr_sqrt(-disc);
    double real = -b / (2.0 * a);
    double imag = sqrt_disc / (2.0 * a);
  }
}

void solve_equation(Polynomial *p, Options *opt) {
  int degree = get_polynomial_dergee(p);

  printf("Polynomial degree: %s %d %s\n",\
    opt->color ? GREEN : "", degree ,opt->color ? RESET : "");

  switch (degree){
    case 0:
      solve_zero(p->coefs[0], opt);
      return;
    case 1:
      solve_linear(p->coefs[1], p->coefs[0], opt);
      return;
    case 2:
      solve_quadratic(p->coefs[2], p->coefs[1], p->coefs[0], opt);
      return;
    default:
      if(degree > 2){
        printf("%sThe polynomial degree is strictly greater than 2, I can't solve.%s\n",\
        opt->color ? RED : "", opt->color ? RESET : "");
      } 
      else {
        printf("Degree not supported\n");
      }
  }
}
