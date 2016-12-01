#include "stdio.h"
#include "stdlib.h"

enum direction { NORTH, EAST, SOUTH, WEST };

int main(int argc, char const *argv[])
{
  char d;
  int n, x = 0, y = 0, facing = 0; // Start facing north

  while(scanf(" %c%d,", &d, &n) != EOF) {
    if (d == 'R') {
      facing = (facing + 1) % 4;
    }
    if (d == 'L') {
      facing = (facing + 3) % 4;
    }

    if (facing == NORTH) {
      y -= n;
    }
    if (facing == EAST) {
      x += n;
    }
    if (facing == SOUTH) {
      y += n;
    }
    if (facing == WEST) {
      x -= n;
    }
  }

  printf("Easter Bunny HQ is %d blocks away\n", abs(x) + abs(y));

  return 0;
}
