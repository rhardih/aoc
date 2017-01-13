/**
 * --- Day 20: Firewall Rules ---
 *
 * You'd like to set up a small hidden computer here so you can use it to get
 * back into the network later. However, the corporate firewall only allows
 * communication with certain external IP addresses.
 *
 * You've retrieved the list of blocked IPs from the firewall, but the list
 * seems to be messy and poorly maintained, and it's not clear which IPs are
 * allowed. Also, rather than being written in dot-decimal notation, they are
 * written as plain 32-bit integers, which can have any value from 0 through
 * 4294967295, inclusive.
 *
 * For example, suppose only the values 0 through 9 were valid, and that you
 * retrieved the following blacklist:
 *
 * 5-8
 * 0-2
 * 4-7
 *
 * The blacklist specifies ranges of IPs (inclusive of both the start and end
 * value) that are not allowed. Then, the only IPs that this firewall allows are
 * 3 and 9, since those are the only numbers not in any range.
 *
 * Given the list of blocked IPs you retrieved from the firewall (your puzzle
 * input), what is the lowest-valued IP that is not blocked?
 *
 * --- Part Two ---
 *
 *  How many IPs are allowed by the blacklist?
 */

#include <stdio.h>
#include <limits.h>

#define max(x, y) ((x) > (y) ? (x) : (y))

int main(int argc, char const *argv[])
{
  unsigned int sfrom, sto, from, to, sum = 0, i;

  // Input is sorted out of program by from value, by piping through "sort -n"
  // first.

  // Populate initial interval
  scanf("%u-%u\n", &from, &to);

  while(scanf("%u-%u\n", &sfrom, &sto) != EOF) {
    if (sfrom > to)
    {
      // Jumped a gap, add difference, non-inclusive, to sum and move current
      // interval ahead.
      sum += sfrom - to - 1;

      from = sfrom;
      to = sto;
    }
    else
    {
      to = max(to, sto);
    }
  }

  // If there's any leftover interval add it to sum
  sum += UINT_MAX - to;

  printf("Number of IPs allowed by blacklist: %u\n", sum);

  return 0;
}
