#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
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
	//printf("FIFO\n\n");
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
	sigaction(SIHCHLD, &sa, NULL);

	int ready, t;
	for(ready = 0, t = 0; done < num; t++){
		while(ready < num && in->p[arr[ready]].R <= t){
			//printf("Index: %d, time: %d\n", arr[ready], t);
			head = heap_push(head, in->p[arr[ready]], in->p[arr[ready]].R);
			ready++;

		}

		if(running == 0){
			head = heap_pop(head);
			if(head != NULL){
				if(head->pop == head)
					head = NULL;
				fork_process(&pid[done], head->pop->p.N, head->pop->p.T);
			}
		}

		unit_time();
	}

	/*for(int i = 0; i < num; i++){
		head = heap_push(head, in->p[arr[i]], in->p[arr[i]].R);
	}
	for(int i = 0; i < num; i++){
		head = heap_pop(head);
	}*/
}