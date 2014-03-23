/*
 * (C) 2014 JinDongHuang
 *
 * init/init.c
 *
 * boot initialization
 *
 */

#include "s3c6410.h"

void disable_watch_dog();
void clock_init();

void disable_watch_dog()
{
	WATDOG = 0;
}

