#include <stdlib.h>
#include <stdio.h>

#include "knot.h"

char *knot_hash(char *input)
{
  int numbers[256], i, j, k, cpos = 0, ssize = 0;
  int length;

  for (i = 0; i < 256; ++i)
    numbers[i] = i;

  for (j = 0; j < 64; ++j)
  {
    k = 0;
    while ((length = input[k++]) != '\0')
    {
      int tmp[length];

      for (i = 0; i < length; ++i)
        tmp[i] = numbers[(cpos + i) % 256];

      for (i = 0; i < length; ++i)
        numbers[(cpos + i) % 256] = tmp[(length - 1) - i];

      cpos += length + ssize;
      ssize++;
    }
  }

  int denseh[16];
  for (i = 0; i < 16; ++i)
  {
    denseh[i] = numbers[16 * i] ^ numbers[16 * i + 1] ^ numbers[16 * i + 2] ^
      numbers[16 * i + 3] ^ numbers[16 * i + 4] ^ numbers[16 * i + 5] ^
      numbers[16 * i + 6] ^ numbers[16 * i + 7] ^ numbers[16 * i + 8] ^
      numbers[16 * i + 9] ^ numbers[16 * i + 10] ^ numbers[16 * i + 11] ^
      numbers[16 * i + 12] ^ numbers[16 * i + 13] ^ numbers[16 * i + 14] ^
      numbers[16 * i + 15];
  }

  char *res = malloc(33 * sizeof(char));
  sprintf(res,
      "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
      denseh[0], denseh[1], denseh[2], denseh[3], denseh[4], denseh[5],
      denseh[6], denseh[7], denseh[8], denseh[9], denseh[10], denseh[11],
      denseh[12], denseh[13], denseh[14], denseh[15]);

  return res;
}

