/**
 * --- Day 17: Conway Cubes ---
 *
 * As your flight slowly drifts through the sky, the Elves at the Mythical
 * Information Bureau at the North Pole contact you. They'd like some help
 * debugging a malfunctioning experimental energy source aboard one of their
 * super-secret imaging satellites.
 *
 * The experimental energy source is based on cutting-edge technology: a set of
 * Conway Cubes contained in a pocket dimension! When you hear it's having
 * problems, you can't help but agree to take a look.
 *
 * The pocket dimension contains an infinite 3-dimensional grid. At every
 * integer 3-dimensional coordinate (x,y,z), there exists a single cube which is
 * either active or inactive.
 *
 * In the initial state of the pocket dimension, almost all cubes start
 * inactive. The only exception to this is a small flat region of cubes (your
 * puzzle input); the cubes in this region start in the specified active (#) or
 * inactive (.) state.
 *
 * The energy source then proceeds to boot up by executing six cycles.
 *
 * Each cube only ever considers its neighbors: any of the 26 other cubes where
 * any of their coordinates differ by at most 1. For example, given the cube at
 * x=1,y=2,z=3, its neighbors include the cube at x=2,y=2,z=2, the cube at
 * x=0,y=2,z=3, and so on.
 *
 * During a cycle, all cubes simultaneously change their state according to the
 * following rules:
 *
 * - If a cube is active and exactly 2 or 3 of its neighbors are also active,
 *   the cube remains active. Otherwise, the cube becomes inactive.
 * - If a cube is inactive but exactly 3 of its neighbors are active, the cube
 *   becomes active. Otherwise, the cube remains inactive.
 *
 * The engineers responsible for this experimental energy source would like you
 * to simulate the pocket dimension and determine what the configuration of
 * cubes should be at the end of the six-cycle boot process.
 *
 * For example, consider the following initial state:
 *
 * .#.
 * ..#
 * ###
 *
 * Even though the pocket dimension is 3-dimensional, this initial state
 * represents a small 2-dimensional slice of it. (In particular, this initial
 * state defines a 3x3x1 region of the 3-dimensional space.)
 *
 * Simulating a few cycles from this initial state produces the following
 * configurations, where the result of each cycle is shown layer-by-layer at
 * each given z coordinate (and the frame of view follows the active cells in
 * each cycle):
 *
 * Before any cycles:
 *
 * z=0
 * .#.
 * ..#
 * ###
 *
 *
 * After 1 cycle:
 *
 * z=-1
 * #..
 * ..#
 * .#.
 *
 * z=0
 * #.#
 * .##
 * .#.
 *
 * z=1
 * #..
 * ..#
 * .#.
 *
 *
 * After 2 cycles:
 *
 * z=-2
 * .....
 * .....
 * ..#..
 * .....
 * .....
 *
 * z=-1
 * ..#..
 * .#..#
 * ....#
 * .#...
 * .....
 *
 * z=0
 * ##...
 * ##...
 * #....
 * ....#
 * .###.
 *
 * z=1
 * ..#..
 * .#..#
 * ....#
 * .#...
 * .....
 *
 * z=2
 * .....
 * .....
 * ..#..
 * .....
 * .....
 *
 *
 * After 3 cycles:
 *
 * z=-2
 * .......
 * .......
 * ..##...
 * ..###..
 * .......
 * .......
 * .......
 *
 * z=-1
 * ..#....
 * ...#...
 * #......
 * .....##
 * .#...#.
 * ..#.#..
 * ...#...
 *
 * z=0
 * ...#...
 * .......
 * #......
 * .......
 * .....##
 * .##.#..
 * ...#...
 *
 * z=1
 * ..#....
 * ...#...
 * #......
 * .....##
 * .#...#.
 * ..#.#..
 * ...#...
 *
 * z=2
 * .......
 * .......
 * ..##...
 * ..###..
 * .......
 * .......
 * .......
 *
 * After the full six-cycle boot process completes, 112 cubes are left in the
 * active state.
 *
 * Starting with your given initial configuration, simulate six cycles. How many
 * cubes are left in the active state after the sixth cycle?
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define GDIM 30
#define INPUT_DIM 8

typedef struct {
  int xmin;
  int ymin;
  int zmin;
  int xmax;
  int ymax;
  int zmax;

  char current_grid[GDIM][GDIM][GDIM];
  char next_grid[GDIM][GDIM][GDIM];
} dimension_t;

/* // Sample */
/* char *input[] = { */
/*   ".#.", */
/*   "..#", */
/*   "###" */
/* }; */

char *input[] = {
	"...#..#.",
	".....##.",
	"##..##.#",
	"#.#.##..",
	"#..#.###",
	"...##.#.",
	"#..##..#",
	".#.#..#."
};

int active_neigbors(dimension_t d, int x, int y, int z) {
  int count = 0;

  for (int i = x - 1; i <= x + 1; i++) {
    for (int j = y - 1; j <= y + 1; j++) {
      for (int k = z - 1; k <= z + 1; k++) {
        if (i == x && j == y && k == z) continue;

        if (d.current_grid[i][j][k] == '#') {
          count++;
        }
      }
    }
  }

  return count;
}


