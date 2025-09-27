#include "../include/computor.h"

void fatal_error(const char *filename, const char *func_name, int line, const char *msg){
  fprintf(stderr, "ERROR: %s:%s:%d → %s\n", filename, func_name, line, msg);
  exit(69);
}

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

long long sr_llabs(long long x){
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

// void print_fraction(long long num, long long den) {
//     long long g = sr_gcf(num, den);
//     num /= g;
//     den /= g;
//     if (den == 1) printf("%lld\n", num);
//     else printf("%lld/%lld\n", num, den);
// }

void poly_add(Polynomial *dst, const Polynomial *a, const Polynomial *b, int sign){
  for (int i = 0; i <= MAX_DEGREE; ++i)
    dst->coefs[i] = a->coefs[i] + sign * b->coefs[i];
}

void poly_mul(Polynomial *dst, const Polynomial *a, const Polynomial *b) {
    Polynomial r = {{0.0}};

    for (int i = 0; i <= MAX_DEGREE; ++i) {
        double ai = a->coefs[i];
        if (is_zero(ai))
          continue;
        for (int j = 0; j <= MAX_DEGREE - i; ++j) {
            double bj = b->coefs[j];
            if (is_zero(bj))
              continue;
            r.coefs[i + j] += ai * bj;
        }
    }
    for (int k = 0; k <= MAX_DEGREE; ++k) dst->coefs[k] = r.coefs[k];
}

void poly_pow(Polynomial *dst, const Polynomial *base, int exp) {
    Polynomial result = {{0.0}};
    result.coefs[0] = 1.0;

    if (exp == 0) {
        for (int i = 0; i <= MAX_DEGREE; ++i) dst->coefs[i] = result.coefs[i];
        return;
    }

    Polynomial cur; 
    for (int i = 0; i <= MAX_DEGREE; ++i) cur.coefs[i] = base->coefs[i];

    while (exp > 0) {
        if (exp & 1) {
            Polynomial tmp1 = {{0.0}};
            poly_mul(&tmp1, &result, &cur);
            for (int i = 0; i <= MAX_DEGREE; ++i) result.coefs[i] = tmp1.coefs[i];
        }
        exp >>= 1;
        if (exp) {
            Polynomial tmp2 = {{0.0}};
            poly_mul(&tmp2, &cur, &cur);
            for (int i = 0; i <= MAX_DEGREE; ++i) cur.coefs[i] = tmp2.coefs[i];
        }
    }
    for (int i = 0; i <= MAX_DEGREE; ++i) dst->coefs[i] = result.coefs[i];
}