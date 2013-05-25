
#include <stdio.h>
#include <stdlib.h>

#include "fuzzy.h"

/* cpu (time)
 *
 * 100         /+---------
 *            /
 * 20  +-----+
 *     |
 *     0     40 60       inf
 */
static DECLARE_INIT_FS(fuzzy_set_cpu,0,20,40,20,60,100,65,100);

/* disk (bytes)
 * 
 *                          +-----------------------
 *			                   /
 * 			                  /
 * 80                    /
 *                      /
 *           	         /
 * 40          +-----++
 *            /
 * 10 -------+
 *
 *    0     196  4096   500,096  10^7 + 96             
 */
static DECLARE_INIT_FS(fuzzy_set_disk,196,10,4096,40,500096,80,10000096,100);


int main(int argc, char *argv[])
{
  int cpu_usage = 22;
  int cpu_deg = fuzzy_degree(&fuzzy_set_cpu, cpu_usage);
  printf("%d %d\n", cpu_usage, cpu_deg);
  
	return 0;
} 
