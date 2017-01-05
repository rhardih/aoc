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
 */

#include <stdio.h> 

#define XMAX 32
#define YMAX 30

typedef struct {
  int size;
  int used;
  int avail;
} node_t;

int main(int argc, char const *argv[])
{
  char buf[50];
  int x0, x1, y0, y1, pairs = 0;
  node_t grid[YMAX][XMAX], A, B;

  // skip first two lines
  fgets(buf, 50, stdin);
  fgets(buf, 50, stdin);

  while(fgets(buf, 50, stdin) != NULL) {
    node_t n;

    sscanf(buf, "/dev/grid/node-x%d-y%d %dT %dT %d", &x0, &y0, &n.size, &n.used, &n.avail);

    grid[y0][x0] = n;
  }

  for (y0 = 0; y0 < YMAX; y0++)
  {
    for (x0 = 0; x0 < XMAX; x0++)
    {
      A = grid[y0][x0];

      for (y1 = 0; y1 < YMAX; y1++)
      {
        for (x1 = 0; x1 < XMAX; x1++)
        {
          if (x0 == x1 && y0 == y1) continue;

          B = grid[y1][x1];

          if (A.used != 0 && A.used <= B.avail) pairs++;
        }
      }
    }
  }

  printf("Number of viable pairs: %d\n", pairs);

  return 0;
}
