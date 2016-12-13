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
