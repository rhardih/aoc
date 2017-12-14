/**
 * --- Day 14: Disk Defragmentation ---
 * 
 * Suddenly, a scheduled job activates the system's disk defragmenter. Were the
 * situation different, you might sit and watch it for a while, but today, you
 * just don't have that kind of time. It's soaking up valuable system resources
 * that are needed elsewhere, and so the only option is to help it finish its
 * task as soon as possible.
 * 
 * The disk in question consists of a GDxGD grid; each square of the grid is
 * either free or used. On this disk, the state of the grid is tracked by the
 * bits in a sequence of knot hashes.
 * 
 * A total of GD knot hashes are calculated, each corresponding to a single row
 * in the grid; each hash contains GD bits which correspond to individual grid
 * squares. Each bit of a hash indicates whether that square is free (0) or used
 * (1).
 * 
 * The hash inputs are a key string (your puzzle input), a dash, and a number
 * from 0 to GD - 1 corresponding to the row. For example, if your key string were
 * flqrgnkx, then the first row would be given by the bits of the knot hash of
 * flqrgnkx-0, the second row from the bits of the knot hash of flqrgnkx-1, and
 * so on until the last row, flqrgnkx-GD - 1.
 * 
 * The output of a knot hash is traditionally represented by 32 hexadecimal
 * digits; each of these digits correspond to 4 bits, for a total of 4 * 32 =
 * GD bits. To convert to bits, turn each hexadecimal digit to its equivalent
 * binary value, high-bit first: 0 becomes 0000, 1 becomes 0001, e becomes 1110,
 * f becomes 1111, and so on; a hash that begins with a0c2017... in hexadecimal
 * would begin with 10100000110000100000000101110000... in binary.
 * 
 * Continuing this process, the first 8 rows and columns for key flqrgnkx appear
 * as follows, using # to denote used squares, and . to denote free ones:
 * 
 * ##.#.#..-->
 * .#.#.#.#   
 * ....#.#.   
 * #.#.##.#   
 * .##.#...   
 * ##..#..#   
 * .#...#..   
 * ##.#.##.-->
 * |      |   
 * V      V   
 *
 * In this example, 8108 squares are used across the entire GDxGD grid.
 * 
 * Given your actual key string, how many squares are used?
 *
 * --- Part Two ---
 * 
 * Now, all the defragmenter needs to know is the number of regions. A region is
 * a group of used squares that are all adjacent, not including diagonals. Every
 * used square is in exactly one region: lone used squares form their own
 * isolated regions, while several adjacent squares all count as a single
 * region.
 * 
 * In the example above, the following nine regions are visible, each marked
 * with a distinct digit:
 * 
 * 11.2.3..-->
 * .1.2.3.4   
 * ....5.6.   
 * 7.8.55.9   
 * .88.5...   
 * 88..5..8   
 * .8...8..   
 * 88.8.88.-->
 * |      |   
 * V      V   
 *
 * Of particular interest is the region marked 8; while it does not appear
 * contiguous in this small view, all of the squares marked 8 are connected when
 * considering the whole GDxGD grid. In total, in this example, 1242 regions
 * are present.
 * 
 * How many regions are present given your key string?
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "knot.h"

// Grid dimensions
#define GD 128

static char input[] = "ffayrhll";

static int grid[GD][GD];

void flood(int y, int x, int label)
{
  if (grid[y][x] != 0)
    return;

  if (x < 0 || y < 0 || x > GD - 1 || y > GD - 1)
    return;

  grid[y][x] = label;

  flood(y - 1, x, label);
  flood(y + 1, x, label);
  flood(y, x - 1, label);
  flood(y, x + 1, label);
}

int main(int argc, char const *argv[])
{

  char tmp[13], *kh, letter;
  int regions = 1, i, j, l, m;
  unsigned int k;

  for (i = 0; i < GD; ++i)
  {
    sprintf(tmp, "%s-%d", input, i);
    kh = knot_hash(tmp);

    for (j = 0, m = 0; j < 32; ++j, m += 4)
    {
      sscanf(kh + j, "%01x", &k);

      for (l = 0; l < 4; ++l)
      {
        if (((k << l) & 8) == 8)
          grid[i][l + m] = 0;
        else
          grid[i][l + m] = -1;
      }
    }

    free(kh);
  }

  for (i = 0; i < GD; ++i)
  {
    for (j = 0; j < GD; ++j)
    {
      if (grid[i][j] != 0)
        continue;

      flood(i, j, regions++);
    }
  }

  printf("Regions present: %d\n", regions - 1);
  return 0;
}
