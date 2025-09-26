#include "../include/computor.h"

// node
Node *new_node(NodeType type, double value, Node *left, Node *right, int pos) {
  Node *node = (Node*)malloc(sizeof(Node));
  if (!node){ 
    fprintf(stderr, "Couldn't allocate memory, you ran out of RAM ? ¯\\_(ツ)_/¯ \n");
    exit(1);
    }
  node->type = type;
  node->value = value;
  node->left = left;
  node->right = right; 
  node->pos = pos;
  return node;
}

void free_node(Node *root) {
  if (!root) return;
  free_node(root->left);
  free_node(root->right);
  free(root);
}

// math stuff
double sr_fabs(double x){
  return (x < 0) ? -x : x;
}

long long sr_llround(double x) {
    return x >= 0.0 ? (long long)(x + 0.5) : (long long)(x - 0.5);
}

int is_zero(double x){
  return sr_fabs(x) < EPSILON;
}

long long sr_gcf(long long a, long long b){
  if (a < 0) a = -a;
  if (b < 0) b = -b;
  while (b != 0) {
    long long t = a % b;
    a = b;
    b = t;
  }
  return a;
}

// x must be x >= 0
double sr_sqrt(double x) {

    if (x < 0) return -1;
    if (x == 0) return 0;
    double guess = x / 2.0;
    for (int i = 0; i < 50; i++) {
        guess = 0.5 * (guess + x / guess);
    }
    return guess;
}

// strings stuff

void trim_spaces(char *str) {
    char *p1 = str, *p2 = str;
    while (*p2) {
        if (!isspace((unsigned char)*p2)) *p1++ = *p2;
        p2++;
    }
    *p1 = 0;
}

void print_fraction(long long num, long long den) {
    long long g = sr_gcf(num, den);
    num /= g;
    den /= g;
    if (den == 1) printf("%lld\n", num);
    else printf("%lld/%lld\n", num, den);
}

static void print_indent(const char *prefix, int is_tail) {
    printf("%s", prefix);
    printf(is_tail ? "└── " : "├── ");
}

void poly_zero(Polynomial *p){

}

void poly_add(Polynomial *dst, Polynomial *a, Polynomial *b, int sign){}
void poly_mul(){}
void poly_pow(){}