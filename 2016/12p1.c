/**
 * --- Day 12: Leonardo's Monorail ---
 * 
 * You finally reach the top floor of this building: a garden with a slanted
 * glass ceiling. Looks like there are no more stars to be had.
 * 
 * While sitting on a nearby bench amidst some tiger lilies, you manage to
 * decrypt some of the files you extracted from the servers downstairs.
 * 
 * According to these documents, Easter Bunny HQ isn't just this building - it's
 * a collection of buildings in the nearby area. They're all connected by a
 * local monorail, and there's another building not far from here!
 * Unfortunately, being night, the monorail is currently not operating.
 * 
 * You remotely connect to the monorail control systems and discover that the
 * boot sequence expects a password. The password-checking logic (your puzzle
 * input) is easy to extract, but the code it uses is strange: it's assembunny
 * code designed for the new computer you just assembled. You'll have to execute
 * the code and get the password.
 * 
 * The assembunny code you've extracted operates on four registers (a, b, c, and
 * d) that start at 0 and can hold any integer. However, it seems to make use of
 * only a few instructions:
 * 
 * - cpy x y copies x (either an integer or the value of a register) into
 *   register y.
 * - inc x increases the value of register x by one.
 * - dec x decreases the value of register x by one.
 * - jnz x y jumps to an instruction y away (positive means forward; negative
 *   means backward), but only if x is not zero.
 *
 * The jnz instruction moves relative to itself: an offset of -1 would continue
 * at the previous instruction, while an offset of 2 would skip over the next
 * instruction.
 * 
 * For example:
 * 
 * cpy 41 a
 * inc a
 * inc a
 * dec a
 * jnz a 2
 * dec a
 *
 * The above code would set register a to 41, increase its value by 2, decrease
 * its value by 1, and then skip the last dec a (because a is not zero, so the
 * jnz a 2 skips it), leaving register a at 42. When you move past the last
 * instruction, the program halts.
 * 
 * After executing the assembunny code in your puzzle input, what value is left
 * in register a?
 */

#include "stdio.h"
#include "string.h"

int main(int argc, char const *argv[])
{
  char *arg_a, *arg_b;
  char *instruction;
  char *newline;
  char instructions[23][10], copy[10];
  int registers[4] = {0};
  int offset = (int)'a';
  int i = 0;

  // Read all instructions
  while (fgets(instructions[i], 10, stdin) != NULL) {
    // don't store newline with instructions
    *(strchr(instructions[i], '\n')) = 0;
    i++;
  }

  int pc = 0; // program counter

  while (pc <= 22)
  {
    // use a copy, since strtok is destructive
    strcpy(copy, instructions[pc]);
    instruction = strtok(copy, " ");

    if (strcmp(instruction, "cpy") == 0) {
      arg_a = strtok(NULL, " ");
      arg_b = strtok(NULL, " ");

      if (sscanf(arg_a, "%d", &i)) {
        registers[arg_b[0] - offset] = i;
      } else {
        registers[arg_b[0] - offset] = registers[arg_a[0] - offset];
      }

      pc++;
    } else if (strcmp(instruction, "jnz") == 0) {
      arg_a = strtok(NULL, " ");
      arg_b = strtok(NULL, " ");

      if (registers[arg_a[0] - offset] != 0) {
        sscanf(arg_b, "%d", &i);
        pc += i;
      } else {
        pc++;
      }
    } else if (strcmp(instruction, "inc") == 0) {
      arg_a = strtok(NULL, " ");

      registers[arg_a[0] - offset]++;

      pc++;
    } else if (strcmp(instruction, "dec") == 0) {
      arg_a = strtok(NULL, " ");

      registers[arg_a[0] - offset]--;

      pc++;
    }
  }

  printf("Value left in register a: %d\n", registers[0]);
  
  return 0;
}
