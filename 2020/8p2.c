/**
 * --- Part Two ---
 *
 * After some careful analysis, you believe that exactly one instruction is
 * corrupted.
 * 
 * Somewhere in the program, either a jmp is supposed to be a nop, or a nop is
 * supposed to be a jmp. (No acc instructions were harmed in the corruption of
 * this boot code.)
 * 
 * The program is supposed to terminate by attempting to execute an instruction
 * immediately after the last instruction in the file. By changing exactly one
 * jmp or nop, you can repair the boot code and make it terminate correctly.
 * 
 * For example, consider the same program from above:
 * 
 * nop +0
 * acc +1
 * jmp +4
 * acc +3
 * jmp -3
 * acc -99
 * acc +1
 * jmp -4
 * acc +6
 *
 * If you change the first instruction from nop +0 to jmp +0, it would create a
 * single-instruction infinite loop, never leaving that instruction. If you
 * change almost any of the jmp instructions, the program will still eventually
 * find another jmp instruction and loop forever.
 * 
 * However, if you change the second-to-last instruction (from jmp -4 to nop
 * -4), the program terminates! The instructions are visited in this order:
 * 
 * nop +0  | 1
 * acc +1  | 2
 * jmp +4  | 3
 * acc +3  |
 * jmp -3  |
 * acc -99 |
 * acc +1  | 4
 * nop -4  | 5
 * acc +6  | 6
 *
 * After the last instruction (acc +6), the program terminates by attempting to
 * run the instruction below the last instruction in the file. With this change,
 * after the program terminates, the accumulator contains the value 8 (acc +1,
 * acc +1, acc +6).
 * 
 * Fix the program so that it terminates normally by changing exactly one jmp
 * (to nop) or nop (to jmp). What is the value of the accumulator after the
 * program terminates?
 */

#include <stdio.h>
#include <stdlib.h>

#define INS_COUNT 654
#define INS_MAX_LEN 8

int main(int argc, char **argv) {
  int accumulator, i = 0, pc = 0, value;
  char instructions[INS_COUNT][INS_MAX_LEN + 1];
  int replacements[INS_COUNT + 1] = { 0 };

  while(gets(instructions[i++]) != NULL) {};

  while(pc != INS_COUNT) {
    int marks[INS_COUNT] = { 0 };
    int replaced = 0;
    
    accumulator = 0;
    pc = 0;

    while(marks[pc] == 0) {
      marks[pc] = 1;

      value = atoi(instructions[pc] + 4);

      switch(instructions[pc][0]) {
        case 'a':
          // acc
          accumulator += value;
          pc++;
          break;
        case 'j':
          if (replaced || replacements[pc]) {
            // jmp
            pc += value;
          } else {
            replaced = 1;
            replacements[pc] = 1;

            // nop
            pc++;
          }
          break;
        case 'n':
          if (replaced || replacements[pc]) {
            // nop
            pc++;
          } else {
            replaced = 1;
            replacements[pc] = 1;

            // jmp
            pc += value;
          }
          break;
      }
    }
  }

  printf("Value of the accumulator: %d\n", accumulator);

  return 0;
}
