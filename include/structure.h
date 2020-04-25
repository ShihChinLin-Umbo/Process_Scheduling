#define _GNU_SOURCE

struct process{
	char N[32];
	int R, T;
};
typedef struct process Process;

struct input{
	Process p[10000]; //assume num <= 10000
};
typedef struct input Input;

struct heap_node{
	Process p;
	int priority;
	int index;
	int size;
	struct heap_node *left;
	struct heap_node *right;
	struct heap_node *parent;
	struct heap_node *pop;
};
typedef struct heap_node HEAP_NODE;