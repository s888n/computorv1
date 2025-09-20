# include "computor.h"

int main(int ac, char **av) {
    if (ac != 2) {
        printf("Usage: %s \"equation\"\n", av[0]);
        return 1;
    }
    // char *eq = strdup(av[1]);
    double coef[MAX_DEGREE + 1] = {0};
    // parse_equation(eq);
    size_t degree =  get_degree(coef);
    printf("degree %zu", degree);
    // print_reduced_form(degree);
    // solve(degree);

    // free(eq);
    return 0;
}
