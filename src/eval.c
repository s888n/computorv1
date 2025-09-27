#include "../include/computor.h"

Polynomial eval_node(Node *node){
  Polynomial result = {{0.0}};
  if(!node) return result;
  
  switch(node->type){

    case N_NUM :
      result.coefs[0] = node->value;
      return result; 

    case N_VAR :
      result.coefs[1] = 1.0;
      return result;

    case N_ADD : {
      Polynomial L = eval_node(node->left);
      Polynomial R = eval_node(node->right);
      poly_add(&result, &L, &R, +1);
      return result; 
    }

    case N_SUB : {
      Polynomial L = eval_node(node->left);
      Polynomial R = eval_node(node->right);
      poly_add(&result, &L, &R, -1);
      return result; 
    }

    case N_MUL : {
      Polynomial L = eval_node(node->left);
      Polynomial R = eval_node(node->right);
      poly_mul(&result, &L, &R);
      return result; 
    }

    case N_POW : {
      if (node->right == NULL || node->right->type != N_NUM){
        fatal_error(__FILE__, __func__, __LINE__, "Eval error: exponent node invalid");
        // fprintf(stderr, "Eval error: exponent node invalid (pos %d)\n", n->pos)
      }
      Polynomial base = eval_node(node->left);
      poly_pow(&result, &base, node->right->value);
      return result; 
    }

    case N_EQ :
      fatal_error(__FILE__, __func__, __LINE__, "Eval error: tried to eval EQ node");

    default:
      fatal_error(__FILE__, __func__, __LINE__, "Eval error: unknown node type");
  }
  return (Polynomial){0.0};
}
