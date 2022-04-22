/*
 * Director.h
 *
 *  Created on: Apr 12, 2022
 *      Author: Rafael
 */

#ifndef TASKS_DIRECTOR_DIRECTOR_H_
#define TASKS_DIRECTOR_DIRECTOR_H_
#include "phantom_vars.h"

typedef struct DirectorParams_t{
    QueueArr_t q;
    TaskHandle_t task_handles[5];
}DirectorParams_t;

void vTaskDirector(void* pvParams);




#endif /* TASKS_DIRECTOR_DIRECTOR_H_ */
