#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include "include/structure.h"

void unit_time(){
	volatile unsigned long i;
	for(i = 0; i < 1000000UL; i++)
		;
}

void set_cpu(pid_t pid, int n){
	cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(n, &mask);
	if(sched_setaffinity(pid, sizeof(mask), &mask) != 0){
		fprintf(stderr, "Failed to set cpu!\n");
	}

	struct sched_param param;
	param.sched_priority = sched_get_priority_max(SCHED_FIFO);
	if(sched_setscheduler(pid, SCHED_FIFO, &param) != 0){
		fprintf(stderr, "Failed to set priority!\n");
	}
}

void fork_process(pid_t* pid, char* N, int T){
	if((*pid = fork()) == 0){
		char T_string[20];
		sprintf(T_string, "%d", T);
		if(execl("./process", "./process", N, T_string, (char *)0) == -1){
			fprintf(stderr, "Failed to exec!\n");
		}
	}
	set_cpu(*pid, 1);
}