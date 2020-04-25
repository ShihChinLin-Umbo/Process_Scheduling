#define _GNU_SOURCE

HEAP_NODE* heap_push(HEAP_NODE *head, Process p, int priority);
HEAP_NODE* heap_pop(HEAP_NODE *head);
void print_heap(HEAP_NODE *head);