/**
 * --- Part Two ---
 *
 * Before you can give the destination to the captain, you realize that the
 * actual action meanings were printed on the back of the instructions the whole
 * time.
 *
 * Almost all of the actions indicate how to move a waypoint which is relative
 * to the ship's position:
 *
 * - Action N means to move the waypoint north by the given value.
 * - Action S means to move the waypoint south by the given value.
 * - Action E means to move the waypoint east by the given value.
 * - Action W means to move the waypoint west by the given value.
 * - Action L means to rotate the waypoint around the ship left
 *   (counter-clockwise) the given number of degrees.
 * - Action R means to rotate the waypoint around the ship right (clockwise) the
 *   given number of degrees.
 * - Action F means to move forward to the waypoint a number of times equal to
 *   the given value.
 *
 * The waypoint starts 10 units east and 1 unit north relative to the ship. The
 * waypoint is relative to the ship; that is, if the ship moves, the waypoint
 * moves with it.
 *
 * For example, using the same instructions as above:
 *
 * - F10 moves the ship to the waypoint 10 times (a total of 100 units east and
 *   10 units north), leaving the ship at east 100, north 10. The waypoint stays
 *   10 units east and 1 unit north of the ship.
 * - N3 moves the waypoint 3 units north to 10 units east and 4 units north of
 *   the ship. The ship remains at east 100, north 10.
 * - F7 moves the ship to the waypoint 7 times (a total of 70 units east and 28
 *   units north), leaving the ship at east 170, north 38. The waypoint stays 10
 *   units east and 4 units north of the ship.
 * - R90 rotates the waypoint around the ship clockwise 90 degrees, moving it to
 *   4 units east and 10 units south of the ship. The ship remains at east 170,
 *   north 38.
 * - F11 moves the ship to the waypoint 11 times (a total of 44 units east and
 *   110 units south), leaving the ship at east 214, south 72. The waypoint
 *   stays 4 units east and 10 units south of the ship.
 *
 * After these operations, the ship's Manhattan distance from its starting
 * position is 214 + 72 = 286.
 *
 * Figure out where the navigation instructions actually lead. What is the
 * Manhattan distance between that location and the ship's starting position?
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char action;
  int value;
} instruction_t;

typedef struct {
  int x;
  int y;
} waypoint_t;

typedef struct {
  int x;
  int y;
  waypoint_t w;
} ship_t;

void rotate_waypoint(ship_t *s, instruction_t i) {
  int tmp;

  switch(i.value) {
    case 90:
      if (i.action == 'R') {
        tmp = s->w.x;
        s->w.x = -s->w.y;
        s->w.y = tmp;
      } else {
        tmp = s->w.x;
        s->w.x = s->w.y;
        s->w.y = -tmp;
      }
      break;
    case 180:
      s->w.x = -s->w.x;
      s->w.y = -s->w.y;
      break;
    case 270:
      if (i.action == 'R') {
        tmp = s->w.x;
        s->w.x = s->w.y;
        s->w.y = -tmp;
      } else {
        tmp = s->w.x;
        s->w.x = -s->w.y;
        s->w.y = tmp;
      }
      break;
  }
}

void sail(ship_t *s, int times) {
  for(int i = 0; i < times; i++) {
    s->x += s->w.x;
    s->y += s->w.y;
  }
}

int main(int argc, char **argv) {
  ship_t s = { 0, 0, { 10, -1 } };
  instruction_t i;

  while(scanf("%c%d\n", &i.action, &i.value) != EOF) {
    switch(i.action) {
      case 'N':
        s.w.y -= i.value;
        break;
      case 'S':
        s.w.y += i.value;
        break;
      case 'E':
        s.w.x += i.value;
        break;
      case 'W':
        s.w.x -= i.value;
        break;
      case 'L':
      case 'R':
        rotate_waypoint(&s, i);
        break;
      case 'F':
        sail(&s, i.value);
        break;
    }
  }

  printf("The Manhattan distance between ships current and starting position: "
      "%d\n", abs(s.x + s.y));

  return 0;
}
