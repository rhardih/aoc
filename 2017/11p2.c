/**
 * --- Day 11: Hex Ed ---
 * 
 * Crossing the bridge, you've barely reached the other side of the stream when
 * a program comes up to you, clearly in distress. "It's my child process," she
 * says, "he's gotten lost in an infinite grid!"
 * 
 * Fortunately for her, you have plenty of experience with infinite grids.
 * 
 * Unfortunately for you, it's a hex grid.
 * 
 * The hexagons ("hexes") in this grid are aligned such that adjacent hexes can
 * be found to the north, northeast, southeast, south, southwest, and northwest:
 * 
 *   \ n  /
 * nw +--+ ne
 *   /    \
 * -+      +-
 *   \    /
 * sw +--+ se
 *   / s  \
 *
 * You have the path the child process took. Starting where he started, you need
 * to determine the fewest number of steps required to reach him. (A "step"
 * means to move from the hex you are in to any adjacent hex.)
 * 
 * For example:
 * 
 * - ne,ne,ne is 3 steps away.
 * - ne,ne,sw,sw is 0 steps away (back where you started).
 * - ne,ne,s,s is 2 steps away (se,se).
 * - se,sw,se,sw,sw is 3 steps away (s,s,sw).
 *
 * --- Part Two ---
 *
 * How many steps away is the furthest he ever got from his starting position?
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char const *argv[])
{
  double x = 0, y = 0, step_max = 0;
  char *line = NULL;
  size_t linecap = 0;
  ssize_t linelen;
  char *token, *string, *tofree;

  linelen = getline(&line, &linecap, stdin);
  tofree = string = strdup(line);

  while ((token = strsep(&string, ",\n")) != NULL)
  {
    if (strcmp(token, "n") == 0)
    {
      y++;
    }
    else if (strcmp(token, "nw") == 0)
    {
      y += 0.5;
      x -= 0.5;
    }
    else if (strcmp(token, "sw") == 0)
    {
      y -= 0.5;
      x -= 0.5;
    }
    else if (strcmp(token, "s") == 0)
    {
      y--;
    }
    else if (strcmp(token, "se") == 0)
    {
      y -= 0.5;
      x += 0.5;
    }
    else if (strcmp(token, "ne") == 0)
    {
      y += 0.5;
      x += 0.5;
    }

    if (x + y > step_max)
      step_max = x + y;
  }

  free(tofree);

  printf("Furthest away: %d\n", (int)(step_max));

  return 0;
}
