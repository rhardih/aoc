/**
 *
 * --- Day 11: Radioisotope Thermoelectric Generators ---
 * 
 * You come upon a column of four floors that have been entirely sealed off from
 * the rest of the building except for a small dedicated lobby. There are some
 * radiation warnings and a big sign which reads "Radioisotope Testing
 * Facility".
 * 
 * According to the project status board, this facility is currently being used
 * to experiment with Radioisotope Thermoelectric Generators (RTGs, or simply
 * "generators") that are designed to be paired with specially-constructed
 * microchips. Basically, an RTG is a highly radioactive rock that generates
 * electricity through heat.
 * 
 * The experimental RTGs have poor radiation containment, so they're dangerously
 * radioactive. The chips are prototypes and don't have normal radiation
 * shielding, but they do have the ability to generate an electromagnetic
 * radiation shield when powered. Unfortunately, they can only be powered by
 * their corresponding RTG. An RTG powering a microchip is still dangerous to
 * other microchips.
 * 
 * In other words, if a chip is ever left in the same area as another RTG, and
 * it's not connected to its own RTG, the chip will be fried. Therefore, it is
 * assumed that you will follow procedure and keep chips connected to their
 * corresponding RTG when they're in the same room, and away from other RTGs
 * otherwise.
 * 
 * These microchips sound very interesting and useful to your current
 * activities, and you'd like to try to retrieve them. The fourth floor of the
 * facility has an assembling machine which can make a self-contained, shielded
 * computer for you to take with you - that is, if you can bring it all of the
 * RTGs and microchips.
 * 
 * Within the radiation-shielded part of the facility (in which it's safe to
 * have these pre-assembly RTGs), there is an elevator that can move between the
 * four floors. Its capacity rating means it can carry at most yourself and two
 * RTGs or microchips in any combination. (They're rigged to some heavy
 * diagnostic equipment - the assembling machine will detach it for you.) As a
 * security measure, the elevator will only function if it contains at least one
 * RTG or microchip. The elevator always stops on each floor to recharge, and
 * this takes long enough that the items within it and the items on that floor
 * can irradiate each other. (You can prevent this if a Microchip and its
 * Generator end up on the same floor in this way, as they can be connected
 * while the elevator is recharging.)
 * 
 * You make some notes of the locations of each component of interest (your
 * puzzle input). Before you don a hazmat suit and start moving things around,
 * you'd like to have an idea of what you need to do.
 * 
 * When you enter the containment area, you and the elevator will start on the
 * first floor.
 * 
 * For example, suppose the isolated area has the following arrangement:
 * 
 * The first floor contains a hydrogen-compatible microchip and a lithium-compatible microchip.
 * The second floor contains a hydrogen generator.
 * The third floor contains a lithium generator.
 * The fourth floor contains nothing relevant.
 *
 * As a diagram (F# for a Floor number, E for Elevator, H for Hydrogen, L for
 * Lithium, M for Microchip, and G for Generator), the initial state looks like
 * this:
 * 
 * F4 .  .  .  .  .  
 * F3 .  .  .  LG .  
 * F2 .  HG .  .  .  
 * F1 E  .  HM .  LM 
 *
 * Then, to get everything up to the assembling machine on the fourth floor, the
 * following steps could be taken:
 * 
 * - Bring the Hydrogen-compatible Microchip to the second floor, which is safe
 *   because it can get power from the Hydrogen Generator:
 * 
 *   F4 .  .  .  .  .  
 *   F3 .  .  .  LG .  
 *   F2 E  HG HM .  .  
 *   F1 .  .  .  .  LM 
 *
 * - Bring both Hydrogen-related items to the third floor, which is safe because
 *   the Hydrogen-compatible microchip is getting power from its generator:
 * 
 *   F4 .  .  .  .  .  
 *   F3 E  HG HM LG .  
 *   F2 .  .  .  .  .  
 *   F1 .  .  .  .  LM 
 *
 * - Leave the Hydrogen Generator on floor three, but bring the
 *   Hydrogen-compatible Microchip back down with you so you can still use the
 *   elevator:
 * 
 *   F4 .  .  .  .  .  
 *   F3 .  HG .  LG .  
 *   F2 E  .  HM .  .  
 *   F1 .  .  .  .  LM 
 *
 * - At the first floor, grab the Lithium-compatible Microchip, which is safe
 *   because Microchips don't affect each other:
 * 
 *   F4 .  .  .  .  .  
 *   F3 .  HG .  LG .  
 *   F2 .  .  .  .  .  
 *   F1 E  .  HM .  LM 
 *
 * - Bring both Microchips up one floor, where there is nothing to fry them:
 * 
 *   F4 .  .  .  .  .  
 *   F3 .  HG .  LG .  
 *   F2 E  .  HM .  LM 
 *   F1 .  .  .  .  .  
 *
 * - Bring both Microchips up again to floor three, where they can be
 *   temporarily connected to their corresponding generators while the elevator
 *   recharges, preventing either of them from being fried:
 * 
 *   F4 .  .  .  .  .  
 *   F3 E  HG HM LG LM 
 *   F2 .  .  .  .  .  
 *   F1 .  .  .  .  .  
 *
 * - Bring both Microchips to the fourth floor:
 * 
 *   F4 E  .  HM .  LM 
 *   F3 .  HG .  LG .  
 *   F2 .  .  .  .  .  
 *   F1 .  .  .  .  .  
 *
 * - Leave the Lithium-compatible microchip on the fourth floor, but bring the
 *   Hydrogen-compatible one so you can still use the elevator; this is safe
 *   because although the Lithium Generator is on the destination floor, you can
 *   connect Hydrogen-compatible microchip to the Hydrogen Generator there:
 * 
 *   F4 .  .  .  .  LM 
 *   F3 E  HG HM LG .  
 *   F2 .  .  .  .  .  
 *   F1 .  .  .  .  .  
 *
 * - Bring both Generators up to the fourth floor, which is safe because you can
 *   connect the Lithium-compatible Microchip to the Lithium Generator upon
 *   arrival:
 * 
 *   F4 E  HG .  LG LM 
 *   F3 .  .  HM .  .  
 *   F2 .  .  .  .  .  
 *   F1 .  .  .  .  .  
 *
 * - Bring the Lithium Microchip with you to the third floor so you can use the
 *   elevator:
 * 
 *   F4 .  HG .  LG .  
 *   F3 E  .  HM .  LM 
 *   F2 .  .  .  .  .  
 *   F1 .  .  .  .  .  
 *
 * - Bring both Microchips to the fourth floor:
 * 
 *   F4 E  HG HM LG LM 
 *   F3 .  .  .  .  .  
 *   F2 .  .  .  .  .  
 *   F1 .  .  .  .  .  
 *
 * In this arrangement, it takes 11 steps to collect all of the objects at the
 * fourth floor for assembly. (Each elevator stop counts as one step, even if
 * nothing is added to or removed from it.)
 * 
 * In your situation, what is the minimum number of steps required to bring all
 * of the objects to the fourth floor?
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#include "ll.h"

// 4^10
#define COMBINATIONS 1048576
#define ALLON4TH 1023

typedef enum { POG = 1, THG, PRG, RUG, COG, POM, THM, PRM, RUM, COM } rtg;

typedef struct {
  int steps;
  rtg *floors;
} fchecker_t;

void print_floors(rtg *f) {
  for (int i = 0; i < 4; i++)
  {
    printf("F%d ", i + 1);
    for (int j = 0; j < 10; j++) {
      rtg r = *((rtg *)f + i * 10 + j);
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
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 10; j++) {
      // for each chip on a floor, scan all adjecent rtgs and determine if it
      // will fry or it's protected
      rtg current = *((rtg *)f + i * 10 + j);

      if (current == 0) continue;
      if (current < POM) continue;

      int protected = 0;
      int fry = 0;

      for (int k = 0; k < 10 && j != k; k++) {
        rtg other = *((rtg *)f + i * 10 + k);

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
  rtg *copy = malloc(10 * 4 * sizeof(rtg));
  memcpy(copy, f, 10 * 4 * sizeof(rtg));
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

  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      r = *((rtg *)f + i * 10 + j);
      mask |= (((long)!!r) << ((4 * 10 - 1) - (i * 10 + j)));
    }
  }

  return mask;
}

void copy_and_enqueue(ll_t *q, rtg *floors, int steps) {
  printf("copying and enq. with steps: %d\n", steps);
  ll_node_t *n = ll_node_create();

  print_floors(floors);

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

/*typedef struct {*/
  /*rtg_t rtgs[10];*/
