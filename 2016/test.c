#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"

int bst_comp(const void *a, const void *b)
{
  if (a == NULL || b == NULL) return 0;
  return *(int *)a < *(int *)b;
}

void bst_printer(void *p)
{
  int a = *(int *)p;

  printf(" %d ", a);
}

void test_bst_insert() {
  printf("\ntest_bst_insert()\n");

  bst_tree_t *t = malloc(sizeof(bst_tree_t));
  t->root = NULL;

  int values[] = { 42, 123, 11, 20 };
  bst_node_t n[] = {
    { &values[0], NULL, NULL, NULL },
    { &values[1], NULL, NULL, NULL },
    { &values[2], NULL, NULL, NULL },
    { &values[3], NULL, NULL, NULL }
  };

  for (size_t i = 0; i < 4; ++i)
  {
    printf("-> %d\n", *(int *)n[i].key);
    bst_insert(t, &n[i], bst_comp);
    bst_iotw(t->root, bst_printer);
    printf("\n");
  }

  printf("parents:\n");
  bst_node_t *current = &n[3];
  while (current != NULL)
  {
    bst_printer(current->key);
    printf(" -> ");
    current = current->parent;
  }
  printf("\n");

  free(t);
}

void test_bst_search() {
  printf("\ntest_bst_search()\n");

  bst_tree_t *t = malloc(sizeof(bst_tree_t));
  t->root = NULL;

  int values[] = { 42, 123, 11, 20 };
  bst_node_t n[] = {
    { &values[0], NULL, NULL, NULL },
    { &values[1], NULL, NULL, NULL },
    { &values[2], NULL, NULL, NULL },
    { &values[3], NULL, NULL, NULL }
  };

  for (size_t i = 0; i < 4; ++i)
    bst_insert(t, &n[i], bst_comp);

  printf("tree:\n");
  bst_iotw(t->root, bst_printer);
  printf("\n");

  bst_node_t *result = bst_search(t->root, &values[3], bst_comp);

  printf("search:\n");
  bst_printer(n[3].key);
  printf("\n");
  printf("result:\n");
  bst_printer(result->key);
  printf("\n");

  free(t);
}

void test_bst_minimum() {
  printf("\ntest_bst_minimum()\n");

  bst_tree_t *t = malloc(sizeof(bst_tree_t));
  t->root = NULL;

  int values[] = { 42, 123, 11, 20 };
  bst_node_t n[] = {
    { &values[0], NULL, NULL, NULL },
    { &values[1], NULL, NULL, NULL },
    { &values[2], NULL, NULL, NULL },
    { &values[3], NULL, NULL, NULL }
  };

  for (size_t i = 0; i < 4; ++i)
    bst_insert(t, &n[i], bst_comp);

  printf("tree:\n");
  bst_iotw(t->root, bst_printer);
  printf("\n");

  bst_node_t *result = bst_minimum(t->root);

  printf("minimum:\n");
  bst_printer(result->key);
  printf("\n");

  free(t);
}

void test_bst_maximum() {
  printf("\ntest_bst_maximum()\n");

  bst_tree_t *t = malloc(sizeof(bst_tree_t));
  t->root = NULL;

  int values[] = { 42, 123, 11, 20 };
  bst_node_t n[] = {
    { &values[0], NULL, NULL, NULL },
    { &values[1], NULL, NULL, NULL },
    { &values[2], NULL, NULL, NULL },
    { &values[3], NULL, NULL, NULL }
  };

  for (size_t i = 0; i < 4; ++i)
    bst_insert(t, &n[i], bst_comp);

  printf("tree:\n");
  bst_iotw(t->root, bst_printer);
  printf("\n");

  bst_node_t *result = bst_maximum(t->root);

  printf("maximum:\n");
  bst_printer(result->key);
  printf("\n");

  free(t);
}

