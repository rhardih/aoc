#include "stdio.h"

enum position {
  ONE, TWO, THREE,
  FOUR, FIVE, SIX,
  SEVEN, EIGHT, NINE
};

int main(int argc, char const *argv[])
{

  char in;
  int code = 0;
  int pos = FIVE;

  while (scanf("%c", &in) != EOF) {
    switch (in) {
      case 'U':
        if (pos > THREE) pos -= 3;
        break;
      case 'R':
        if (pos != THREE && pos != SIX && pos != NINE) pos += 1;
        break;
      case 'D':
        if (pos < SEVEN) pos += 3;
        break;
      case 'L':
        if (pos != ONE && pos != FOUR && pos != SEVEN) pos -= 1;
        break;
      case '\n':
        code += pos + 1;
        code *= 10; // shift digit one right
        break;
    }
  }

  // final newline causing one too many multiplications
  code /= 10;

  printf("The bathroom code is: %d\n", code);

  return 0;
}
