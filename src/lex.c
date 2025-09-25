#include "../include/computor.h"

void lex_error(const char *src, int pos, const char *msg){
  fprintf(stderr, "Lex error at pos %d: %s\n", pos, msg);
  // print_context(src, pos);
  exit(1);
}

void lex_init(Lexer *lexer, const char *input){
  lexer->src = input;
  lexer->pos = 0;
  lex_next(lexer);
}

void lex_next(Lexer *lexer){

  const char *s = lexer->src;
  int len = (int)strlen(s);

  while(lexer->pos < len && isspace((unsigned char)s[lexer->pos])) lexer->pos++;

  if(lexer->pos >= len){
    lexer->cur.type = T_END;
    lexer->cur.pos = lexer->pos;
    return;
  }

  char c = s[lexer->pos];
  int  pos = lexer->pos;

  switch (c){
    case '+':  lexer->cur.type = T_PLUS; lexer->cur.pos = pos; lexer->pos++; return;
    case '-':  lexer->cur.type = T_MINUS; lexer->cur.pos = pos; lexer->pos++; return;
    case '*':  lexer->cur.type = T_MUL; lexer->cur.pos = pos; lexer->pos++; return;
    case '^':  lexer->cur.type = T_POW; lexer->cur.pos = pos; lexer->pos++; return;
    case '=':  lexer->cur.type = T_EQ; lexer->cur.pos = pos; lexer->pos++; return;
    case '(':  lexer->cur.type = T_LPAREN; lexer->cur.pos = pos; lexer->pos++; return;
    case ')':  lexer->cur.type = T_RPAREN; lexer->cur.pos = pos; lexer->pos++; return;
    case 'X': case 'x': lexer->cur.type = T_VAR; lexer->cur.pos = pos; lexer->pos++; return;
    default:
      if(isdigit((unsigned char)c) || c == '.'){
        lexer->cur.value = parse_number(s, &pos);
        lexer->cur.type = T_NUM;
        lexer->cur.pos = pos;
        lexer->pos++; 
        return;
        }
      lex_error(s, pos, "unexpected character");
  }
}
