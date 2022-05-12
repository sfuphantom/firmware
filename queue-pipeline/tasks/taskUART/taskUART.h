/*
 * taskUART.h
 *
 *  Created on: Apr 19, 2022
 *      Author: Rafael
 */

#ifndef TASKS_TASKUART_TASKUART_H_
#define TASKS_TASKUART_TASKUART_H_

#include "common.h"
#include "phantom_vars.h"
#include "phantom_config.h"

void debugger_init(QueueHandle_t);
void vTaskDebugger(void* pvParams);

#endif /* TASKS_TASKUART_TASKUART_H_ */
