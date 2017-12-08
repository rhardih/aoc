/**
 * --- Day 8: I Heard You Like Registers ---
 * 
 * You receive a signal directly from the CPU. Because of your recent assistance
 * with jump instructions, it would like you to compute the result of a series
 * of unusual register instructions.
 * 
 * Each instruction consists of several parts: the register to modify, whether
 * to increase or decrease that register's value, the amount by which to
 * increase or decrease it, and a condition. If the condition fails, perform the
 * instruction without modifying the register. The registers all start at 0. The
 * instructions look like this:
 * 
 * b inc 5 if a > 1
 * a inc 1 if b < 5
 * c dec -10 if a >= 1
 * c inc -20 if c == 10
 *
 * These instructions would be processed as follows:
 * 
 * - Because a starts at 0, it is not greater than 1, and so b is not modified.
 * - a is increased by 1 (to 1) because b is less than 5 (it is 0).
 * - c is decreased by -10 (to 10) because a is now greater than or equal to 1
 *   (it is 1).
 * - c is increased by -20 (to -10) because c is equal to 10.
 *
 * After this process, the largest value in any register is 1.
 * 
 * You might also encounter <= (less than or equal to) or != (not equal to).
 * However, the CPU doesn't have the bandwidth to tell you what all the
 * registers are named, and leaves that to you to determine.
 * 
 * What is the largest value in any register after completing the instructions
 * in your puzzle input?
 */

#include <stdio.h>
#include <string.h>

int regtoi(char *reg)
{
  int i;

  switch (strlen(reg))
  {
    case 1:
      i = reg[0] - 'a';
      break;
    case 2:
      i = (reg[0] - 'a' + 1) * 26 + reg[1] - 'a';
      break;
    case 3:
      i = (reg[0] - 'a' + 1) * 26 * 26 + (reg[1] - 'a' + 1) * 26 + reg[2] - 'a';
      break;
    default:
      printf("Unmatched %s\n", reg);
      return -1;
      break;
  }

  return i;
}

// Assuming registers of max three letters, and a 26 letter alphabet, that makes
// for a total of 26^1 + 26^2 + 26^3 = 18278 possible namings.
#define REGISTER_COUNT 18278
static int registers[REGISTER_COUNT];

int main(int argc, char const *argv[])
{
  char *line = NULL;
  size_t linecap = 0;
  ssize_t linelen;

  char reg0[6], inst[6], reg1[6], cond[5];
  int val0, val1, perform, max;

  while ((linelen = getline(&line, &linecap, stdin)) > 0)
  {
    sscanf(line, "%s %s %d if %s %s %d", reg0, inst, &val0, reg1, cond, &val1);

    perform = 0;

    if (strcmp(cond, "<") == 0)
    {
      perform = registers[regtoi(reg1)] < val1;
    }
    else if (strcmp(cond, ">") == 0)
    {
      perform = registers[regtoi(reg1)] > val1;
    }
    else if (strcmp(cond, ">=") == 0)
    {
      perform = registers[regtoi(reg1)] >= val1;
    }
    else if (strcmp(cond, "<=") == 0)
    {
      perform = registers[regtoi(reg1)] <= val1;
    }
    else if (strcmp(cond, "!=") == 0)
    {
      perform = registers[regtoi(reg1)] != val1;
    }
    else if (strcmp(cond, "==") == 0)
    {
      perform = registers[regtoi(reg1)] == val1;
    }

    if (perform)
    {
      if (strcmp(inst, "inc") == 0)
      {
        registers[regtoi(reg0)] += val0;
      }
      else
      {
        registers[regtoi(reg0)] -= val0;
      }
    }
  }

  max = 0;
  for (size_t i = 0; i < REGISTER_COUNT; ++i)
  {
    if (registers[i] > max)
      max = registers[i];
  }

  printf("Max value of any register: %d\n", max);

  return 0;
}
