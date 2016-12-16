#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ll.h"

#define FLOORS 4
#define NRTGS 10
#define ALLON4TH 1023

typedef enum { POG = 1, THG, PRG, RUG, COG, POM, THM, PRM, RUM, COM } rtg;

typedef struct {
  int steps;
  rtg *floors;
} fchecker_t;

void print_floors(rtg *f) {
  for (int i = 0; i < FLOORS; i++)
  {
    printf("F%d ", i + 1);
    for (int j = 0; j < NRTGS; j++) {
      rtg r = *((rtg *)f + i * NRTGS + j);
      switch(r) {
        case POG:
          printf("POG");
          break;
        case THG:
          printf("THG");
          break;
        case PRG:
          printf("PRG");
          break;
        case RUG:
          printf("RUG");
          break;
        case COG:
          printf("COG");
          break;
        case POM:
          printf("POM");
          break;
        case THM:
          printf("THM");
          break;
        case PRM:
          printf("PRM");
          break;
        case RUM:
          printf("RUM");
          break;
        case COM:
          printf("COM");
          break;
        default:
          printf("  .");
          break;
      }
      
      printf(" ");
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

/**
 * Since rtgs are only moved vertical in their own column, each floor
 * constellation can be represented in 10 bits, either the rtg is present in
 * its designated location on the floor or it isn't.
 *
 * Uniquely identifying the aggregate constellation of all four floors thus
 * requires 40 bits. Assuming a long is 64 bits, all possible constellations of
 * rtgs across floors can then each be expressed by a single 64 bit integer.
 *
 * Largest possible value is then:
 *
 *   1111111111000000000000000000000000000000 (base 2)
 *   1098437885952                            (base 10)
 */
long marshall(rtg *f) {
  long mask = 0, r;

  for (int i = 0; i < FLOORS; i++)
  {
    for (int j = 0; j < NRTGS; j++)
    {
      r = *((rtg *)f + i * NRTGS + j);
      mask |= (((long)!!r) << ((FLOORS * NRTGS - 1) - (i * NRTGS + j)));
    }
  }

  return mask;
}

void copy_and_enqueue(ll_t *q, rtg *floors, int steps) {
  /*printf("copying and enq. with steps: %d\n", steps);*/
  ll_node_t *n = ll_node_create();

  /*print_floors(floors);*/

  fchecker_t *c = malloc(sizeof(fchecker_t));
  c->steps = steps;
  c->floors = copy_floors(floors);

  n->value = c;
  ll_append(q, n);
}

int checked_finder(void *v0, void *v1) {
  return *(long *)v0 == *(long *)v1;
}

void checked_printer(void *p) {
  printf("%lu", *(long *)p);
}

int main(int argc, char const *argv[])
{
  int steps = 0, i, j, k;
  int all_sum = POG + THG + PRG + RUG + COG + POM + THM + PRM + RUM + COM;
  long *m;

  rtg floors[FLOORS][NRTGS] = {
    { POG, THG, THM, PRG, RUG, RUM, COG, COM, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, POM, PRM },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
  };

  ll_t *q = ll_list_create();
  ll_t *checked = ll_list_create();

  copy_and_enqueue(q, (rtg *)floors, 0);

  ll_node_t *cnode = ll_node_create();
  m = malloc(sizeof(long));
  *m = marshall((rtg *)floors);
  cnode->value = m;
  ll_append(checked, cnode);

  while (!ll_empty(q)) {
    ll_node_t *current_node = ll_remove_head(q);
    fchecker_t *current_checker = (fchecker_t *)current_node->value;
    rtg *from, *to;

    // when all rtgs arrive at fourth floor, save steps if it's a new low
    if (marshall(current_checker->floors) == ALLON4TH &&
        current_checker->steps < steps) {
      steps = current_checker->steps;
      break;
    }

    for (i = 0; i < FLOORS; i++) {
      for (j = 0; j < NRTGS; j++) {
        rtg *from = (rtg *)current_checker->floors + i * NRTGS + j;

        if (*from == 0) continue;

        if (i < 3) {
          // swap, copy and enqueue if valid, then swap back

          // upward move single
          to = (rtg *)current_checker->floors + (i + 1) * NRTGS + j;
          swap(from, to);

          m = malloc(sizeof(long));
          *m = marshall((rtg *)current_checker->floors);

          if (valid(current_checker->floors) &&
                ll_find(checked, m, checked_finder) == NULL) {
            cnode = ll_node_create();
            cnode->value = m;
            ll_append(checked, cnode);
            copy_and_enqueue(q, current_checker->floors, current_checker->steps + 1);
          }

          // upward move double
          for (k = 0; k != j && k < NRTGS; k++) {
            rtg *inner_from = (rtg *)current_checker->floors + i * NRTGS + k;

            if (*inner_from == 0) continue;

            rtg *inner_to = (rtg *)current_checker->floors + (i + 1) * NRTGS + k;
            swap(inner_from, inner_to);

            m = malloc(sizeof(long));
            *m = marshall((rtg *)current_checker->floors);

            if (valid(current_checker->floors) &&
                ll_find(checked, m, checked_finder) == NULL) {
              cnode = ll_node_create();
              cnode->value = m;
              ll_append(checked, cnode);
              copy_and_enqueue(q, current_checker->floors, current_checker->steps + 1);
            }

            swap(inner_from, inner_to);
          }

          swap(from, to);
        }

        if (i > 0) {
          to = (rtg *)current_checker->floors + (i - 1) * NRTGS + j;
          
          swap(from, to);

          m = malloc(sizeof(long));
          *m = marshall((rtg *)current_checker->floors);

          if (valid(current_checker->floors) &&
              ll_find(checked, m, checked_finder) == NULL) {
            cnode = ll_node_create();
            cnode->value = m;
            ll_append(checked, cnode);
            copy_and_enqueue(q, current_checker->floors, current_checker->steps + 1);
          }

          swap(from, to);
        }
      }
    }
  }

  printf("Minimum number of steps required: %d\n", valid((rtg *)floors));

  return 0;
}
