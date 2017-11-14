/**
 * --- Day 1: No Time for a Taxicab ---
 * 
 * Santa's sleigh uses a very high-precision clock to guide its movements, and
 * the clock's oscillator is regulated by stars. Unfortunately, the stars have
 * been stolen... by the Easter Bunny. To save Christmas, Santa needs you to
 * retrieve all fifty stars by December 25th.
 * 
 * Collect stars by solving puzzles. Two puzzles will be made available on each
 * day in the advent calendar; the second puzzle is unlocked when you complete
 * the first. Each puzzle grants one star. Good luck!
 * 
 * You're airdropped near Easter Bunny Headquarters in a city somewhere. "Near",
 * unfortunately, is as close as you can get - the instructions on the Easter
 * Bunny Recruiting Document the Elves intercepted start here, and nobody had
 * time to work them out further.
 * 
 * The Document indicates that you should start at the given coordinates (where
 * you just landed) and face North. Then, follow the provided sequence: either
 * turn left (L) or right (R) 90 degrees, then walk forward the given number of
 * blocks, ending at a new intersection.
 * 
 * There's no time to follow such ridiculous instructions on foot, though, so
 * you take a moment and work out the destination. Given that you can only walk
 * on the street grid of the city, how far is the shortest path to the
 * destination?
 * 
 * For example:
 * 
 *  - Following R2, L3 leaves you 2 blocks East and 3 blocks North, or 5 blocks
 *    away.
 *  - R2, R2, R2 leaves you 2 blocks due South of your starting position, which
 *    is 2 blocks away.
 *  - R5, L5, R5, R3 leaves you 12 blocks away.
 *
 * --- Part Two ---
 *
 *  Then, you notice the instructions continue on the back of the Recruiting
 *  Document. Easter Bunny HQ is actually at the first location you visit twice.
 *
 *  For example, if your instructions are R8, R4, R4, R8, the first location you
 *  visit twice is 4 blocks away, due East.
 *
 *  How many blocks away is the first location you visit twice?
 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

enum directions { NORTH, EAST, SOUTH, WEST };

int main(int argc, char const *argv[])
{
  char d;
  int maxima = 0;
  int n, facing = 0; // Start facing north

  // Without knowing a specific direction, the maximum distance the bunny can
  // move in *any* direction, is the sum of all instruction lengths.
  while(scanf(" %*[^0-9]%d,", &n) != EOF) {
    maxima += n;
  }

  rewind(stdin);

  // Make a grid than can fit maximum distance of travel in any direction and
  // place the bunny in the center.
  int grid[maxima * 2 + 1][maxima * 2 + 1];
  memset(grid, 0, sizeof(grid[0][0]) * (maxima * 2 + 1) * 2);
  int dx = maxima, dy = maxima;
  int i, stop = 0;

  while(scanf(" %c%d,", &d, &n) != EOF) {
    if (d == 'R') {
      facing = (facing + 1) % 4;
    }
    if (d == 'L') {
      facing = (facing + 3) % 4;
    }

    for (i = 0; i < n; i++) {
      if (facing == NORTH) {
        dy -= 1;
      }
      if (facing == EAST) {
        dx += 1;
      }
      if (facing == SOUTH) {
        dy += 1;
      }
      if (facing == WEST) {
        dx -= 1;
      }

      if (grid[dx][dy]++ != 0) {
        stop = 1;
        break;
      }
    }

    if (stop) break;
  }

  printf("%d, %d\n", dx, dy);
  printf("Easter Bunny HQ is %d blocks away\n", dx + dy - 2 * maxima);

  return 0;
}
