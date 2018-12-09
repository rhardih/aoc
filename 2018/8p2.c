/**
 * --- Day 8: Memory Maneuver ---
 *
 * --- Part Two ---
 *
 * The second check is slightly more complicated: you need to find the value of
 * the root node (A in the example above).
 * 
 * The value of a node depends on whether it has child nodes.
 * 
 * If a node has no child nodes, its value is the sum of its metadata entries.
 * So, the value of node B is 10+11+12=33, and the value of node D is 99.
 * 
 * However, if a node does have child nodes, the metadata entries become indexes
 * which refer to those child nodes. A metadata entry of 1 refers to the first
 * child node, 2 to the second, 3 to the third, and so on. The value of this
 * node is the sum of the values of the child nodes referenced by the metadata
 * entries. If a referenced child node does not exist, that reference is
 * skipped. A child node can be referenced multiple time and counts each time it
 * is referenced. A metadata entry of 0 does not refer to any child node.
 * 
 * For example, again using the above nodes:
 * 
 * - Node C has one metadata entry, 2. Because node C has only one child node, 2
 *   references a child node which does not exist, and so the value of node C is
 *   0.
 * - Node A has three metadata entries: 1, 1, and 2. The 1 references node A's
 *   first child node, B, and the 2 references node A's second child node, C.
 *   Because node B has a value of 33 and node C has a value of 0, the value of
 *   node A is 33+33+0=66.
 *
 * So, in this example, the value of the root node is 66.
 * 
 * What is the value of the root node?
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node node_t;

struct node {
  int qchild;
  int qmeta;
  int value;
  node_t **children;
};

node_t *read_node() {
  int i, tmp;

  node_t *n = malloc(sizeof(node_t));
  scanf("%d %d", &n->qchild, &n->qmeta);
  n->children = malloc(sizeof(node_t) * n->qchild);
  n->value = 0;

  if (n->qchild) {
    for (i = 0; i < n->qchild; i++) {
      n->children[i] = read_node();
    }

    if (n->qmeta) {
      for (i = 0; i < n->qmeta; i++) {
        scanf("%d", &tmp);

        if (tmp > 0 && tmp <= n->qchild) {
          n->value += n->children[tmp - 1]->value;
        }
      }
    }
  } else {
    for (i = 0; i < n->qmeta; i++) {
      scanf("%d", &tmp);
      n->value += tmp;
    }
  }

  return n;
}

int main(int argc, char const *argv[]) {
  printf("Value of the root node: %d\n", read_node()->value);

  // free... meh

  return 0;
}
