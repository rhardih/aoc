#include "stdio.h"

int max(int a, int b) {
  return a > b ? a : b;
}

int main(int argc, char const *argv[])
{
  int sum = 0, l, w, h;

  while(scanf("%dx%dx%d", &l, &w, &h) != EOF) {
    sum += 2 * (l + w + h - max(l, max(w, h))) + l * w * h;
  }

  printf("The elves should order %d feet of ribbon.\n", sum); 

  return 0;
}
