/*
 * Agent1.c
 *
 *  Created on: Apr 11, 2022
 *      Author: Rafael
 */


#include "Agent1.h"

static QueueArr_t q;

void agent1Init(QueueArr_t other){

    /* Deep copy elements */
    q.rx = other.rx;
    q.tx = other.tx; 
}

void vTaskAgent1(void* pvParams){


    static AgentMessage_t data = {0};
    static AgentMessage_t* data_ptr = &data;
    data_ptr->id = AGENT_ONE;

    while(true){


        // read inputs from pin
        data_ptr->msg = gioGetBit(gioPORTB, 1);

        // send data to actor
        xQueueSend(

            &q.tx,
            ( void * ) data_ptr,
            ( TickType_t ) 10

        );

        vTaskDelay(pdMS_TO_TICKS(100));

    }



}
