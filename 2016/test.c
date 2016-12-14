#include <stdio.h>
#include <stdlib.h>

#include "ll.h"

typedef struct {
  int foo;
} bar;

void bar_printer(void *p) {
  printf("%d", ((bar *)p)->foo);
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

int main(int argc, char const *argv[])
{
  test_linked_list_prepend();
  test_linked_list_append();
  test_linked_list_remove_head();
  test_linked_list_remove_tail();
  test_linked_list_empty();

  return 0;
}
