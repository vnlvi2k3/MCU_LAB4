/*
 * fsm.c
 *
 *  Created on: Nov 20, 2023
 *      Author: Lan Vi
 */

#include "fsm.h"
int command_flag = 0;
int parser_status = 0;
int uart_status = 0;
char s[100];
char endline[] = "\r\n";
int waiting_flag = 0;
uint32_t ADC_value = 0;
uint8_t pos = 0;
uint8_t len = 0;



void extract_data(){
	if((pos + len) <= MAX_BUFFER_SIZE){
		strncpy(command_data, buffer + pos, len);
	}
	else{
		char temp[10];
		strncpy(command_data, buffer + pos, MAX_BUFFER_SIZE - pos);
		strncpy(temp, buffer, len - (MAX_BUFFER_SIZE - pos));
		strcat(command_data, temp);
	}
}

void command_parser_fsm(){
	switch(parser_status){
	case WAIT:
		command_flag = 0;
		if(temp == '!'){
			pos = index_buffer;
			len = 0;
			memset(&command_data[0], 0, sizeof(command_data));
		}
		else if(temp == '#'){
			extract_data();
			HAL_UART_Transmit(&huart2, endline, sizeof(endline), 1000);
			command_flag = 1;
			uart_status = CHECK;
			parser_status = WAIT;
		}
		else{
			len++;
		}
		break;
	default:
		break;
	}
}

//command_flag = 0 khi check?
void uart_communication_fsm(){
	if(command_flag){
		switch(uart_status){
		case CHECK:
			if(strcmp(command_data, "RST") == 0){
				timer0_flag = 1;
				waiting_flag = 1;
				uart_status = SEND;
			}
			else if(strcmp(command_data, "OK") == 0){
				waiting_flag = 0;
			}
			else{
				if(waiting_flag){
					uart_status = SEND;
				}
			}
			break;
		case SEND:
			if(timer0_flag){
				setTimer0(300);
				HAL_ADC_Start(&hadc1);
				ADC_value = HAL_ADC_GetValue(&hadc1);
				HAL_ADC_Stop(&hadc1);
				HAL_UART_Transmit(&huart2, (void *)s, sprintf(s, "!ADC=%ld#\r\n", ADC_value), 1000);
				HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
			}
			break;
		default:
			break;
		}
	}
}
















