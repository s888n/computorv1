# include "../include/computor.h"

int main(int ac, char **av) {

  if (ac != 2){
    printf("Usage: %s \"equation\"\n", av[0]);
    return 1;
  }
  Parser parser;
  lex_init(&parser.lexer, av[1]);

  Node *root = NULL;
  root = parse_equation(&parser);
  print_ast(root, "", 1);
  free_node(root);
  return 0;
}