int active_count(dimension_t d) {
  int count = 0;

  for (int x = d.xmin  - 1; x <= d.xmax + 1; x++) {
    for (int y = d.xmin  - 1; y <= d.ymax + 1; y++) {
      for (int z = d.zmin  - 1; z <= d.zmax + 1; z++) {
        if (d.current_grid[x][y][z] == '#') {
          count++;
        }
      }
    }
  }

  return count;
}

void print_anc(dimension_t d, int z) {
  printf("z=%d\n", z);
  for (int y = d.ymin; y < d.ymax; y++) {
    for (int x = d.xmin; x < d.xmax; x++) {
      if (x > d.xmin) {
        printf(",");
      }
      printf("%d", active_neigbors(d, x, y, z));
    }
    printf("\n");
  }
  printf("\n");
}

void copy(dimension_t *d) {
  for (int x = d->xmin  - 1; x <= d->xmax + 1; x++) {
    for (int y = d->xmin  - 1; y <= d->ymax + 1; y++) {
      for (int z = d->zmin  - 1; z <= d->zmax + 1; z++) {
        d->current_grid[x][y][z] = d->next_grid[x][y][z];
      }
    }
  }
}

void reset_next(dimension_t *d) {
  for (int x = d->xmin  - 1; x <= d->xmax + 1; x++) {
    for (int y = d->xmin  - 1; y <= d->ymax + 1; y++) {
      for (int z = d->zmin  - 1; z <= d->zmax + 1; z++) {
        d->next_grid[x][y][z] = '.';
      }
    }
  }
}

void reset_current(dimension_t *d) {
  for (int x = d->xmin  - 1; x <= d->xmax + 1; x++) {
    for (int y = d->xmin  - 1; y <= d->ymax + 1; y++) {
      for (int z = d->zmin  - 1; z <= d->zmax + 1; z++) {
        d->current_grid[x][y][z] = '.';
      }
    }
  }
}

void print(dimension_t d) {
  printf("xmin: %d, ymin: %d, zmin: %d, ", d.xmin, d.ymin, d.zmin);
  printf("xmax: %d, ymax: %d, zmax: %d\n", d.xmax, d.ymax, d.zmax);

  for (int z = d.zmin - 1; z <= d.zmax + 1; z++) {
    printf("z=%d%*c", z - d.zmin - 1, d.xmax - d.xmin + 1, ' ');
  }
  printf(" \n");

  for (int y = d.ymin - 1; y <= d.ymax + 1; y++) {
    for (int z = d.zmin - 1; z <= d.zmax + 1; z++) {
      for (int x = d.xmin - 1; x <= d.xmax + 1; x++) {
        printf("%c", d.current_grid[x][y][z]);
      }
      printf(" ");
    }
    printf("\n");
  }
  printf("\n");
}

void update_bounding_box(dimension_t *d) {
  for (int x = d->xmin - 1; x <= d->xmax + 1; x++) {
    for (int y = d->xmin - 1; y <= d->ymax + 1; y++) {
      for (int z = d->zmin - 1; z <= d->zmax + 1; z++) {
        if (d->current_grid[x][y][z] == '#') {
          if (x < d->xmin) d->xmin = x;
          if (x > d->xmax) d->xmax = x;
          if (y < d->ymin) d->ymin = y;
          if (y > d->ymax) d->ymax = y;
          if (z < d->zmin) d->zmin = z;
          if (z > d->zmax) d->zmax = z;
        }
      }
    }
  }
}

int main(int argc, char *argv[]) {
  int x, y, z, i, an;
  dimension_t dim;

  dim.xmin = dim.ymin = dim.zmin = GDIM / 2;
  dim.xmax = dim.ymax = GDIM / 2 + INPUT_DIM;
  dim.zmax = GDIM / 2 + 1;

  reset_current(&dim);
  reset_next(&dim);

  // Seed
  for (x = dim.xmin; x < dim.xmax; x++) {
    for (y = dim.ymin; y < dim.ymax; y++) {
      dim.current_grid[x][y][dim.zmin] = input[y - dim.ymin][x - dim.xmin];
    }
  }

  /* printf("Before any cycles:\n\n"); */
  /* print(dim); */

  for (i = 1; i <= 6; i++) {
    update_bounding_box(&dim);

    for (x = dim.xmin - 1; x <= dim.xmax + 1; x++) {
      for (y = dim.ymin - 1; y <= dim.ymax + 1; y++) {
        for (z = dim.zmin - 1; z <= dim.zmax + 1; z++) {
          an = active_neigbors(dim, x, y, z);

          if (dim.current_grid[x][y][z] == '#') {
            if (an == 2 || an == 3) {
              dim.next_grid[x][y][z] = '#';
            } else {
              dim.next_grid[x][y][z] = '.';
            }
          } else {
            if (an == 3) {
              dim.next_grid[x][y][z] = '#';
            } else {
              dim.next_grid[x][y][z] = '.';
            }
          }
        }
      }
    }

    update_bounding_box(&dim);

    copy(&dim);
    reset_next(&dim);

    /* printf("After cycle %d:\n\n", i); */
    /* print(dim); */
  }

  printf("Active count after six cycles: %d\n", active_count(dim));

  return 0;
}
