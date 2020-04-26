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

int ready_psjf = 0;
int done_psjf = 0;
pid_t pid_psjf[10000];
HEAP_NODE *head_psjf = NULL;
HEAP_NODE *run_node_psjf = NULL;

void child_handler_psjf(){
	wait(NULL);
	done_psjf++;
}

void pop_psjf(){
	head_psjf = heap_pop(head_psjf);
	run_node_psjf = head_psjf->pop;
	if(head_psjf->pop == head_psjf){
		head_psjf = NULL;
	}
	return;
}

int adjust_proirity_psjf(Input *in, int t){
	if(ready_psjf > done_psjf){
		pop_psjf();
		in->p[run_node_psjf->index].T--;
		if(in->p[run_node_psjf->index].T > 0)
			head_psjf = heap_push(head_psjf, in->p[run_node_psjf->index], in->p[run_node_psjf->index].T, run_node_psjf->index);
		set_priority(pid_psjf[run_node_psjf->index], 99);
		return 1;
	}
	return 0;
}

int psjf(Input *in, int num){
	int arr[10000];
	pid_t pid[10000];
	for(int i = 0; i < num; i++)
		arr[i] = i;

	merge_sort(in, arr, 0, num - 1);

	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = child_handler_psjf;
	sigaction(SIGCHLD, &sa, NULL);

	int t, child;
	for(t = 0; done_psjf < num; t++){
		while(ready_psjf < num && in->p[arr[ready_psjf]].R <= t){
			head_psjf = heap_push(head_psjf, in->p[arr[ready_psjf]], in->p[arr[ready_psjf]].T, arr[ready_psjf]);
			fork_process(&pid_psjf[ready_psjf], in->p[arr[ready_psjf]].N, in->p[arr[ready_psjf]].T);
			ready_psjf++;
		}
		child = adjust_proirity_psjf(in, t);
		if(child == 0)
			unit_time();
	}
	return 0;
}