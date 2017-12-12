#ifndef QUEUE_T
#define QUEUE_T

#include "ll.h"

typedef ll_node_t q_node_t;
typedef ll_t q_t;

#define q_queue_create ll_list_create
#define q_node_create ll_node_create
#define q_enqueue ll_prepend
#define q_dequeue ll_remove_tail
#define q_empty ll_empty
#define q_print ll_print

#endif
