/*
 * Agent2.c
 *
 *  Created on: Apr 11, 2022
 *      Author: Rafael
 */


#include "Agent2.h"

static QueueArr_t q;

void agent2Init(QueueArr_t other){

    /* Deep copy elements */
    q.rx = other.rx;
    q.tx = other.tx; 
}
void vTaskAgent2(void* pvParams){

    static AgentMessage_t data = {0};
    static AgentMessage_t* data_ptr = &data;
    data_ptr->id = AGENT_TWO;

    while(true){


        // read inputs from pin
        data_ptr->msg = gioGetBit(gioPORTB, 2);

        // send data to actor
        xQueueSend(
            &q.tx,
            ( void * ) data_ptr,
            ( TickType_t ) 10

        );

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
