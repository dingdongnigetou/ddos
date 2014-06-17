/*
 * (C) 2014 Jindong Huang
 *
 * include/pwm.h
 *
 * The interface of pwm -> timer.
 */

#ifndef _PWM_H_
#define _PWM_H_

void timer_init();

void timer_start();

void timer_stop();

void waitTimerTick();

#endif /* _PWM_H_ */

