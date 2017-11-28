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
 */

#include "stdio.h"
#include "limits.h"

#define XMAX 50
#define YMAX 50

#define FAVNUM 1364

#define XTARGET 31
#define YTARGET 39

void fill_distances(int x, int y, int dist, char office[XMAX][YMAX], int distances[XMAX][YMAX]) {
  if (x < 0 || x >= XMAX || y < 0 || y >= YMAX || office[x][y] != '.') {
    return;
  }

  distances[x][y] = dist;
  office[x][y] = '+';

  fill_distances(x - 1, y, dist + 1, office, distances);
  fill_distances(x + 1, y, dist + 1, office, distances);
  fill_distances(x, y - 1, dist + 1, office, distances);
  fill_distances(x, y + 1, dist + 1, office, distances);
}

int main(int argc, char const *argv[])
{
  int steps = 0;
  int x, y, tmp, bit_count;
  char office[XMAX][YMAX];
  int distances[XMAX][YMAX];

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

      office[x][y] = bit_count % 2 == 0 ? '.' : '#'; 
    }
  }

  fill_distances(1, 1, 0, office, distances);
  steps = distances[XTARGET - 1][YTARGET - 1];

  printf("Fewest number of steps required to reach %d, %d: %d\n", XTARGET, YTARGET, steps);

  return 0;
}
