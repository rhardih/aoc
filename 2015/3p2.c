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
 *
 * --- Part Two ---
 *
 * The next year, to speed up the process, Santa creates a robot version of
 * himself, Robo-Santa, to deliver presents with him.
 * 
 * Santa and Robo-Santa start at the same location (delivering two presents to
 * the same starting house), then take turns moving based on instructions from
 * the elf, who is eggnoggedly reading from the same script as the previous
 * year.
 * 
 * This year, how many houses receive at least one present?
 * 
 * For example:
 * 
 * - ^v delivers presents to 3 houses, because Santa goes north, and then
 *   Robo-Santa goes south.
 * - ^>v< now delivers presents to 3 houses, and Santa and Robo-Santa end up
 *   back where they started.
 * - ^v^v^v^v^v now delivers presents to 11 houses, with Santa going one
 *   direction and Robo-Santa going the other.
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
  unsigned int s_x = 8192, s_y = 8192, r_x = 8192, r_y = 8192, houses = 1;
  unsigned int turn = 0, *tmp_x, *tmp_y;
  char direction;

  grid[s_x][s_y] = 2;

  while(scanf("%c", &direction) != EOF)
  {
    if (turn == 0)
    {
      tmp_x = &s_x;
      tmp_y = &s_y;
    }
    else
    {
      tmp_x = &r_x;
      tmp_y = &r_y;
    }

    turn = (turn + 1) % 2;

    switch(direction) {
      case '^':
        (*tmp_y)--;
        break;
      case '>':
        (*tmp_x)++;
        break;
      case 'v':
        (*tmp_y)++;
        break;
      case '<':
        (*tmp_x)--;
        break;
      default:
        printf("Wrong way: %c\n", direction);
        break;
    }

    if (grid[*tmp_x][*tmp_y] == 0)
    {
      grid[*tmp_x][*tmp_y]++;
      houses++;
    }
  }

  printf("Houses that receive at least one present: %u\n", houses);

  return 0;
}
