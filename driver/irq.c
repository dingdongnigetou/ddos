/*
 * (C) 2014 Jindong Huang
 *
 * driver/irq.c
 *
 */

int sys_enirq()
{
	asm(                          
		"mrs r0, spsr\n"
		"bic r0, r0, #0x80\n" 
		"msr spsr, r0\n" 
	   );

	return 0;
}

int sys_disirq()
{
	asm(                     
		"mrs r0, spsr\n"
		"orr r0, r0, #0x80\n"
		"msr spsr, r0\n"
	   );

	return 0;
}

