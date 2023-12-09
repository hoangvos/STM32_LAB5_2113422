/*
 * uart.h
 *
 *  Created on: Dec 9, 2023
 *      Author: hoang
 */

#ifndef INC_UART_H_
#define INC_UART_H_
#include "main.h"
#include "command.h"
#include "software_timer.h"
#define MAX_BUFFER_SIZE	30

enum UART_STATE{
	INIT,
	RST_STATE,
	OK_STATE
};


extern enum UART_STATE cur_uart_state;
extern uint8_t temp;
extern uint8_t buffer[MAX_BUFFER_SIZE];
extern uint8_t index_buffer;
extern uint8_t buffer_flag;


void uart_communication_fsm();
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart);

#endif /* INC_UART_H_ */
