#include <stdio.h>
#include <stdlib.h>

#include "ll.h"

ll_t *ll_list_create() {
  ll_t *l = malloc(sizeof(ll_t));

  l->first = NULL;

  return l;
}

ll_node_t *ll_node_create() {
  ll_node_t *n = malloc(sizeof(ll_node_t));

  n->value = NULL;
  n->next = NULL;

  return n;
}

void ll_prepend(ll_t *list, ll_node_t *node) {
  node->next = list->first;
  list->first = node;
}

void ll_append(ll_t *list, ll_node_t *node) {
  ll_node_t *current = list->first;

  if (current == NULL ) {
    list->first = node;
  } else {
    while (current->next != NULL) {
      current = current->next;
    }

    current->next = node;
  }
}

ll_node_t *ll_remove_tail(ll_t *list) {
  ll_node_t *tail;
  ll_node_t *current = list->first;

  if (current == NULL) return NULL;

  if (current->next == NULL) {
    tail = current;
    list->first = NULL;
  } else {
    while (current->next->next != NULL) {
      current = current->next;
    }

    tail = current->next;
    current->next = NULL;
  }


  return tail;
}

ll_node_t *ll_remove_head(ll_t *list) {
  ll_node_t *head = list->first;

  if (head == NULL) return NULL;

  list->first = list->first->next;

  return head;
}

int ll_empty(ll_t *list) {
  return list->first == NULL;
}

void ll_print(ll_t *list, void (*printer)(void *)) {
  ll_node_t *current = list->first;

  printf("( ");

  if (current != NULL) {
    printer(current->value);

    while (current->next != NULL) {
      current = current->next;
      printf(", ");
      printer(current->value);
    }
  }

  printf(" )\n");
}
