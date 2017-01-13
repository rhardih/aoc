/**
 * --- Day 19: An Elephant Named Joseph ---
 * 
 * The Elves contact you over a highly secure emergency channel. Back at the
 * North Pole, the Elves are busy misunderstanding White Elephant parties.
 * 
 * Each Elf brings a present. They all sit in a circle, numbered starting with
 * position 1. Then, starting with the first Elf, they take turns stealing all
 * the presents from the Elf to their left. An Elf with no presents is removed
 * from the circle and does not take turns.
 * 
 * For example, with five Elves (numbered 1 to 5):
 * 
 *   1
 * 5   2
 *  4 3
 *
 * Elf 1 takes Elf 2's present.
 * Elf 2 has no presents and is skipped.
 * Elf 3 takes Elf 4's present.
 * Elf 4 has no presents and is also skipped.
 * Elf 5 takes Elf 1's two presents.
 *
 * Neither Elf 1 nor Elf 2 have any presents, so both are skipped.
 *
 * Elf 3 takes Elf 5's three presents.
 *
 * So, with five Elves, the Elf that sits starting in position 3 gets all the
 * presents.
 * 
 * With the number of Elves given in your puzzle input, which Elf gets all the
 * presents?
 */

#include <stdio.h>
#include <stdlib.h>

#define INPUT 3014387

int main(int argc, char const *argv[])
{
  int last_elf_number = 1;

  // Realising that whenever the number of elfs is one in the series;
  //
  //   n = 2 * (n - 1) + 1, n > 0
  // 
  // The n'th elf gets all the gifts. Let's call this the last elf numbers. The
  // solution is then the difference between the given number of elfs and the
  // first last elf number greater the given number.

  while (last_elf_number < INPUT)
    last_elf_number = last_elf_number * 2 + 1;

  printf("Elf number %2d, gets all the presents.\n", INPUT - (last_elf_number % INPUT));

  return 0;
}
