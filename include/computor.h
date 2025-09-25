#ifndef COMPUTOR_H
# define COMPUTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <math.h>

#define EPSILON 1e-12
#define MAX_DEGREE 1024

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
  int pos;      /* current index into src */
  Token cur;    /* current lookahead token */
} Lexer;

typedef struct {
  Lexer lexer;
} Parser;



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

// print.c
void print_ast(Node *node, const char *prefix, int is_tail);

// utils.c
void free_node(Node *root);
Node *new_node(NodeType type, double value, Node *left, Node *right, int pos);

#endif
