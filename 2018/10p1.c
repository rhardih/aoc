/**
 * --- Day 10: The Stars Align ---
 *
 * It's no use; your navigation system simply isn't capable of providing walking
 * directions in the arctic circle, and certainly not in 1018.
 * 
 * The Elves suggest an alternative. In times like these, North Pole rescue
 * operations will arrange points of light in the sky to guide missing Elves
 * back to base. Unfortunately, the message is easy to miss: the points move
 * slowly enough that it takes hours to align them, but have so much momentum
 * that they only stay aligned for a second. If you blink at the wrong time, it
 * might be hours before another message appears.
 * 
 * You can see these points of light floating in the distance, and record their
 * position in the sky and their velocity, the relative change in position per
 * second (your puzzle input). The coordinates are all given from your
 * perspective; given enough time, those positions and velocities will move the
 * points into a cohesive message!
 * 
 * Rather than wait, you decide to fast-forward the process and calculate what
 * the points will eventually spell.
 * 
 * For example, suppose you note the following points:
 * 
 * position=< 9,  1> velocity=< 0,  2>
 * position=< 7,  0> velocity=<-1,  0>
 * position=< 3, -2> velocity=<-1,  1>
 * position=< 6, 10> velocity=<-2, -1>
 * position=< 2, -4> velocity=< 2,  2>
 * position=<-6, 10> velocity=< 2, -2>
 * position=< 1,  8> velocity=< 1, -1>
 * position=< 1,  7> velocity=< 1,  0>
 * position=<-3, 11> velocity=< 1, -2>
 * position=< 7,  6> velocity=<-1, -1>
 * position=<-2,  3> velocity=< 1,  0>
 * position=<-4,  3> velocity=< 2,  0>
 * position=<10, -3> velocity=<-1,  1>
 * position=< 5, 11> velocity=< 1, -2>
 * position=< 4,  7> velocity=< 0, -1>
 * position=< 8, -2> velocity=< 0,  1>
 * position=<15,  0> velocity=<-2,  0>
 * position=< 1,  6> velocity=< 1,  0>
 * position=< 8,  9> velocity=< 0, -1>
 * position=< 3,  3> velocity=<-1,  1>
 * position=< 0,  5> velocity=< 0, -1>
 * position=<-2,  2> velocity=< 2,  0>
 * position=< 5, -2> velocity=< 1,  2>
 * position=< 1,  4> velocity=< 2,  1>
 * position=<-2,  7> velocity=< 2, -2>
 * position=< 3,  6> velocity=<-1, -1>
 * position=< 5,  0> velocity=< 1,  0>
 * position=<-6,  0> velocity=< 2,  0>
 * position=< 5,  9> velocity=< 1, -2>
 * position=<14,  7> velocity=<-2,  0>
 * position=<-3,  6> velocity=< 2, -1>
 *
 * Each line represents one point. Positions are given as <X, Y> pairs: X
 * represents how far left (negative) or right (positive) the point appears,
 * while Y represents how far up (negative) or down (positive) the point
 * appears.
 * 
 * At 0 seconds, each point has the position given. Each second, each point's
 * velocity is added to its position. So, a point with velocity <1, -2> is
 * moving to the right, but is moving upward twice as quickly. If this point's
 * initial position were <3, 9>, after 3 seconds, its position would become <6,
 * 3>.
 * 
 * Over time, the points listed above would move like this:
 * 
 * Initially:
 * ........#.............
 * ................#.....
 * .........#.#..#.......
 * ......................
 * #..........#.#.......#
 * ...............#......
 * ....#.................
 * ..#.#....#............
* .......#..............
* ......#...............
* ...#...#.#...#........
* ....#..#..#.........#.
* .......#..............
* ...........#..#.......
* #...........#.........
* ...#.......#..........
* 
* After 1 second:
* ......................
* ......................
* ..........#....#......
* ........#.....#.......
* ..#.........#......#..
* ......................
* ......#...............
* ....##.........#......
* ......#.#.............
* .....##.##..#.........
* ........#.#...........
* ........#...#.....#...
* ..#...........#.......
* ....#.....#.#.........
* ......................
* ......................
* 
* After 2 seconds:
* ......................
* ......................
* ......................
* ..............#.......
* ....#..#...####..#....
* ......................
* ........#....#........
* ......#.#.............
* .......#...#..........
* .......#..#..#.#......
* ....#....#.#..........
* .....#...#...##.#.....
* ........#.............
* ......................
* ......................
* ......................
* 
* After 3 seconds:
* ......................
* ......................
* ......................
* ......................
* ......#...#..###......
* ......#...#...#.......
* ......#...#...#.......
* ......#####...#.......
* ......#...#...#.......
* ......#...#...#.......
* ......#...#...#.......
* ......#...#..###......
* ......................
* ......................
* ......................
* ......................
* 
* After 4 seconds:
* ......................
* ......................
* ......................
* ............#.........
* ........##...#.#......
* ......#.....#..#......
* .....#..##.##.#.......
* .......##.#....#......
* ...........#....#.....
* ..............#.......
* ....#......#...#......
* .....#.....##.........
* ...............#......
* ...............#......
* ......................
* ......................
*
* After 3 seconds, the message appeared briefly: HI. Of course, your message
* will be much longer and will take many more seconds to appear.
* 
* What message will eventually appear in the sky?
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

    x_max += llabs(x_min);
    y_max += llabs(y_min);

    if (x_max <= TMULT * TCOLS && y_max <= TMULT * TLINES)
      break;
  }

  // Transform points into positive space for easier printing
  for (i = 0; i < INPUT_SIZE; i++) {
    points[i].pos.x += llabs(x_min);
    points[i].pos.y += llabs(y_min);
  }

  x_max++;
  y_max++;

  char grid[y_max][x_max];
  int tmp = 0;

  while (tmp < 27) {
    for (j = 0; j < y_max; j++) {
      for (k = 0; k < x_max; k++) {
        grid[j][k] = '.';
      }
    }

    for (l = 0; l < INPUT_SIZE; l++) {
      p = points[l];

      grid[p.pos.y][p.pos.x] = '#';
    }

    for (j = 0; j < y_max; j++) {
      for (k = 0; k < x_max; k++) {
        printf("%c", grid[j][k]);
      }
      printf("\n");
    }
    printf("\n\n");


    for (l = 0; l < INPUT_SIZE; l++) {
      points[l].pos.x += points[l].vel.x;
      points[l].pos.y += points[l].vel.y;
    }

    // TODO: Terminate by tracking size of area and breaking when minimized,
    // instead of terminating by ctrl-c
    tmp++;
  }

  return 0;
}
