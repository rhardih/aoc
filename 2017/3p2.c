/**
 * --- Day 3: Spiral Memory ---
 *
 * You come across an experimental new kind of memory stored on an infinite
 * two-dimensional grid.
 *
 * Each square on the grid is allocated in a spiral pattern starting at a
 * location marked 1 and then counting up while spiraling outward. For example,
 * the first few squares are allocated like this:
 *
 * 17  16  15  14  13
 * 18   5   4   3  12
 * 19   6   1   2  11
 * 20   7   8   9  10
 * 21  22  23---> ...
 *
 * While this is very space-efficient (no squares are skipped), requested data
 * must be carried back to square 1 (the location of the only access port for
 * this memory system) by programs that can only move up, down, left, or right.
 * They always take the shortest path: the Manhattan Distance between the
 * location of the data and square 1.
 *
 * For example:
 *
 * - Data from square 1 is carried 0 steps, since it's at the access port.
 * - Data from square 12 is carried 3 steps, such as: down, left, left.
 * - Data from square 23 is carried only 2 steps: up twice.
 * - Data from square 1024 must be carried 31 steps.
 *
 * How many steps are required to carry the data from the square identified in
 * your puzzle input all the way to the access port?
 *
 * --- Part Two ---
 *
 * As a stress test on the system, the programs here clear the grid and then
 * store the value 1 in square 1. Then, in the same allocation order as shown
 * above, they store the sum of the values in all adjacent squares, including
 * diagonals.
 *
 * So, the first few squares' values are chosen as follows:
 *
 * - Square 1 starts with the value 1.
 * - Square 2 has only one adjacent filled square (with value 1), so it also
 *   stores 1.
 * - Square 3 has both of the above squares as neighbors and stores the sum of
 *   their values, 2.
 * - Square 4 has all three of the aforementioned squares as neighbors and
 *   stores the sum of their values, 4.
 * - Square 5 only has the first and fourth squares as neighbors, so it gets the
 *   value 5.
 *
 * Once a square is written, its value does not change. Therefore, the first few
 * squares would receive the following values:
 *
 * 147  142  133  122   59
 * 304    5    4    2   57
 * 330   10    1    1   54
 * 351   11   23   25   26
 * 362  747  806--->   ...
 *
 * What is the first value written that is larger than your puzzle input?
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

static const double input = 312051;

int main(int argc, char const *argv[])
{
  // The smallest possible square grid which can hold 312051 locations
  int grid_side_length = ceil(sqrt(input));
  int grid_size = grid_side_length * grid_side_length;
  int *grid = calloc(grid_size, sizeof(int));
  int val = 0;
  int step = grid_side_length;
  int layer_side_length = 3;
  int n, nw, w, sw, s, se, e, ne;
  int x, y, i, j;

  x = y = ceil((double)grid_side_length / 2.0);

  // row major
  grid[y * step + x] = 1;

  while (val < (int)input)
  {
    // start of new layer, step right one
    x++;

    // Fill right side
    i = y;
    while(i >= y - (layer_side_length - 2))
    {
      nw = grid[(i - 1) * step + (x - 1)];
      w = grid[i * step + (x - 1)];
      sw = grid[(i + 1) * step + (x - 1)];
      s = grid[(i + 1) * step + x];

      grid[i * step + x] = nw + w + sw + s;

      if (grid[i * step + x] > (int)input)
      {
        val = grid[i * step + x];
        goto done;
      }

      i--;
    }

    y = i + 1;

    // Fill top
    x--;
    i = x;
    // 2 offset instead of 1, because we're already one step left
    while (i >= x - (layer_side_length - 2))
    {
      sw = grid[(y + 1) * step + (i - 1)];
      s = grid[(y + 1) * step + i];
      se = grid[(y + 1) * step + (i + 1)];
      e = grid[y * step + (i + 1)];

      grid[y * step + i] = sw + s + se + e;

      if (grid[y * step + i] > (int)input)
      {
        val = grid[y * step + i];
        goto done;
      }

      i--;
    }

    x = i + 1;

    // Fill left side
    y++;
    i = y;
    while(i <= y + (layer_side_length - 2))
    {
      n = grid[(i - 1) * step + x];
      ne = grid[(i - 1) * step + (x + 1)];
      e = grid[i * step + (x + 1)];
      se = grid[(i + 1) * step + (x + 1)];

      grid[i * step + x] = n + ne + e + se;

      if (grid[i * step + x] > (int)input)
      {
        val = grid[i * step + x];
        goto done;
      }

      i++;
    }

    y = i - 1;

    // Fill bottom
    x++;
    i = x;
    while (i <= x + (layer_side_length - 2))
    {
      w = grid[y * step + (i - 1)];
      nw = grid[(y - 1) * step + (i - 1)];
      n = grid[(y - 1) * step + i];
      ne = grid[(y - 1) * step + (i + 1)];

      grid[y * step + i] = w + nw + n + ne;

      if (grid[y * step + i] > (int)input)
      {
        val = grid[y * step + i];
        goto done;
      }

      i++;
    }

    x = i - 1;

    layer_side_length += 2;
  }

done:

  free(grid);

  printf("First value larger than input: %d\n", val);

  return 0;
}
