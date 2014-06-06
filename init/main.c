/*
 * (C) 2014 JinDongHuang
 *
 * init/main.c
 *
 * Initialize the os after boot.
 *
 */
#include <unistd.h>

int main()
{	
	char c;

	ledop(1, 1);
	while(1);

	return 0;
}

