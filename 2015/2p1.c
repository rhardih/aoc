#include "stdio.h"

int min(int a, int b) {
  return a < b ? a : b;
}

int main(int argc, char const *argv[])
{
  int sum = 0, l, w, h, a, b ,c;

  while(scanf("%dx%dx%d", &l, &w, &h) != EOF) {
    a = l * w;
    b = w * h;
    c = h * l;

    sum += 2 * (a + b + c) + min(a, min(b, c));
  }

  printf("The elves should order %d square feet of paper.\n", sum); 

  return 0;
}
