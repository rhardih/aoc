/**
 * --- Day 16: Permutation Promenade ---
 *
 * You come upon a very unusual sight; a group of programs here appear to be
 * dancing.
 *
 * There are sixteen programs in total, named a through p. They start by
 * standing in a line: a stands in position 0, b stands in position 1, and so on
 * until p, which stands in position 15.
 *
 * The programs' dance consists of a sequence of dance moves:
 *
 * - Spin, written sX, makes X programs move from the end to the front, but
 *   maintain their order otherwise. (For example, s3 on abcde produces cdeab).
 * - Exchange, written xA/B, makes the programs at positions A and B swap
 *   places.
 * - Partner, written pA/B, makes the programs named A and B swap places.
 *
 * For example, with only five programs standing in a line (abcde), they could
 * do the following dance:
 *
 * - s1, a spin of size 1: eabcd.
 * - x3/4, swapping the last two programs: eabdc.
 * - pe/b, swapping programs e and b: baedc.
 *
 * After finishing their dance, the programs end up in order baedc.
 *
 * You watch the dance for a while and record their dance moves (your puzzle
 * input). In what order are the programs standing after their dance?
 */

#include <stdio.h>

#define PCOUNT 16

int main(int argc, char const *argv[])
{
  int s, x0, x1, i;
  char p0, p1;
  char programs[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
    'l', 'm', 'n', 'o', 'p' };
  char tmp[PCOUNT];

  while(1)
  {
    if (scanf("s%d,", &s) == 1)
    {
      for (i = 0; i < PCOUNT; ++i)
        tmp[i] = programs[(PCOUNT - s + i) % PCOUNT];

      for (i = 0; i < PCOUNT; ++i)
        programs[i] = tmp[i];
    }
    else if (scanf("x%d/%d,", &x0, &x1) == 2)
    {
      programs[x0] ^= programs[x1];
      programs[x1] ^= programs[x0];
      programs[x0] ^= programs[x1];
    }
    else if (scanf("p%c/%c,", &p0, &p1) == 2)
    {
      for (i = 0; i < PCOUNT; ++i)
      {
        if (programs[i] == p0) x0 = i;
        if (programs[i] == p1) x1 = i;
      }

      programs[x0] ^= programs[x1];
      programs[x1] ^= programs[x0];
      programs[x0] ^= programs[x1];
    }
    else
    {
      break;
    }
  }

  char out[PCOUNT + 1];
  snprintf(out, PCOUNT + 1, "%s", programs);

  printf("The order of the programs: %s\n", out);

  return 0;
}
