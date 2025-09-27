#include "../include/computor.h"


void print_reduced(const Polynomial *p) {
    int first = 1;
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

int print_fraction(double v, int is_complex) {
    for (long long den = 1; den <= 1000000LL; den *= 10LL) {
        long long num = sr_llround(v * (double)den);
        double approx = (double)num / (double)den;
        if (is_zero(approx - v)) {
            long long d = den;
            long long a = sr_llabs(num), b = den;
            while (b) { long long t = a % b; a = b; b = t; }
            long long gg = a ? a : 1;
            num /= gg; d /= gg;
            if (d == 1) printf("%lld %s", num, is_complex ? "i" : "");
            else printf("%lld%s/%lld", num, is_complex ? "i" : "",d);
            return 1;
        }
    }
    return 0;
}

void print_number(double value, int is_complex){
  if (!print_fraction(value, is_complex))
      printf("%.6g%s", value, is_complex ? "i" : "" );
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

void  print_ast(Node *node, const char *prefix, int is_tail){

  char new_prefix [256];

  if (!node)return;  
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


