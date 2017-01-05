/**
 * --- Day 22: Grid Computing ---
 *
 * You gain access to a massive storage cluster arranged in a grid; each storage
 * node is only connected to the four nodes directly adjacent to it (three if
 * the node is on an edge, two if it's in a corner).
 *
 * You can directly access data only on node /dev/grid/node-x0-y0, but you can
 * perform some limited actions on the other nodes:
 *
 * You can get the disk usage of all nodes (via df). The result of doing this is
 * in your puzzle input.  You can instruct a node to move (not copy) all of its
 * data to an adjacent node (if the destination node has enough space to receive
 * the data). The sending node is left empty after this operation.  Nodes are
 * named by their position: the node named node-x10-y10 is adjacent to nodes
 * node-x9-y10, node-x11-y10, node-x10-y9, and node-x10-y11.
 *
 * Before you begin, you need to understand the arrangement of data on these
 * nodes. Even though you can only move data between directly connected nodes,
 * you're going to need to rearrange a lot of the data to get access to the data
 * you need. Therefore, you need to work out how you might be able to shift data
 * around.
 *
 * To do this, you'd like to count the number of viable pairs of nodes. A viable
 * pair is any two nodes (A,B), regardless of whether they are directly
 * connected, such that:
 *
 * Node A is not empty (its Used is not zero).  Nodes A and B are not the same
 * node.  The data on node A (its Used) would fit on node B (its Avail).  How
 * many viable pairs of nodes are there?
 *
 * --- Part Two ---
 *
 * Now that you have a better understanding of the grid, it's time to get to
 * work.
 *
 * Your goal is to gain access to the data which begins in the node with y=0 and
 * the highest x (that is, the node in the top-right corner).
 *
 * For example, suppose you have the following grid:
 *
 * Filesystem            Size  Used  Avail  Use%
 * /dev/grid/node-x0-y0   10T    8T     2T   80%
 * /dev/grid/node-x0-y1   11T    6T     5T   54%
 * /dev/grid/node-x0-y2   32T   28T     4T   87%
 * /dev/grid/node-x1-y0    9T    7T     2T   77%
 * /dev/grid/node-x1-y1    8T    0T     8T    0%
 * /dev/grid/node-x1-y2   11T    7T     4T   63%
 * /dev/grid/node-x2-y0   10T    6T     4T   60%
 * /dev/grid/node-x2-y1    9T    8T     1T   88%
 * /dev/grid/node-x2-y2    9T    6T     3T   66%
 *
 * In this example, you have a storage grid 3 nodes wide and 3 nodes tall. The
 * node you can access directly, node-x0-y0, is almost full. The node containing
 * the data you want to access, node-x2-y0 (because it has y=0 and the highest x
 * value), contains 6 terabytes of data - enough to fit on your node, if only
 * you could make enough space to move it there.
 *
 * Fortunately, node-x1-y1 looks like it has enough free space to enable you to
 * move some of this data around. In fact, it seems like all of the nodes have
 * enough space to hold any node's data (except node-x0-y2, which is much
 * larger, very full, and not moving any time soon). So, initially, the grid's
 * capacities and connections look like this:
 *
 * ( 8T/10T) --  7T/ 9T -- [ 6T/10T]
 *     |           |           |
 *   6T/11T  --  0T/ 8T --   8T/ 9T
 *     |           |           |
 *  28T/32T  --  7T/11T --   6T/ 9T
 *
 * The node you can access directly is in parentheses; the data you want starts
 * in the node marked by square brackets.
 *
 * In this example, most of the nodes are interchangable: they're full enough
 * that no other node's data would fit, but small enough that their data could
 * be moved around. Let's draw these nodes as .. The exceptions are the empty
 * node, which we'll draw as _, and the very large, very full node, which we'll
 * draw as #. Let's also draw the goal data as G. Then, it looks like this:
 *
 * (.) .  G
 *  .  _  .
 *  #  .  .
 *
 * The goal is to move the data in the top right, G, to the node in parentheses.
 * To do this, we can issue some commands to the grid and rearrange the data:
 *
 * Move data from node-y0-x1 to node-y1-x1, leaving node node-y0-x1 empty:
 *
 * (.) _  G
 *  .  .  .
 *  #  .  .
 *
 * Move the goal data from node-y0-x2 to node-y0-x1:
 *
 * (.) G  _
 *  .  .  .
 *  #  .  .
 *
 * At this point, we're quite close. However, we have no deletion command, so we
 * have to move some more data around. So, next, we move the data from
 * node-y1-x2 to node-y0-x2:
 *
 * (.) G  .
 *  .  .  _
 *  #  .  .
 *
 * Move the data from node-y1-x1 to node-y1-x2:
 *
 * (.) G  .
 *  .  _  .
 *  #  .  .
 *
 * Move the data from node-y1-x0 to node-y1-x1:
 *
 * (.) G  .
 *  _  .  .
 *  #  .  .
 *
 * Next, we can free up space on our node by moving the data from node-y0-x0 to
 * node-y1-x0:
 *
 * (_) G  .
 *  .  .  .
 *  #  .  .
 *
 * Finally, we can access the goal data by moving the it from node-y0-x1 to
 * node-y0-x0:
 *
 * (G) _  .
 *  .  .  .
 *  #  .  .
 *
 * So, after 7 steps, we've accessed the data we want. Unfortunately, each of
 * these moves takes time, and we need to be efficient:
 *
 * What is the fewest number of steps required to move your goal data to node-x0-y0?
 */

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

