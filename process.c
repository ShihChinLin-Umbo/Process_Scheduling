#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include "include/all.h"

int main(int argc, char **argv){
	if(argc != 3){
		fprintf(stderr, "Only %d argv.\nusage: ./program_name process_name excute_time\n", argc);
		return 1;
	}

	char *name = argv[1];
	int excute_time = atoi(argv[2]);
	pid_t pid = getpid();
	printf("%s %d\n", name, pid);

	long long start, end;
	start = syscall(334);
	for(int i = 0; i < excute_time; i++){
		unit_time();
		if(i != excute_time -1){
			set_priority(pid, 1);
		}
	}
	end = syscall(334);

	syscall(335, pid, start, end);
	return 0;
}