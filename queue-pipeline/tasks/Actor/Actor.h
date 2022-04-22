/*
 * Actor.h
 *
 *  Created on: Apr 11, 2022
 *      Author: Rafael
 */

#ifndef TASKS_ACTOR_ACTOR_H_
#define TASKS_ACTOR_ACTOR_H_
#include <stdlib.h>
#include "stdio.h"
#include "phantom_vars.h"
#include "gio.h"
#include "common.h"
void vTaskActor(void* pvParams);

void actorInit(QueueArr_t);
typedef struct Actor_t
{
    /* Queue Handles */
    QueueArr_t queue;

    /* Input Data */ 
    AgentMessage_t data;
    uint8_t agent1_state;
    uint8_t agent2_state;
    
    /* Output Data */
    uint8_t tx_data;

}Actor_t;

uint8_t actor_logic(AgentMessage_t, uint8_t, uint8_t);



#endif /* TASKS_ACTOR_ACTOR_H_ */
