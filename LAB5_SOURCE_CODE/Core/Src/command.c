/*
 * command.c
 *
 *  Created on: Dec 9, 2023
 *      Author: hoang
 */
#include "command.h"
enum COMMAND_FLAG command_flag = NO_FLAG;
enum COMMAND_STATE command_state = CHECK_BUFFER;
uint8_t a = 'b';


void command_parser_fsm(){
	uint8_t pre_1 = (index_buffer - 1) < 0 ? index_buffer + 29 :index_buffer - 1 ;
	uint8_t pre_2 = (index_buffer - 2) < 0 ? index_buffer + 28 :index_buffer - 2 ;
	uint8_t pre_3 = (index_buffer - 3) < 0 ? index_buffer + 27 :index_buffer - 3 ;
	uint8_t pre_4 = (index_buffer - 4) < 0 ? index_buffer + 26 :index_buffer - 4 ;
	uint8_t pre_5 = (index_buffer - 5) < 0 ? index_buffer + 25 :index_buffer - 5 ;
	switch(command_state){
	case CHECK_BUFFER:
//		HAL_UART_Transmit(&huart2 , &buffer[pre_1] , 1, 50) ;
//		HAL_UART_Transmit(&huart2 , &buffer[pre_2] , 1, 50) ;
//		HAL_UART_Transmit(&huart2 , &buffer[pre_3] , 1, 50) ;
//		HAL_UART_Transmit(&huart2 , &buffer[pre_4] , 1, 50) ;
//		HAL_UART_Transmit(&huart2 , &buffer[pre_5] , 1, 50) ;
//		HAL_UART_Transmit(&huart2 , (void*)str , sprintf(str , "\r\n"), 1000);

		if(buffer[pre_1]=='#' && buffer[pre_2] == 'T' && buffer[pre_3] == 'S' && buffer[pre_4] == 'R' && buffer[pre_5] == '!'){
			HAL_UART_Transmit(&huart2, (void*)str , sprintf(str , "!RST#"), 1000) ;
			command_state = FINISH_RST;
			buffer_flag = 1;
		}
		if(buffer[pre_1] == '#' && buffer[pre_2] == 'K' && buffer[pre_3] == 'O' && buffer[pre_4] == '!'){
			HAL_UART_Transmit(&huart2, (void*)str , sprintf(str , "!OK#"), 1000) ;
			command_state = FINISH_OK;
			buffer_flag = 1;
		}
		break;
	case FINISH_RST:
		HAL_UART_Transmit(&huart2 , (void*) str , sprintf(str , "\r\n"), 1000);
		command_state = CHECK_BUFFER;
		command_flag = FLAG_RST;
		buffer_flag = 0;
		break;
	case FINISH_OK:
		HAL_UART_Transmit(&huart2 , (void*) str , sprintf(str , "\r\n"), 1000);
		command_state = CHECK_BUFFER;
		command_flag = FLAG_OK;
		buffer_flag = 0;
	}
}


