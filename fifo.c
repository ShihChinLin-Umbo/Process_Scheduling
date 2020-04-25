#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "include/structure.h"

int fifo(Input *in, int num){
	printf("FIFO\n");
	for(int i = 0; i < num; i++){
		printf("%s %d %d\n", in->p[i].N, in->p[i].R, in->p[i].T);
	}
}