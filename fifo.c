#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include "include/structure.h"
#include "include/heap.h"
#include "include/sort.h"
#include "include/all.h"

int running = 0;
int done = 0;

void child_handler(){
	wait(NULL);
	running = 0;
	done++;
}

int fifo(Input *in, int num){
	HEAP_NODE *head = NULL;
	int arr[10000];
	pid_t pid[10000];
	for(int i = 0; i < num; i++)
		arr[i] = i;

	merge_sort(in, arr, 0, num - 1);

	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = child_handler;
	sigaction(SIGCHLD, &sa, NULL);

	int ready, t;
	for(ready = 0, t = 0; done < num; t++){
		while(ready < num && in->p[arr[ready]].R <= t){
			head = heap_push(head, in->p[arr[ready]], in->p[arr[ready]].R);
			ready++;

		}

		if(running == 0){
			head = heap_pop(head);
			if(head != NULL){
				running = 1;
				fork_process(&pid[done], head->pop->p.N, head->pop->p.T);
				if(head->pop == head)
					head = NULL;
			}
		}

		unit_time();
	}
}