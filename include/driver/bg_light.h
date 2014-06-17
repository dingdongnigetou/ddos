/*
 * (C) 2014 Jindong Huang
 *
 * include/bg_light.h
 *
 * The interface of bglight.c.
 * You should start back ground light first 
 * if you want to control LCD.
 *
 */

#ifndef _BGLIGHT_H_
#define _BGLIGHT_H_

#include <types.h>

/* set the background light of LCD with brightness */
int set_bglight(u_char brightness);

#endif /* _BGLIGHT_H_ */

