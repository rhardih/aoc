#include "stdio.h"
#include "string.h"

void show_display(int d[6][50]) {
  for (int row = 0; row < 6; row++)
  {
    for (int col = 0; col < 50; col++)
    {
      printf("%d", d[row][col]);
    }
    printf("\n");
  }
  printf("\n");
}

int main(int argc, char const *argv[])
{
  char buf[100] = "";
  int display[6][50] = { 0 };
  int lit_pixels = 0, i, w, h, tmp, amount, row, col;

  while(fgets(buf, 100, stdin) != NULL)
  {
    if(strncmp("rect", buf, 4) == 0) {
      sscanf(buf, "rect %dx%d", &w, &h);

      for (row = 0; row < h; row++)
      {
        for (col = 0; col < w; col++)
        {
          display[row][col] = 1;
        }
      }

    } else if (strncmp("rotate row", buf, 10) == 0) {
      sscanf(buf, "rotate row y=%d by %d", &row, &amount);

      for (i = 0; i < amount; i++)
      {
        // shift all elements one position to the right and
        // wrap around last element to first.
        tmp = display[row][49];
        for (col = 49; col > 0; col--)
        {
          display[row][col] = display[row][col - 1];
        }
        display[row][0] = tmp;
      }
    } else {
      sscanf(buf, "rotate column x=%d by %d", &col, &amount);

      for (i = 0; i < amount; i++)
      {
        // shift all elements one position down and
        // wrap around last element to first.
        tmp = display[5][col];
        for (row = 5; row > 0; row--)
        {
          display[row][col] = display[row - 1][col];
        }
        display[0][col] = tmp;
      }
    }

  }

  show_display(display);

  for (row = 0; row < 6; row++)
  {
    for (col = 0; col < 50; col++)
    {
      lit_pixels += display[row][col];
    }
  }

  printf("%d pixels should be lit.\n", lit_pixels);

  return 0;
}
