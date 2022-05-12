/*
 * Agent1.h
 *
 *  Created on: Apr 11, 2022
 *      Author: Rafael
 */

#ifndef TASKS_AGENT1_AGENT1_H_
#define TASKS_AGENT1_AGENT1_H_

#include "FreeRTOS.h"
#include "os_task.h"
#include "os_queue.h"
#include <stdlib.h>
#include "sys_common.h"
#include "string.h"
#include "sci.h"
#include "stdio.h"
#include "common.h"
#include "gio.h"
#include "phantom_vars.h"
#include "het.h"

void agent1Init(QueueArr_t other);
void vTaskAgent1(void* pvParams);

#endif /* TASKS_AGENT1_AGENT1_H_ */
