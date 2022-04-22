/*
 * Actor.c
 *
 *  Created on: Apr 11, 2022
 *      Author: Rafael
 */

#include "Actor.h"

/* Initialize struct */
static Actor_t actor_data = {
    .data = {0},
    .tx_data = 0,
    .agent1_state = 0,
    .agent2_state = 0,
    .queue={0}
};

static Actor_t* this = &actor_data; 

void actorInit(QueueArr_t other){

    /* Deep copy elements */
    this->queue.rx = other.rx;
    this->queue.tx = other.tx;
}


void vTaskActor(void* pvParams){
    
    /* Initialize intermediate variables */
    static BaseType_t rx_success = pdFALSE;

    while(true){

        /* receive data from agents (suspended until available data) */
        rx_success = xQueueReceive(
            this->queue.rx,
            &this->data,
            ( TickType_t ) pdMS_TO_TICKS(1)  // block for 1 tick
        );

        /* failed to receive data; do smt!! */
        if(rx_success == pdFALSE){
            continue;
        }

        /* act on agent data */
        this->tx_data = actor_logic(this->data, this->agent1_state, this->agent2_state);

        /* transmit data */
        xQueueSend(
            this->queue.tx,
            &this->tx_data,
            ( TickType_t ) 1
        );

    } // superloop

}

uint8_t actor_logic(AgentMessage_t data, uint8_t agent1_state, uint8_t agent2_state){


    switch(data.id){

        case AGENT_ONE:
            agent1_state = data.msg;

            gioSetBit(gioPORTB, 1, agent1_state);
//            log_messagef(MSG_ONE);
            log_valuef(data.msg);
            break;

        case AGENT_TWO:
            agent2_state =  data.msg;
            gioSetBit(gioPORTB, 2, agent2_state);
            break;
    } // switchcase
    return agent2_state && agent1_state;
}
