/*
 * common.h
 *
 *  Created on: Apr 11, 2022
 *      Author: Rafael
 */

#ifndef COMMON_COMMON_H_
#define COMMON_COMMON_H_

#include "FreeRTOS.h"
#include "os_task.h"
#include "os_queue.h"
#include <stdlib.h>
#include "sys_common.h"
#include "string.h"
#include "sci.h"
#include "stdio.h"
#include "phantom_vars.h"


#define PC_UART scilinREG



void split(char* str, const char* delimeter, char* buffer, int buffer_size);
void delayms(uint16_t ms);
void UARTSend(sciBASE_t *sci, char data[]);
void UARTInit(sciBASE_t *sci, uint32 baud);
void UARTprintf(char msg[]);


void debug_init(QueueHandle_t);
uint8_t log_messagef(uint32_t index);
uint8_t log_valuef(uint32_t value);

#endif /* COMMON_COMMON_H_ */
