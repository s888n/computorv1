#include "../include/computor.h"


void print_reduced(const Polynomial *p, Options *opt) {
    int first = 1;

    (void) opt;
    TODO("Add colored output");
    printf("Reduced form: ");
    for (int i = 0; i <= MAX_DEGREE; ++i) {

        double value = p->coefs[i];
        if (is_zero(value))
          continue;
        if (!first) {
            value < 0.0 ? printf(" - ") : printf(" + ");
        } else {
            if (value < 0.0) printf("-");
        }
        printf("%.6g * X^%d", sr_fabs(value), i);
        first = 0;
    }
    if (first)
      printf("0 * X^0");
    printf(" = 0\n");
}


static void print_indent(const char *prefix, int is_tail) {
  printf("%s", prefix);
  printf(is_tail ? "└── " : "├── ");
}

static const char *node_type_str(NodeType type) {
  switch(type){
    case N_NUM: return "NUM";
    case N_VAR: return "VAR";
    case N_ADD: return "+";
    case N_SUB: return "-";
    case N_MUL: return "*";
    case N_POW: return "^";
    case N_EQ:  return "=";
    default: return "?";
  }
}

void print_ast(Node *node, const char *prefix, int is_tail){

  if (!node) return;

  print_indent(prefix, is_tail);
  switch (node->type) {
    case N_NUM:
      printf("NUM(%g)\n", node->value);
      break;
    case N_VAR:
      printf("VAR(X)\n");
      break;
    default:
      printf("(%s)\n", node_type_str(node->type));
      break;
  }

  char new_prefix[256];
  snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_tail ? "    " : "│   ");

  if (node->left || node->right){
    if (node->left && node->right){
      print_ast(node->left, new_prefix, 0);
      print_ast(node->right, new_prefix, 1);
      } else if (node->left){
      print_ast(node->left, new_prefix, 1);
      } else if (node->right) {
          print_ast(node->right, new_prefix, 1);
      }
  }
}


