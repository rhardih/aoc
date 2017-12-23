/**
 * --- Day 23: Coprocessor Conflagration --- You decide to head directly to the
 *  CPU and fix the printer from there. As you get close, you find an
 *  experimental coprocessor doing so much work that the local programs are
 *  afraid it will halt and catch fire. This would cause serious issues for the
 *  rest of the computer, so you head in and see what you can do.
 *
 * The code it's running seems to be a variant of the kind you saw recently on
 * that tablet. The general functionality seems very similar, but some of the
 * instructions are different:
 *
 * - set X Y sets register X to the value of Y.
 * - sub X Y decreases register X by the value of Y.
 * - mul X Y sets register X to the result of multiplying the value contained in
 *   register X by the value of Y.
 * - jnz X Y jumps with an offset of the value of Y, but only if the value of X
 *   is not zero. (An offset of 2 skips the next instruction, an offset of -1
 *   jumps to the previous instruction, and so on.)
 *
 * Only the instructions listed above are used. The eight registers here, named
 * a through h, all start at 0.
 *
 * The coprocessor is currently set to some kind of debug mode, which allows for
 * testing, but prevents it from doing any meaningful work.
 *
 * If you run the program (your puzzle input), how many times is the mul
 * instruction invoked?
 */

#include <stdio.h>
#include <regex.h>
#include <string.h>

#define INPUT_SIZE 32

static long registers[8];
static char *program[INPUT_SIZE];

int main(int argc, char const *argv[])
{
  long i, value, muls = 0;
  char instruction[4], reg_x, reg_y;
  char *line = NULL;
  size_t linecap = 0;
  regex_t type0, type1;

  regcomp(&type0, "... . -?[0-9]+", REG_EXTENDED);
  regcomp(&type1, "... . [a-z]", REG_EXTENDED);

  while (getline(&program[i++], &linecap, stdin) > 0);

  for (i = 0; i < 8; ++i)
    registers[i] = 0;

  i = 0;

  while (i >= 0 && i < INPUT_SIZE)
  {
    if (regexec(&type0, program[i], 0, NULL, 0) == 0)
    {
      sscanf(program[i], "%s %c %ld", instruction, &reg_x, &value);
      reg_x -= 'a';

      if (strncmp(instruction, "set", 3) == 0)
      {
        registers[reg_x] = value;
      }
      else if (strncmp(instruction, "sub", 3) == 0)
      {
        registers[reg_x] -= value;
      }
      else if (strncmp(instruction, "mul", 3) == 0)
      {
        registers[reg_x] *= value;
        muls++;
      }
      else if (strncmp(instruction, "jnz", 3) == 0)
      {
        if (registers[reg_x] != 0)
        {
          i += value;
          continue;
        }
      }
    }
    else if (regexec(&type1, program[i], 0, NULL, 0) == 0)
    {
      sscanf(program[i], "%s %c %c", instruction, &reg_x, &reg_y);
      reg_x -= 'a';
      reg_y -= 'a';

      if (strncmp(instruction, "set", 3) == 0)
      {
        registers[reg_x] = registers[reg_y];
      }
      else if (strncmp(instruction, "sub", 3) == 0)
      {
        registers[reg_x] -= registers[reg_y];
      }
      else if (strncmp(instruction, "mul", 3) == 0)
      {
        registers[reg_x] *= registers[reg_y];
        muls++;
      }
      else if (strncmp(instruction, "jnz", 3) == 0)
      {
        if (registers[reg_x] != 0)
        {
          i += registers[reg_y];
          continue;
        }
      }
    }

    i++;
  }

  printf("The mul instruction is invoked %ld times.\n", muls);

  return 0;
}
