#include "computor.h"




void solve_equation(double *coef){
  size_t degree = get_degree(coef);
  printf("%zu\n",degree);
}


// void solve(int degree) {
//     printf("Polynomial degree: %d\n", degree);

//     if (degree == 0) {
//         if (my_abs(coef[0]) < 1e-12)
//             printf("Any real number is a solution.\n");
//         else
//             printf("No solution.\n");
//     }
//     else if (degree == 1) {
//         double a = coef[1], b = coef[0];
//         printf("The solution is:\n%lf\n", -b / a);
//     }
//     else if (degree == 2) {
//         double a = coef[2], b = coef[1], c = coef[0];
//         double delta = b*b - 4*a*c;
//         if (delta > 0) {
//             printf("Discriminant is strictly positive, the two solutions are:\n");
//             double x1 = (-b - my_sqrt(delta)) / (2*a);
//             double x2 = (-b + my_sqrt(delta)) / (2*a);
//             printf("%lf\n%lf\n", x1, x2);
//         }
//         else if (my_abs(delta) < 1e-12) {
//             printf("Discriminant is zero, the solution is:\n");
//             double x = -b / (2*a);
//             printf("%lf\n", x);
//         }
//         else {
//             printf("Discriminant is strictly negative, the two complex solutions are:\n");
//             double real = -b / (2*a);
//             double imag = my_sqrt(-delta) / (2*a);
//             printf("%lf + %lfi\n", real, imag);
//             printf("%lf - %lfi\n", real, imag);
//         }
//     }
//     else {
//         printf("The polynomial degree is strictly greater than 2, I can't solve.\n");
//     }
// }
