/**
 * --- Part Two ---
 *
 * For some reason, your simulated results don't match what the experimental
 * energy source engineers expected. Apparently, the pocket dimension actually
 * has four spatial dimensions, not three.
 *
 * The pocket dimension contains an infinite 4-dimensional grid. At every
 * integer 4-dimensional coordinate (x,y,z,w), there exists a single cube
 * (really, a hypercube) which is still either active or inactive.
 *
 * Each cube only ever considers its neighbors: any of the 80 other cubes where
 * any of their coordinates differ by at most 1. For example, given the cube at
 * x=1,y=2,z=3,w=4, its neighbors include the cube at x=2,y=2,z=3,w=3, the cube
 * at x=0,y=2,z=3,w=4, and so on.
 *
 * The initial state of the pocket dimension still consists of a small flat
 * region of cubes. Furthermore, the same rules for cycle updating still apply:
 * during each cycle, consider the number of active neighbors of each cube.
 *
 * For example, consider the same initial state as in the example above. Even
 * though the pocket dimension is 4-dimensional, this initial state represents a
 * small 2-dimensional slice of it. (In particular, this initial state defines a
 * 3x3x1x1 region of the 4-dimensional space.)
 *
 * Simulating a few cycles from this initial state produces the following
 * configurations, where the result of each cycle is shown layer-by-layer at
 * each given z and w coordinate:
 *
 * Before any cycles:
 *
 * z=0, w=0
 * .#.
 * ..#
 * ###
 *
 *
 * After 1 cycle:
 *
 * z=-1, w=-1
 * #..
 * ..#
 * .#.
 *
 * z=0, w=-1
 * #..
 * ..#
 * .#.
 *
 * z=1, w=-1
 * #..
 * ..#
 * .#.
 *
 * z=-1, w=0
 * #..
 * ..#
 * .#.
 *
 * z=0, w=0
 * #.#
 * .##
 * .#.
 *
 * z=1, w=0
 * #..
 * ..#
 * .#.
 *
 * z=-1, w=1
 * #..
 * ..#
 * .#.
 *
 * z=0, w=1
 * #..
 * ..#
 * .#.
 *
 * z=1, w=1
 * #..
 * ..#
 * .#.
 *
 *
 * After 2 cycles:
 *
 * z=-2, w=-2
 * .....
 * .....
 * ..#..
 * .....
 * .....
 *
 * z=-1, w=-2
 * .....
 * .....
 * .....
 * .....
 * .....
 *
 * z=0, w=-2
 * ###..
 * ##.##
 * #...#
 * .#..#
 * .###.
 *
 * z=1, w=-2
 * .....
 * .....
 * .....
 * .....
 * .....
 *
 * z=2, w=-2
 * .....
 * .....
 * ..#..
 * .....
 * .....
 *
 * z=-2, w=-1
 * .....
 * .....
 * .....
 * .....
 * .....
 *
 * z=-1, w=-1
 * .....
 * .....
 * .....
 * .....
 * .....
 *
 * z=0, w=-1
 * .....
 * .....
 * .....
 * .....
 * .....
 *
 * z=1, w=-1
 * .....
 * .....
 * .....
 * .....
 * .....
 *
 * z=2, w=-1
 * .....
 * .....
 * .....
 * .....
 * .....
 *
 * z=-2, w=0
 * ###..
 * ##.##
 * #...#
 * .#..#
 * .###.
 *
 * z=-1, w=0
 * .....
 * .....
 * .....
 * .....
 * .....
 *
 * z=0, w=0
 * .....
 * .....
 * .....
 * .....
 * .....
 *
 * z=1, w=0
 * .....
 * .....
 * .....
 * .....
 * .....
 *
 * z=2, w=0
 * ###..
 * ##.##
 * #...#
 * .#..#
 * .###.
 *
 * z=-2, w=1
 * .....
 * .....
 * .....
 * .....
 * .....
 *
 * z=-1, w=1
 * .....
 * .....
 * .....
 * .....
 * .....
 *
 * z=0, w=1
 * .....
 * .....
 * .....
 * .....
 * .....
 *
 * z=1, w=1
 * .....
 * .....
 * .....
 * .....
 * .....
 *
 * z=2, w=1
 * .....
 * .....
 * .....
 * .....
 * .....
 *
 * z=-2, w=2
 * .....
 * .....
 * ..#..
 * .....
 * .....
 *
 * z=-1, w=2
 * .....
 * .....
 * .....
 * .....
 * .....
 *
 * z=0, w=2
 * ###..
 * ##.##
 * #...#
 * .#..#
 * .###.
 *
 * z=1, w=2
 * .....
 * .....
 * .....
 * .....
 * .....
 *
 * z=2, w=2
 * .....
 * .....
 * ..#..
 * .....
 * .....
 *
 * After the full six-cycle boot process completes, 848 cubes are left in the
 * active state.
 *
 * Starting with your given initial configuration, simulate six cycles in a
 * 4-dimensional space. How many cubes are left in the active state after the
 * sixth cycle?
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
  int wmin;
  int wmax;

  char current_grid[GDIM][GDIM][GDIM][GDIM];
  char next_grid[GDIM][GDIM][GDIM][GDIM];
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

int active_neigbors(dimension_t d, int x, int y, int z, int w) {
  int count = 0;

  for (int i = x - 1; i <= x + 1; i++) {
    for (int j = y - 1; j <= y + 1; j++) {
      for (int k = z - 1; k <= z + 1; k++) {
        for (int l = w - 1; l <= w + 1; l++) {
          if (i == x && j == y && k == z && l == w) continue;

          if (d.current_grid[i][j][k][l] == '#') {
            count++;
          }
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
        for (int w = d.wmin  - 1; w <= d.wmax + 1; w++) {
          if (d.current_grid[x][y][z][w] == '#') {
            count++;
          }
        }
      }
    }
  }

  return count;
}

void copy(dimension_t *d) {
  for (int x = d->xmin  - 1; x <= d->xmax + 1; x++) {
    for (int y = d->xmin  - 1; y <= d->ymax + 1; y++) {
      for (int z = d->zmin  - 1; z <= d->zmax + 1; z++) {
        for (int w = d->wmin  - 1; w <= d->wmax + 1; w++) {
          d->current_grid[x][y][z][w] = d->next_grid[x][y][z][w];
        }
      }
    }
  }
}

void reset_next(dimension_t *d) {
  for (int x = d->xmin  - 1; x <= d->xmax + 1; x++) {
    for (int y = d->xmin  - 1; y <= d->ymax + 1; y++) {
      for (int z = d->zmin  - 1; z <= d->zmax + 1; z++) {
        for (int w = d->wmin  - 1; w <= d->wmax + 1; w++) {
          d->next_grid[x][y][z][w] = '.';
        }
      }
    }
  }
}

void reset_current(dimension_t *d) {
  for (int x = d->xmin  - 1; x <= d->xmax + 1; x++) {
    for (int y = d->xmin  - 1; y <= d->ymax + 1; y++) {
      for (int z = d->zmin  - 1; z <= d->zmax + 1; z++) {
        for (int w = d->wmin  - 1; w <= d->wmax + 1; w++) {
          d->current_grid[x][y][z][w] = '.';
        }
      }
    }
  }
}

void update_bounding_box(dimension_t *d) {
  for (int x = d->xmin - 1; x <= d->xmax + 1; x++) {
    for (int y = d->xmin - 1; y <= d->ymax + 1; y++) {
      for (int z = d->zmin - 1; z <= d->zmax + 1; z++) {
        for (int w = d->wmin  - 1; w <= d->wmax + 1; w++) {
          if (d->current_grid[x][y][z][w] == '#') {
            if (x < d->xmin) d->xmin = x;
            if (x > d->xmax) d->xmax = x;
            if (y < d->ymin) d->ymin = y;
            if (y > d->ymax) d->ymax = y;
            if (z < d->zmin) d->zmin = z;
            if (z > d->zmax) d->zmax = z;
            if (w < d->wmin) d->wmin = w;
            if (w > d->wmax) d->wmax = w;
          }
        }
      }
    }
  }
}

int main(int argc, char *argv[]) {
  int x, y, z, w, i, an;
  dimension_t dim;

  dim.xmin = dim.ymin = dim.zmin = dim.wmin = GDIM / 2;
  dim.xmax = dim.ymax = dim.zmax = GDIM / 2 + INPUT_DIM;
  dim.wmax = GDIM / 2 + 1;

  reset_current(&dim);
  reset_next(&dim);

  // Seed
  for (x = dim.xmin; x < dim.xmax; x++) {
    for (y = dim.ymin; y < dim.ymax; y++) {
      dim.current_grid[x][y][dim.zmin][dim.wmin] = input[y - dim.ymin][x - dim.xmin];
    }
  }

  for (i = 1; i <= 6; i++) {
    update_bounding_box(&dim);

    for (x = dim.xmin - 1; x <= dim.xmax + 1; x++) {
      for (y = dim.ymin - 1; y <= dim.ymax + 1; y++) {
        for (z = dim.zmin - 1; z <= dim.zmax + 1; z++) {
          for (w = dim.wmin - 1; w <= dim.wmax + 1; w++) {
            an = active_neigbors(dim, x, y, z, w);

            if (dim.current_grid[x][y][z][w] == '#') {
              if (an == 2 || an == 3) {
                dim.next_grid[x][y][z][w] = '#';
              } else {
                dim.next_grid[x][y][z][w] = '.';
              }
            } else {
              if (an == 3) {
                dim.next_grid[x][y][z][w] = '#';
              } else {
                dim.next_grid[x][y][z][w] = '.';
              }
            }
          }
        }
      }
    }

    update_bounding_box(&dim);

    copy(&dim);
    reset_next(&dim);
  }

  printf("Active count after six cycles: %d\n", active_count(dim));

  return 0;
}
