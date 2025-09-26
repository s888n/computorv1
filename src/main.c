# include "../include/computor.h"


static void usage(const char *bin_name){
  fprintf(stderr, 
  "Usage:\n"
  "  %s -[tcs] \"equation\"\n"
  "  -t   Print the Abstract Syntax Tree\n"
  "  -c   Enable color output\n"
  "  -s   Show detailed solution steps\n",
  bin_name
  );
}


static void parse_args(int ac, char **av, Options *opt, const char **input ){
  
  if(ac == 2){
    *input = av[1];
  }
  else if(ac == 3){
    const char *flags = av[1];
    if(flags[0] == '-'){
      for (const char *p = flags + 1; *p; p++){
        if (*p == 't') opt->ast = 1;
        else if (*p == 'c') opt->color = 1;
        else if (*p == 's') opt->steps = 1;
        else {
          fprintf(stderr, "Unknown flag: -%c\n", *p);
          usage(av[0]);
          exit(1);
        }
      }
    } else {
      usage(av[0]);
      exit(1);
  }
  *input = av[2];
  }
  else{
    usage(av[0]);
    exit(1);
  }
  
}


int main(int ac, char **av) {

  const char *input = NULL;
  Options opt = {.color = 0, .ast = 0, .steps = 0 };

  parse_args(ac, av, &opt, &input);


  Parser parser;
  lex_init(&parser.lexer, input);

  Node *root = NULL;
  root = parse_equation(&parser);
  
  if (!root) {
      fprintf(stderr, "Failed to parse equation\n");
      return 1;
    }

  if (root->type != N_EQ) {
      fprintf(stderr, "Internal parser error: root is not EQ\n");
      free_node(root);
      return 1;
    }

  Polynomial lhs = eval_node(root->left);
  Polynomial rhs = eval_node(root->right);

  Polynomial reduced = {.coefs = {0}};
  for (int i = 0; i <= MAX_DEGREE; ++i)
    reduced.coefs[i] = lhs.coefs[i] - rhs.coefs[i];  
  solve_equation(&reduced, &opt);

  if(opt.ast)
    print_ast(root, "", 1);

  free_node(root);

  return 0;
}
