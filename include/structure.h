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