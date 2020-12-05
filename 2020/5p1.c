/**
 * --- Part Two ---
 *
 * Ding! The "fasten seat belt" signs have turned on. Time to find your seat.
 * 
 * It's a completely full flight, so your seat should be the only missing
 * boarding pass in your list. However, there's a catch: some of the seats at
 * the very front and back of the plane don't exist on this aircraft, so they'll
 * be missing from your list as well.
 * 
 * Your seat wasn't at the very front or back, though; the seats with IDs +1 and
 * -1 from yours will be in your list.
 * 
 * What is the ID of your seat?
 */

#include <stdio.h>

typedef struct {
  int row;
  int column;
  int id;
} seating_t;

int main(int argc, char **argv) {
  char boarding_pass[11];
  int i, j, k, half;
  seating_t seat, highest_id_seat = { 0, 0, 0 };

  while(scanf("%10s\n", boarding_pass) != EOF) {
    j = 0;
    k = 127;

    for (i = 0; i < 7; i++) {
      half = (k - j) / 2 + 1;
      boarding_pass[i] == 'B' ? (j += half) : (k -= half);
    }

    seat.row = j;

    j = 0;
    k = 7;

    for (i = 7; i < 10; i++) {
      half = (k - j) / 2 + 1;
      boarding_pass[i] == 'R' ? (j += half) : (k -= half);
    }

    seat.column = j;
    seat.id = seat.row * 8 + seat.column;

    if (seat.id > highest_id_seat.id) {
      highest_id_seat = seat;
    }
  }

  printf("Highest seat id on a boarding pass; %d\n", highest_id_seat.id);

  return 0;
}
