/*
 * (C) 2014 Jindong Huang
 *
 * pm/mutex.c
 */

unsigned volatile int semaphore = 0;

void mutex_try_lock()
{
	register unsigned int sema_addr = (unsigned int) &semaphore;

	__asm__ volatile (
		 "spin:\n"
		 "MOV r1, %0\n"
		 "MOV r2, #0x01\n"
		 "SWP r3, r2, [r1]\n"
		 "CMP r3, #0x01\n"
		 "BEQ spin"
		 :
		 : "r"(sema_addr)
	);

}

void mutex_unlock()
{
	register unsigned int sema_addr = (unsigned int) &semaphore;   

	__asm__ volatile (
		 "MOV r1, %0\n"
		 "MOV r2, #0\n"
		 "SWP r0, r2,[r1]\n"
		 :
		 : "r"(sema_addr)   
	);
}

