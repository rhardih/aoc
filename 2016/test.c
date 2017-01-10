#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ll.h"
#include "bst.h"

typedef struct {
  int foo;
} bar;

void bar_printer(void *p) {
  printf("%d", ((bar *)p)->foo);
}

int foo_finder(void *p, void *v) {
  return *(int *)v == ((bar *)p)->foo;
}

void test_linked_list_prepend() {
  printf("\ntest_linked_list_prepend()\n");

  ll_t *list = ll_list_create();
  ll_node_t *n0 = ll_node_create();
  ll_node_t *n1 = ll_node_create();

  bar *b0 = malloc(sizeof(bar));
  b0->foo = 42;
  n0->value = b0;

  bar *b1 = malloc(sizeof(bar));
  b1->foo = 123;
  n1->value = b1;

  ll_print(list, bar_printer);

  ll_prepend(list, n0);
  ll_print(list, bar_printer);

  ll_prepend(list, n1);
  ll_print(list, bar_printer);

  free(b0);
  free(b1);
  free(n0);
  free(n1);
  free(list);
}

void test_linked_list_append() {
  printf("\ntest_linked_list_append()\n");

  ll_t *list = ll_list_create();
  ll_node_t *n0 = ll_node_create();
  ll_node_t *n1 = ll_node_create();

  bar *b0 = malloc(sizeof(bar));
  b0->foo = 42;
  n0->value = b0;

  bar *b1 = malloc(sizeof(bar));
  b1->foo = 123;
  n1->value = b1;

  ll_print(list, bar_printer);

  ll_append(list, n0);
  ll_print(list, bar_printer);

  ll_append(list, n1);
  ll_print(list, bar_printer);

  free(b0);
  free(b1);
  free(n0);
  free(n1);
  free(list);
}

void test_linked_list_remove_tail() {
  printf("\ntest_linked_list_remove_tail()\n");

  ll_t *list = ll_list_create();
  ll_node_t *n0 = ll_node_create();
  ll_node_t *n1 = ll_node_create();

  bar *b0 = malloc(sizeof(bar));
  b0->foo = 42;
  n0->value = b0;

  bar *b1 = malloc(sizeof(bar));
  b1->foo = 123;
  n1->value = b1;

  ll_append(list, n0);
  ll_append(list, n1);

  ll_print(list, bar_printer);

  // Two elements
  ll_remove_tail(list);
  ll_print(list, bar_printer);

  // One element
  ll_remove_tail(list);
  ll_print(list, bar_printer);

  // Empty list
  ll_remove_tail(list);
  ll_print(list, bar_printer);

  free(b0);
  free(b1);
  free(n0);
  free(n1);
  free(list);
}

void test_linked_list_remove_head() {
  printf("\ntest_linked_list_remove_head()\n");

  ll_t *list = ll_list_create();
  ll_node_t *n0 = ll_node_create();
  ll_node_t *n1 = ll_node_create();

  bar *b0 = malloc(sizeof(bar));
  b0->foo = 42;
  n0->value = b0;

  bar *b1 = malloc(sizeof(bar));
  b1->foo = 123;
  n1->value = b1;

  ll_append(list, n0);
  ll_append(list, n1);

  ll_print(list, bar_printer);

  // Two elements
  ll_remove_head(list);
  ll_print(list, bar_printer);

  // One element
  ll_remove_head(list);
  ll_print(list, bar_printer);

  // Empty list
  ll_remove_head(list);
  ll_print(list, bar_printer);

  free(b0);
  free(b1);
  free(n0);
  free(n1);
  free(list);
}

void test_linked_list_empty() {
  printf("\ntest_linked_list_empty()\n");

  ll_t *list = ll_list_create();
  ll_node_t *n0 = ll_node_create();

  bar *b0 = malloc(sizeof(bar));
  b0->foo = 42;
  n0->value = b0;

  ll_append(list, n0);

  printf("empty: %d ", ll_empty(list));
  ll_print(list, bar_printer);

  ll_remove_tail(list);

  printf("empty: %d ", ll_empty(list));
  ll_print(list, bar_printer);

  free(b0);
  free(n0);
  free(list);
}

void test_linked_list_find() {
  printf("\ntest_linked_list_find()\n");

  ll_t *list = ll_list_create();
  ll_node_t *n0 = ll_node_create();
  ll_node_t *n1 = ll_node_create();
  ll_node_t *n2 = ll_node_create();

  bar *b0 = malloc(sizeof(bar));
  b0->foo = 42;
  n0->value = b0;

  bar *b1 = malloc(sizeof(bar));
  b1->foo = 123;
  n1->value = b1;

  bar *b2 = malloc(sizeof(bar));
  b2->foo = -1;
  n2->value = b2;

  ll_append(list, n0);
  ll_append(list, n1);
  ll_append(list, n2);

  ll_print(list, bar_printer);

  int value = 123;
  ll_node_t *result = ll_find(list, &value, foo_finder);

  printf("Found %d\n", ((bar *)result->value)->foo);

  free(b0);
  free(b1);
  free(b2);
  free(n0);
  free(n1);
  free(n2);
  free(list);
}

//------------------------------------------------------------------------------

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

  printf("%s\nLinked list\n%s\n", divider, divider);

  test_linked_list_prepend();
  test_linked_list_append();
  test_linked_list_remove_head();
  test_linked_list_remove_tail();
  test_linked_list_empty();
  test_linked_list_find();

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
