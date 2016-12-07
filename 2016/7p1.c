#include "stdio.h"

int main(int argc, char const *argv[])
{
  char abba[] = "...";
  int sum = 0;
  int hyper = 0;
  int valid = 0;
  int inside = 0;

  // Store number of bytes in input
  fseek(stdin, 0, SEEK_END);
  long fp = ftell(stdin);
  rewind(stdin);

  while(fp > 4) {
    // scan for every single character despite reading four at a time
    fseek(stdin, -fp--, SEEK_END);
    scanf("%4c", abba);

    if (abba[0] - abba[3] == 0 &&
        abba[1] - abba[2] == 0 &&
        abba[0] != abba[1]) {
      hyper |= inside;
      valid = 1 - hyper;
    }

    if (abba[0] == '[') inside = 1;
    if (abba[0] == ']') inside = 0;

    // new ip
    if (abba[0] == '\n')  {
      sum += valid;

      valid = 0;
      hyper = 0;
    }
  }

  printf("IPs that support TLS: %d\n", sum);

  return 0;
}
