/**
 * --- Part Two ---
 *
 * To completely determine whether you have enough adapters, you'll need to
 * figure out how many different ways they can be arranged. Every arrangement
 * needs to connect the charging outlet to your device. The previous rules about
 * when adapters can successfully connect still apply.
 * 
 * The first example above (the one that starts with 16, 10, 15) supports the
 * following arrangements:
 * 
 * (0), 1, 4, 5, 6, 7, 10, 11, 12, 15, 16, 19, (22)
 * (0), 1, 4, 5, 6, 7, 10, 12, 15, 16, 19, (22)
 * (0), 1, 4, 5, 7, 10, 11, 12, 15, 16, 19, (22)
 * (0), 1, 4, 5, 7, 10, 12, 15, 16, 19, (22)
 * (0), 1, 4, 6, 7, 10, 11, 12, 15, 16, 19, (22)
 * (0), 1, 4, 6, 7, 10, 12, 15, 16, 19, (22)
 * (0), 1, 4, 7, 10, 11, 12, 15, 16, 19, (22)
 * (0), 1, 4, 7, 10, 12, 15, 16, 19, (22)
 *
 * (The charging outlet and your device's built-in adapter are shown in
 * parentheses.) Given the adapters from the first example, the total number of
 * arrangements that connect the charging outlet to your device is 8.
 * 
 * The second example above (the one that starts with 28, 33, 18) has many
 * arrangements. Here are a few:
 * 
 * (0), 1, 2, 3, 4, 7, 8, 9, 10, 11, 14, 17, 18, 19, 20, 23, 24, 25, 28, 31,
 * 32, 33, 34, 35, 38, 39, 42, 45, 46, 47, 48, 49, (52)
 * 
 * (0), 1, 2, 3, 4, 7, 8, 9, 10, 11, 14, 17, 18, 19, 20, 23, 24, 25, 28, 31,
 * 32, 33, 34, 35, 38, 39, 42, 45, 46, 47, 49, (52)
 * 
 * (0), 1, 2, 3, 4, 7, 8, 9, 10, 11, 14, 17, 18, 19, 20, 23, 24, 25, 28, 31,
 * 32, 33, 34, 35, 38, 39, 42, 45, 46, 48, 49, (52)
 * 
 * (0), 1, 2, 3, 4, 7, 8, 9, 10, 11, 14, 17, 18, 19, 20, 23, 24, 25, 28, 31,
 * 32, 33, 34, 35, 38, 39, 42, 45, 46, 49, (52)
 * 
 * (0), 1, 2, 3, 4, 7, 8, 9, 10, 11, 14, 17, 18, 19, 20, 23, 24, 25, 28, 31,
 * 32, 33, 34, 35, 38, 39, 42, 45, 47, 48, 49, (52)
 * 
 * (0), 3, 4, 7, 10, 11, 14, 17, 20, 23, 25, 28, 31, 34, 35, 38, 39, 42, 45,
 * 46, 48, 49, (52)
 * 
 * (0), 3, 4, 7, 10, 11, 14, 17, 20, 23, 25, 28, 31, 34, 35, 38, 39, 42, 45,
 * 46, 49, (52)
 * 
 * (0), 3, 4, 7, 10, 11, 14, 17, 20, 23, 25, 28, 31, 34, 35, 38, 39, 42, 45,
 * 47, 48, 49, (52)
 * 
 * (0), 3, 4, 7, 10, 11, 14, 17, 20, 23, 25, 28, 31, 34, 35, 38, 39, 42, 45,
 * 47, 49, (52)
 * 
 * (0), 3, 4, 7, 10, 11, 14, 17, 20, 23, 25, 28, 31, 34, 35, 38, 39, 42, 45,
 * 48, 49, (52)
 *
 * In total, this set of adapters can connect the charging outlet to your device
 * in 19208 distinct arrangements.
 * 
 * You glance back down at your bag and try to remember why you brought so many
 * adapters; there must be more than a trillion valid ways to arrange them!
 * Surely, there must be an efficient way to count the arrangements.
 * 
 * What is the total number of distinct ways you can arrange the adapters to
 * connect the charging outlet to your device?
 */

#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 103
#define TOTAL_SIZE 105

int ratings[TOTAL_SIZE] = { 0 };
uint64_t memo[TOTAL_SIZE] = { 0 };

uint64_t count(int i) {
  if (i < 0) return 0;
  if (memo[i]) return memo[i];

  uint64_t c = 0;

  if (i == 0) {
    c = 1;
  } else {
    if (ratings[i] - ratings[i - 1] <= 3) {
      c += count(i - 1);
    }
    if (ratings[i] - ratings[i - 2] <= 3) {
      c += count(i - 2);
    }
    if (ratings[i] - ratings[i - 3] <= 3) {
      c += count(i - 3);
    }
  }

  memo[i] = c;

  return c;
}

int intcmp(const void *a, const void *b) {
  return (*(int*)a - *(int*)b);
}

int main(int argc, char **argv) {
  int i = 0, one_diffs = 0, three_diffs = 0;

  while(scanf("%d\n", &ratings[1 + i++]) != EOF) {}

  // Sort only input part
  qsort(ratings + 1, INPUT_SIZE, sizeof(int), intcmp);

  // Set first to source and last to sink
  ratings[0] = 0;
  ratings[TOTAL_SIZE - 1] = ratings[TOTAL_SIZE - 2] + 3;

  printf(
    "Total number of distinct ways to arrange the adapters: %llu\n",
    count(TOTAL_SIZE - 1)
  );

  return 0;
}
