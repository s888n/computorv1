# include "computor.h"

int main(int ac, char **av) {
    double coef[MAX_DEGREE + 1] = {0};
    if (ac != 2) {
        printf("Usage: %s \"equation\"\n", av[0]);
        return 1;
    }
    char *eq = strdup(av[1]);
    // parse_equation(eq);

    int degree = (int) get_degree(coef);
    printf("degree %d", degree);
    // print_reduced_form(degree);
    // solve(degree);

    free(eq);
    return 0;
}
