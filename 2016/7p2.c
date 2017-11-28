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
 * --- Part Two ---
 * 
 * You would also like to know which IPs support SSL (super-secret listening).
 * 
 * An IP supports SSL if it has an Area-Broadcast Accessor, or ABA, anywhere in
 * the supernet sequences (outside any square bracketed sections), and a
 * corresponding Byte Allocation Block, or BAB, anywhere in the hypernet
 * sequences. An ABA is any three-character sequence which consists of the same
 * character twice with a different character between them, such as xyx or aba.
 * A corresponding BAB is the same characters but in reversed positions: yxy and
 * bab, respectively.
 * 
 * For example:
 * 
 * - aba[bab]xyz supports SSL (aba outside square brackets with corresponding
 *   bab within square brackets).
 * - xyx[xyx]xyx does not support SSL (xyx, but no corresponding yxy).
 * - aaa[kek]eke supports SSL (eke in supernet with corresponding kek in
 *   hypernet; the aaa sequence is not related, because the interior character
 *   must be different).
 * - zazbz[bzb]cdb supports SSL (zaz has no corresponding aza, but zbz has a
 *   corresponding bzb, even though zaz and zbz overlap).
 *
 * How many IPs in your puzzle input support SSL?
 */

#include "stdio.h"
#include "regex.h"
#include "stdlib.h"

int main(int argc, char const *argv[])
{
  char buf[200];
  int sum = 0;
  regex_t match_right, match_left;

  regcomp(&match_right, "\\([a-z]\\)\\([^\\1]\\)\\1[a-z]*\\[\\([a-z]*\\][a-z]*\\[\\)*[a-z]*\\2\\1\\2", REG_BASIC);
  regcomp(&match_left, "\\([a-z]\\)\\([^\\1]\\)\\1[a-z]*\\]\\([a-z]*\\[[a-z]*\\]\\)*[a-z]*\\2\\1\\2", REG_BASIC);

  while(fgets(buf, 200, stdin) != NULL) {
    if (!(regexec(&match_right, buf, 0, NULL, 0) &&
          regexec(&match_left, buf, 0, NULL, 0))) sum++; 
  }

  printf("IPs that support TLS: %d\n", sum);

  return 0;
}
