# Computor v1

## steps
-> 
## leak tests
- pull nd run valgrind ```bash docker run -tiv $PWD:/valgrind karek/valgrind:latest ```
- run ```valgrind ./computor "args..." ```

## notes
- since math.h is not allowed , use **Newton’s Method** to calculate the square root
- my parser is sloppy and i have to do a lot of patching and handling of edge cases, i'm looking into implementing a proper lexer and parser using  **Recursive Descent Parsing** 
- it is worth it to spend as mush time as possible on RDP since i will be using it on other projects
- for printing fraction we multiply the double by 1e6 for example to preserve 6 degrees of percision then find the gcd

## resources
- [Square Roots via Newton’s Method](https://math.mit.edu/~stevenj/18.335/newton-sqrt.pdf)
- [Recursive Descent Parsing](https://www.youtube.com/watch?v=SToUyjAsaFk&ab_channel=hhp3)
- [the best article i've read about the parsing](https://craftinginterpreters.com/scanning.html)
- [LL Parsing and Recursive Descent ](https://blog.jeffsmits.net/ll-parsing-recursive-descent/)
- [Grammars, parsing, and recursive descent - good video](https://www.youtube.com/watch?v=ENKT0Z3gldE&ab_channel=KayLack)
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_DEGREE 100

typedef struct {
    double coeffs[MAX_DEGREE + 1];
    int degree;
} Polynomial;

// ---------------------------
// Utility: gcd (for fractions)
// ---------------------------
int gcd(int a, int b) {
    if (b == 0) return abs(a);
    return gcd(b, a % b);
}

int gcd2(double a, double b){
  // making a and b postive cause we dont need the sign
  if(a < 0) a = -a ;
  if(b < 0) b = -a ;

  // savin 6 degrees of percsion , good enought
  long la = a * 1e6;
  long lb = b * 1e6;

  while (b != 0){
    long t = a % b;
    a = b;
    b = t;
  }
  return a;
}

// ---------------------------
// Helper: remove spaces
// ---------------------------
void trim_spaces(char *str) {
    char *src = str, *dst = str;
    while (*src) {
        if (!isspace((unsigned char)*src)) *dst++ = *src;
        src++;
    }
    *dst = '\0';
}

// ---------------------------
// Normalize input (free-form support)
// Converts things like:
//   "X^2+4X+5" → "1*X^2+4*X^1+5*X^0"
// ---------------------------
void normalize(char *str) {
    char buffer[2048];
    int j = 0;

    for (int i = 0; str[i]; i++) {
        char c = str[i];

        if (c == 'x') c = 'X'; // case-insensitive

        // Insert "*" between number and X (e.g. 4X → 4*X)
        if (c == 'X' && j > 0 && isdigit(buffer[j-1])) {
            buffer[j++] = '*';
        }

        buffer[j++] = c;
    }
    buffer[j] = '\0';

    // Add explicit coefficients (e.g. "-X" → "-1*X")
    char tmp[2048];
    j = 0;
    for (int i = 0; buffer[i]; i++) {
        if (buffer[i] == 'X' && (i == 0 || buffer[i-1] == '+' || buffer[i-1] == '-')) {
            tmp[j++] = '1';
            tmp[j++] = '*';
        }
        tmp[j++] = buffer[i];
    }
    tmp[j] = '\0';

    strcpy(str, tmp);
}

// ---------------------------
// Parse one term like "5*X^2"
// ---------------------------
int parse_term(char *term, Polynomial *poly, int sign) {
    double coeff = 0.0;
    int power = 0;

    char *x_ptr = strchr(term, 'X');
    if (x_ptr) {
        if (x_ptr == term || *(x_ptr-1) == '*') coeff = 1;
        else coeff = atof(term);

        char *pow_ptr = strchr(term, '^');
        if (pow_ptr) {
            power = atoi(pow_ptr + 1);
        } else {
            power = 1;
        }
    } else {
        coeff = atof(term);
        power = 0;
    }

    if (power < 0 || power > MAX_DEGREE) {
        fprintf(stderr, "Error: invalid power in term '%s'\n", term);
        return -1;
    }

    poly->coeffs[power] += sign * coeff;
    if (power > poly->degree) poly->degree = power;
    return 0;
}

// ---------------------------
// Split and parse one side
// ---------------------------
int parse_side(char *side, Polynomial *poly, int overall_sign) {
    char *p = side;
    while (*p) {
        int sign = +1;
        if (*p == '-') { sign = -1; p++; }
        else if (*p == '+') { p++; }

        char term[256];
        int k = 0;
        while (*p && *p != '+' && *p != '-') {
            term[k++] = *p++;
        }
        term[k] = '\0';

        if (strlen(term) > 0) {
            if (parse_term(term, poly, overall_sign * sign) < 0)
                return -1;
        }
    }
    return 0;
}

// ---------------------------
// Parse equation
// ---------------------------
int parse_equation(const char *input, Polynomial *poly) {
    char buffer[2048];
    strcpy(buffer, input);

    trim_spaces(buffer);
    normalize(buffer);

    char *lhs = strtok(buffer, "=");
    char *rhs = strtok(NULL, "=");

    if (!lhs || !rhs) {
        fprintf(stderr, "Error: equation must contain '='\n");
        return -1;
    }

    if (parse_side(lhs, poly, +1) < 0) return -1;
    if (parse_side(rhs, poly, -1) < 0) return -1;

    return 0;
}

// ---------------------------
// Print polynomial
// ---------------------------
void print_poly(Polynomial *poly) {
    int empty = 1;
    for (int i = 0; i <= poly->degree; i++) {
        if (fabs(poly->coeffs[i]) > 1e-9) {
            printf("%+g*X^%d ", poly->coeffs[i], i);
            empty = 0;
        }
    }
    if (empty) printf("0 ");
    printf("= 0\n");
}

// ---------------------------
// Solve polynomial ≤ 2
// ---------------------------
void solve(Polynomial *poly) {
    int deg = poly->degree;
    while (deg > 0 && fabs(poly->coeffs[deg]) < 1e-9) deg--;
    poly->degree = deg;

    printf("Reduced form: ");
    print_poly(poly);
    printf("Polynomial degree: %d\n", deg);

    if (deg == 0) {
        if (fabs(poly->coeffs[0]) < 1e-9)
            printf("Any real number is a solution.\n");
        else
            printf("No solution.\n");
    }
    else if (deg == 1) {
        double a = poly->coeffs[1], b = poly->coeffs[0];
        printf("Equation: %gx + %g = 0\n", a, b);

        int num = (int)(-b * 1e6);
        int den = (int)(a * 1e6);
        if (den != 0) {
            int g = gcd(num, den);
            num /= g; den /= g;
        }

        printf("→ %gx = %g\n", a, -b);
        printf("→ x = -b / a = %d/%d (≈ %g)\n", num, den, (double)num/den);
    }
   else if (deg == 2) {
    double a = poly->coeffs[2];
    double b = poly->coeffs[1];
    double c = poly->coeffs[0];

    printf("Equation: %gx² + %gx + %g = 0\n", a, b, c);

    double d = b*b - 4*a*c;
    printf("Discriminant Δ = b² - 4ac = %g² - 4*%g*%g = %g\n", b, a, c, d);

    if (d > 0) {
        double sqrt_d = sqrt(d);
        double r1 = (-b + sqrt_d) / (2*a);
        double r2 = (-b - sqrt_d) / (2*a);

        // Check if Δ is a perfect square
        int sqrt_int = (int)(sqrt_d + 0.5);
        if (fabs(sqrt_int*sqrt_int - d) < 1e-9) {
            // Exact rational roots
            int num1 = (int)(-b + sqrt_int);
            int num2 = (int)(-b - sqrt_int);
            int den = (int)(2*a);

            int g1 = gcd(num1, den);
            int g2 = gcd(num2, den);

            printf("Δ > 0 → two real solutions:\n");
            printf("x1 = %d/%d (≈ %g)\n", num1/g1, den/g1, r1);
            printf("x2 = %d/%d (≈ %g)\n", num2/g2, den/g2, r2);
        } else {
            printf("Δ > 0 → two real solutions:\n");
            printf("x1 = (-b + √Δ) / (2a) = (%g + √%g) / (2*%g) ≈ %g\n",
                   -b, d, a, r1);
            printf("x2 = (-b - √Δ) / (2a) = (%g - √%g) / (2*%g) ≈ %g\n",
                   -b, d, a, r2);
        }
    } 
    else if (fabs(d) < 1e-9) {
        double r = -b / (2*a);

        int num = (int)(-b);
        int den = (int)(2*a);
        int g = gcd(num, den);
        num /= g; den /= g;

        printf("Δ = 0 → one real solution:\n");
        printf("x = %d/%d (≈ %g)\n", num, den, r);
    } 
    else {
        double sqrt_d = sqrt(-d);
        double real = -b / (2*a);
        double imag = sqrt_d / (2*a);

        printf("Δ < 0 → two complex solutions:\n");
        printf("x1 = (-b + i√|Δ|) / (2a) = (%g + i√%g) / (2*%g) ≈ %g + %gi\n",
               -b, -d, a, real, imag);
        printf("x2 = (-b - i√|Δ|) / (2a) = (%g - i√%g) / (2*%g) ≈ %g - %gi\n",
               -b, -d, a, real, imag);
    }
}

    else {
        printf("The polynomial degree is strictly greater than 2, I can't solve.\n");
    }
}

// ---------------------------
// Main
// ---------------------------
int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s \"equation\"\n", argv[0]);
        return 1;
    }

    Polynomial poly = { .degree = 0 };
    for (int i = 0; i <= MAX_DEGREE; i++) poly.coeffs[i] = 0;

    if (parse_equation(argv[1], &poly) < 0) {
        return 1;
    }

    solve(&poly);

    return 0;
}

```