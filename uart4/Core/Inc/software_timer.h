/*
 * software_timer.h
 *
 *  Created on: Nov 20, 2023
 *      Author: Lan Vi
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

extern int timer0_flag;

void setTimer0(int duration);
void timerRun();

#endif /* INC_SOFTWARE_TIMER_H_ */
