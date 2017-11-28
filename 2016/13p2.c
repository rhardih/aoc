/**
 * --- Day 13: A Maze of Twisty Little Cubicles ---
 * 
 * You arrive at the first floor of this new building to discover a much less
 * welcoming environment than the shiny atrium of the last one. Instead, you are
 * in a maze of twisty little cubicles, all alike.
 * 
 * Every location in this area is addressed by a pair of non-negative integers
 * (x,y). Each such coordinate is either a wall or an open space. You can't move
 * diagonally. The cube maze starts at 0,0 and seems to extend infinitely toward
 * positive x and y; negative values are invalid, as they represent a location
 * outside the building. You are in a small waiting area at 1,1.
 * 
 * While it seems chaotic, a nearby morale-boosting poster explains, the layout
 * is actually quite logical. You can determine whether a given x,y coordinate
 * will be a wall or an open space using a simple system:
 * 
 * - Find x*x + 3*x + 2*x*y + y + y*y.
 * - Add the office designer's favorite number (your puzzle input).
 * - Find the binary representation of that sum; count the number of bits that
 *   are 1.
 *   - If the number of bits that are 1 is even, it's an open space.
 *   - If the number of bits that are 1 is odd, it's a wall.
 *
 * For example, if the office designer's favorite number were 10, drawing walls
 * as # and open spaces as ., the corner of the building containing 0,0 would
 * look like this:
 * 
 *   0123456789
 * 0 .#.####.##
 * 1 ..#..#...#
 * 2 #....##...
 * 3 ###.#.###.
 * 4 .##..#..#.
 * 5 ..##....#.
 * 6 #...##.###
 *
 * Now, suppose you wanted to reach 7,4. The shortest route you could take is
 * marked as O:
 * 
 *   0123456789
 * 0 .#.####.##
 * 1 .O#..#...#
 * 2 #OOO.##...
 * 3 ###O#.###.
 * 4 .##OO#OO#.
 * 5 ..##OOO.#.
 * 6 #...##.###
 *
 * Thus, reaching 7,4 would take a minimum of 11 steps (starting from your
 * current location, 1,1).
 * 
 * What is the fewest number of steps required for you to reach 31,39?
 *
 * --- Part Two ---
 *
 * How many locations (distinct x,y coordinates, including your starting
 * location) can you reach in at most 50 steps?
 */

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
