#ifndef LL_T
#define LL_T

typedef struct ll_node ll_node_t;

struct ll_node {
  void *value;
  ll_node_t *next;
};

typedef struct {
  ll_node_t *first;
} ll_t;

ll_t *ll_list_create();
ll_node_t *ll_node_create();
void ll_prepend(ll_t *list, ll_node_t *node);
void ll_append(ll_t *list, ll_node_t *node);
ll_node_t *ll_remove_tail(ll_t *list);
ll_node_t *ll_remove_head(ll_t *list);
int ll_empty(ll_t *list);
void ll_print(ll_t *list, void (*printer)(void *));

#endif
