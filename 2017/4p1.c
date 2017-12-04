/**
 * --- Day 4: High-Entropy Passphrases ---
 * 
 * A new system policy has been put in place that requires all accounts to use a
 * passphrase instead of simply a password. A passphrase consists of a series of
 * words (lowercase letters) separated by spaces.
 * 
 * To ensure security, a valid passphrase must contain no duplicate words.
 * 
 * For example:
 * 
 * - aa bb cc dd ee is valid.
 * - aa bb cc dd aa is not valid - the word aa appears more than once.
 * - aa bb cc dd aaa is valid - aa and aaa count as different words.
 * 
 * The system's full passphrase list is available as your puzzle input. How many
 * passphrases are valid?
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
  char *line = NULL;
  char *to_free0, *to_free1, *line_dup0, *line_dup1, *tmp0, *tmp1;
  size_t cap;
  int valid, count = 0;

  while (getline(&line, &cap, stdin) != -1)
  {
    valid = 1;

    to_free0 = line_dup0 = strdup(line);

    while((tmp0 = strsep(&line_dup0, " \n")) != NULL && valid != 0)
    {
      if (*tmp0 != '\0')
      {
        to_free1 = line_dup1 = strdup(line_dup0);

        while((tmp1 = strsep(&line_dup1, " \n")) != NULL && valid != 0)
        {
          if (*tmp1 != '\0')
            valid = strcmp(tmp0, tmp1);
        }

        free(to_free1);
      }
    }

    free(to_free0);

    if (valid != 0)
      count++;
  }

  printf("Number of valid passphrases: %d\n", count);

  return 0;
}
