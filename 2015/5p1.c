/**
 * --- Day 5: Doesn't He Have Intern-Elves For This? ---
 * 
 * Santa needs help figuring out which strings in his text file are naughty or
 * nice.
 * 
 * A nice string is one with all of the following properties:
 * 
 * - It contains at least three vowels (aeiou only), like aei, xazegov, or
 *   aeiouaeiouaeiou.
 * - It contains at least one letter that appears twice in a row, like xx,
 *   abcdde (dd), or aabbccdd (aa, bb, cc, or dd).
 * - It does not contain the strings ab, cd, pq, or xy, even if they are part of
 *   one of the other requirements.
 *
 * For example:
 *
 * - ugknbfddgicrmopn is nice because it has at least three vowels
 *   (u...i...o...), a double letter (...dd...), and none of the disallowed
 *   substrings.
 * - aaa is nice because it has at least three vowels and a double letter, even
 *   though the letters used by different rules overlap.
 * - jchzalrnumimnmhp is naughty because it has no double letter.
 * - haegwjzuvuyypxyu is naughty because it contains the string xy.
 * - dvszwmarrgswjxmb is naughty because it contains only one vowel.
 *
 * How many strings are nice?
 */

#include <stdio.h>
#include <regex.h>

int main(int argc, char const *argv[])
{
  char buf[17]; // 16 characters and \0
  regex_t vowels, twice, nono;
  int nice = 0;

  regcomp(&vowels, "[aeiou].*[aeiou].*[aeiou]", REG_BASIC);
  regcomp(&twice, "\\(.\\)\\1", REG_BASIC);
  regcomp(&nono, "ab|cd|pq|xy", REG_EXTENDED);

  while(scanf("%s", buf) != EOF)
  {
    if (regexec(&vowels, buf, 0, NULL, 0) == 0 &&
        regexec(&twice, buf, 0, NULL, 0) == 0 &&
        regexec(&nono, buf, 0, NULL, 0) != 0)
      nice++;
  }

  printf("There are %d nice strings.\n", nice);

  return 0;
}
