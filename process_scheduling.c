#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/*#include <sched.h>*/ //for certain CPU
#include "include/structure.h"
#include "include/all.h"
#include "include/fifo.h"
#include "include/rr.h"
#include "include/sjf.h"
#include "include/psjf.h"

void unknown_policy(){
	fprintf(stderr, "Unknown scheduling policy!\n");
	exit(1);
}

int main(){
	set_cpu(getpid(), 0);
	set_priority(getpid(), 50);

	//read input
	char policy[5];
	int num;
	Input *in;

	scanf("%s", policy);
	scanf("%d", &num);
	in = (Input *)malloc(num * sizeof(Process));
	for(int i = 0; i < num; i++){
		scanf("%s%d%d", in->p[i].N, &in->p[i].R, &in->p[i].T);
	}
	
	//determine policy
	switch(policy[0]){
		case 'F':
			if(strcmp(policy, "FIFO") != 0){
				unknown_policy();
			}
			fifo(in, num);
			break;
		case 'R':
			if(strcmp(policy, "RR") != 0){
				unknown_policy();
			}
			rr(in, num);
			break;
		case 'S':
			if(strcmp(policy, "SJF") != 0){
				unknown_policy();
			}
			sjf(in, num);
			break;
		case 'P':
			if(strcmp(policy, "PSJF") != 0){
				unknown_policy();
			}
			psjf(in, num);
			break;
		default:
			unknown_policy();
			break;
	}
	return 0;
}