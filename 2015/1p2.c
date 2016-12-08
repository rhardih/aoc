#include "stdio.h"

int main(int argc, char const *argv[])
{
  char instruction;
  int floor = 0;
  int position = 1;

  while(scanf("%c", &instruction) != EOF) {
    instruction == '(' ? floor++ : floor--;

    if (floor < 0) break;
    position++;
  }

  printf("Santa enters the basement at character position: %d\n", position); 

  return 0;
}
