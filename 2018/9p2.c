
/**
 * --- Day 9: Marble Mania ---
 *
 * --- Part Two ---
 *
 * Amused by the speed of your answer, the Elves are curious:
 * 
 * What would the new winning Elf's score be if the number of the last marble
 * were 100 times larger?
 */


#include <stdio.h>
#include <stdlib.h>

#define PLAYERS 404
#define WORTH 7185200

typedef struct marble marble_t;

struct marble {
  long long number;
  marble_t *next;
  marble_t *prev;
};

long long scores[PLAYERS];

int main(int argc, char const *argv[]) {
  marble_t *current = malloc(sizeof(marble_t)), *tmp;
  current->number = 0;
  current->next = current;
  current->prev = current;
  long long player = 0, number = 1, i, max;
  marble_t *root = current;

  while (number <= WORTH) {
    if (number > 0 && number % 23 == 0) {
      tmp = current->prev->prev->prev->prev->prev->prev->prev;
      tmp->prev->next = tmp->next;
      tmp->next->prev = tmp->prev;
      current = tmp->next;

      scores[player] += number;
      scores[player] += tmp->number;
      free(tmp);
    } else {
      tmp = malloc(sizeof(marble_t));
      tmp->number = number;

      tmp->next = current->next->next;
      tmp->prev = current->next;

      current->next->next->prev = tmp;
      current->next->next = tmp;

      current = tmp;
    }

    number++;
    player = (player + 1) % PLAYERS;
  }

  for (i = 0, max = 0; i < PLAYERS; i++) {
    if (scores[i] > max)
      max = scores[i];
  }

  printf("The winning Elf's score: %lld\n", max);

  return 0;
}
