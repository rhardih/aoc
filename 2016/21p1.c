/**
 * --- Day 21: Scrambled Letters and Hash ---
 * 
 * The computer system you're breaking into uses a weird scrambling function to
 * store its passwords. It shouldn't be much trouble to create your own
 * scrambled password so you can add it to the system; you just have to
 * implement the scrambler.
 * 
 * The scrambling function is a series of operations (the exact list is provided
 * in your puzzle input). Starting with the password to be scrambled, apply each
 * operation in succession to the string. The individual operations behave as
 * follows:
 * 
 * - swap position X with position Y means that the letters at indexes X and Y
 *   (counting from 0) should be swapped.
 * - swap letter X with letter Y means that the letters X and Y should be
 *   swapped (regardless of where they appear in the string).
 * - rotate left/right X steps means that the whole string should be rotated;
 *   for example, one right rotation would turn abcd into dabc.
 * - rotate based on position of letter X means that the whole string should be
 *   rotated to the right based on the index of letter X (counting from 0) as
 *   determined before this instruction does any rotations. Once the index is
 *   determined, rotate the string to the right one time, plus a number of times
 *   equal to that index, plus one additional time if the index was at least 4.
 * - reverse positions X through Y means that the span of letters at indexes X
 *   through Y (including the letters at X and Y) should be reversed in order.
 * - move position X to position Y means that the letter which is at index X
 *   should be removed from the string, then inserted such that it ends up at
 *   index Y.
 *
 * For example, suppose you start with abcde and perform the following operations:
 * 
 * - swap position 4 with position 0 swaps the first and last letters, producing
 *   the input for the next step, ebcda.
 * - swap letter d with letter b swaps the positions of d and b: edcba.
 * - reverse positions 0 through 4 causes the entire string to be reversed,
 *   producing abcde.
 * - rotate left 1 step shifts all letters left one position, causing the first
 *   letter to wrap to the end of the string: bcdea.
 * - move position 1 to position 4 removes the letter at position 1 (c), then
 *   inserts it at position 4 (the end of the string): bdeac.
 * - move position 3 to position 0 removes the letter at position 3 (a), then
 *   inserts it at position 0 (the front of the string): abdec.
 * - rotate based on position of letter b finds the index of letter b (1), then
 *   rotates the string right once plus a number of times equal to that index
 *   (2): ecabd.
 * - rotate based on position of letter d finds the index of letter d (4), then
 *   rotates the string right once, plus a number of times equal to that index,
 *   plus an additional time because the index was at least 4, for a total of 6
 *   right rotations: decab.
 *
 * After these steps, the resulting scrambled password is decab.
 * 
 * Now, you just need to generate a new scrambled password and you can access
 * the system. Given the list of scrambling operations in your puzzle input,
 * what is the result of scrambling abcdefgh?
 */

#include <stdio.h>
#include <string.h>

#define INPUT "abcdefgh"
#define LINPUT 9

void swap_position(char s[LINPUT], int x, int y) {
  s[x] ^= s[y];
  s[y] ^= s[x];
  s[x] ^= s[y];
};

void swap_letter(char s[LINPUT], char x, char y) {
  char *a = strchr(s, x);
  char *b = strchr(s, y);

  *a ^= *b;
  *b ^= *a;
  *a ^= *b;
}

void rotate_left(char s[LINPUT], int x) {
  int i, l = strlen(s);
  int shift = x % l;
  char tmp;

  while (shift-- > 0) {
    tmp = s[0];

    for (i = 0; i < l - 1; i++) {
      s[i] = s[i + 1];
    }

    s[l - 1] = tmp;
  }
}

void rotate_right(char s[LINPUT], int x) {
  rotate_left(s, strlen(s) - x);
}

void rotate_position(char s[LINPUT], char x) {
  char *a = strchr(s, x);
  int index = a - s;

  int amount = index >= 4 ? index + 2 : index + 1;

  rotate_right(s, amount % (LINPUT - 1));
}

void reverse_positions(char s[LINPUT], int x, int y) {
  // assume x < y
  while (x < y) swap_position(s, x++, y--);
}

void move_position(char s[LINPUT], int x, int y) {
  rotate_left(s + x, 1);
  rotate_right(s + y, 1);
}

int main(int argc, char const *argv[])
{
  int x, y;
  char buf[50], a, b;
  char scrambled[LINPUT] = INPUT;

  while(fgets(buf, 50, stdin) != NULL) {
    if (sscanf(buf, "swap position %d with position %d", &x, &y)) {
      swap_position(scrambled, x, y);
    } else if (sscanf(buf, "swap letter %c with letter %c", &a, &b)) {
      swap_letter(scrambled, a, b);
    } else if (sscanf(buf, "rotate left %d steps", &x)) {
      rotate_left(scrambled, x);
    } else if (sscanf(buf, "rotate right %d steps", &x)) {
      rotate_right(scrambled, x);
    } else if (sscanf(buf, "rotate based on position of letter %c", &a)) {
      rotate_position(scrambled, a);
    } else if (sscanf(buf, "reverse positions %d through %d", &x, &y)) {
      reverse_positions(scrambled, x, y);
    } else if (sscanf(buf, "move position %d to position %d", &x, &y)) {
      move_position(scrambled, x, y);
    }
  }

  printf("Result of scrambling input %s: %s\n", INPUT, scrambled);

  return 0;
}
