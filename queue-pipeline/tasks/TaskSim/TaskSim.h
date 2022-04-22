/*
 * TaskSim.h
 *
 *  Created on: Apr 11, 2022
 *      Author: Rafael
 */

#ifndef TASKS_TASKSIM_TASKSIM_H_
#define TASKS_TASKSIM_TASKSIM_H_

#include "FreeRTOS.h"
#include "os_task.h"
#include "os_queue.h"
#include <stdlib.h>
#include "sys_common.h"
#include "string.h"
#include "sci.h"
#include "stdio.h"
#include "common.h"
#include "phantom_vars.h"

typedef struct Simulation_t{
    
    QueueHandle_t agent1_q;
    QueueHandle_t agent2_q;
    AgentMessage_t agent1;
    AgentMessage_t agent2;

}Simulation_t;

void vTaskSim(void* pvParams);

void simInit(QueueArr_t, QueueArr_t);

#endif /* TASKS_TASKSIM_TASKSIM_H_ */
