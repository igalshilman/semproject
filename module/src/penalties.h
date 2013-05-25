
#ifndef __PENALTIES_H__
#define __PENALTIES_H__

#define PENALTY_RANGE (101)
#define MS_TO_NS(TIME)	((TIME) * 1000 * 1000)	


/* 
 * Here we define the wakeup penalty for a task, as function of its fuzzy membership degreee.
 * A penalty ranges from 6ms (degree of 0) to ~43ms (degree of 1).
 */

static unsigned int task_penalty[PENALTY_RANGE] __read_mostly = {0};

static void init_task_penalties(void) 
{
	int i;
	u64 p = MS_TO_NS(6);
	
	for (i = 0; i < PENALTY_RANGE ; i++) {
		task_penalty[i] = (unsigned int)p;
		p = (p * 1020) / 1000;
	}
}

static inline unsigned int deadline_penalty(int degree)
{
	return task_penalty[degree];
}

#endif
