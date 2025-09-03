#ifndef COMPUTOR_H
#define COMPUTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EPSILON 1e-12
#define MAX_DEGREE 100


// utils
  // math stuff 
double m_abs(double x);
double m_sqrt(double x);
long long m_gdf(long long a, long long b);
  // is_stuff
int is_space(char c);
int is_digit(char c);
int is_integer(double x);
// strings and print stuff
void trim_spaces(char *str);
// some custom print stuff
void print_fraction();
void print_reduced_form();

// parse
void parse_equation(char *equation);
void parse_equation_side(char *side, int sign);

// solve
size_t get_degree(double *coef);
void solve_equation(double *coef);

#endif