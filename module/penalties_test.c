
#include <stdio.h>
#include <stdlib.h>

#define __read_mostly 
typedef unsigned long u64;

#include "penalties.h"

int main(int argc, char *argv[])
{
	int i;
	init_task_penalties();
  printf("fuzzy membership degress [0, 100] vs scheduling penalty [6ms, 43ms]\n"); 

	for (i=0; i <= 100 ; i++) {
		printf("%d %d\n",i, deadline_penalty(i));
	}

	return 0;
} 
