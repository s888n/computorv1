#include "../include/computor.h"
#include <math.h>
void parse_error(Parser *parser, const char *msg) {
    int pos = parser->lexer.cur.pos;
    fprintf(stderr, "Parse error at pos %d: %s\n", pos, msg);
    // print_context(ps->lx.src, pos);
    exit(1);
}

double parse_number(const char *s, int *pos){
  int start = *pos;
  int len = (int) strlen(s);
  int hasdot = 0, hasdigit = 0;

  if(s[*pos] == '.'){
    hasdot = 1;
    if(!isdigit((unsigned char)s[*pos + 1]))
      lex_error(s, *pos, "'.' must be followed by digits for a valid number");
    (*pos)++;
  }

  while(*pos < len && (isdigit((unsigned char)s[*pos]) || s[*pos] == '.')){
    if(s[*pos] == '.'){
      if (hasdot)
        lex_error(s, *pos, "multiple '.' in number");
      hasdot = 1;
    }
    else{
      hasdigit = 1;
    }
    (*pos)++;
  }

  if(!hasdot && !hasdigit){
    lex_error(s, start, "expected digits for number");
  }

  len = *pos - start;

  if (len <= 0 || len >= 128){
    lex_error(s, start, "invalid number length");
  }

  char buf[128];
  memcpy(buf, s + start, len);
  buf[len] = '\0';
  char *endptr = NULL;
  double value = strtod(buf, &endptr);
  if (endptr == buf || *endptr != '\0') {
    lex_error(s, start, "failed to parse numeric literal");
  }

  // if (value >= INT_MAX || value <= ) maybe limit ot the float range
  return value;

}

Node *parse_primary(Parser *parser){

  int pos = parser->lexer.cur.pos;
  TokenType type = parser->lexer.cur.type;

  if (type == T_NUM) {
    double value = parser->lexer.cur.value;
    lex_next(&parser->lexer);
    return new_node(N_NUM, value, NULL, NULL, pos);
  }

  if (type == T_VAR) {
    lex_next(&parser->lexer);
    return new_node(N_VAR, 0.0, NULL, NULL, pos);
  }

  if (type == T_LPAREN) {
    lex_next(&parser->lexer);
    Node *inside = parse_expr(parser);
    if (parser->lexer.cur.type != T_RPAREN) {
      parse_error(parser, "missing closing ')' for '('");
    }
    lex_next(&parser->lexer);
    return inside;
  }

  parse_error(parser, "expected number, variable 'X', or '('");
  return NULL;
}

Node *parse_factor(Parser *parser){

  int sign = 1;

  while (parser->lexer.cur.type == T_PLUS || parser->lexer.cur.type == T_MINUS) {
    if (parser->lexer.cur.type == T_MINUS) sign = -sign;
    lex_next(&parser->lexer);
  }

  Node *base = parse_primary(parser);

  if (parser->lexer.cur.type == T_POW){

    int pow_pos = parser->lexer.cur.pos;
    lex_next(&parser->lexer);

    if (parser->lexer.cur.type != T_NUM){
      parse_error(parser, "expected numeric exponent after '^'");
    }
    
    double raw_exp = parser->lexer.cur.value;
    long long ieb = llround(raw_exp);

    if (fabs(raw_exp - (double)ieb) > 1e-9){
      char buf[128];
      snprintf(buf, sizeof(buf), "exponent must be an integer (found %g) at pos %d",\
        raw_exp, parser->lexer.cur.pos);
      parse_error(parser, buf);
    }

    if (ieb < 0){
      parse_error(parser, "exponent must be non-negative");
    }

    if (ieb > MAX_DEGREE){
      parse_error(parser, "exponent too large");
    }

    Node *expnode = new_node(N_NUM, (double)ieb, NULL, NULL, parser->lexer.cur.pos);
    lex_next(&parser->lexer);
    Node *pownode = new_node(N_POW, 0.0, base, expnode, pow_pos);
    base = pownode;
  }

  if (sign == -1){
    Node *zero = new_node(N_NUM, 0.0, NULL, NULL, parser->lexer.cur.pos);
    Node *neg = new_node(N_SUB, 0.0, zero, base, parser->lexer.cur.pos);
    return neg;
  }
  
  return base;
}

Node *parse_term(Parser *parser){

  Node *node = parse_factor(parser);

  while (parser->lexer.cur.type == T_MUL) {
    int pos = parser->lexer.cur.pos;
    lex_next(&parser->lexer);
    Node *rhs = parse_factor(parser);
    node = new_node(N_MUL, 0.0, node, rhs, pos);
  }

  return node;
}

Node *parse_expr(Parser *parser){

  Node *node = parse_term(parser);

  while (parser->lexer.cur.type == T_PLUS || parser->lexer.cur.type == T_MINUS){
    int pos = parser->lexer.cur.pos;
    TokenType op = parser->lexer.cur.type;
    lex_next(&parser->lexer);
    Node *rhs = parse_term(parser);
    node = new_node(op == T_PLUS ? N_ADD : N_SUB, 0.0, node, rhs, pos);
  }

  return node;
}

Node *parse_equation(Parser *parser){

  Node *lhs = parse_expr(parser);
  if (parser->lexer.cur.type != T_EQ){
    parse_error(parser, "expected '=' between two expressions");
  }

  lex_next(&parser->lexer);

  Node *rhs = parse_expr(parser);
  if (parser->lexer.cur.type != T_END){
    parse_error(parser, "unexpected token after end of equation");
  }

  return new_node(N_EQ, 0.0, lhs, rhs, lhs ? lhs->pos : 0);

}
