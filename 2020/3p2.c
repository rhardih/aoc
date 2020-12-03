/**
 * --- Part Two ---
 *
 * Time to check the rest of the slopes - you need to minimize the probability
 * of a sudden arboreal stop, after all.
 * 
 * Determine the number of trees you would encounter if, for each of the
 * following slopes, you start at the top-left corner and traverse the map all
 * the way to the bottom:
 * 
 * Right 1, down 1.
 * Right 3, down 1. (This is the slope you already checked.)
 * Right 5, down 1.
 * Right 7, down 1.
 * Right 1, down 2.
 *
 * In the above example, these slopes would find 2, 7, 3, 4, and 2 tree(s)
 * respectively; multiplied together, these produce the answer 336.
 * 
 * What do you get if you multiply together the number of trees encountered on
 * each of the listed slopes?
 */

#include <stdio.h>

typedef struct {
  int x;
  int y;
  long tree_count;
} slope_t;

#define W 31
#define H 323

int main(int argc, char **argv) {
  int tree_count = 0, i, x, y = 0;
  long product = 1;
  char map[H][W];

  slope_t slopes[] = {
    { 1, 1, 0 },
    { 3, 1, 0 },
    { 5, 1, 0 },
    { 7, 1, 0 },
    { 1, 2, 0 }
  };

  while(scanf("%31s\n", map[y++]) != EOF);

  for (i = 0; i < 5; i++) {
    for (x = 0, y = 0;
        x < W && y < H;
        x = (x + slopes[i].x) % W, y += slopes[i].y) {
      if (map[y][x] == '#') {
        slopes[i].tree_count++;
      }
    }

    product *= slopes[i].tree_count;
  }

  printf("Trees encountered: %ld\n", product);

  return 0;
}
