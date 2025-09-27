#include "../include/computor.h"


int get_polynomial_dergee(Polynomial *p){
  for (int i = MAX_DEGREE; i >= 0; --i) {
    if (!is_zero(p->coefs[i])) return i;
  }
  return 0;
}

void solve_zero(double a, Options *opt) {
  if (is_zero(a)){
    if (opt->steps){
      printf("Equation: %.6g * X^0 = 0\n", a );
      printf("→ %.6g = 0\n", a);
  }
    printf("All real numbers are solutions.\n");
  } else {
    if (opt->steps){
      printf("Equation: %.6g * X^0 = 0\n", a );
      printf("→ %.6g != 0\n", a);
  }
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

  if (opt->steps){
      printf("Equation: %.6g * X + %.6g = 0\n", a, b);
      printf("→ %.6g * X = %.6g\n", a, -b);
      printf("→ X = -b / a = %.6g / %.6g\n", -b, a);
  }

  double x = -b / a;
  printf("The solution is:\n");
  printf(" X = "); print_number(x, 0); printf("\n");
}

void solve_quadratic(double a, double b, double c, Options *opt) {
  double disc = b * b - 4 * a * c;

  if (opt->steps) {
      printf("Equation: %.6g * X^2 + %.6g * X + %.6g = 0\n", a, b, c);
      printf("Discriminant Δ = b^2 - 4ac = %.6g^2 - 4*%.6g*%.6g\n", b, a, c);
      printf("Δ = %.6g\n", disc);
  }

  if(disc > EPSILON){
    printf("Discriminant strictly positive, two real solutions:\n");
    double sqrt_disc = sr_sqrt(disc);
    double x1 = (-b - sqrt_disc) / (2.0 * a);
    double x2 = (-b + sqrt_disc) / (2.0 * a);

    if (opt->steps) {
          printf("→ X = (-b ± sqrt(Δ)) / (2a)\n");
          printf("→ X = (%.6g ± %.6g) / %.6g\n", -b, sqrt_disc, 2*a);
      }
      printf("X1 = "); print_number(x1, 0);
      printf("\nX2 = "); print_number(x2, 0); printf("\n");

  } else if(is_zero(disc)){
      printf("Discriminant zero, one real solution:\n");
      double x = -b / (2.0 * a);
      if (opt->steps)
          printf("→ X = -b / (2a) = %.6g / %.6g\n", -b, 2*a);
      printf(" X = "); print_number(x, 0); printf("\n");
  } else {

      printf("Discriminant strictly negative, two complex solutions:\n");
      double sqrt_disc = sr_sqrt(-disc);
      double real = -b / (2.0 * a);
      double imag = sqrt_disc / (2.0 * a);
      if (opt->steps) {
        printf("→ X = (-b ± i * sqrt(-Δ)) / (2a)\n");
        printf("→ X = (%.6g ± %.6g i) / %.6g\n", -b, sqrt_disc, 2*a);
      }

      printf(" X1 = "); 
      print_number(real, 0);
      if (imag >= 0) printf(" + ");
      else { printf(" - "); imag = -imag; }
      print_number(imag, 1); printf("\n");

      printf(" X2 = ");
      print_number(real, 0);
      if (imag >= 0) printf(" - ");
      else { printf(" + "); }
      print_number(imag, 1); printf("\n");
  }
}

void solve_equation(Polynomial *p, Options *opt) {
  int degree = get_polynomial_dergee(p);

  printf("Polynomial degree:  %d \n", degree);

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
        printf("The polynomial degree is strictly greater than 2, I can't solve.\n");
      } 
      else {
        printf("Degree not supported\n");
      }
  }
}
