
#include <stdio.h>
#include <stdlib.h>

#include "../src/fuzzy.h"

#define __read_mostly 
typedef unsigned long u64;
#include "../src/penalties.h"

/* 
 * shows the expected delay for a task with a given CPU usage.
 *
 */
static DECLARE_INIT_FS(fuzzy_set_cpu,10,1,40,40,50,80,70,100);

int main(int argc, char *argv[])
{
  int cpu_usage = 0;
  int cpu_deg;
  unsigned int pen = 0;

  init_task_penalties();
  
  
  printf("cpu usage\t\tfuzzy membership degree\t\twakeup delay\n");
  for (cpu_usage = 0 ; cpu_usage <= 100 ; cpu_usage++) {
    cpu_deg = fuzzy_degree(&fuzzy_set_cpu, cpu_usage);
    pen = deadline_penalty(cpu_deg); 
    printf("%d\t\t\t%d\t\t\t%ld\n", cpu_usage, cpu_deg, pen);
  }

	return 0;
} 

