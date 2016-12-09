#include "stdio.h"

int main(int argc, char const *argv[])
{
  char c;
  int index = 0, a, b;
  long i, pos, length = 0;

  fseek(stdin, 0, SEEK_END);
  long input_size = ftell(stdin);
  int multipliers[input_size], current_multiplier;
  for (i = 0; i < input_size; i++) multipliers[i] = 1;

  rewind(stdin);

  while(scanf("%c", &c) != EOF) {
    pos = ftell(stdin);
    current_multiplier = multipliers[pos - 1];

    if (c == '(') {
      scanf("%dx%d)", &a, &b);
      pos = ftell(stdin);

      for (i = pos; i < pos + a && i < input_size; i++)
      {
        multipliers[i] = current_multiplier * b;
      }
    } else if (c == '\n') {
      // skip whitespace
    } else {
      length += current_multiplier;
    }
  }

  printf("Decompressed length of file: %lu\n", length);

  return 0;
}
