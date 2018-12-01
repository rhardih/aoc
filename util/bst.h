/**
 * BST
 *
 * This defines a basic binary search tree, as defined in CLRS,  with the
 * following structures and operations:
 *
 * bst_tree_t
 * bst_node_t
 *
 * bst_search
 * bst_minimum
 * bst_maximum
 * bst_predecessor
 * bst_successor
 * bst_insert
 * bst_delete
 * bst_iotw
 * bst_free
 * bst_tree_new
 * bst_node_new
 */

#ifndef BST
#define BST

typedef struct bst_node bst_node_t;

struct bst_node {
  void *key;

  bst_node_t *left;
  bst_node_t *right;
  bst_node_t *parent;
};


typedef struct {
  bst_node_t *root;
} bst_tree_t;

/**
 * Search
 *
 * Iterative search for node of with certain valued key.
 *
 * Search direction is dictated by the output of compare. Negative will search
 * left child, positive right. For equality compare is expected to return zero.
 */
bst_node_t *bst_search(bst_node_t *x, void *k, int (*compare)(const void *, const void *));

/**
 * Minimum
 *
 * Returns leftmost/lowest node of the tree.
 */
bst_node_t *bst_minimum(bst_node_t *x);

/**
 * Maximum
 *
 * Returns rightmost/highest node of the tree.
 */
bst_node_t *bst_maximum(bst_node_t *x);

/**
 * Predecessor
 *
 * Returns the node with the highest key still smaller than the key of provided
 * node.
 */
bst_node_t *bst_predecessor(bst_node_t *x);

/**
 * Successor
 *
 * Returns the node with smallest key still greater than the key of provided
 * node.
 */
bst_node_t *bst_successor(bst_node_t *x);

/**
 * Insert
 *
 * Inserts node into tree according to the output of compare. Non-zero will
 * assign as left child, zero right.
 */
void bst_insert(bst_tree_t *tree, bst_node_t *x, int (*compare)(const void *, const void *));

/**
 * Delete
 *
 * Removes a node from the tree.
 */
void bst_delete(bst_tree_t *t, bst_node_t *z);

/**
 * Inorder tree walk
 */
void bst_iotw(bst_node_t *x, void (*printer)(void *));

/**
 * Recursive free of all nodes in tree
 */
void bst_free(bst_node_t *tree);

/**
 * Return a pointer to a new tree with root set to n.
 *
 * Pointer to be freed after use.
 */
bst_tree_t *bst_tree_new(bst_node_t *n);

/**
 * Return a pointer to a new node with key set to p and parent, left and right
 * set to NULL.
 *
 * Pointer to be freed after use.
 */
bst_node_t *bst_node_new(void *p);

#endif