/*} floor_t;*/

/*typedef struct {*/
  /*floor_t floors[4];*/
/*} column_t;*/

int oob(int f) {
  return f < 0 || f > 4 - 1;
}

int invalid(int pog, int thg, int thm, int prg, int rug, int rum, int cog, int com, int pom, int prm) {
  int thm_fry, rum_fry, com_fry, pom_fry, prm_fry;

  if (oob(pog) || oob(thg) || oob(thm) || oob(prg) || oob(rug) ||
      oob(rum) || oob(cog) || oob(com) || oob(pom) || oob(prm))
    return 1;


  thm_fry = thm != thg && (thm == pog || thm == prg || thm == rug || thm == cog);
  rum_fry = rum != rug && (rum == pog || rum == prg || rum == thg || rum == cog); 
  com_fry = com != cog && (com == pog || com == prg || com == rug || com == thg); 
  pom_fry = pom != pog && (pom == thg || pom == prg || pom == rug || pom == cog); 
  prm_fry = prm != prg && (prm == pog || prm == thg || prm == rug || prm == cog); 

  return thm_fry || rum_fry || com_fry || pom_fry || prm_fry;
}

int xvalid(int rtg[10]) {
  int i, j, protected, fry;

  for (i = 0; i < 10; ++i)
    if (rtg[i] < 0 || rtg[i] > 4 - 1) return 0;

  // For each microchip
  for (i = 0; i < 10 / 2; ++i)
  {
    // Check if its generator is on the same floor
    protected = rtg[i] == rtg[i + 10 / 2];

    // And whether it has the potential to be fried
    for (j = 10 / 2 + 1; j < 10; ++j) // skipping its own generator
    {
      fry = rtg[i] == rtg[j];

      if (!protected && fry) return 0;
    }
  }

  return 1;
}

