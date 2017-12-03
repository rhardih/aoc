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
 */

#include <stdio.h>
#include <math.h>

static const double input = 312051;

int main(int argc, char const *argv[])
{
  // The smallest possible square grid which can hold 312051 locations
  int grid_side_length = ceil(sqrt(input));
  int grid_size = grid_side_length * grid_side_length;
  int center = ceil((double)grid_side_length / 2.0);
  int x = grid_side_length - (grid_size - input);
  int dx = center - x;
  int dy = floor((double)grid_side_length / 2.0);

  printf("Steps required: %d\n", dy + dx);

  return 0;
}
