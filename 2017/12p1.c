/**
 * --- Day 12: Digital Plumber ---
 *
 * Walking along the memory banks of the stream, you find a small village that
 * is experiencing a little confusion: some programs can't communicate with each
 * other.
 *
 * Programs in this village communicate using a fixed system of pipes. Messages
 * are passed between programs using these pipes, but most programs aren't
 * connected to each other directly. Instead, programs pass messages between
 * each other until the message reaches the intended recipient.
 *
 * For some reason, though, some of these messages aren't ever reaching their
 * intended recipient, and the programs suspect that some pipes are missing.
 * They would like you to investigate.
 *
 * You walk through the village and record the ID of each program and the IDs
 * with which it can communicate directly (your puzzle input). Each program has
 * one or more programs with which it can communicate, and these pipes are
 * bidirectional; if 8 says it can communicate with 11, then 11 will say it can
 * communicate with 8.
 *
 * You need to figure out how many programs are in the group that contains
 * program ID 0.
 *
 * For example, suppose you go door-to-door like a travelling salesman and
 * record the following list:
 *
 * 0 <-> 2
 * 1 <-> 1
 * 2 <-> 0, 3, 4
 * 3 <-> 2, 4
 * 4 <-> 2, 3, 6
 * 5 <-> 6
 * 6 <-> 4, 5
 *
 * In this example, the following programs are in the group that contains
 * program ID 0:
 *
 * - Program 0 by definition.
 * - Program 2, directly connected to program 0.
 * - Program 3 via program 2.
 * - Program 4 via program 2.
 * - Program 5 via programs 6, then 4, then 2.
 * - Program 6 via programs 4, then 2.
 *
 * Therefore, a total of 6 programs are in this group; all but program 1, which
 * has a pipe that connects it to itself.
 *
 * How many programs are in the group that contains program ID 0?
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "ll.h"
#include "q.h"

#define INPUT_SIZE  2000

typedef struct node node_t;

struct node {
  enum { WHITE, GRAY, BLACK } color;
  int d;
  node_t *predecessor;
  ll_t *adj;

  void *value;
};

void bfs(node_t graph[INPUT_SIZE], node_t *s) {
  node_t *u;

  for (int i = 0; i < INPUT_SIZE; ++i)
  {
    u = &graph[i];

    if (u == s)
      continue;

    u->color = WHITE;
    u->d = INT_MAX;
    u->predecessor = NULL;
  }

  s->color = GRAY;
  s->d = 0;
  s->predecessor = NULL;

  // Create a queue
  q_t *queue = q_queue_create();

  // Enqueue s
  q_node_t *q_s = q_node_create();
  q_s->value = s;
  q_enqueue(queue, q_s);

  q_node_t *q_u, *adj;
  ll_node_t *ll_v, *q_v;
  node_t *v;

  while (!q_empty(queue)) {
    q_u = q_dequeue(queue);
    u = (node_t *)q_u->value;

    ll_v = u->adj->first;

    while (ll_v != NULL) {
      v = (node_t *)ll_v->value;

      if (v->color == WHITE)
      {
        v->color = GRAY;
        v->d = u->d + 1;
        v->predecessor = u;

        q_v = q_node_create();
        q_v->value = v;
        q_enqueue(queue, q_v);
      }

      ll_v = ll_v->next;
    }

    u->color = BLACK;
    free(q_u);
  }

  free(queue);
}

static node_t graph[INPUT_SIZE];

int main(int argc, char const *argv[])
{
  char *line = NULL;
  size_t linecap = 0;
  ssize_t linelen;
  char *token, *string, *tofree;
  uint64_t i, j;

  while ((linelen = getline(&line, &linecap, stdin)) > 0)
  {
    tofree = string = strdup(line);

    token = strsep(&string, " ");

    sscanf(token, "%lld", &i);

    graph[i].value = (void *)i;
    graph[i].adj = ll_list_create();

    // Skip the <->
    token = strsep(&string, " ");

    while ((token = strsep(&string, " ,\n")) != NULL)
    {
      if (*token != '\0')
      {
        sscanf(token, "%lld", &j);

        ll_node_t *new = ll_node_create();
        new->value = &graph[j];
        graph[j].value = (void *)j;
        ll_append(graph[i].adj, new);
      }
    }

    free(tofree);
  }

  // Find all connected nodes using a breadth first search
  bfs(graph, &graph[0]);

  // All nodes connected to 0, should now have a distance != INT_MAX,
  int ncount = 0;

  for (i = 0; i < INPUT_SIZE; ++i)
    if (graph[i].d != INT_MAX)
      ncount++;

  // Cleanup
  for (i = 0; i < INPUT_SIZE; ++i)
  {
    ll_node_t *a = graph[i].adj->first, *tmp;
    while (a != NULL)
    {
      tmp = a;
      a = a->next;
      free(tmp);
    }
    free(graph[i].adj);
  }

  printf("Number of nodes connected to the '0' node: %d\n", ncount);
}
