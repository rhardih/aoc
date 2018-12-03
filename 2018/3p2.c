/**
 * --- Day 3: No Matter How You Slice It ---
 *
 * --- Part Two ---
 *
 * Amidst the chaos, you notice that exactly one claim doesn't overlap by even a
 * single square inch of fabric with any other claim. If you can somehow draw
 * attention to it, maybe the Elves will be able to make Santa's suit after all!
 * 
 * For example, in the claims above, only claim 3 is intact after all claims are
 * made.
 * 
 * What is the ID of the only claim that doesn't overlap?
 */

#include <stdio.h>

// $ gwc -l 3.in
// 1301 3.in
#define INPUT_LEN 1301

int main(int argc, char const *argv[]) {
  int result = 0;
  int id, x, y, w, h;
  static int fabric[1000][1000];
  static int overlap[INPUT_LEN];
  int i, j;

  while(scanf("#%d @ %d,%d: %dx%d\n", &id, &x, &y, &w, &h) != EOF) {
    for (i = x; i < x + w; i++) {
      for (j = y; j < y + h; j++) {
        if (fabric[i][j]) {
          overlap[id - 1] = 1;
          overlap[fabric[i][j] - 1] = 1;
        } else {
          fabric[i][j] = id;
        }
      }
    }
  }

  for (i = 0; i < INPUT_LEN; i++) {
    if(!overlap[i]) {
      result = i + 1;
      break;
    }
  }

  printf("ID of the only claim that doesn't overlap: %d\n", result);

  return 0;
}

