#include "stdio.h"

char keypad[5][5] = {
  {'0', '0', '1', '0', '0'},
  {'0', '2', '3', '4', '0'},
  {'5', '6', '7', '8', '9'},
  {'0', 'A', 'B', 'C', '0'},
  {'0', '0', 'D', '0', '0'}
};

int moves[5][5] = {
  {0, 0, 1, 0, 0},
  {0, 1, 1, 1, 0},
  {1, 1, 1, 1, 1},
  {0, 1, 1, 1, 0},
  {0, 0, 1, 0, 0}
};

int main(int argc, char const *argv[])
{
  char in;
  char code[] = "12345";
  int code_index = 0;
  int x_pos = 0;
  int y_pos = 2;

  while (scanf("%c", &in) != EOF) {
    switch (in) {
      case 'U':
        if (y_pos > 0) y_pos -= moves[x_pos][y_pos - 1];
        break;
      case 'R':
        if (x_pos < 4) x_pos += moves[x_pos + 1][y_pos];
        break;
      case 'D':
        if (y_pos < 4) y_pos += moves[x_pos][y_pos + 1];
        break;
      case 'L':
        if (x_pos > 0) x_pos -= moves[x_pos - 1][y_pos];
        break;
      case '\n':
        code[code_index] = keypad[x_pos][y_pos];
        code_index++;
        break;
    }
  }

  printf("The bathroom code is: %s\n", code);

  return 0;
}
