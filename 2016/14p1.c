/**
 * --- Day 14: One-Time Pad ---
 * 
 * In order to communicate securely with Santa while you're on this mission,
 * you've been using a one-time pad that you generate using a pre-agreed
 * algorithm. Unfortunately, you've run out of keys in your one-time pad, and so
 * you need to generate some more.
 * 
 * To generate keys, you first get a stream of random data by taking the MD5 of
 * a pre-arranged salt (your puzzle input) and an increasing integer index
 * (starting with 0, and represented in decimal); the resulting MD5 hash should
 * be represented as a string of lowercase hexadecimal digits.
 * 
 * However, not all of these MD5 hashes are keys, and you need 64 new keys for
 * your one-time pad. A hash is a key only if:
 * 
 * - It contains three of the same character in a row, like 777. Only consider
 *   the first such triplet in a hash.
 * - One of the next 1000 hashes in the stream contains that same character five
 *   times in a row, like 77777.
 *
 * Considering future hashes for five-of-a-kind sequences does not cause those
 * hashes to be skipped; instead, regardless of whether the current hash is a
 * key, always resume testing for keys starting with the very next hash.
 * 
 * For example, if the pre-arranged salt is abc:
 * 
 * - The first index which produces a triple is 18, because the MD5 hash of
 *   abc18 contains ...cc38887a5.... However, index 18 does not count as a key
 *   for your one-time pad, because none of the next thousand hashes (index 19
 *   through index 1018) contain 88888.
 * - The next index which produces a triple is 39; the hash of abc39 contains
 *   eee. It is also the first key: one of the next thousand hashes (the one at
 *   index 816) contains eeeee.
 * - None of the next six triples are keys, but the one after that, at index 92,
 *   is: it contains 999 and index 200 contains 99999.
 * - Eventually, index 22728 meets all of the criteria to generate the 64th key.
 *
 * So, using our example salt of abc, index 22728 produces the 64th key.
 * 
 * Given the actual salt in your puzzle input, what index produces your 64th
 * one-time pad key?
 */

#include "stdio.h"
#include "openssl/md5.h"
#include "string.h"

#define MD5_LEN 33
#define HBUF_SIZE 1001

char input[] = "zpqevtbw";

void md5(char *s, char *res) {
  unsigned char digest[MD5_DIGEST_LENGTH];

  MD5((const unsigned char *)s, strlen((const char *)s), (unsigned char *)&digest);

  for(int i = 0; i < 16; i++)
    sprintf(&res[i*2], "%02x", (unsigned int)digest[i]);
}

int main(int argc, char const *argv[])
{
  char candidate[30];
  char hashes[HBUF_SIZE][MD5_LEN];
  char c;
  int keys = 0, i = 0, j, k, l, m, toak, foak;

  while (keys != 64) {
    sprintf(candidate, "%s%d", input, i);

    md5(candidate, hashes[i % HBUF_SIZE]);

    if (i >= 1000) {
      toak = 0;
      foak = 0;
      j = i - 1000;
      c = 0;

      for (k = 2; k < MD5_LEN; k++) {
        if (hashes[j % HBUF_SIZE][k] == hashes[j % HBUF_SIZE][k - 1] &&
            hashes[j % HBUF_SIZE][k] == hashes[j % HBUF_SIZE][k - 2]) {
          toak = 1;
          c = hashes[j % HBUF_SIZE][k];
          break;
        }
      }

      if (toak) {
        for (l = 1; l <= 1000; l++) {
          for (m = 4; m < MD5_LEN; m++) {
            if (hashes[(j + l) % HBUF_SIZE][m] == c &&
                hashes[(j + l) % HBUF_SIZE][m - 1] == c &&
                hashes[(j + l) % HBUF_SIZE][m - 2] == c &&
                hashes[(j + l) % HBUF_SIZE][m - 3] == c &&
                hashes[(j + l) % HBUF_SIZE][m - 4] == c)
              foak = 1;
          }
          if (foak) break;
        }
      }

      if (toak && foak) keys++;
    }

    i++;
  }

  printf("Index %d produces 64th key.\n", j);

  return 0;
}
