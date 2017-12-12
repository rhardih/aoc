#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ll.h"
#include "q.h"

// Linked list tests

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

// Queue tests

void test_queue_enqueue() {
  printf("\ntest_queue_enqueue()\n");

  q_t *queue = q_queue_create();
  q_node_t *n0 = q_node_create();
  q_node_t *n1 = q_node_create();

  bar *b0 = malloc(sizeof(bar));
  b0->foo = 1;
  n0->value = b0;

  bar *b1 = malloc(sizeof(bar));
  b1->foo = 2;
  n1->value = b1;

  q_print(queue, bar_printer);

  q_enqueue(queue, n0);
  q_print(queue, bar_printer);

  q_enqueue(queue, n1);
  q_print(queue, bar_printer);

  free(b0);
  free(b1);
  free(n0);
  free(n1);
  free(queue);
}

void test_queue_dequeue() {
  printf("\ntest_queue_dequeue()\n");

  q_t *queue = q_queue_create();
  q_node_t *n0 = q_node_create();
  q_node_t *n1 = q_node_create();

  bar *b0 = malloc(sizeof(bar));
  b0->foo = 1;
  n0->value = b0;

  bar *b1 = malloc(sizeof(bar));
  b1->foo = 2;
  n1->value = b1;

  q_enqueue(queue, n0);
  q_enqueue(queue, n1);

  q_print(queue, bar_printer);

  // Two elements
  q_dequeue(queue);
  q_print(queue, bar_printer);

  // One element
  q_dequeue(queue);
  q_print(queue, bar_printer);

  // Empty queue
  q_dequeue(queue);
  q_print(queue, bar_printer);

  free(b0);
  free(b1);
  free(n0);
  free(n1);
  free(queue);
}

void test_queue_empty() {
  printf("\ntest_queue_empty()\n");

  q_t *queue = q_queue_create();
  q_node_t *n0 = q_node_create();
  q_node_t *n1 = q_node_create();

  bar *b0 = malloc(sizeof(bar));
  b0->foo = 42;
  n0->value = b0;

  q_enqueue(queue, n0);

  q_print(queue, bar_printer);

  printf("Empty: %d\n", q_empty(queue));

  // Empty queue
  q_dequeue(queue);
  q_print(queue, bar_printer);

  printf("Empty: %d\n", q_empty(queue));

  free(b0);
  free(n0);
  free(queue);
}

//------------------------------------------------------------------------------

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

  printf("%s\n\nQueue\n%s\n", divider, divider);

  test_queue_enqueue();
  test_queue_dequeue();
  test_queue_empty();

  return 0;
}
