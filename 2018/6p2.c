/**
 * --- Day 6: Chronal Coordinates ---
 *
 * --- Part Two ---
 *
 * On the other hand, if the coordinates are safe, maybe the best you can do is
 * try to find a region near as many coordinates as possible.
 * 
 * For example, suppose you want the sum of the Manhattan distance to all of the
 * coordinates to be less than 32. For each location, add up the distances to
 * all of the given coordinates; if the total of those distances is less than
 * 32, that location is within the desired region. Using the same coordinates as
 * above, the resulting region looks like this:
 * 
 * ..........
 * .A........
 * ..........
 * ...###..C.
 * ..#D###...
 * ..###E#...
 * .B.###....
 * ..........
 * ..........
 * ........F.
 *
 * In particular, consider the highlighted location 4,3 located at the top
 * middle of the region. Its calculation is as follows, where abs() is the
 * absolute value function:
 * 
 * - Distance to coordinate A: abs(4-1) + abs(3-1) =  5
 * - Distance to coordinate B: abs(4-1) + abs(3-6) =  6
 * - Distance to coordinate C: abs(4-8) + abs(3-3) =  4
 * - Distance to coordinate D: abs(4-3) + abs(3-4) =  2
 * - Distance to coordinate E: abs(4-5) + abs(3-5) =  3
 * - Distance to coordinate F: abs(4-8) + abs(3-9) = 10
 * - Total distance: 5 + 6 + 4 + 2 + 3 + 10 = 30
 *
 * Because the total distance to all coordinates (30) is less than 32, the
 * location is within the region.
 * 
 * This region, which also includes coordinates D and E, has a total size of 16.
 * 
 * Your actual region will need to be much larger than this example, though,
 * instead including all locations with a total distance of less than 10000.
 * 
 * What is the size of the region containing all locations which have a total
 * distance to all given coordinates of less than 10000?
 */

#include <stdio.h>
#include <stdlib.h>

//$ wc -l 6.in
//        50 6.in
#define INPUT_SIZE 50

typedef struct point {
  int x, y;
} point_t;

int mdist(point_t p, point_t q) {
  return abs(p.x - q.x) + abs(p.y - q.y);
}

int main(int argc, char const *argv[]) {
  int x, y;

  point_t points[INPUT_SIZE], p, q;
  int i = 0, j, k, max = 0, sum, area = 0;

  while(scanf("%d, %d", &points[i].x, &points[i].y) != EOF) {
    if (points[i].x > max)
      max = points[i].x;
    if (points[i].y > max)
      max = points[i].y;

    i++;
  }

  for (i = 0; i < max; i++) {
    for (j = 0; j < max; j++) {
      sum = 0;

      for (k = 0; k < INPUT_SIZE; k++) {
        p = points[k];
        q.x = j;
        q.y = i;
        sum += mdist(p, q);
      }

      if (sum > 0 && sum < 10000)
        area++;
    }
  }

  printf("Size of the region containing all locations which have a total distance to all given coordinates of less than 10000: %d\n", area);

  return 0;
}
