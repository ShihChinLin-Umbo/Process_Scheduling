#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "include/structure.h"
#include "include/sort.h"
#include "include/all.h"

int running_rr = 0;
int ready_rr = 0;
int done_rr = 0;
int count_rr = 0;
int queue[10000] = {0};
int front = 0, back = 0, current;
pid_t pid_rr[10000];

void push_rr(int i){
	back = (back + 1) % 10000;
	queue[back] = i;
}

int pop_rr(void){
	front = (front + 1) % 10000;
	return queue[front];
}

int get_size(void){
	if(front <= back)
		return back - front;
	return front - back;
}

void child_handler_rr(){
	wait(NULL);
	done_rr++;
	count_rr = 0;
	running_rr = 0;
}

int adjust_proirity_rr(void){
	if(ready_rr > done_rr){
		running_rr = 1;
		if(count_rr == 500){
			push_rr(current);
			current = pop_rr();
			count_rr = 0;
		}
		count_rr++;
		set_priority(pid_rr[current], 99);
		return 1;
	}
	return 0;
}

int rr(Input *in, int num){
	int arr[10000];
	for(int i = 0; i < num; i++)
		arr[i] = i;

	merge_sort(in, arr, 0, num - 1);

	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = child_handler_rr;
	sigaction(SIGCHLD, &sa, NULL);

	int t, child;
	for(t = 0; done_rr < num; t++){
		while(ready_rr < num && in->p[arr[ready_rr]].R <= t){
			push_rr(arr[ready_rr]);
			fork_process(&pid_rr[ready_rr], in->p[arr[ready_rr]].N, in->p[arr[ready_rr]].T);
			ready_rr++;
		}
		if(running_rr == 0 && get_size() != 0)
			current = pop_rr();
		child = adjust_proirity_rr();
		if(child == 0)
			unit_time();
	}
	return 0;
}