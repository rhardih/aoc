/**
 * --- Day 3: Perfectly Spherical Houses in a Vacuum ---
 * 
 * Santa is delivering presents to an infinite two-dimensional grid of houses.
 * 
 * He begins by delivering a present to the house at his starting location, and
 * then an elf at the North Pole calls him via radio and tells him where to move
 * next. Moves are always exactly one house to the north (^), south (v), east
 * (>), or west (<). After each move, he delivers another present to the house
 * at his new location.
 * 
 * However, the elf back at the north pole has had a little too much eggnog, and
 * so his directions are a little off, and Santa ends up visiting some houses
 * more than once. How many houses receive at least one present?
 * 
 * For example:
 * 
 * - > delivers presents to 2 houses: one at the starting location, and one to
 *   the east.
 * - ^>v< delivers presents to 4 houses in a square, including twice to the
 *   house at his starting/ending location.
 * - ^v^v^v^v^v delivers a bunch of presents to some very lucky children at only
 *   2 houses.
 */

#include <stdio.h>

/*
 * Doing a preliminary inspection of the input file reveals it to be 8192 bytes.
 * That means Santa would maximally move 8192 times in any given direction. In
 * this case we can settle for a grid of size NxN, where N = (8192 * 2 + 1) =
 * 16385, if Santa starts at coordinates, 8192, 8192.
 */

static unsigned int grid[16385][16385];

int main(int argc, char const *argv[])
{
  unsigned int x = 8192, y = 8192, houses = 1;
  char direction;


  grid[x][y] = 1;

  while(scanf("%c", &direction) != EOF)
  {
    switch(direction) {
      case '^':
        y--;
        break;
      case '>':
        x++;
        break;
      case 'v':
        y++;
        break;
      case '<':
        x--;
        break;
      default:
        printf("Wrong way: %c\n", direction);
        break;
    }

    if (grid[x][y] == 0)
    {
      grid[x][y]++;
      houses++;
    }
  }

  printf("Houses that receive at least one present: %u\n", houses);

  return 0;
}
