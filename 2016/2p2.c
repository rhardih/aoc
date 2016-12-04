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
  int col = 0;
  int row = 2;

  while (scanf("%c", &in) != EOF) {
    switch (in) {
      case 'U':
        if (row > 0) row -= moves[row - 1][col];
        break;
      case 'R':
        if (col < 4) col += moves[row][col + 1];
        break;
      case 'D':
        if (row < 4) row += moves[row + 1][col];
        break;
      case 'L':
        if (col > 0) col -= moves[row][col - 1];
        break;
      case '\n':
        code[code_index] = keypad[row][col];
        code_index++;
        break;
    }
  }

  printf("The bathroom code is: %s\n", code);

  return 0;
}
