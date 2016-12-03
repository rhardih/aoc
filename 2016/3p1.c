#include "stdio.h"

int main(int argc, char const *argv[])
{
  int a, b, c;
  int possible = 0;

  while(scanf("  %d  %d  %d", &a, &b, &c) != EOF) {
    if (a + b > c && a + c > b && b + c > a) possible++;
  }

  printf("Possible triangles: %d\n", possible);

  return 0;
}
