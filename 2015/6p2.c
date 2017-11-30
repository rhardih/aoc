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
 *
 * --- Part Two ---
 * 
 * You just finish implementing your winning light pattern when you realize you
 * mistranslated Santa's message from Ancient Nordic Elvish.
 * 
 * The light grid you bought actually has individual brightness controls; each
 * light can have a brightness of zero or more. The lights all start at zero.
 * 
 * The phrase turn on actually means that you should increase the brightness of
 * those lights by 1.
 * 
 * The phrase turn off actually means that you should decrease the brightness of
 * those lights by 1, to a minimum of zero.
 * 
 * The phrase toggle actually means that you should increase the brightness of
 * those lights by 2.
 * 
 * What is the total brightness of all lights combined after following Santa's
 * instructions?
 * 
 * For example:
 * 
 * - turn on 0,0 through 0,0 would increase the total brightness by 1.
 * - toggle 0,0 through 999,999 would increase the total brightness by 2000000.
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

static int grid[1000][1000];

// Longest line in input is 32 characters + newline
#define MAX_LINE_LENGTH 33

int main(int argc, char const *argv[])
{
  char *buf = malloc(MAX_LINE_LENGTH * sizeof(char));
  char instruction[9];
  int x0, y0, x1, y1;
  int brightnes = 0;

  while(fgets(buf, MAX_LINE_LENGTH + 1, stdin) != NULL)
  {
    if (sscanf(buf, "turn %s %d,%d through %d,%d", instruction, &x0, &y0, &x1,
          &y1) == 5)
    {
      int val;

      strcmp(instruction, "on") == 0 ? (val = 1) : (val = -1);

      for (int x = x0; x <= x1; ++x)
      {
        for (int y = y0; y <= y1; ++y)
        {
          grid[x][y] += val;
          grid[x][y] = max(grid[x][y], 0);
        }
      }
    }
    else if (sscanf(buf, "toggle %d,%d through %d,%d", &x0, &y0, &x1, &y1) == 4)
    {
      for (int x = x0; x <= x1; ++x)
      {
        for (int y = y0; y <= y1; ++y)
        {
          grid[x][y] += 2;
        }
      }
    }
  }

  free(buf);

  for (int x = 0; x < 1000; ++x)
  {
    for (int y = 0; y < 1000; ++y)
    {
      if(grid[x][y] != 0)
        brightnes += grid[x][y];
    }
  }

  printf("The total brightness of the grid is: %d\n", brightnes);

  return 0;
}
