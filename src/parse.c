#include "computor.h"
// void parse_side(char *side, int sign) {
//     int i = 0, len = strlen(side);
//     while (i < len) {
//         int local_sign = 1;
//         if (side[i] == '+') { i++; }
//         else if (side[i] == '-') { local_sign = -1; i++; }

//         // coefficient
//         double value = 0.0;
//         int has_coef = 0;
//         while (i < len && (isdigit(side[i]) || side[i] == '.')) {
//             has_coef = 1;
//             value = value * 10 + (side[i] - '0');
//             if (side[i] == '.') {
//                 i++;
//                 double frac = 0.1;
//                 while (i < len && isdigit(side[i])) {
//                     value += (side[i] - '0') * frac;
//                     frac /= 10;
//                     i++;
//                 }
//                 break;
//             }
//             i++;
//         }
//         if (!has_coef) value = 1.0;

//         // exponent
//         int exp = 0;
//         if (i < len && side[i] == '*') i++;
//         if (i < len && (side[i] == 'X' || side[i] == 'x')) {
//             exp = 1; i++;
//             if (i < len && side[i] == '^') {
//                 i++;
//                 exp = 0;
//                 while (i < len && isdigit(side[i])) {
//                     exp = exp * 10 + (side[i] - '0');
//                     i++;
//                 }
//             }
//         }
//         coef[exp] += sign * local_sign * value;
//     }
// }

void parse_equation(char *equation) {
    trim_spaces(equation);
    char *eq = strchr(equation, '=');
    if (!eq) {
        fprintf(stderr, "Invalid equation: no '=' found\n");
        exit(1);
    }
    *eq = '\0';
    // parse_side(equation, +1);
    // parse_side(eq + 1, -1);
}
