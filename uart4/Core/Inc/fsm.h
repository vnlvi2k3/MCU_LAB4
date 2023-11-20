/*
 * fsm.h
 *
 *  Created on: Nov 20, 2023
 *      Author: Lan Vi
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "main.h"
#include "software_timer.h"
#include <stdio.h>
#include <string.h>

#define WAIT 1
#define EXTRACT 2

#define LISTEN 6
#define CHECK 7
#define SEND 8

extern int parser_status;
int uart_status;
uint8_t command_data[30];
int command_flag;
uint32_t ADC_value;
uint8_t pos;
uint8_t len;

void command_parser_fsm();
void uart_communication_fsm();

#endif /* INC_FSM_H_ */
