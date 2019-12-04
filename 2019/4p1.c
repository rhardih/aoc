/**
 * --- Day 4: Secure Container ---
 *
 * You arrive at the Venus fuel depot only to discover it's protected by a
 * password. The Elves had written the password on a sticky note, but someone
 * threw it out.
 * 
 * However, they do remember a few key facts about the password:
 * 
 * - It is a six-digit number.
 * - The value is within the range given in your puzzle input.
 * - Two adjacent digits are the same (like 22 in 122345).
 * - Going from left to right, the digits never decrease; they only ever
 *   increase or stay the same (like 111123 or 135679).
 *
 * Other than the range rule, the following are true:
 * 
 * - 111111 meets these criteria (double 11, never decreases).
 * - 223450 does not meet these criteria (decreasing pair of digits 50).
 * - 123789 does not meet these criteria (no double).
 *
 * How many different passwords within the range given in your puzzle input meet
 * these criteria?
 */
#include <stdio.h>

// RANGE
#define MIN 125730
#define MAX 579381

int main() {
  int count, i, tmp;

  for(i = MIN; i <= MAX; i++) {
    int digits[] = {
      i % 10,
      i / 10 % 10,
      i / 100 % 10,
      i / 1000 % 10,
      i / 10000 % 10,
      i / 100000
    };

    int adjecent = 
      digits[0] == digits[1] ||
      digits[1] == digits[2] ||
      digits[2] == digits[3] ||
      digits[3] == digits[4] ||
      digits[4] == digits[5];

    int increasing = 
      digits[5] <= digits[4] &&
      digits[4] <= digits[3] &&
      digits[3] <= digits[2] &&
      digits[2] <= digits[1] &&
      digits[1] <= digits[0];

    if (adjecent && increasing) {
      count++;
    }
  }

  printf("Number of dfferent passwords: %d\n", count);

  return 0;
}
