#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "include/structure.h"
#include "include/sort.h"
#include "include/all.h"

int ready_fifo = 0;
int done_fifo = 0;
pid_t pid_fifo[10000];

void child_handler_fifo(){
	wait(NULL);
	done_fifo++;
}

int adjust_proirity_fifo(void){
	if(ready_fifo > done_fifo){
		set_priority(pid_fifo[done_fifo], 99);
		return 1;
	}
	return 0;
}

int fifo(Input *in, int num){
	int arr[10000];
	for(int i = 0; i < num; i++)
		arr[i] = i;

	merge_sort(in, arr, 0, num - 1);

	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = child_handler_fifo;
	sigaction(SIGCHLD, &sa, NULL);

	int t, child;
	for(t = 0; done_fifo < num; t++){
		while(ready_fifo < num && in->p[arr[ready_fifo]].R <= t){
			fork_process(&pid_fifo[ready_fifo], in->p[arr[ready_fifo]].N, in->p[arr[ready_fifo]].T);
			ready_fifo++;
		}
		child = adjust_proirity_fifo();
		if(child == 0)
			unit_time();
	}
	return 0;
}