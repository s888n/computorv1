#include "../include/computor.h"

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


