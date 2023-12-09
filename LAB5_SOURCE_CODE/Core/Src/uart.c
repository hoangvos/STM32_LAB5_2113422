/*
 * uart.c
 *
 *  Created on: Dec 9, 2023
 *      Author: hoang
 */
#include "uart.h"
enum UART_STATE cur_uart_state = INIT;
uint8_t temp = 0;
uint8_t buffer[MAX_BUFFER_SIZE] = {0};

uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;


void uart_communication_fsm(){
	switch(cur_uart_state){
	case INIT:
		HAL_ADC_Start(&hadc1);
		cur_uart_state = RST_STATE;
		break;
	case RST_STATE:
		if(command_flag == FLAG_RST){
			ADC_value = HAL_ADC_GetValue(&hadc1);
			HAL_UART_Transmit(&huart2 , (void*)str , sprintf(str,"!ADC=%ld#\r\n", ADC_value ), 1000);
			HAL_GPIO_TogglePin( LED_RED_GPIO_Port , LED_RED_Pin );
			cur_uart_state = OK_STATE;
			setTimer(300);
		}
		break;
	case OK_STATE:
		if(timer_flag){
			HAL_UART_Transmit(&huart2 , (void*)str , sprintf(str,"!ADC=%ld#\r\n", ADC_value ), 1000);
			HAL_GPIO_TogglePin( LED_RED_GPIO_Port , LED_RED_Pin );
			setTimer(300);
		}
		if(command_flag == FLAG_OK){
			cur_uart_state = RST_STATE;
		}

		break;
	}
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart){
	if(huart->Instance == USART2 ){
		//HAL_UART_Transmit(&huart2 , &temp , 1, 50) ;
		buffer[index_buffer++]=temp;
		if( index_buffer == 30) index_buffer = 0;
		buffer_flag = 1;
		HAL_UART_Receive_IT(&huart2, &temp, 1);
	}
}


