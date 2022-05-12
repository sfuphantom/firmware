/*
 * Director.h
 *
 *  Created on: Apr 12, 2022
 *      Author: Rafael
 */

#ifndef TASKS_DIRECTOR_DIRECTOR_H_
#define TASKS_DIRECTOR_DIRECTOR_H_
#include "phantom_vars.h"


typedef struct Control_t{
    TaskHandle_t agent1;
    TaskHandle_t agent2;
    TaskHandle_t actor;
}Control_t;

void directorInit(QueueArr_t, Control_t);
void vTaskDirector(void* pvParams);




#endif /* TASKS_DIRECTOR_DIRECTOR_H_ */
