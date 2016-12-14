#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ll.h"

//#define DEBUG

typedef struct {
  int number;
  int low;
  int high;
  int val0;
  int val1;
  char ltype[7];
  char htype[7];
} bot_t;

int bot_finder(void *bot, void *value) {
  bot_t *b = (bot_t *)bot;
  return b->number == *(int *)value;
}

#ifdef DEBUG
void bot_printer(void *p) {
  bot_t *b = (bot_t *)p;
  printf("[%d(%d,%d): %c%d, %c%d]", b->number, b->val0, b->val1, b->ltype[0], b->low, b->htype[0], b->high);
}
#endif

void give_value(bot_t *b, int v) {
  if (b->val0 == -1) {
    b->val0 = v;
  } else if (b->val1 == -1) {
    b->val1 = v;
  }
}

int main(int argc, char const *argv[])
{
  char buf[100];
  int bot_number = 0;
  int giver, low, high;
  char low_type[] = "......";
  char high_type[] = "......";
  int value, receiver;

  ll_t *bots = ll_list_create();

  // First scan-through to establish all bots
  while(fgets(buf, 100, stdin) != NULL) {
    if (strncmp(buf, "value", 5) == 0) continue;

    sscanf(buf, "bot %d gives low to %s %d and high to %s %d\n", &giver,
        low_type, &low,
        high_type, &high);

    bot_t *bot = malloc(sizeof(bot_t));
    bot->number = giver;
    sprintf(bot->ltype, "%s", low_type);
    bot->low = low;
    sprintf(bot->htype, "%s", high_type);
    bot->high = high;

    bot->val0 = -1;
    bot->val1 = -1;

    ll_node_t *n = ll_node_create();
    n->value = bot;
    ll_append(bots, n);
  }

  rewind(stdin);

  // Second scan-through assigns values
  while(fgets(buf, 100, stdin) != NULL) {
    if (strncmp(buf, "bot", 3) == 0) continue;

    sscanf(buf, "value %d goes to bot %d\n", &value, &receiver);

    ll_t *q = ll_list_create();
    ll_node_t *receiver_node = ll_find(bots, &receiver, bot_finder);

    give_value((bot_t *)receiver_node->value, value);

    ll_node_t *receiver_node_copy = ll_node_create();
    receiver_node_copy->value = receiver_node->value;
    ll_append(q, receiver_node_copy);

    while (!ll_empty(q)) {
      ll_node_t *current = ll_remove_head(q);
      bot_t *bot = (bot_t *)current->value;

      if (bot->val0 != -1 && bot->val1 != -1) {
        if ((bot->val0 == 61 && bot->val1 == 17) ||
            (bot->val0 == 17 && bot->val1 == 61)) {
          bot_number = bot->number;
        }

        if (bot->val0 < bot->val1) {
          low = bot->val0;
          high = bot->val1;
        } else {
          low = bot->val1;
          high = bot->val0;
        }

        // don't queue outputs
        if (strncmp(bot->ltype, "bot", 3) == 0) {
          ll_node_t *lreceiver = ll_find(bots, &(bot->low), bot_finder);
          bot_t *lbot = (bot_t *)lreceiver->value;

          give_value(lbot, low);

          ll_node_t *lreceiver_copy = ll_node_create();
          lreceiver_copy->value = lbot;

          ll_append(q, lreceiver_copy);
        }

        if (strncmp(bot->htype, "bot", 3) == 0) {
          ll_node_t *hreceiver = ll_find(bots, &(bot->high), bot_finder);
          bot_t *hbot = (bot_t *)hreceiver->value;

          give_value(hbot, high);

          ll_node_t *hreceiver_copy = ll_node_create();
          hreceiver_copy->value = hbot;

          ll_append(q, hreceiver_copy);
        }

        bot->val0 = -1;
        bot->val1 = -1;
      }
    }
  }

  printf("Bot number: %d\n", bot_number);

  return 0;
}
