/**
 * --- Day 6: Memory Reallocation ---
 * 
 * A debugger program here is having an issue: it is trying to repair a memory
 * reallocation routine, but it keeps getting stuck in an infinite loop.
 * 
 * In this area, there are sixteen memory banks; each memory bank can hold any
 * number of blocks. The goal of the reallocation routine is to balance the
 * blocks between the memory banks.
 * 
 * The reallocation routine operates in cycles. In each cycle, it finds the
 * memory bank with the most blocks (ties won by the lowest-numbered memory
 * bank) and redistributes those blocks among the banks. To do this, it removes
 * all of the blocks from the selected bank, then moves to the next (by index)
 * memory bank and inserts one of the blocks. It continues doing this until it
 * runs out of blocks; if it reaches the last memory bank, it wraps around to
 * the first one.
 * 
 * The debugger would like to know how many redistributions can be done before a
 * blocks-in-banks configuration is produced that has been seen before.
 * 
 * For example, imagine a scenario with only four memory banks:
 * 
 * - The banks start with 0, 2, 7, and 0 blocks. The third bank has the most
 *   blocks, so it is chosen for redistribution.
 * - Starting with the next bank (the fourth bank) and then continuing to the
 *   first bank, the second bank, and so on, the 7 blocks are spread out over
 *   the memory banks. The fourth, first, and second banks get two blocks each,
 *   and the third bank gets one back. The final result looks like this: 2 4 1
 *   2.
 * - Next, the second bank is chosen because it contains the most blocks (four).
 *   Because there are four memory banks, each gets one block. The result is: 3
 *   1 2 3.
 * - Now, there is a tie between the first and fourth memory banks, both of
 *   which have three blocks. The first bank wins the tie, and its three blocks
 *   are distributed evenly over the other three banks, leaving it with none: 0
 *   2 3 4.
 * - The fourth bank is chosen, and its four blocks are distributed such that
 *   each of the four banks receives one: 1 3 4 1.
 * - The third bank is chosen, and the same thing happens: 2 4 1 2.
 *
 * At this point, we've reached a state we've seen before: 2 4 1 2 was already
 * seen. The infinite loop is detected after the fifth block redistribution
 * cycle, and so the answer in this example is 5.
 * 
 * Given the initial block counts in your puzzle input, how many redistribution
 * cycles must be completed before a configuration is produced that has been
 * seen before?
 *
 * --- Part Two ---
 *
 * Out of curiosity, the debugger would also like to know the size of the loop:
 * starting from a state that has already been seen, how many block
 * redistribution cycles must be performed before that same state is seen
 * again?
 *
 * In the example above, 2 4 1 2 is seen again after four cycles, and so the
 * answer in that example would be 4.
 *
 * How many cycles are in the infinite loop that arises from the configuration
 * in your puzzle input?
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define BANK_COUNT 16

int main(int argc, char const *argv[])
{
  uint64_t banks[BANK_COUNT], i = 0, j, max_i, max_v, dup0 = 0, dup1 = 0;
  char **states = NULL;
  int states_count = 0, cycles = 0;
  char tmp[100];

  while(scanf("%llu", banks + i++) != EOF);

  while(dup0 == 0 || dup1 == 0)
  {
    cycles++;

    // Find index of largest number
    for (i = 0, max_v = 0; i < BANK_COUNT; ++i)
    {
      if (banks[i] > max_v)
      {
        max_i = i;
        max_v = banks[i];
      }
    }

    banks[max_i] = 0;
    j = max_i;

    // Redistribute
    while(max_v > 0)
    {
      j = (j + 1) % BANK_COUNT;
      banks[j]++;
      max_v--;
    }

    sprintf(tmp, "%llu%llu%llu%llu%llu%llu%llu%llu"
        "%llu%llu%llu%llu%llu%llu%llu%llu", banks[0], banks[1], banks[2],
        banks[3], banks[4], banks[5], banks[6], banks[7], banks[8], banks[9],
        banks[10], banks[11], banks[12], banks[13], banks[14], banks[15]);

    // Make room for the new string and insert it in states
    states = realloc(states, (states_count + 1) * sizeof(char *));
    states[states_count] = malloc(strlen(tmp) + 1);
    strcpy(states[states_count], tmp);

    states_count++;

    for (i = 0; i < states_count - 1; ++i)
    {
      if (strcmp(tmp, states[i]) == 0)
      {
        if (dup0 == 0)
        {
          dup0 = i;
          printf("First duplicate at index %llu: %s\n", dup0, states[dup0]);
        }
      }
    }

    for (i = dup0 + 1; i < states_count - 1; ++i)
    {
      if (strcmp(states[dup0], states[i]) == 0)
      {
        if (dup1 == 0)
        {
          dup1 = i;
          printf("Second duplicate at index %llu: %s\n", dup1, states[dup1]);
        }
      }
    }
  }

  for (i = 0; i < states_count; ++i)
    free(states[i]);
  free(states);

  printf("Cycles: %llu\n", dup1 - dup0);

  return 0;
}
