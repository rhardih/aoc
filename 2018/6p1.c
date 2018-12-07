/**
 * --- Day 6: Chronal Coordinates ---
 *
 * The device on your wrist beeps several times, and once again you feel like you're falling.
 * 
 * "Situation critical," the device announces. "Destination indeterminate.
 * Chronal interference detected. Please specify new target coordinates."
 * 
 * The device then produces a list of coordinates (your puzzle input). Are they
 * places it thinks are safe or dangerous? It recommends you check manual page
 * 729. The Elves did not give you a manual.
 * 
 * If they're dangerous, maybe you can minimize the danger by finding the
 * coordinate that gives the largest distance from the other points.
 * 
 * Using only the Manhattan distance, determine the area around each coordinate
 * by counting the number of integer X,Y locations that are closest to that
 * coordinate (and aren't tied in distance to any other coordinate).
 * 
 * Your goal is to find the size of the largest area that isn't infinite. For
 * example, consider the following list of coordinates:
 * 
 * 1, 1
 * 1, 6
 * 8, 3
 * 3, 4
 * 5, 5
 * 8, 9
 *
 * If we name these coordinates A through F, we can draw them on a grid, putting
 * 0,0 at the top left:
 * 
 * ..........
 * .A........
 * ..........
 * ........C.
 * ...D......
 * .....E....
 * .B........
 * ..........
 * ..........
 * ........F.
 *
 * This view is partial - the actual grid extends infinitely in all directions.
 * Using the Manhattan distance, each location's closest coordinate can be
 * determined, shown here in lowercase:
 * 
 * aaaaa.cccc
 * aAaaa.cccc
 * aaaddecccc
 * aadddeccCc
 * ..dDdeeccc
 * bb.deEeecc
 * bBb.eeee..
 * bbb.eeefff
 * bbb.eeffff
 * bbb.ffffFf
 *
 * Locations shown as . are equally far from two or more coordinates, and so
 * they don't count as being closest to any.
 * 
 * In this example, the areas of coordinates A, B, C, and F are infinite - while
 * not shown here, their areas extend forever outside the visible grid. However,
 * the areas of coordinates D and E are finite: D is closest to 9 locations, and
 * E is closest to 17 (both including the coordinate's location itself).
 * Therefore, in this example, the size of the largest area is 17.
 * 
 * What is the size of the largest area that isn't infinite?
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//$ wc -l 6.in
//        50 6.in
#define INPUT_SIZE 50

typedef struct point {
  int x, y;
  int interior;
} point_t;

int mdist(point_t p, point_t q) {
  return abs(p.x - q.x) + abs(p.y - q.y);
}

int main(int argc, char const *argv[]) {
  int x, y;

  point_t points[INPUT_SIZE], p, q;
  int i = 0, j, k, l, max = 0, min, tmp;

  while(scanf("%d, %d", &points[i].x, &points[i].y) != EOF) {
    if (points[i].x > max)
      max = points[i].x;
    if (points[i].y > max)
      max = points[i].y;

    i++;
  }

  int infinite[INPUT_SIZE] = { 0 };

  // For every position at the edge of the grid, find the nearest point and mark
  // it as an infinite region
  for (i = 0; i < max + 1; i++) {
    for (j = 0; j < max + 1; j++) {
      if (i > 0 && i < max &&
          j > 0 && j < max)
        continue;

      min = INT_MAX;

      for (k = 0; k < INPUT_SIZE; k++) {
        p = points[k];
        q.x = j;
        q.y = i;
        tmp = mdist(p, q);

        if (tmp < min) {
          min = tmp;
          l = k;
        }
      }

      infinite[l] = 1;
    }
  }

  int areas[INPUT_SIZE] = { 0 };

  for (i = 0; i < max + 1; i++) {
    for (j = 0; j < max + 1; j++) {
      min = INT_MAX;

      // For each position, we want to find the two closest points and if one is
      // closer than the other, account position in the area of the region
      // belonging to the closest point.
      for (k = 0; k < INPUT_SIZE; k++) {
        p = points[k];
        q.x = j;
        q.y = i;
        tmp = mdist(p, q);

        if (tmp < min) {
          min = tmp;
          l = k;
        }
      }

      // See if another point is same minimum distance from point
      for (k = 0; k < INPUT_SIZE; k++) {
        if (k == l) continue;

        p = points[k];
        q.x = j;
        q.y = i;
        tmp = mdist(p, q);

        if (tmp == min) {
          min = -1;
          break;
        }
      }

      if (min >= 0) {
        areas[l]++;
      }
    }
  }

  max = 0;

  for (i = 0; i < INPUT_SIZE; i++) {
    if (!infinite[i] && areas[i] > max) {
      max = areas[i];
      j = i;
    }
  }

  printf("Size of the largest area that isn't infinite (%c): %d\n", j + 'A', max);

  return 0;
}
