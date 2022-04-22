/*
 * Agent2.h
 *
 *  Created on: Apr 11, 2022
 *      Author: Rafael
 */

#ifndef TASKS_AGENT2_AGENT2_H_
#define TASKS_AGENT2_AGENT2_H_

#include "common.h"
#include "phantom_vars.h"

void agent2Init(QueueArr_t);
void vTaskAgent2(void* pvParams);


#endif /* TASKS_AGENT2_AGENT2_H_ */
