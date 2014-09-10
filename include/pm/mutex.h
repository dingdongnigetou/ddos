/*
 * (C) 2014 Jindong Huang
 *
 * include/pm/mutex.h
 *
 */

#ifndef _MUTEX_H_
#define _MUTEX_H_

/*
 * 0 is unlock
 * 1 is lock
 */
extern unsigned int semaphore; /* define in mutex.c */

/*
 * try to lock semaphore, poll 
 */
void mutex_try_lock();

/*
 * unlock semaphore
 */
void mutex_unlock();

#endif /* _MUTEX_H_ */

