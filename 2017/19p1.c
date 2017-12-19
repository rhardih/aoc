/**
 * --- Day 19: A Series of Tubes ---
 *
 * Somehow, a network packet got lost and ended up here. It's trying to follow a
 * routing diagram (your puzzle input), but it's confused about where to go.
 *
 * Its starting point is just off the top of the diagram. Lines (drawn with |,
 * -, and +) show the path it needs to take, starting by going down onto the
 *  only line connected to the top of the diagram. It needs to follow this path
 *  until it reaches the end (located somewhere within the diagram) and stop
 *  there.
 *
 * Sometimes, the lines cross over each other; in these cases, it needs to
 * continue going the same direction, and only turn left or right when there's
 * no other option. In addition, someone has left letters on the line; these
 * also don't change its direction, but it can use them to keep track of where
 * it's been. For example:
 *
 *      |
 *      |  +--+
 *      A  |  C
 *  F---|----E|--+
 *      |  |  |  D
 *      +B-+  +--+
 *
 * Given this diagram, the packet needs to take the following path:
 *
 * - Starting at the only line touching the top of the diagram, it must go down,
 *   pass through A, and continue onward to the first +.
 * - Travel right, up, and right, passing through B in the process.
 * - Continue down (collecting C), right, and up (collecting D).
 * - Finally, go all the way left through E and stopping at F.
 *
 * Following the path to the end, the letters it sees on its path are ABCDEF.
 *
 * The little packet looks up at you, hoping you can help it find the way. What
 * letters will it see (in the order it would see them) if it follows the path?
 * (The routing diagram is very wide; make sure you view it without line
 * wrapping.)
 */

#include <stdio.h>
#include <string.h>

#define GRID_SIZE 201

int main(int argc, char const *argv[])
{
  char diagram[GRID_SIZE][GRID_SIZE];
  int i, j, current_x, current_y = 0, next_x = -1, next_y = -1, prev_x = -1, prev_y = -1;
  char *line = NULL;
  size_t linecap = 0;
  ssize_t linelen;

  while ((linelen = getline(&line, &linecap, stdin)) > 0)
    strncpy(diagram[i++], line, GRID_SIZE);

  // Find entry point
  for (i = 0; i < GRID_SIZE; ++i)
  {
    if (diagram[0][i] == '|')
    {
      current_x = i;
      break;
    }
  }

  int directions[4][2] = {
    {-1, 0},
    {1, 0},
    {0, 1},
    {0, -1}
  };

  int current_d = 2;

  printf("The packet sees: ");

  while (1)
  {
    if (diagram[current_y][current_x] == '+')
    {
      // Find a new direction to go in
      for (i = 0; i < 4; ++i)
      {
        next_x = current_x + directions[i][0];
        next_y = current_y + directions[i][1];

        // Don't go back from where we came
        if (next_x == prev_x && next_y == prev_y)
          continue;

        if (next_x < 0 || next_x >= GRID_SIZE ||
            next_y < 0 || next_y >= GRID_SIZE)
          goto done;

        if (diagram[next_y][next_x] == ' ')
          continue;

        current_d = i;
        break;
      }
    }
    else
    {
      // Continue in the current direction
      next_x = current_x + directions[current_d][0];
      next_y = current_y + directions[current_d][1];
    }

    prev_x = current_x;
    prev_y = current_y;
    current_x = next_x;
    current_y = next_y;

    if (diagram[current_y][current_x] != '|' &&
        diagram[current_y][current_x] != '+' &&
        diagram[current_y][current_x] != '-' &&
        diagram[current_y][current_x] != ' ')
    {
      printf("%c", diagram[current_y][current_x]);
    }
  }

done:

  printf("\n");

  return 0;
}
