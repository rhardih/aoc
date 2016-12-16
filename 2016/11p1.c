#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ll.h"

#define FLOORS 4
#define NRTGS 10

typedef enum { POG = 1, THG, PRG, RUG, COG, POM, THM, PRM, RUM, COM } rtg;

typedef struct {
  int steps;
  rtg *floors;
} fchecker_t;

void print_floors(rtg *f) {
  for (int i = 0; i < FLOORS; i++)
  {
    for (int j = 0; j < NRTGS; j++) {
      printf("%d", *((rtg *)f + i * NRTGS + j));
      if (j < 9) printf(", ");
    }
    printf("\n");
  }
}

int valid(rtg *f) {
  for (int i = 0; i < FLOORS; i++)
  {
    for (int j = 0; j < NRTGS; j++) {
      // for each chip on a floor, scan all adjecent rtgs and determine if it
      // will fry or it's protected
      rtg current = *((rtg *)f + i * NRTGS + j);

      if (current == 0) continue;
      if (current < POM) continue;

      int protected = 0;
      int fry = 0;

      for (int k = 0; k < NRTGS && j != k; k++) {
        rtg other = *((rtg *)f + i * NRTGS + k);

        if (other == 0) continue;

        if (other < POM) fry = 1;
        if (other == current - 5) protected = 1;
      }

      if (fry && !protected)
        return 0;
    }
  }

  return 1;
}

void swap(rtg *a, rtg *b) {
  *a = *a ^ *b;
  *b = *a ^ *b;
  *a = *b ^ *a;
}

rtg *copy_floors(rtg *f) {
  rtg *copy = malloc(NRTGS * FLOORS * sizeof(rtg));
  memcpy(copy, f, NRTGS * FLOORS * sizeof(rtg));
  return copy;
}

void copy_and_enqueue(ll_t *q, rtg *floors, int steps) {
  printf("copying and enq. with steps: %d\n", steps);
  ll_node_t *n = ll_node_create();

  fchecker_t *c = malloc(sizeof(fchecker_t));
  c->steps = steps;
  c->floors = copy_floors(floors);

  n->value = c;
  ll_append(q, n);
}

int main(int argc, char const *argv[])
{
  int steps = 0, i, j, k;
  int all_sum = POG + THG + PRG + RUG + COG + POM + THM + PRM + RUM + COM;


  rtg floors[FLOORS][NRTGS] = {
    { POG, THG, THM, PRG, RUG, RUM, COG, COM, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, POM, PRM },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
  };

  ll_t *q = ll_list_create();

  copy_and_enqueue(q, floors, 0);

  while (!ll_empty(q)) {
    ll_node_t *current_node = ll_remove_head(q);
    fchecker_t *current_checker = (fchecker_t *)current_node->value;
    rtg *from, *to;

    for (i = 0; i < FLOORS; i++) {
      int rtg_sum = 0;

      for (j = 0; j < NRTGS; j++) {
        rtg *from = (rtg *)current_checker->floors + i * NRTGS + j;

        if (*from == 0) continue;

        if (i < 3) {
          // swap, copy and enqueue if valid, then swap back

          // upward move single
          to = (rtg *)current_checker->floors + (i + 1) * NRTGS + j;
          swap(from, to);

          if (valid(current_checker->floors)) {
            copy_and_enqueue(q, current_checker->floors, current_checker->steps + 1);
          }

          // upward move double
          for (k = 0; k != j && k < NRTGS; k++) {
            rtg *inner_from = (rtg *)current_checker->floors + i * NRTGS + k;

            if (*inner_from == 0) continue;

            rtg *inner_to = (rtg *)current_checker->floors + (i + 1) * NRTGS + k;
            swap(inner_from, inner_to);

            if (valid(current_checker->floors)) {
              copy_and_enqueue(q, current_checker->floors, current_checker->steps + 1);
            }

            swap(inner_from, inner_to);
          }

          swap(from, to);
        }

        if (i > 0) {
          to = (rtg *)current_checker->floors + (i - 1) * NRTGS + j;
          
          swap(from, to);

          if (valid(current_checker->floors)) {
            copy_and_enqueue(q, current_checker->floors, current_checker->steps + 1);
          }

          swap(from, to);
        }

        if (i == FLOORS - 1) rtg_sum += *from;
      }

      // when all rtgs arrive at fourth floor, save steps if it's a new low
      if (i == FLOORS - 1 && rtg_sum == all_sum && current_checker->steps < steps)
        steps = current_checker->steps;
    }
  }

  printf("Minimum number of steps required: %d\n", valid((rtg *)floors));

  return 0;
}
