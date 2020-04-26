#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "include/structure.h"
#include "include/heap.h"
#include "include/sort.h"
#include "include/all.h"

int ready_sjf = 0;
int done_sjf = 0;
int running_sjf = 0;
pid_t pid_sjf[10000];
HEAP_NODE *head_sjf = NULL;
HEAP_NODE *run_node_sjf = NULL;

void child_handler_sjf(){
	wait(NULL);
	done_sjf++;
	running_sjf = 0;
}

void pop_sjf(){
	head_sjf = heap_pop(head_sjf);
	run_node_sjf = head_sjf->pop;
	if(head_sjf->pop == head_sjf){
		head_sjf = NULL;
	}
	return;
}

int adjust_proirity_sjf(){
	if(ready_sjf > done_sjf){
		running_sjf = 1;
		set_priority(pid_sjf[run_node_sjf->index], 99);
		return 1;
	}
	return 0;
}

int sjf(Input *in, int num){
	int arr[10000];
	pid_t pid[10000];
	for(int i = 0; i < num; i++)
		arr[i] = i;

	merge_sort(in, arr, 0, num - 1);

	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = child_handler_sjf;
	sigaction(SIGCHLD, &sa, NULL);

	int t, child;
	for(t = 0; done_sjf < num; t++){
		while(ready_sjf < num && in->p[arr[ready_sjf]].R <= t){
			head_sjf = heap_push(head_sjf, in->p[arr[ready_sjf]], in->p[arr[ready_sjf]].T, arr[ready_sjf]);
			fork_process(&pid_sjf[ready_sjf], in->p[arr[ready_sjf]].N, in->p[arr[ready_sjf]].T);
			ready_sjf++;
		}	
		if(running_sjf == 0 && head_sjf != NULL)
			pop_sjf();
		child = adjust_proirity_sjf();
		if(child == 0)
			unit_time();
	}
	return 0;
}