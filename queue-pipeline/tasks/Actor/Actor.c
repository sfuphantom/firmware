/*
 * Actor.c
 *
 *  Created on: Apr 11, 2022
 *      Author: Rafael
 */

#include "Actor.h"

QueueArr_t queue;
static QueueArr_t* q_ptr = &queue;

void actorInit(QueueArr_t other){

    /* Deep copy elements */
    q_ptr->rx = other.rx;
    q_ptr->tx = other.tx;
}

void vTaskActor(void* pvParams){
    
    /* Initialize struct */
    static Actor_t actor_data = {
        .data = {0},
        .tx_data = 0,
        .agent1_state = 0,
        .agent2_state = 0,
    };
    static Actor_t* self = &actor_data;

    /* Initialize intermediate variables */
    static BaseType_t rx_success = pdFALSE;
    uint8_t debug_success = 1;

    while(true){

        /* receive data from agents (suspend until data available) */
        rx_success = xQueueReceive(
            q_ptr->rx,
            &self->data,
            ( TickType_t ) pdMS_TO_TICKS(500)  // block for 500ms
        );

        /* failed to receive data; do smt!! */
        if(rx_success == pdFALSE){
            continue;
        }

        /* act on agent data */
        actor_logic(self);
        debug_success = log_valuef(self->tx_data);

        /* transmit data */
        xQueueSend(
            q_ptr->tx,
            &self->tx_data,
            ( TickType_t ) 1
        );

    } // superloop

}

void actor_logic(Actor_t* inst){

    switch(inst->data.id){

        case AGENT_ONE:
            inst->agent1_state = inst->data.msg;
            gioSetBit(gioPORTB, 1, inst->agent1_state);
            break;

        case AGENT_TWO:
            inst->agent2_state = inst->data.msg;
            gioSetBit(gioPORTB, 2, inst->agent2_state);
            break;
    } // switchcase
    inst->tx_data = inst->agent2_state && inst->agent1_state;
}
