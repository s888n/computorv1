#ifndef COMPUTOR_H
# define COMPUTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define EPSILON 1e-12
#define MAX_DEGREE 1024
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define PINK    "\033[35m"
#define CYAN    "\033[36m"

#ifdef DEBUG
# define TODO(msg) \
    fprintf(stderr, "TODO at %s:%s:%d → %s\n", __FILE__, __func__, __LINE__, msg)
#else
# define TODO(msg) ((void)0)
#endif



typedef enum {
  T_NUM,
  T_VAR,
  T_PLUS,
  T_MINUS,
  T_MUL, 
  T_POW,
  T_EQ,
  T_LPAREN, 
  T_RPAREN, 
  T_END
} TokenType;

typedef enum {
  N_NUM,
  N_VAR,
  N_ADD,
  N_SUB,
  N_MUL,
  N_POW,
  N_EQ
  } NodeType;

typedef struct {
  TokenType type;
  double value; 
  int pos;
} Token;

typedef struct Node {
  NodeType type;
  double value;
  struct Node *left, *right;
  int pos;
} Node;

typedef struct {
  const char *src;
  int pos;
  Token cur;
} Lexer;

typedef struct {
  Lexer lexer;
} Parser;

typedef struct {
  int color;
  int ast;
  int steps;
} Options;

typedef struct { double coefs[MAX_DEGREE + 1]; } Polynomial;


// lex.c
void lex_init(Lexer *lexer, const char *input);
void lex_error(const char *src, int pos, const char *msg);
void lex_next(Lexer *lexer);
// parse.c
void parse_error(Parser *parser, const char *msg);
double parse_number(const char *s, int *pos);
Node *parse_primary(Parser *parser);
Node *parse_factor(Parser *parser);
Node *parse_term(Parser *parser);
Node *parse_expr(Parser *parser);
Node *parse_equation(Parser *parser);
// solve.c
void solve_equation(Polynomial *equation, Options *opt);
// eval.c
Polynomial eval_node(Node *node);
// print.c
void print_ast(Node *node, const char *prefix, int is_tail);

// utils.c
// math //
int is_zero(double x);
double sr_fabs(double x);
double sr_sqrt(double x);
long long sr_llround(double x);
// node //
void free_node(Node *root);
Node *new_node(NodeType type, double value, Node *left, Node *right, int pos);

#endif
