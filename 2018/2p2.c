/**
 * --- Day 2: Inventory Management System ---
 *
 * --- Part Two ---
 *
 * Confident that your list of box IDs is complete, you're ready to find the
 * boxes full of prototype fabric.
 * 
 * The boxes will have IDs which differ by exactly one character at the same
 * position in both strings. For example, given the following box IDs:
 * 
 * abcde
 * fghij
 * klmno
 * pqrst
 * fguij
 * axcye
 * wvxyz
 *
 * The IDs abcde and axcye are close, but they differ by two characters (the
 * second and fourth). However, the IDs fghij and fguij differ by exactly one
 * character, the third (h and u). Those must be the correct boxes.
 * 
 * What letters are common between the two correct box IDs? (In the example
 * above, this is found by removing the differing character from either ID,
 * producing fgij.)
 */

#include <stdio.h>
#include <stdlib.h>

// $ gwc -Ll 2.in
//  250   26 2.in
#define INPUT_LEN 205
#define LINE_LEN 26

char ids[INPUT_LEN][LINE_LEN + 1];

int sdiff(char *a, char *b, int len) {
  int result = 0;
  for (int i = 0; i < len; ++i) {
    if (a[i] != b[i]) result++;
  }
  return result;
}

int main(int argc, char const *argv[]) {
  int n0, n1;
  int i = 0, j, k, l;
  char *id0, *id1;
  char result[LINE_LEN];

  while(scanf("%s", ids[i]) != EOF) { i++; }

  for (i = 0; i < INPUT_LEN; ++i) {
    id0 = ids[i];
    for (j = i + 1; j < INPUT_LEN; ++j) {
      id1 = ids[j];

      if (sdiff(id0, id1, LINE_LEN) == 1) {
        for (k = 0, l = 0; k < LINE_LEN; ++k) {
          if (id0[k] == id1[k]) {
            result[l++] = id0[k];
          }
        }
        result[l] = '\0';

        goto done;
      }
    }
  }

done:

  printf("The letters common between the two correct box IDs: %s\n", result);

  return 0;
}
