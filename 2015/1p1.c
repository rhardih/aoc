#include "stdio.h"

int main(int argc, char const *argv[])
{
  char instruction;
  int floor = 0;

  while(scanf("%c", &instruction) != EOF) {
    instruction == '(' ? floor++ : floor--;
  }

  printf("Instructions take Santa to floor number: %d\n", floor); 

  return 0;
}
