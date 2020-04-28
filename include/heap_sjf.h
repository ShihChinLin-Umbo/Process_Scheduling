#define _GNU_SOURCE

HEAP_NODE* heap_push_sjf(HEAP_NODE *head, Process p, int priority, int index);
HEAP_NODE* heap_pop_sjf(HEAP_NODE *head);
void print_heap_sjf(HEAP_NODE *head);