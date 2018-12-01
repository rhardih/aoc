#include "stdlib.h"
#include <stdio.h>

#include "bst.h"

bst_node_t *bst_search(bst_node_t *x, void *k, int (*compare)(const void *, const void *))
{
  while (x != NULL) {
    int c = compare(k, x->key);

    if (c == 0) {
      break;
    } else if (c < 0) {
      x = x->left;
    } else {
      x = x->right;
    }
  }

  return x;
}

bst_node_t *bst_minimum(bst_node_t *x)
{
  while (x->left != NULL)
    x = x->left;
  return x;
}

bst_node_t *bst_maximum(bst_node_t *x)
{
  while (x->right != NULL)
    x = x->right;
  return x;
}

bst_node_t *bst_predecessor(bst_node_t *x)
{
  if (x->left != NULL)
    return bst_maximum(x->left);

  bst_node_t *y = x->parent;

  while (y != NULL && x == y->left)
  {
    x = y;
    y = y->parent;
  }

  return y;
}

bst_node_t *bst_successor(bst_node_t *x)
{
  if (x->right != NULL)
    return bst_minimum(x->right);

  bst_node_t *y = x->parent;

  while (y != NULL && x == y->right)
  {
    x = y;
    y = y->parent;
  }

  return y;
}

void bst_insert(bst_tree_t *tree, bst_node_t *z, int (*compare)(const void *, const void *))
{
  bst_node_t *y = NULL;
  bst_node_t *x = tree->root;

  while (x != NULL)
  {
    y = x;

    if (compare(z->key, x->key))
    {
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  }

  z->parent = y;

  if (y == NULL)
  {
    tree->root = z;
  }
  else if (compare(z->key, y->key))
  {
    y->left = z;
  }
  else
  {
    y->right = z;
  }
}

void bst_transplant(bst_tree_t *t, bst_node_t *u, bst_node_t *v)
{
  if (u->parent == NULL)
    t->root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;

  if (v != NULL)
    v->parent = u->parent;
}

void bst_delete(bst_tree_t *t, bst_node_t *z)
{
  if (z->left == NULL)
    bst_transplant(t, z, z->right);
  else if (z->right == NULL)
    bst_transplant(t, z, z->left);
  else
  {
    bst_node_t *y = bst_minimum(z->right);

    if (y->parent != z)
    {
      bst_transplant(t, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }

    bst_transplant(t, z, y);
    y->left = z->left;
    y->left->parent = y;
  }
}

void bst_iotw(bst_node_t *x, void (*printer)(void *))
{
  if (x == NULL) return;

  printf("(");
  bst_iotw(x->left, printer);
  printer(x->key);
  bst_iotw(x->right, printer);
  printf(")");
}

void bst_free(bst_node_t *x)
{
  if (x == NULL) return;

  bst_free(x->left);
  bst_free(x->right);
  free(x);
}

bst_tree_t *bst_tree_new(bst_node_t *n)
{
  bst_tree_t *t = malloc(sizeof(bst_tree_t));
  t->root = n;
  return t;
}

bst_node_t *bst_node_new(void *p)
{
  bst_node_t *n = malloc(sizeof(bst_node_t));
  n->key = p;
  n->parent = n->left = n->right = NULL;
  return n;
}
