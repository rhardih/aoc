/**
 * --- Day 5: Alchemical Reduction ---
 *
 * You've managed to sneak in to the prototype suit manufacturing lab. The Elves
 * are making decent progress, but are still struggling with the suit's size
 * reduction capabilities.
 * 
 * While the very latest in 1518 alchemical technology might have solved their
 * problem eventually, you can do better. You scan the chemical composition of
 * the suit's material and discover that it is formed by extremely long polymers
 * (one of which is available as your puzzle input).
 * 
 * The polymer is formed by smaller units which, when triggered, react with each
 * other such that two adjacent units of the same type and opposite polarity are
 * destroyed. Units' types are represented by letters; units' polarity is
 * represented by capitalization. For instance, r and R are units with the same
 * type but opposite polarity, whereas r and s are entirely different types and
 * do not react.
 * 
 * For example:
 * 
 * - In aA, a and A react, leaving nothing behind.
 * - In abBA, bB destroys itself, leaving aA. As above, this then destroys
 *   itself, leaving nothing.
 * - In abAB, no two adjacent units are of the same type, and so nothing
 *   happens.
 * - In aabAAB, even though aa and AA are of the same type, their polarities
 *   match, and so nothing happens.
 *
 * Now, consider a larger example, dabAcCaCBAcCcaDA:
 * 
 * dabAcCaCBAcCcaDA  The first 'cC' is removed.
 * dabAaCBAcCcaDA    This creates 'Aa', which is removed.
 * dabCBAcCcaDA      Either 'cC' or 'Cc' are removed (the result is the same).
 * dabCBAcaDA        No further actions can be taken.
 *
 * After all possible reactions, the resulting polymer contains 10 units.
 * 
 * How many units remain after fully reacting the polymer you scanned?
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
#if 1
  char *line = NULL;
  size_t linecap = 0;
  ssize_t linelen;
  linelen = getline(&line, &linecap, stdin);
  // get rid of newline
  line[linelen - 1] = '\0';
  linelen--;
#else
  char line[] = "dabAcCaCBAcCcaDA";
  ssize_t linelen = strlen(line);
#endif

  int reductions, i, j;
  // Difference in numerical value of the same character with different casing
  int span = 'a' - 'A';

  do {
    reductions = 0;

    for (i = 0, j = 0; i < linelen - 1; i++) {
      if (abs(line[i] - line[i + 1]) == span) {
        i += 1;
        reductions++;
      } else {
        line[j] = line[i];
        j++;
      }
    }

    line[j] = line[i];

    if (reductions) {
      linelen = j + 1;
      line[linelen] = '\0';
    }

  } while(reductions > 0);

  printf("Units remaining after fully reacting the polymer: %lu\n", linelen);

	return 0;
}
