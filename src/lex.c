#include "../include/computor.h"

void lex_error(const char *src, int pos, const char *msg){
  fprintf(stderr, "Lex error at pos %d: %s\n", pos, msg);
  // print_context(src, pos);
  (void)src;
  TODO("Add context for lexer errors");
  exit(1);
}

void lex_init(Lexer *lexer, const char *input){
  lexer->src = input;
  lexer->pos = 0;
  lex_next(lexer);
}

void lex_next(Lexer *lexer) {
  const char *s = lexer->src;
  int len = (int)strlen(s);

  while (lexer->pos < len && isspace((unsigned char)s[lexer->pos])) {
      lexer->pos++;
  }

  if (lexer->pos >= len) {
      lexer->cur.type = T_END;
      lexer->cur.pos  = lexer->pos;
      return;
  }

  char c  = s[lexer->pos];
  int pos = lexer->pos;

  switch (c) {
    case '+': lexer->cur.type = T_PLUS;   break;
    case '-': lexer->cur.type = T_MINUS;  break;
    case '*': lexer->cur.type = T_MUL;    break;
    case '^': lexer->cur.type = T_POW;    break;
    case '=': lexer->cur.type = T_EQ;     break;
    case '(': lexer->cur.type = T_LPAREN; break;
    case ')': lexer->cur.type = T_RPAREN; break;
    case 'X': case 'x':
        lexer->cur.type = T_VAR;          break;
    default:
        if (isdigit((unsigned char)c) || c == '.') {
            int p = lexer->pos;
            double val = parse_number(s, &p);
            lexer->cur.type  = T_NUM;
            lexer->cur.value = val;
            lexer->cur.pos   = pos;
            lexer->pos       = p;
            return;
        }
        lex_error(s, pos, "unexpected character");
  }
  lexer->cur.pos = pos;
  lexer->pos++;
}
