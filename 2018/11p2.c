/**
 * --- Day 11: Chronal Charge ---
 *
 * --- Part Two ---
 *
 * You discover a dial on the side of the device; it seems to let you select a
 * square of any size, not just 3x3. Sizes from 1x1 to 300x300 are supported.
 * 
 * Realizing this, you now must find the square of any size with the largest
 * total power. Identify this square by including its size as a third parameter
 * after the top-left coordinate: a 9x9 square with a top-left corner of 3,5 is
 * identified as 3,5,9.
 * 
 * For example:
 * 
 * - For grid serial number 18, the largest total square (with a total power of
 *   113) is 16x16 and has a top-left corner of 90,269, so its identifier is
 *   90,269,16.
 * - For grid serial number 42, the largest total square (with a total power of
 *   119) is 12x12 and has a top-left corner of 232,251, so its identifier is
 *   232,251,12.
 *
 * What is the X,Y,size identifier of the square with the largest total power?
 */

#include <stdio.h>

#if 0
#define GSN 42
#else
#define GSN 5235
#endif

long long total_power(long long grid[300][300], long long x, long long y, long long size) {
  long long sum = 0, i, j;

  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      sum += grid[y + i][x + j];
    }
  }

  return sum;
}

int main(int argc, char const *argv[]) {
  long long grid[300][300];
  long long x, y, z, rack_id, plevel;
  long long tmp, ltp = 0, ltpx, ltpy, ltpsize;

  for (y = 1; y <= 300; y++) {
    for (x = 1; x <= 300; x++) {
      rack_id = x + 10;
      plevel = rack_id * y;
      plevel += GSN;
      plevel *= rack_id;
      plevel = (plevel / 100) % 10;
      plevel -= 5;

      grid[y - 1][x - 1] = plevel;
    }
  }

  for (y = 1; y <= 300; y++) {
    for (x = 1; x <= 300; x++) {
      for (z = 1; z <= 300 - x && z <= 300 - y; z++) {
        tmp = total_power(grid, x - 1, y - 1, z);

        if (tmp > ltp) {
          ltpx = x;
          ltpy = y;
          ltpsize = z;
          ltp = tmp;
        }
      }
    }
  }

  printf("%lld,%lld,%lld: %lld\n", ltpx, ltpy, ltpsize, ltp);

  return 0;
}
