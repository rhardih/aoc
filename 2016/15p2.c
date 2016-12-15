#include <stdio.h>

int main(int argc, char const *argv[])
{
  int discs[7][2];
  int i, count, position, time = 0;
  char line[] = "Disc #%d has %d positions; at time=0, it is at position %d.\n";

  int p1, p2, p3, p4, p5, p6, p7;

  while (scanf(line, &i, &count, &position) != EOF) {
    discs[i - 1][0] = count;
    discs[i - 1][1] = position;
  }

  discs[6][0] = 11;
  discs[6][1] = 0;

  for (i = 0; time == 0; i++)
  {
    p1 = (discs[0][1] + i) % discs[0][0];
    p2 = (discs[1][1] + i + 1) % discs[1][0];
    p3 = (discs[2][1] + i + 2) % discs[2][0];
    p4 = (discs[3][1] + i + 3) % discs[3][0];
    p5 = (discs[4][1] + i + 4) % discs[4][0];
    p6 = (discs[5][1] + i + 5) % discs[5][0];
    p7 = (discs[6][1] + i + 6) % discs[6][0];

    if (p1 + p2 + p3 + p4 + p5 + p6 + p7 == 0) time = i - 1;
  }

  printf("First time to press the button is: %d\n", time);

  return 0;
}
