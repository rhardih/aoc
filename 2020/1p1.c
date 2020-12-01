/**
 * --- Day 1: Report Repair ---
 *
 * After saving Christmas five years in a row, you've decided to take a vacation
 * at a nice resort on a tropical island. Surely, Christmas will go on without
 * you.
 * 
 * The tropical island has its own currency and is entirely cash-only. The gold
 * coins used there have a little picture of a starfish; the locals just call
 * them stars. None of the currency exchanges seem to have heard of them, but
 * somehow, you'll need to find fifty of these coins by the time you arrive so
 * you can pay the deposit on your room.
 * 
 * To save your vacation, you need to get all fifty stars by December 25th.
 * 
 * Collect stars by solving puzzles. Two puzzles will be made available on each
 * day in the Advent calendar; the second puzzle is unlocked when you complete
 * the first. Each puzzle grants one star. Good luck!
 * 
 * Before you leave, the Elves in accounting just need you to fix your expense
 * report (your puzzle input); apparently, something isn't quite adding up.
 * 
 * Specifically, they need you to find the two entries that sum to 2020 and then
 * multiply those two numbers together.
 * 
 * For example, suppose your expense report contained the following:
 * 
 * 1721
 * 979
 * 366
 * 299
 * 675
 * 1456
 *
 * In this list, the two entries that sum to 2020 are 1721 and 299. Multiplying
 * them together produces 1721 * 299 = 514579, so the correct answer is 514579.
 * 
 * Of course, your expense report is much larger. Find the two entries that sum
 * to 2020; what do you get if you multiply them together?
 */

#include <stdio.h>

#define INPUT_SIZE 200

int main(int argc, char **argv) {
  int expense, expenses[INPUT_SIZE], i = 0, j, k, result;

  while(scanf("%d\n", &expense) != EOF) {
    expenses[i++] = expense;
  }

  for(j = 0; j < INPUT_SIZE - 1; j++) {
    for(k = j + 1; k < INPUT_SIZE; k++) {
      if(expenses[j] + expenses[k] == 2020) {
        result = expenses[j] * expenses[k];
        goto done;
      }
    }
  }

done:

  printf("Result of multiplying the two entries: %d\n", result);

  return 0;
}
