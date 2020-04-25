#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "include/structure.h"

int sjf(Input *in, int num){
	printf("SJF\n");
	for(int i = 0; i < num; i++){
		printf("%s %d %d\n", in->p[i].N, in->p[i].R, in->p[i].T);
	}
}