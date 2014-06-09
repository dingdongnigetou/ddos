/*
 * (C) 2014 Jindong Huang
 *
 * driver/fiq.c
 *
 */

int sys_enfiq()
{
	asm(                          
		"mrs r0, spsr\n"
		"bic r0, r0, #0x40\n" 
		"msr spsr, r0\n" 
	   );

	return 0;
}

int sys_disfiq()
{
	asm(                     
		"mrs r0, spsr\n"
		"orr r0, r0, #0x40\n"
		"msr spsr, r0\n"
	   );

	return 0;
}

