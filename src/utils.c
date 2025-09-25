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
double m_abs(double x){
  return (x < 0) ? -x : x;
}

long long gcf(long long a, long long b){
  if (a < 0) a = -a;
  if (b < 0) b = -b;
  while (b != 0) {
    long long t = a % b;
    a = b;
    b = t;
  }
  return a;
}

int get_degree(double *coef){
  for(int i = MAX_DEGREE; i >= 0; i--){
      if(m_abs(coef[i]) >= EPSILON)
        return i;
  }
  return 0;
}

double m_sqrt(double x) {
    if (x < 0) return -1;
    if (x == 0) return 0;
    double guess = x / 2.0;
    for (int i = 0; i < 50; i++) {
        guess = 0.5 * (guess + x / guess);
    }
    return guess;
}

// strings stuff

int is_space(char c){
    return c == ' ' || c == '\n' || c == '\t' || c == '\r';
}

void trim_spaces(char *str) {
    char *p1 = str, *p2 = str;
    while (*p2) {
        if (!is_space((unsigned char)*p2)) *p1++ = *p2;
        p2++;
    }
    *p1 = 0;
}

void print_fraction(long long num, long long den) {
    long long g = gcf(num, den);
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