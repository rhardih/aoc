/**
 * --- Day 4: Repose Record ---
 *
 *  --- Part Two ---
 * Strategy 2: Of all guards, which guard is most frequently asleep on the same
 * minute?
 * 
 * In the example above, Guard #99 spent minute 45 asleep more than any other
 * guard or minute - three times in total. (In all other cases, any guard spent
 * any minute asleep at most twice.)
 * 
 * What is the ID of the guard you chose multiplied by the minute you chose? (In
 * the above example, the answer would be 99 * 45 = 4455.)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ll.h"

typedef struct guard {
  int id;
  int minutes[60];
} guard_t;

int guard_finder(void *guard, void *value) {
  guard_t *g = (guard_t *)guard;
  return g->id == *(int *)value;
}

int sleep_total(guard_t *g) {
  int result = 0;

  for (int i = 0; i < 60; i++) {
    result += g->minutes[i];
  }

  return result;
}

int main(int argc, char const *argv[]) {
  // 1518-11-01 00:00
  char timestamp[17], note[50];
  struct tm asleep_time, wakeup_time;
  int minutes[60];
  int id, i;

  ll_t *guards = ll_list_create();
  ll_node_t *guard_node;
  guard_t *guard;

  while(scanf("[%[^]]] %[^\n]\n", timestamp, note) != EOF) {
    if (note[0] == 'G') {
      sscanf(note, "Guard #%d begins shift\n", &id);
      guard_node = ll_find(guards, &id, guard_finder);

      if (guard_node == NULL) {
        guard_node = ll_node_create();
        guard = malloc(sizeof(guard_t));
        guard->id = id;

        for (i = 0; i < 60; i++) {
          guard->minutes[i] = 0;
        }

        guard_node->value = guard;
        ll_append(guards, guard_node);
      } else {
        guard = guard_node->value;
      }
    } else if (note[0] == 'f') {
      strptime(timestamp, "%Y-%m-%d %H:%M", &asleep_time);
    } else if (note[0] == 'w') {
      strptime(timestamp, "%Y-%m-%d %H:%M", &wakeup_time);

      for (i = asleep_time.tm_min; i < wakeup_time.tm_min; i++) {
        guard->minutes[i]++;
      }
    }
  }

  int most_total = 0, most_minute;
  int max, minute;
  guard_node = guards->first;

  while (guard_node != NULL) {
    guard = guard_node-> value;

    max = 0;
    minute = 0;
    for (i = 0; i < 60; i++) {
      if (guard->minutes[i] > max) {
        max = guard->minutes[i];
        minute = i;
      }
    }

    if (max > most_total) {
      most_total = max;
      most_minute = minute;
      id = guard->id;
    }

    guard_node = guard_node->next;
  }

  printf("ID of guard multiplied by minute: %d\n", id * most_minute);

  return 0;
}
