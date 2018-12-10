/**
 * --- Day 10: The Stars Align ---
 *
 * --- Part Two ---
 *
 * Good thing you didn't have to wait, because that would have taken a long time
 * - much longer than the 3 seconds in the example above.
 * 
 * Impressed by your sub-hour communication capabilities, the Elves are curious:
 * exactly how many seconds would they have needed to wait for that message to
 * appear?
 */

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

// terminal dimension
#define TCOLS 178
#define TLINES 54
#define TMULT 5
#define INPUT_SIZE 357

typedef struct tuple {
  long long x, y;
} tuple_t;

typedef struct point {
  tuple_t pos, vel;
} point_t;

int main(int argc, char const *argv[]) {
  point_t points[INPUT_SIZE], p;
  long long x_max, x_min, y_max, y_min;
  int i = 0, j, k, l;
  int wait = 0;

  while(scanf("position=<%lld,%lld> velocity=<%lld,%lld>\n", &points[i].pos.x,
        &points[i].pos.y, &points[i].vel.x, &points[i].vel.y) != EOF) {
    i++;
  }

  // Move points continously, until they fit on screen and can be printed
  while (1) {
    x_max = 0, x_min = INT_MAX, y_max = 0, y_min = INT_MAX;

    for (i = 0; i < INPUT_SIZE; i++) {
      points[i].pos.x += points[i].vel.x;
      points[i].pos.y += points[i].vel.y;

      if (points[i].pos.x > x_max)
        x_max = points[i].pos.x;
      if (points[i].pos.x < x_min)
        x_min = points[i].pos.x;
      if (points[i].pos.y > y_max)
        y_max = points[i].pos.y;
      if (points[i].pos.y < y_min)
        y_min = points[i].pos.y;

    }

    wait++;

    x_max += llabs(x_min);
    y_max += llabs(y_min);

    if (x_max <= TMULT * TCOLS && y_max <= TMULT * TLINES)
      break;
  }

  // 27 (- 1) from part 1
  printf("Seconds the elves would have needed to wait: %d\n", wait + 26);

  return 0;
}
