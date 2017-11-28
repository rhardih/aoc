/**
 * --- Day 7: Internet Protocol Version 7 ---
 * 
 * While snooping around the local network of EBHQ, you compile a list of IP
 * addresses (they're IPv7, of course; IPv6 is much too limited). You'd like to
 * figure out which IPs support TLS (transport-layer snooping).
 * 
 * An IP supports TLS if it has an Autonomous Bridge Bypass Annotation, or ABBA.
 * An ABBA is any four-character sequence which consists of a pair of two
 * different characters followed by the reverse of that pair, such as xyyx or
 * abba. However, the IP also must not have an ABBA within any hypernet
 * sequences, which are contained by square brackets.
 * 
 * For example:
 * 
 * - abba[mnop]qrst supports TLS (abba outside square brackets).
 * - abcd[bddb]xyyx does not support TLS (bddb is within square brackets, even
 *   though xyyx is outside square brackets).
 * - aaaa[qwer]tyui does not support TLS (aaaa is invalid; the interior
 *   characters must be different).
 * - ioxxoj[asdfgh]zxcvbn supports TLS (oxxo is outside square brackets, even
 *   though it's within a larger string).
 * 
 * How many IPs in your puzzle input support TLS?
 */

#include "stdio.h"

int main(int argc, char const *argv[])
{
  char abba[] = "...";
  int sum = 0;
  int hyper = 0;
  int valid = 0;
  int inside = 0;

  // Store number of bytes in input
  fseek(stdin, 0, SEEK_END);
  long fp = ftell(stdin);
  rewind(stdin);

  while(fp > 4) {
    // scan for every single character despite reading four at a time
    fseek(stdin, -fp--, SEEK_END);
    scanf("%4c", abba);

    if (abba[0] - abba[3] == 0 &&
        abba[1] - abba[2] == 0 &&
        abba[0] != abba[1]) {
      hyper |= inside;
      valid = 1 - hyper;
    }

    if (abba[0] == '[') inside = 1;
    if (abba[0] == ']') inside = 0;

    // new ip
    if (abba[0] == '\n')  {
      sum += valid;

      valid = 0;
      hyper = 0;
    }
  }

  printf("IPs that support TLS: %d\n", sum);

  return 0;
}
