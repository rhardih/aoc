/**
 * --- Part Two ---
 *
 * The Elves in accounting are thankful for your help; one of them even offers
 * you a starfish coin they had left over from a past vacation. They offer you a
 * second one if you can find three numbers in your expense report that meet the
 * same criteria.
 * 
 * Using the above example again, the three entries that sum to 2020 are 979,
 * 366, and 675. Multiplying them together produces the answer, 241861950.
 * 
 * In your expense report, what is the product of the three entries that sum to
 * 2020?
 */

#include <stdio.h>

#define INPUT_SIZE 200

int main(int argc, char **argv) {
  int expense, expenses[INPUT_SIZE], i = 0, j, k, l, result;

  while(scanf("%d\n", &expense) != EOF) {
    expenses[i++] = expense;
  }

  for(j = 0; j < INPUT_SIZE - 1; j++) {
    for(k = j + 1; k < INPUT_SIZE - 2; k++) {
      for(l = k + 1; l < INPUT_SIZE; l++) {
        if(expenses[j] + expenses[k] + expenses[l] == 2020) {
          result = expenses[j] * expenses[k] * expenses[l];
          goto done;
        }
      }
    }
  }

done:

  printf("Result of multiplying the three entries: %d\n", result);

  return 0;
}