typedef struct {
  int *positions;
  int steps;
  ll_t* adjecent;
} layout_t;

layout_t *layout_create(int *positions) {
  layout_t *l = malloc(sizeof(layout_t));

  l->positions = positions;
  l->steps = 0;
  l->adjecent = ll_list_create();

  return l;
}

int main(int argc, char const *argv[])
{
  // 1. Run through all possible of floor layouts, (4**10), and store whether
  //    they are valid;
  // 3. Build a graph of connections between combinations, storing possible
  //    moves from one layout to another.
  // 4. Find the shortest path in the graph, between the starting layout and the
  //    end layout.

  int i, j;
  int *positions, xx[10];
  int s = 0;
  ll_node_t *n;

  /**l = layout_create(0, 0, 0, 0, 0, 0, 0, 0, 1, 1), */

  /*layout_t *all = malloc(COMBINATIONS * sizeof(layout_t *));*/
  layout_t *l, *start, *end;
  layout_t *all[4][4][4][4][4][4][4][4][4][4];

  for (xx[0] = 0; xx[0] < 4; ++xx[0])
  for (xx[1] = 0; xx[1] < 4; ++xx[1])
  for (xx[2] = 0; xx[2] < 4; ++xx[2])
  for (xx[3] = 0; xx[3] < 4; ++xx[3])
  for (xx[4] = 0; xx[4] < 4; ++xx[4])
  for (xx[5] = 0; xx[5] < 4; ++xx[5])
  for (xx[6] = 0; xx[6] < 4; ++xx[6])
  for (xx[7] = 0; xx[7] < 4; ++xx[7])
  for (xx[8] = 0; xx[8] < 4; ++xx[8])
  for (xx[9] = 0; xx[9] < 4; ++xx[9])
  {
    positions = malloc(10 * sizeof(int));
    for (i = 0; i < 10; ++i)
      positions[i] = xx[i];

    l = layout_create(positions);
    l->valid = xvalid(positions);

    // Assuming order:
    //   com pom prm rum thm cog pog prg rug thg
    if (xx[0] == 0 && xx[1] == 1 && xx[2] == 1 && xx[3] == 0 && xx[4] == 0 &&
        xx[5] == 0 && xx[6] == 0 && xx[7] == 0 && xx[8] == 0 && xx[9] == 0)
      start = l;

    all[xx[0]][xx[1]][xx[2]][xx[3]][xx[4]][xx[5]][xx[6]][xx[7]][xx[8]][xx[9]] = l;
  }

  end = all[3][3][3][3][3][3][3][3][3][3];

  for (xx[0] = 0; xx[0] < 4; ++xx[0])
  for (xx[1] = 0; xx[1] < 4; ++xx[1])
  for (xx[2] = 0; xx[2] < 4; ++xx[2])
  for (xx[3] = 0; xx[3] < 4; ++xx[3])
  for (xx[4] = 0; xx[4] < 4; ++xx[4])
  for (xx[5] = 0; xx[5] < 4; ++xx[5])
  for (xx[6] = 0; xx[6] < 4; ++xx[6])
  for (xx[7] = 0; xx[7] < 4; ++xx[7])
  for (xx[8] = 0; xx[8] < 4; ++xx[8])
  for (xx[9] = 0; xx[9] < 4; ++xx[9])
  {
    l = all[xx[0]][xx[1]][xx[2]][xx[3]][xx[4]][xx[5]][xx[6]][xx[7]][xx[8]][xx[9]];
  }

  // Breadth first search to find number of steps between valid floor layouts.
  ll_t *q = ll_list_create();
  ll_node_t *root = ll_node_create(), *ncurrent, *nadjecent;
  layout_t *lcurrent, *ladjecent;
  root->value = l;

  ll_prepend(q, root);

  int *s;

  while (!ll_empty(q))
  {
    current = ll_remove_tail(q);
    lcurrent = current->value;
    nadjecent = lcurrent->adjecent->first;

    while (nadjecent != NULL)
    {
      ladjecent = nadjecent->value;

      if (*s == INT_MAX)
      {
      }
    }
  }

  return 0;

  /*
  int steps = 0, i, j, k;
  int all_sum = POG + THG + PRG + RUG + COG + POM + THM + PRM + RUM + COM;
  long *m;

  rtg floors[4][10] = {
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

    for (i = 0; i < 4; i++) {
      for (j = 0; j < 10; j++) {
        rtg *from = (rtg *)current_checker->floors + i * 10 + j;

        if (*from == 0) continue;

        if (i < 3) {
          // swap, copy and enqueue if valid, then swap back

          // upward move single
          to = (rtg *)current_checker->floors + (i + 1) * 10 + j;
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
          for (k = 0; k != j && k < 10; k++) {
            rtg *inner_from = (rtg *)current_checker->floors + i * 10 + k;

            if (*inner_from == 0) continue;

            rtg *inner_to = (rtg *)current_checker->floors + (i + 1) * 10 + k;
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
          to = (rtg *)current_checker->floors + (i - 1) * 10 + j;
          
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

  */
  return 0;
}
