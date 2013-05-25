#ifndef __LOG_ENTRY__H_
#define __LOG_ENTRY__H_

#ifndef __KERNEL__ 
/* Since we can not include the definition of u64, cputime64_t and cputime_t,
 * we need to redefine them here.
 * We will do it by testing the value of stdlib's ULONG_MAX.
 */
#include <limits.h>
#if (((ULONG_MAX) >> 33) > 0)
	/* 64 bit */
	typedef unsigned long cputime64_t;
	typedef unsigned long cputime_t;
#else
	/* 32 bit */
	typedef unsigned long long cputime64_t;
	typedef unsigned long cputime_t;
#endif

/* TASK_COMM_LEN is define at sched.h and it had stayed constat for years. */
#define TASK_COMM_LEN 16

#else /* __KERNEL__ */

#if TASK_COMM_LEN != 16
#error "Incorrect TASK_COMM_LEN defined at __FILE__, the correct size defined at sched.h" 
#endif

#endif /* __KERNEL__ */

struct log_entry {
	unsigned long	timestamp;
	/* identity - defined at sched.h */
	char		comm[TASK_COMM_LEN];
	pid_t		pid;
	/* Machine learning - types defined at compute_cognitiv_score */
	long		target;
	int		output;
	/* acc stuff defined at sched.h in struct task_struct */
	cputime_t	user; 
	cputime_t	kern;
	/* fuzzy	*/
	unsigned int	fuzzy_cpu_load_u; 
  unsigned int	fuzzy_cpu_load_k;
  unsigned int	fuzzy_io_read;
  unsigned int	fuzzy_io_write;
	unsigned int	fuzzy_net_read;
	unsigned int	fuzzy_net_write;
	unsigned int	fuzzy_minor_fault;
	unsigned int	fuzzy_major_fault;
	unsigned int 	fuzzy_rss_size;
	/* raw data */	
  unsigned long	io_write; 
	unsigned long	io_read;
  unsigned long	net_write;
	unsigned long	net_read;
	unsigned long	number_vulentary_context_switches;
  unsigned long	number_in_vulentary_context_switches;
	/* memory	*/	
	unsigned long	minor_fault;
	unsigned long	major_fault;
	unsigned long	rss_size;
	/* system raw data */
	unsigned long	sys_io_write;
  unsigned long	sys_io_read;
	unsigned long	sys_net_read;
	unsigned long	sys_net_write;
 	unsigned long	sys_cpu_load;
  unsigned long	sys_mem_load;
};

#endif

