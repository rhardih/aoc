/**
 * --- Part Two ---
 *
 * As soon as people start to arrive, you realize your mistake. People don't
 * just care about adjacent seats - they care about the first seat they can see
 * in each of those eight directions!
 *
 * Now, instead of considering just the eight immediately adjacent seats,
 * consider the first seat in each of those eight directions. For example, the
 * empty seat below would see eight occupied seats:
 *
 * .......#.
 * ...#.....
 * .#.......
 * .........
 * ..#L....#
 * ....#....
 * .........
 * #........
 * ...#.....
 *
 * The leftmost empty seat below would only see one empty seat, but cannot see
 * any of the occupied ones:
 *
 * .............
 * .L.L.#.#.#.#.
 * .............
 *
 * The empty seat below would see no occupied seats:
 *
 * .##.##.
 * #.#.#.#
 * ##...##
 * ...L...
 * ##...##
 * #.#.#.#
 * .##.##.
 *
 * Also, people seem to be more tolerant than you expected: it now takes five or
 * more visible occupied seats for an occupied seat to become empty (rather than
 * four or more from the previous rules). The other rules still apply: empty
 * seats that see no occupied seats become occupied, seats matching no rule
 * don't change, and floor never changes.
 *
 * Given the same starting layout as above, these new rules cause the seating
 * area to shift around as follows:
 *
 * L.LL.LL.LL
 * LLLLLLL.LL
 * L.L.L..L..
 * LLLL.LL.LL
 * L.LL.LL.LL
 * L.LLLLL.LL
 * ..L.L.....
 * LLLLLLLLLL
 * L.LLLLLL.L
 * L.LLLLL.LL
 *
 * #.##.##.##
 * #######.##
 * #.#.#..#..
 * ####.##.##
 * #.##.##.##
 * #.#####.##
 * ..#.#.....
 * ##########
 * #.######.#
 * #.#####.##
 *
 * #.LL.LL.L#
 * #LLLLLL.LL
 * L.L.L..L..
 * LLLL.LL.LL
 * L.LL.LL.LL
 * L.LLLLL.LL
 * ..L.L.....
 * LLLLLLLLL#
 * #.LLLLLL.L
 * #.LLLLL.L#
 *
 * #.L#.##.L#
 * #L#####.LL
 * L.#.#..#..
 * ##L#.##.##
 * #.##.#L.##
 * #.#####.#L
 * ..#.#.....
 * LLL####LL#
 * #.L#####.L
 * #.L####.L#
 *
 * #.L#.L#.L#
 * #LLLLLL.LL
 * L.L.L..#..
 * ##LL.LL.L#
 * L.LL.LL.L#
 * #.LLLLL.LL
 * ..L.L.....
 * LLLLLLLLL#
 * #.LLLLL#.L
 * #.L#LL#.L#
 *
 * #.L#.L#.L#
 * #LLLLLL.LL
 * L.L.L..#..
 * ##L#.#L.L#
 * L.L#.#L.L#
 * #.L####.LL
 * ..#.#.....
 * LLL###LLL#
 * #.LLLLL#.L
 * #.L#LL#.L#
 *
 * #.L#.L#.L#
 * #LLLLLL.LL
 * L.L.L..#..
 * ##L#.#L.L#
 * L.L#.LL.L#
 * #.LLLL#.LL
 * ..#.L.....
 * LLL###LLL#
 * #.LLLLL#.L
 * #.L#LL#.L#
 *
 * Again, at this point, people stop shifting around and the seating area
 * reaches equilibrium. Once this occurs, you count 26 occupied seats.
 *
 * Given the new visibility method and the rule change for occupied seats
 * becoming empty, once equilibrium is reached, how many seats end up occupied?
 */

#include <stdio.h>

#define INPUT_SIZE 90
#define LINE_LENGTH 99

typedef struct {
  int x;
  int y;
} direction_t;

char layout[INPUT_SIZE][LINE_LENGTH + 1];
int adjecents[INPUT_SIZE][LINE_LENGTH + 1];

int count_adjecents(int i, int j) {
  int k, l, m, c = 0;

  direction_t directions[] = {
    { -1, -1 },
    { 0, -1 },
    { 1, -1 },
    { -1, 0 },
    { 1, 0 },
    { -1, 1 },
    { 0, 1 },
    { 1, 1 }
  };

  for(m = 0; m < 8; m++) {
    direction_t d = directions[m];
    k = i;
    l = j;

    while(k >= 0 && l >= 0 && k < INPUT_SIZE && l < LINE_LENGTH) {
      k += d.x;
      l += d.y;

      if (layout[k][l] == '#') {
        c++;
        break;
      }

      if (layout[k][l] == 'L') {
        break;
      }
    }
  }

  return c;
}

void fill_adjecents() {
  for(int i = 0; i < INPUT_SIZE; i++) {
    for(int j = 0; j < LINE_LENGTH; j++) {
      adjecents[i][j] = count_adjecents(i, j);
    }
  }
}

int occupancy() {
  int count = 0;

  for(int i = 0; i < INPUT_SIZE; i++) {
    for(int j = 0; j < LINE_LENGTH; j++) {
      count += layout[i][j] == '#';
    }
  }

  return count;
}

int main(int argc, char **argv) {
  int i = 0, j, k, l, changes = 0;

  while(scanf("%99s\n", layout[i++]) != EOF) {}

  do {
    changes = 0;
    fill_adjecents();

    for(i = 0; i < INPUT_SIZE; i++) {
      for(j = 0; j < LINE_LENGTH; j++) {
        int empty = layout[i][j] == 'L';
        int occupied = layout[i][j] == '#';

        if (empty && adjecents[i][j] == 0) {
          layout[i][j] = '#';
          changes = 1;
        } else if (occupied && adjecents[i][j] >= 5) {
          layout[i][j] = 'L';
          changes = 1;
        }
      }
    }

  } while (changes);

  printf("Number of seats ending up occupied: %d\n", occupancy());

  return 0;
}
