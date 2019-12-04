/**
 * --- Part Two ---
 *
 * An Elf just remembered one more important detail: the two adjacent matching
 * digits are not part of a larger group of matching digits.
 * 
 * Given this additional criterion, but still ignoring the range rule, the
 * following are now true:
 * 
 * - 112233 meets these criteria because the digits never decrease and all
 *   repeated digits are exactly two digits long.
 * - 123444 no longer meets the criteria (the repeated 44 is part of a larger
 *   group of 444).
 * - 111122 meets the criteria (even though 1 is repeated more than twice, it
 *   still contains a double 22).
 *
 * How many different passwords within the range given in your puzzle input meet
 * all of the criteria?
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

    int adjecent_non_grouped = 
      (digits[0] == digits[1] && (digits[1] != digits[2])) ||
      (digits[1] == digits[2] && (digits[0] != digits[1] && digits[2] != digits[3])) ||
      (digits[2] == digits[3] && (digits[1] != digits[2] && digits[3] != digits[4])) ||
      (digits[3] == digits[4] && (digits[2] != digits[3] && digits[4] != digits[5])) ||
      (digits[4] == digits[5] && (digits[3] != digits[4]));

    if (!adjecent_non_grouped) continue;

    int increasing = 
      digits[5] <= digits[4] &&
      digits[4] <= digits[3] &&
      digits[3] <= digits[2] &&
      digits[2] <= digits[1] &&
      digits[1] <= digits[0];

    if (!increasing) continue;

    count++;
  }

  printf("Number of dfferent passwords: %d\n", count);

  return 0;
}
