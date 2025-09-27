# include "../include/computor.h"

static void usage(const char *bin_name){
  fprintf(stderr, 
  "usage: %s -[ts] \"equation\"\n"
  "  -t   Print the Abstract Syntax Tree\n"
  "  -s   Show detailed solution steps\n",
  bin_name
  );
}

static void parse_args(int ac, char **av, Options *opt, const char **input) {
    if (ac == 2) {
        *input = av[1];
        return;
    }
    if (ac == 3) {
        const char *flags = av[1];
        if (flags[0] != '-') {
            usage(av[0]);
            exit(1);
        }
        for (const char *p = flags + 1; *p; p++) {
            switch (*p) {
                case 't': opt->ast   = 1; break;
                case 's': opt->steps = 1; break;
                default:
                    fprintf(stderr, "Unknown flag: -%c\n", *p);
                    usage(av[0]);
                    exit(1);
            }
        }
        *input = av[2];
        return;
    }
    usage(av[0]);
    exit(1);
}

int main(int ac, char **av) {
  const char *input = NULL;
  Options opt = {.ast = 0, .steps = 0 };

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

  if(opt.ast)
    print_ast(root, "", 1);

  Polynomial lhs = eval_node(root->left);
  Polynomial rhs = eval_node(root->right);

  Polynomial reduced = {{0.0}};
  for (int i = 0; i <= MAX_DEGREE; ++i){
    // if (!is_zero(lhs.coefs[i] - rhs.coefs[i]))
    //   printf("L -> %.6g, R -> %.6g , (L - R) => %.6g\n",lhs.coefs[i],rhs.coefs[i],lhs.coefs[i] - rhs.coefs[i]);
    reduced.coefs[i] = lhs.coefs[i] - rhs.coefs[i];
  }

  print_reduced(&reduced);

  solve_equation(&reduced, &opt);

  free_node(root);

  return 0;
}
