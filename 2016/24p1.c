/**
 * --- Day 24: Air Duct Spelunking ---
 * 
 * You've finally met your match; the doors that provide access to the roof are
 * locked tight, and all of the controls and related electronics are
 * inaccessible. You simply can't reach them.
 * 
 * The robot that cleans the air ducts, however, can.
 * 
 * It's not a very fast little robot, but you reconfigure it to be able to
 * interface with some of the exposed wires that have been routed through the
 * HVAC system. If you can direct it to each of those locations, you should be
 * able to bypass the security controls.
 * 
 * You extract the duct layout for this area from some blueprints you acquired
 * and create a map with the relevant locations marked (your puzzle input). 0 is
 * your current location, from which the cleaning robot embarks; the other
 * numbers are (in no particular order) the locations the robot needs to visit
 * at least once each. Walls are marked as #, and open passages are marked as ..
 * Numbers behave like open passages.
 * 
 * For example, suppose you have a map like the following:
 * 
 * ###########
 * #0.1.....2#
 * #.#######.#
 * #4.......3#
 * ###########
 *
 * To reach all of the points of interest as quickly as possible, you would have
 * the robot take the following path:
 * 
 * 0 to 4 (2 steps)
 * 4 to 1 (4 steps; it can't move diagonally)
 * 1 to 2 (6 steps)
 * 2 to 3 (2 steps)
 *
 * Since the robot isn't very fast, you need to find it the shortest route. This
 * path is the fewest steps (in the above example, a total of 14) required to
 * start at 0 and then visit every other location at least once.
 * 
 * Given your actual map, and starting from location 0, what is the fewest
 * number of steps required to visit every non-0 number marked on the map at
 * least once?
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#include "ll.h"

#define MWIDTH 183
#define MWIDTH_END 184 // room for \0
#define MHEIGHT 37
#define LCOUNT 8

typedef struct {
  int x;
  int y;
} location_t;

#define min(x, y) ((x) < (y) ? (x) : (y))

// modified breadth first search from 13p2
void bfs(char m[MHEIGHT][MWIDTH_END], int d[MHEIGHT][MWIDTH], location_t start) {
  ll_t *q = ll_list_create();
  ll_node_t *current, *new;
  location_t *root = malloc(sizeof(location_t)), l, *c, *n;
  int i, x, y;

  root->x = start.x;
  root->y = start.y;
  d[root->y][root->x] = 0;

  // enqueue root
  new = ll_node_create();
  new->value = root;
  ll_prepend(q, new);

  while (!ll_empty(q)) {
    current = ll_remove_tail(q);
    c = (location_t *)current->value;
    location_t adjecent[4] = {
      { c->x, c->y - 1 },
      { c->x + 1, c->y },
      { c->x, c->y + 1 },
      { c->x - 1, c->y }
    };

    for (i = 0; i < 4; i++)
    {
      l = adjecent[i];

      if (m[l.y][l.x] != '#' && d[l.y][l.x] == INT_MAX)
      {
        new = ll_node_create();
        n = malloc(sizeof(location_t));

        d[l.y][l.x] = d[c->y][c->x] + 1;

        n->x = l.x;
        n->y = l.y;
        new->value = n;

        ll_prepend(q, new);
      }
    }
  }
}

void init_distances(int d[MHEIGHT][MWIDTH]) {
  for (int i = 0; i < MHEIGHT; i++)
    for (int j = 0; j < MWIDTH; j++)
      d[i][j] = INT_MAX;
}

// Brute forcing all possible combinations, since there's only 8 destinations.
// This should result in 7! tests, given fixed starting location 0.
int travel(int location_distances[LCOUNT][LCOUNT], int visited[LCOUNT], int current) {
  int i, j, d = INT_MAX, tmp;

  for (i = 0; i < LCOUNT; i++)
  {
    if (i == current || visited[i]) continue;

    int vcopy[LCOUNT];
    for (j = 0; j < LCOUNT; j++) vcopy[j] = visited[j];
    vcopy[i] = 1;

    d = min(d, location_distances[current][i] + travel(location_distances, vcopy, i));
  }

  return d == INT_MAX ? 0 : d;
}

int main(int argc, char const *argv[])
{
  char map[MHEIGHT][MWIDTH_END], *p;
  int steps = 0, i = 0, j, d;
  location_t locations[LCOUNT], start, end;
  int distances[MHEIGHT][MWIDTH];
  int location_distances[LCOUNT][LCOUNT];

  // Read map and save locations
  while(scanf("%s\n", map[i]) != EOF) {
    for (j = 0; j < LCOUNT; j++)
    {
      // save x, y coordinates of locations by finding number characters
      if ((p = strchr(map[i], (int)'0' + j)) != NULL) {
        locations[j].x = (int)(p - map[i]);
        locations[j].y = i;
      }
    }
    i++;
  }

  // Find distances between locations with breadth first search
  for (i = 0; i < LCOUNT; i++)
  {
    init_distances(distances);
    start = locations[i];
    bfs(map, distances, start);

    /*printf("L%d: %d, %d\n", i, locations[i].x, locations[i].y);*/

    for (j = 0; j < LCOUNT; j++)
    {
      if (i == j)
      {
        location_distances[i][j] = 0;
        location_distances[j][i] = 0;
      } else {
        end = locations[j];
        d = distances[end.y][end.x];
        location_distances[i][j] = d;
        location_distances[j][i] = d;
      }

      /*printf("  - Distance to L%d: %d\n", j, location_distances[i][j]);*/
    }
  }

  // Marks first location as visited, remaining elements will be zero
  int visited[LCOUNT] = { 1 };
  steps = travel(location_distances, visited, 0);

  printf("Fewest number of steps required to visit all locations: %d\n", steps);

  return 0;
}
