/*
 * main.h
 *
 *  Created on: May 2, 2024
 *      Author: Usef
 */

#ifndef MAIN_H_
#define MAIN_H_

#define SIZE_TASK_STACK				1024U
#define SIZE_SCHED_STACK			1024U

#define SRAM_START					0x20000000U
#define SIZE_SRAM					(128*1024)
#define SRAM_END					((SRAM_START) + (SIZE_SRAM))



void Task1_Handler(void);
void Task2_Handler(void);
void Task3_Handler(void);
void Task4_Handler(void);


#endif /* MAIN_H_ */
