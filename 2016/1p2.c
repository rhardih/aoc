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
