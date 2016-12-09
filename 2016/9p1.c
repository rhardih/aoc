#include "stdio.h"

int main(int argc, char const *argv[])
{
  char c;
  int length = 0, index = 0, a, b;

  while(scanf("%c", &c) != EOF) {
    if (c == '(') {
      scanf("%dx%d)", &a, &b);
      length += a * b;
      fseek(stdin, a, SEEK_CUR);
    } else if (c == '\n') {
      // skip whitespace
    } else {
      length++;
    }
  }

  printf("Decompressed length of file: %d\n", length);

  return 0;
}
