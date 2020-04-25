#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include "include/structure.h"
#include "include/heap.h"
#include "include/sort.h"
#include "include/all.h"

int running_sjf = 0;
int done_sjf = 0;

void child_handler_sjf(){
	wait(NULL);
	running_sjf = 0;
	done_sjf++;
}

int sjf(Input *in, int num){
	printf("SJF\n");
	HEAP_NODE *head = NULL;
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

	int ready, t;
	for(ready = 0, t = 0; done_sjf < num; t++){
		while(ready < num && in->p[arr[ready]].R <= t){
			head = heap_push(head, in->p[arr[ready]], in->p[arr[ready]].T);
			printf("\n%d\n", t);
			print_heap(head);
			printf("\n");
			ready++;
		}

		if(running_sjf == 0){
			head = heap_pop(head);
			if(head != NULL){
				running_sjf = 1;
				printf("fork at %d\n", t);
				fork_process(&pid[done_sjf], head->pop->p.N, head->pop->p.T);
				if(head->pop == head)
					head = NULL;
			}
		}

		unit_time();
	}
}