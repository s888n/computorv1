# include "computor.h"

// math stuff
double m_abs(double x){
  return (x < 0) ? -x : x;
}

long long gcf(long long a, long long b){
  if (a < 0) a = -a;
  if (b < 0) b = -b;
  while (b != 0) {
    long long t = a % b;
    a = b;
    b = t;
  }
  return a;
}

size_t get_degree(double *coef){
  for(size_t i = MAX_DEGREE; i >=0; i--){
      if(m_abs(coef[i]) >= EPSILON)
        return i;
  }
  return 0;
}

double m_sqrt(double x) {
    if (x < 0) return -1;
    if (x == 0) return 0;
    double guess = x / 2.0;
    for (int i = 0; i < 50; i++) {
        guess = 0.5 * (guess + x / guess);
    }
    return guess;
}

// strings stuff

int is_space(char c){
    return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

void trim_spaces(char *str) {
    char *p1 = str, *p2 = str;
    while (*p2) {
        if (!is_space((unsigned char)*p2)) *p1++ = *p2;
        p2++;
    }
    *p1 = 0;
}

void print_fraction(long long num, long long den) {
    long long g = gcf(num, den);
    num /= g;
    den /= g;
    if (den == 1) printf("%lld\n", num);
    else printf("%lld/%lld\n", num, den);
}

// void print_reduced_form(int degree) {
//     printf("Reduced form: ");
//     int first = 1;
//     for (int i = 0; i <= degree; i++) {
//         if (my_abs(coef[i]) > 1e-12) {
//             if (!first && coef[i] >= 0) printf("+ ");
//             printf("%.6g * X^%d ", coef[i], i);
//             first = 0;
//         }
//     }
//     if (first) printf("0 ");
//     printf("= 0\n");
// }



// int is_integer(double x) {
//     long long r = (long long)(x + (x >= 0 ? 0.5 : -0.5));
//     return (my_abs(x - r) < 1e-9);
// }
// double my_abs(double x) {
//     return (x < 0) ? -x : x;
// }



// // void solve(int degree) {
// //     printf("Polynomial degree: %d\n", degree);

// //     if (degree == 0) {
// //         if (my_abs(coef[0]) < 1e-12)
// //             printf("Any real number is a solution.\n");
// //         else
// //             printf("No solution.\n");
// //     }
// //     else if (degree == 1) {
// //         double a = coef[1], b = coef[0];
// //         double sol = -b / a;

// //         long long num = -(long long)(b * 1000000);
// //         long long den = (long long)(a * 1000000);
// //         long long g = my_gcd(num, den);
// //         num /= g; den /= g;

// //         printf("The solution is:\n");
// //         if (den == 1) printf("%lld\n", num);
// //         else printf("%lld/%lld\n", num, den);
// //     }
// //     else if (degree == 2) {
// //         double a = coef[2], b = coef[1], c = coef[0];
// //         double delta = b*b - 4*a*c;

// //         if (delta > 0) {
// //             printf("Discriminant is strictly positive, the two solutions are:\n");
// //             double sqrt_delta = my_sqrt(delta);
// //             double x1 = (-b - sqrt_delta) / (2*a);
// //             double x2 = (-b + sqrt_delta) / (2*a);

// //             // check if roots are rational
// //             if (is_integer(sqrt_delta) && is_integer(2*a)) {
// //                 long long num1 = -(long long)b - (long long)sqrt_delta;
// //                 long long den1 = 2 * (long long)a;
// //                 print_fraction(num1, den1);

// //                 long long num2 = -(long long)b + (long long)sqrt_delta;
// //                 long long den2 = 2 * (long long)a;
// //                 print_fraction(num2, den2);
// //             } else {
// //                 printf("%lf\n%lf\n", x1, x2);
// //             }
// //         }
// //         else if (my_abs(delta) < 1e-12) {
// //             printf("Discriminant is zero, the solution is:\n");
// //             double x = -b / (2*a);

// //             if (is_integer(2*a) && is_integer(b)) {
// //                 long long num = -(long long)b;
// //                 long long den = 2 * (long long)a;
// //                 print_fraction(num, den);
// //             } else {
// //                 printf("%lf\n", x);
// //             }
// //         }
// //         else {
// //             printf("Discriminant is strictly negative, the two complex solutions are:\n");
// //             double real = -b / (2*a);
// //             double imag = my_sqrt(-delta) / (2*a);
// //             printf("%lf + %lfi\n", real, imag);
// //             printf("%lf - %lfi\n", real, imag);
// //         }
// //     }
// //     else {
// //         printf("The polynomial degree is strictly greater than 2, I can't solve.\n");
// //     }
// // }