void test_bst_successor() {
  printf("\ntest_bst_successor()\n");

  bst_tree_t *t = malloc(sizeof(bst_tree_t));
  t->root = NULL;

  int values[] = { 42, 123, 11, 20 };
  bst_node_t n[] = {
    { &values[0], NULL, NULL, NULL },
    { &values[1], NULL, NULL, NULL },
    { &values[2], NULL, NULL, NULL },
    { &values[3], NULL, NULL, NULL }
  };

  for (size_t i = 0; i < 4; ++i)
    bst_insert(t, &n[i], bst_comp);

  printf("tree:\n");
  bst_iotw(t->root, bst_printer);
  printf("\n");

  bst_node_t *result = bst_successor(&n[3]);

  printf("successor:\n");
  bst_printer(n[3].key);
  printf("\n");
  printf("result:\n");
  bst_printer(result->key);
  printf("\n");

  free(t);
}

void test_bst_predecessor() {
  printf("\ntest_bst_predecessor()\n");

  bst_tree_t *t = malloc(sizeof(bst_tree_t));
  t->root = NULL;

  int values[] = { 42, 123, 11, 20 };
  bst_node_t n[] = {
    { &values[0], NULL, NULL, NULL },
    { &values[1], NULL, NULL, NULL },
    { &values[2], NULL, NULL, NULL },
    { &values[3], NULL, NULL, NULL }
  };

  for (size_t i = 0; i < 4; ++i)
    bst_insert(t, &n[i], bst_comp);

  printf("tree:\n");
  bst_iotw(t->root, bst_printer);
  printf("\n");

  bst_node_t *result = bst_predecessor(&n[0]);

  printf("predecessor:\n");
  bst_printer(n[0].key);
  printf("\n");
  printf("result:\n");
  bst_printer(result->key);
  printf("\n");

  free(t);
}

void test_bst_delete() {
  printf("\ntest_bst_delete()\n");

  bst_tree_t *t;
  int values[] = { 42, 123, 11, 20 };
  size_t i, j;

  // Delete each node one at a time
  printf("One at a time\n");
  for (i = 0; i < 4; ++i)
  {
    t = malloc(sizeof(bst_tree_t));
    t->root = NULL;

    bst_node_t n[] = {
      { &values[0], NULL, NULL, NULL },
      { &values[1], NULL, NULL, NULL },
      { &values[2], NULL, NULL, NULL },
      { &values[3], NULL, NULL, NULL }
    };

    for (j = 0; j < 4; ++j)
      bst_insert(t, &n[j], bst_comp);

    printf("tree:\n");
    bst_iotw(t->root, bst_printer);
    printf("\n");

    printf("delete:\n");
    bst_printer(n[i].key);
    printf("\n");

    bst_delete(t, &n[i]);

    printf("tree:\n");
    bst_iotw(t->root, bst_printer);
    printf("\n\n");

    free(t);
  }

  printf("Sequentially\n");
  bst_node_t n[4];
  n[0].key = &values[0];
  n[0].parent = NULL;
  n[0].left = NULL;
  n[0].right = NULL;
  n[1].key = &values[1];
  n[1].parent = NULL;
  n[1].left = NULL;
  n[1].right = NULL;
  n[2].key = &values[2];
  n[2].parent = NULL;
  n[2].left = NULL;
  n[2].right = NULL;
  n[3].key = &values[3];
  n[3].parent = NULL;
  n[3].left = NULL;
  n[3].right = NULL;

  t = malloc(sizeof(bst_tree_t));
  t->root = NULL;

  for (i = 0; i < 4; ++i)
    bst_insert(t, &n[i], bst_comp);

  printf("tree:\n");
  bst_iotw(t->root, bst_printer);
  printf("\n");

  // Delete each node sequentially
  for (i = 0; i < 4; ++i)
  {
    printf("delete:\n");
    bst_printer(n[i].key);
    printf("\n");

    bst_delete(t, &n[i]);

    printf("tree:\n");
    bst_iotw(t->root, bst_printer);
    printf("\n\n");
  }

  free(t);
}

int main(int argc, char const *argv[])
{
  char divider[81] = { 0 };
  memset(divider, '-', 80);

  printf("%s\nBinary search tree\n%s\n", divider, divider);

  test_bst_insert();
  test_bst_search();
  test_bst_minimum();
  test_bst_maximum();
  test_bst_successor();
  test_bst_predecessor();
  test_bst_delete();

  return 0;
}
