#include "stdio.h"

int main(int argc, char const *argv[])
{
  int a, b, c, d, e, f, g, h, i;
  int possible = 0;

  while (1) {
    if (scanf("  %d  %d  %d", &a, &d, &g) == EOF) break;
    scanf("  %d  %d  %d", &b, &e, &h);
    scanf("  %d  %d  %d", &c, &f, &i);

    if (a + b > c && a + c > b && b + c > a) possible++;
    if (d + e > f && d + f > e && e + f > d) possible++;
    if (g + h > i && g + i > h && h + i > g) possible++;
  }

  printf("Possible triangles: %d\n", possible);

  return 0;
}
