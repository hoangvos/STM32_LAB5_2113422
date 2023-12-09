/*
 * command.h
 *
 *  Created on: Dec 9, 2023
 *      Author: hoang
 */

#ifndef INC_COMMAND_H_
#define INC_COMMAND_H_
#include "main.h"
#include "software_timer.h"
#include "uart.h"

enum COMMAND_FLAG{
	NO_FLAG,
	FLAG_RST,
	FLAG_OK
};
enum COMMAND_STATE{
	CHECK_BUFFER,
	FINISH_RST,
	FINISH_OK
};
extern enum COMMAND_FLAG command_flag;
extern enum COMMAND_STATE command_state;


void command_parser_fsm();

#endif /* INC_COMMAND_H_ */
