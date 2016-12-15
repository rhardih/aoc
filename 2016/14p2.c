#include "stdio.h"
#include "openssl/md5.h"
#include "string.h"

#define MD5_LEN 33
#define HBUF_SIZE 1001

char input[] = "zpqevtbw";

void md5(char *s, char *res) {
  unsigned char digest[MD5_DIGEST_LENGTH];
  char current[MD5_LEN];
  int i, j;

  strcpy(current, s);

  for (i = 0; i < 2017; i++)
  {
    MD5((const unsigned char *)current, strlen((const char *)current), (unsigned char *)&digest);

    for(j = 0; j < 16; j++)
      sprintf(&current[j*2], "%02x", (unsigned int)digest[j]);
  }

  for(i = 0; i < 16; i++)
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
