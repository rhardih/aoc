/**
 * --- Part Two ---
 *
 * The final step in breaking the XMAS encryption relies on the invalid number
 * you just found: you must find a contiguous set of at least two numbers in
 * your list which sum to the invalid number from step 1.
 * 
 * Again consider the above example:
 * 
 * 35
 * 20
 * 15
 * 25
 * 47
 * 40
 * 62
 * 55
 * 65
 * 95
 * 102
 * 117
 * 150
 * 182
 * 127
 * 219
 * 299
 * 277
 * 309
 * 576
 *
 * In this list, adding up all of the numbers from 15 through 40 produces the
 * invalid number from step 1, 127. (Of course, the contiguous set of numbers in
 * your actual list might be much longer.)
 * 
 * To find the encryption weakness, add together the smallest and largest number
 * in this contiguous range; in this example, these are 15 and 47, producing 62.
 * 
 * What is the encryption weakness in your XMAS-encrypted list of numbers?
 */

#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 1000
#define PREAMBLE 25

int main(int argc, char **argv) {
  int i = 0, j, k, sum_of_two = 1;
  long numbers[INPUT_SIZE], invalid_number, smallest, largest, sum;

  while(scanf("%ld\n", &numbers[i]) != EOF && sum_of_two) {
    if (i >= PREAMBLE) {
      sum_of_two = 0;

      for(j = 1; j < PREAMBLE + 1; j++) {
        for(k = j + 1; k < PREAMBLE + 1; k++) {
          if (numbers[i - j] != numbers[i - k] &&
              numbers[i - j] + numbers[i - k] == numbers[i]) {
            sum_of_two = 1;
            goto loop_end;
          }
        }
      }
    }

loop_end:

    i++;
  };

  invalid_number = numbers[i - 1];
  i = 0;

  while(i < INPUT_SIZE && sum != invalid_number) {
    sum = numbers[i];
    smallest = numbers[i], largest = numbers[i];
    j = 1;

    while (i + j < INPUT_SIZE && sum < invalid_number) {
      sum += numbers[i + j];

      if (numbers[i + j] < smallest)
        smallest = numbers[i + j];
      if (numbers[i + j] > largest)
        largest = numbers[i + j];

      j++;
    }

    i++;
  }

  printf("Encryption weakness in the XMAS-encrypted list of numbers: %ld\n",
      smallest + largest);

  return 0;
}
