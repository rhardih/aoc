/**
 * --- Day 6: Probably a Fire Hazard ---
 * 
 * Because your neighbors keep defeating you in the holiday house decorating
 * contest year after year, you've decided to deploy one million lights in a
 * 1000x1000 grid.
 * 
 * Furthermore, because you've been especially nice this year, Santa has mailed
 * you instructions on how to display the ideal lighting configuration.
 * 
 * Lights in your grid are numbered from 0 to 999 in each direction; the lights
 * at each corner are at 0,0, 0,999, 999,999, and 999,0. The instructions
 * include whether to turn on, turn off, or toggle various inclusive ranges
 * given as coordinate pairs. Each coordinate pair represents opposite corners
 * of a rectangle, inclusive; a coordinate pair like 0,0 through 2,2 therefore
 * refers to 9 lights in a 3x3 square. The lights all start turned off.
 * 
 * To defeat your neighbors this year, all you have to do is set up your lights
 * by doing the instructions Santa sent you in order.
 * 
 * For example:
 * 
 * - turn on 0,0 through 999,999 would turn on (or leave on) every light.
 * - toggle 0,0 through 999,0 would toggle the first line of 1000 lights,
 *   turning off the ones that were on, and turning on the ones that were off.
 * - turn off 499,499 through 500,500 would turn off (or leave off) the middle
 *   four lights.
 *
 * After following the instructions, how many lights are lit?
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

static unsigned int grid[1000][1000];

// Longest line in input is 32 characters + newline
#define MAX_LINE_LENGTH 33

int main(int argc, char const *argv[])
{
  char *buf = malloc(MAX_LINE_LENGTH * sizeof(char));
  char instruction[9];
  unsigned int x0, y0, x1, y1;
  int lit = 0;

  while(fgets(buf, MAX_LINE_LENGTH + 1, stdin) != NULL)
  {
    if (sscanf(buf, "turn %s %u,%u through %u,%u", instruction, &x0, &y0, &x1,
          &y1) == 5)
    {
      unsigned int val;

      strcmp(instruction, "on") == 0 ? (val = 1) : (val = 0);

      for (unsigned int x = x0; x <= x1; ++x)
      {
        for (unsigned int y = y0; y <= y1; ++y)
        {
          grid[x][y] = val;
        }
      }
    }
    else if (sscanf(buf, "toggle %u,%u through %u,%u", &x0, &y0, &x1, &y1) == 4)
    {
      for (unsigned int x = x0; x <= x1; ++x)
      {
        for (unsigned int y = y0; y <= y1; ++y)
        {
          grid[x][y] = grid[x][y] == 1 ? 0 : 1;
        }
      }
    }
  }

  free(buf);

  for (unsigned int x = 0; x < 1000; ++x)
  {
    for (unsigned int y = 0; y < 1000; ++y)
    {
      if(grid[x][y] != 0)
        lit++;
    }
  }

  printf("There are %d lights lit.\n", lit);

  return 0;
}
