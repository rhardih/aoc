#include "stdio.h"
#include "string.h"

int main(int argc, char const *argv[])
{
  char *arg_a, *arg_b;
  char *instruction;
  char *newline;
  char instructions[23][10], copy[10];
  int registers[4] = { 0, 0, 1, 0 };
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