#include "ll.h"

#define XMAX 32
#define YMAX 30
#define USELIMIT 85
#define MOVELIMIT 94 // found in input as size of 0% node
#define TICK 30

#define clear() printf("\033[H\033[J")
#define swap(x, y) (x) ^= (y); (y) ^= (x); (x) ^= (y)

typedef struct node node_t;

struct node {
  int size;
  int used;
  int avail;
  int use;

  ll_t *adjecent;
  node_t *parent;
  int distance;

  int x;
  int y;
  int goal;
};

void print(node_t *grid[YMAX][XMAX]) {
  int x, y;
  node_t *n;

  for (y = 0; y < YMAX; y++)
  {
    for (x = 0; x < XMAX; x++)
    {
      n = grid[y][x];

      if (y == 0 && x == 0) {
        printf("(");
      } else {
        printf(" ");
      }

      if (n->goal) {
        printf("G");
      } else {
        if (n->avail) {
          if (n->use > USELIMIT) {
            printf("#");
          } else if (n->use == 0) {
            printf("_");
          } else {
            printf(".");
          }
        }
      }

      if (y == 0 && x == 0) {
        printf(")");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
}

void bfs(node_t *grid[YMAX][XMAX], node_t *root) {
  node_t *A, *B;

  for (int y = 0; y < YMAX; y++)
  {
    for (int x = 0; x < XMAX; x++)
    {
      A = grid[y][x];

      A->distance = INT_MAX;
      A->parent = NULL;

      A->adjecent = ll_list_create();

      if (y > 0) {
        B = grid[y - 1][x];

        if (B->used <= MOVELIMIT && B->goal == 0)
        {
          ll_node_t *up = ll_node_create();
          up->value = B;
          ll_append(A->adjecent, up);
        }
      }

      if (y < YMAX - 1) {
        B = grid[y + 1][x];

        if (B->used <= MOVELIMIT && B->goal == 0)
        {
          ll_node_t *down = ll_node_create();
          down->value = B;
          ll_append(A->adjecent, down);
        }
      }

      if (x > 0) {
        B = grid[y][x - 1];

        if (B->used <= MOVELIMIT && B->goal == 0)
        {
          ll_node_t *left = ll_node_create();
          left->value = B;
          ll_append(A->adjecent, left);
        }
      }

      if (x < XMAX - 1) {
        B = grid[y][x + 1];

        if (B->used <= MOVELIMIT && B->goal == 0)
        {
          ll_node_t *right = ll_node_create();
          right->value = B;
          ll_append(A->adjecent, right);
        }
      }
    }
  }

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

    while (adjecent != NULL) {
      node_t *n = (node_t *)adjecent->value;

      if (n->distance == INT_MAX) {
        n->distance = c->distance + 1;
        n->parent = c;

        ll_node_t *lln = ll_node_create();
        lln->value = n;

        ll_prepend(q, lln);
      }

      adjecent = adjecent->next;
    }
  }
}

void move(node_t *current, node_t *next) {
  node_t tmp = *current;
  *current = *next;
  *next = tmp;

  // Swap coordinates back
  swap(current->x, next->x);
  swap(current->y, next->y);
}

int move_empty_swap_goal(node_t *grid[YMAX][XMAX], ll_node_t *llcurrent) {
  int steps = 0, y, x;
  ll_t *etog = ll_list_create();
  node_t *ncurrent, *nempty, *ngoal, *nnext;
  ll_node_t *n;

  for (y = 0; y < YMAX; y++)
  {
    for (x = 0; x < XMAX; x++)
    {
      if (grid[y][x]->goal)
        ngoal = grid[y][x];

      if (grid[y][x]->used == 0)
        nempty = grid[y][x];
    }
  }

  // Route from current empty node to first location on gtos
  bfs(grid, nempty);

  ncurrent = llcurrent->value;

  // Reverse route, not including root
  while (ncurrent->parent != NULL) {
    n = ll_node_create();
    n->value = ncurrent;
    ll_prepend(etog, n);

    printf("t: %d, %d\n", ncurrent->y, ncurrent->x);

    ncurrent = ncurrent->parent;
  }

  // first non root node
  llcurrent = etog->first;

  // Traverse route updating empty node
  while (llcurrent != NULL) {
    ncurrent = llcurrent->value;

    clear();
    print(grid);
    usleep(TICK * 1000);

    move(ncurrent, nempty);

    nempty = ncurrent;
    llcurrent = llcurrent->next;

    steps++;
  }

  clear();
  print(grid);
  usleep(TICK * 1000);

  // Move goal node data to empty node

  move(ngoal, nempty);
  steps++;

  clear();
  print(grid);
  usleep(TICK * 1000);

  return steps;
}

int main(int argc, char const *argv[])
{
  char buf[50];
  int steps = 0;
  node_t *grid[YMAX][XMAX], *ncurrent;
  int availp[YMAX][XMAX][YMAX][XMAX] = { 0 };
  ll_t *gtos = ll_list_create();
  ll_node_t *n, *llcurrent;

  // skip first two lines
  fgets(buf, 50, stdin);
  fgets(buf, 50, stdin);

  while(fgets(buf, 50, stdin) != NULL) {
    node_t *n = malloc(sizeof(node_t));

    sscanf(buf, "/dev/grid/node-x%d-y%d %dT %dT %dT %d",
        &n->x, &n->y, &n->size, &n->used, &n->avail, &n->use);

    n->goal = 0;

    grid[n->y][n->x] = n;
  }

  grid[0][XMAX - 1]->goal = 1;

  // First step is determining the shortest viable route where the data can be
  // moved from the goal node to the target node. Let's call this route the GR.
  //
  // When the GR is known, we can continually make the next location the empty
  // node, and then move the data from the current goal node onto the empty
  // node.
  //
  // In order to minimize the overal steps needed, it's also necessary to
  // minimize the steps needed to make the next location the empty node.
  //
  // After each data move from the goal node, it is thus necessary to find the
  // shortest viable path from the current location of the empty node, to the
  // next location on the goal nodes shortest route. Let's call this route ER.
  //
  // When the ER is known, data is continuously swapped onto the empty node
  // until it is at the location of the next location on the GR.

  // Bread first search from goal node, to find shortest path to x0, y0
  bfs(grid, grid[0][XMAX - 1]);

  // Store route in reverse order for easier traversal
  ncurrent = grid[0][0];
  while (ncurrent != NULL) {
    n = ll_node_create();
    n->value = ncurrent;
    ll_prepend(gtos, n);

    ncurrent = ncurrent->parent;
  }

  // first non root node
  llcurrent = gtos->first->next;

  while (llcurrent != NULL) {
    steps += move_empty_swap_goal(grid, llcurrent);

    llcurrent = llcurrent->next;
  }

  printf("Fewest number of steps needed: %d\n", steps);

  return 0;
}
