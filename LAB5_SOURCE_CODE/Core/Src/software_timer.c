/*
 * software_timer.c
 *
 *  Created on: Dec 9, 2023
 *      Author: hoang
 */
#include<software_timer.h>
int counter = 0;
int timer_flag = 0;
void setTimer(int num){
	counter = num;
	timer_flag = 0;
}

void timer_run(){
	if(counter > 0){
		counter--;
		if(counter <= 0){
			timer_flag = 1;
		}
	}
}
