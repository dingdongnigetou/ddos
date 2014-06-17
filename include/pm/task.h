/*
 * (C) 2014 Jindong Huang
 *
 * include/task.h
 *
 * structure pcb and interfaces on 
 * control task
 */

#ifndef _TASK_H
#define _TASK_H

#define NR_TASK 

struct pcb{
	long state;
	long counter;
	long priority;
	long exit_code;
	long pid;
	long ppid;
	long ptb; /* process table base address */
};

#endif /* _TASK_H */

