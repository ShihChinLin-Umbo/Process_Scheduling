#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "include/structure.h"

void unit_time(){
	volatile unsigned long i;
	for(i = 0; i < 1000000UL; i++)
		;
}