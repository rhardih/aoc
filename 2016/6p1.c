#include "stdio.h"

int main(int argc, char const *argv[])
{
  int char_frequencies[8][26] = {0};
  char a, b ,c, d, e, f, g, h;
  int offset = (int)'a';
  char msg[] = "........";
  int highest_index = 0;

  while(scanf("%c%c%c%c%c%c%c%c\n", &a, &b, &c, &d, &e, &f, &g, &h) != EOF)
  {
    char_frequencies[0][a - offset]++;
    char_frequencies[1][b - offset]++;
    char_frequencies[2][c - offset]++;
    char_frequencies[3][d - offset]++;
    char_frequencies[4][e - offset]++;
    char_frequencies[5][f - offset]++;
    char_frequencies[6][g - offset]++;
    char_frequencies[7][h - offset]++;
  }

  for (size_t i = 0; i < 8; i++)
  {
    for (size_t j = 0; j < 26; j++)
    {
      if (char_frequencies[i][j] > char_frequencies[i][highest_index])
      {
        highest_index = j;
      }
    }

    msg[i] = highest_index + offset;
    highest_index = 0;
  }

  printf("Error corrected message: %s\n", msg);

  return 0;
}
