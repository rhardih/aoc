/**
 * --- Day 20: Firewall Rules ---
 *
 * You'd like to set up a small hidden computer here so you can use it to get
 * back into the network later. However, the corporate firewall only allows
 * communication with certain external IP addresses.
 *
 * You've retrieved the list of blocked IPs from the firewall, but the list
 * seems to be messy and poorly maintained, and it's not clear which IPs are
 * allowed. Also, rather than being written in dot-decimal notation, they are
 * written as plain 32-bit integers, which can have any value from 0 through
 * 4294967295, inclusive.
 *
 * For example, suppose only the values 0 through 9 were valid, and that you
 * retrieved the following blacklist:
 *
 * 5-8
 * 0-2
 * 4-7
 *
 * The blacklist specifies ranges of IPs (inclusive of both the start and end
 * value) that are not allowed. Then, the only IPs that this firewall allows are
 * 3 and 9, since those are the only numbers not in any range.
 *
 * Given the list of blocked IPs you retrieved from the firewall (your puzzle
 * input), what is the lowest-valued IP that is not blocked?
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "bst.h"

typedef struct {
  unsigned int from;
  unsigned int to;
} interval_t;

int itvcompare(const void *p, const void *q)
{
  interval_t *i0 = (interval_t *)p;
  interval_t *i1 = (interval_t *)q;

  return i0->from < i1->from;
}

int intersects(bst_node_t *n, unsigned int i)
{
  if (n == NULL) return 0;

  interval_t *ni = n->key;

  return (ni->from <= i && i <= ni->to) ||
    intersects(n->left, i) ||
    intersects(n->right, i);
}

int main(int argc, char const *argv[])
{
  bst_tree_t *t = bst_tree_new(NULL);
  bst_node_t *n;
  interval_t *scanned;
  unsigned int from, to, i;

  while(scanf("%u-%u\n", &from, &to) != EOF) {
    scanned = malloc(sizeof(interval_t));
    scanned->from = from;
    scanned->to = to;
    n = bst_node_new(scanned);
    bst_insert(t, n, itvcompare);
  }

  for (i = 0; i < UINT_MAX; ++i)
    if (!intersects(t->root, i)) break;

  printf("Lowest-valued IP that is not blocked: %u\n", i);

  return 0;
}
