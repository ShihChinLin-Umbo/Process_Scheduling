#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include "include/all.h"

int main(int argv, char **argv){
	if(argc != 3){
		fprintf(stderr, "usage: ./program_name process_name excute_time")
		return 1;
	}

	char *name = argv[1];
	int excute_time = atoi(argv[2]);
	int pid = getpid();
	printf("%s %d\n", name, pid);

	long long start, end;
	start = syscall(334);
	for(int i = 0; i < excute_time; i++)
		unit_time()
	end = syscall(334);

	syscall(335, pid, start, end);
	return 0;
}