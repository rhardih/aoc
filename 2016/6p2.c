/**
 * --- Day 6: Signals and Noise ---
 * 
 * Something is jamming your communications with Santa. Fortunately, your signal
 * is only partially jammed, and protocol in situations like this is to switch
 * to a simple repetition code to get the message through.
 * 
 * In this model, the same message is sent repeatedly. You've recorded the
 * repeating message signal (your puzzle input), but the data seems quite
 * corrupted - almost too badly to recover. Almost.
 * 
 * All you need to do is figure out which character is most frequent for each
 * position. For example, suppose you had recorded the following messages:
 * 
 * eedadn
 * drvtee
 * eandsr
 * raavrd
 * atevrs
 * tsrnev
 * sdttsa
 * rasrtv
 * nssdts
 * ntnada
 * svetve
 * tesnvt
 * vntsnd
 * vrdear
 * dvrsen
 * enarar
 *
 * The most common character in the first column is e; in the second, a; in the
 * third, s, and so on. Combining these characters returns the error-corrected
 * message, easter.
 * 
 * --- Part Two ---
 *
 *  Of course, that would be the message - if you hadn't agreed to use a
 *  modified repetition code instead.
 *
 *  In this modified code, the sender instead transmits what looks like random
 *  data, but for each character, the character they actually want to send is
 *  slightly less likely than the others. Even after signal-jamming noise, you
 *  can look at the letter distributions in each column and choose the least
 *  common letter to reconstruct the original message.
 *
 *  In the above example, the least common character in the first column is a;
 *  in the second, d, and so on. Repeating this process for the remaining
 *  characters produces the original message, advent.
 *
 *  Given the recording in your puzzle input and this new decoding methodology,
 *  what is the original message that Santa is trying to send?
 */

#include "stdio.h"

int main(int argc, char const *argv[])
{
  int char_frequencies[8][26] = {0};
  char a, b ,c, d, e, f, g, h;
  int offset = (int)'a';
  char msg[] = "........";
  int highest_index = 25;

  while(scanf("%c%c%c%c%c%c%c%c\n", &a, &b, &c, &d, &e, &f, &g, &h) != EOF)
  {
    char_frequencies[0][a - offset]++;
    char_frequencies[1][b - offset]++;
    char_frequencies[2][c - offset]++;
    char_frequencies[3][d - offset]++;
    char_frequencies[4][e - offset]++;
    char_frequencies[5][f - offset]++;
    char_frequencies[6][g - offset]++;
    char_frequencies[7][h - offset]++;
  }

  for (size_t i = 0; i < 8; i++)
  {
    for (size_t j = 0; j < 26; j++)
    {
      if (char_frequencies[i][j] < char_frequencies[i][highest_index])
      {
        highest_index = j;
      }
    }

    msg[i] = highest_index + offset;
    highest_index = 25;
  }

  printf("Error corrected message: %s\n", msg);

  return 0;
}
