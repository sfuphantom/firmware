/*
 * Agent1.c
 *
 *  Created on: Apr 11, 2022
 *      Author: Rafael
 */


#include "Agent1.h"

static QueueArr_t q;
static QueueArr_t* q_ptr = &q;

void agent1Init(QueueArr_t other){

    /* Deep copy elements */
    q_ptr->tx = other.tx;
}

void vTaskAgent1(void* pvParams){


    static AgentMessage_t data = {0};
    static AgentMessage_t* data_ptr = &data;
    data_ptr->id = AGENT_ONE;

    while(true){

        // read inputs from pin
        data_ptr->msg = gioGetBit(hetPORT1, 15);

        // send data to actor
        xQueueSend(
            q_ptr->tx,
            ( void * ) data_ptr,
            ( TickType_t ) 10

        );

        vTaskDelay(pdMS_TO_TICKS(10));
    } // superloop
}
