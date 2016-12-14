#include "stdio.h"
#include "limits.h"
#include "stdlib.h"

#include "ll.h"

#define XMAX 60
#define YMAX 50

#define FAVNUM 1364

//#define DEBUG

typedef struct node node_t;

struct node {
  int distance;
  node_t *parent;
  ll_t *adjecent;

  int x;
  int y;
};

#ifdef DEBUG
void node_printer(void *p) {
  node_t *n = (node_t *)p;

  printf("[%d,%d]: %d", n->x, n->y, n->distance);
}
#endif

// breadth first search
void bfs(node_t *graph[XMAX][YMAX], node_t *root) {
  ll_t *q = ll_list_create();
  ll_node_t *current, *adjecent;

  root->distance = 0;

  // enqueue root
  ll_node_t *n = ll_node_create();
  n->value = root;
  ll_prepend(q, n);

  while (!ll_empty(q)) {
    current = ll_remove_tail(q);
    node_t *c = (node_t *)current->value;
    adjecent = c->adjecent->first;

#ifdef DEBUG
    printf("b; %d,%d: ", c->x, c->y);
    ll_print(c->adjecent, node_printer);
#endif
    
    while (adjecent != NULL) {
      node_t *n = (node_t *)adjecent->value;

      if (n->distance == INT_MAX) {
        n->distance = c->distance + 1;
        n->parent = c;

        ll_node_t *lln = malloc(sizeof(ll_node_t));
        lln->value = n;

        ll_prepend(q, lln);
      }

      adjecent = adjecent->next;
    }

#ifdef DEBUG
    printf("a; %d,%d: ", c->x, c->y);
    ll_print(c->adjecent, node_printer);
    printf("a; q:");
    ll_print(q, node_printer);
#endif
  }
}

int main(int argc, char const *argv[])
{
  int locations = 0;
  int x, y, tmp, bit_count;
  char office[XMAX][YMAX];
  node_t *graph[XMAX][YMAX];

  for (y = 0; y < YMAX; y++)
  {
    for (x = 0; x < XMAX; x++)
    {
      tmp = x * x + 3 * x + 2 * x * y + y + y * y;
      tmp += FAVNUM;
      bit_count = 0;

      while (tmp > 0)
      {
        bit_count += tmp & 1;
        tmp = tmp >> 1;
      }

      if (bit_count % 2 == 0) {
        office[x][y] =  '.'; 
        graph[x][y] = malloc(sizeof(node_t));
        graph[x][y]->distance = INT_MAX;
        graph[x][y]->parent = NULL;
        graph[x][y]->adjecent = ll_list_create();
        graph[x][y]->x = x;
        graph[x][y]->y = y;
      } else {
        office[x][y] =  '#';
        graph[x][y] = NULL;
      }
    }
  }

  // Build adjecency list for each location
  for (y = 0; y < YMAX; y++)
  {
    for (x = 0; x < XMAX; x++)
    {
      if (graph[x][y] != NULL) {
        if (x > 0 && graph[x - 1][y] != NULL) {
          ll_node_t *n = ll_node_create();
          n->value = graph[x - 1][y];
          ll_append(graph[x][y]->adjecent, n);
        }

        if (x < XMAX - 1 && graph[x + 1][y] != NULL) {
          ll_node_t *n = ll_node_create();
          n->value = graph[x + 1][y];
          ll_append(graph[x][y]->adjecent, n);
        }

        if (y > 0 && graph[x][y - 1] != NULL) {
          ll_node_t *n = ll_node_create();
          n->value = graph[x][y - 1];
          ll_append(graph[x][y]->adjecent, n);
        }

        if (y < YMAX - 1 && graph[x][y + 1] != NULL) {
          ll_node_t *n = ll_node_create();
          n->value = graph[x][y + 1];
          ll_append(graph[x][y]->adjecent, n);
        }
      }
    }
  }

  bfs(graph, graph[1][1]);
  office[31][39] = 'X';

  for (y = 0; y < YMAX; y++)
  {
    for (x = 0; x < XMAX; x++)
    {
      node_t *n = graph[x][y];
      if (n != NULL && n->distance <= 50) {
        locations++;
        printf("%c", '+');
      } else {
        printf("%c", office[x][y]);
      }
    }
    printf("\n");
  }

  printf("Fewest number of steps required: %d\n", graph[31][39]->distance);
  printf("Reachable locations in 50 steps: %d\n", locations);

  return 0;
}
