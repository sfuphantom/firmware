/*
 * TaskSim.c
 *
 *  Created on: Apr 11, 2022
 *      Author: Rafael
 */

#include "TaskSim.h"

static Simulation_t sim_data = {
    .agent1 = {
        .id = AGENT_ONE,
        .msg = 0
    },
    .agent2 = {
        .id = AGENT_TWO,
        .msg = 0
    },
    .agent1_q = NULL,
    .agent2_q = NULL
};

static Simulation_t* this = &sim_data;

void simInit(QueueArr_t agent1_queues, QueueArr_t agent2_queues){
    this->agent1_q = agent1_queues.tx;
    this->agent2_q = agent2_queues.tx;
}

void vTaskSim(void* pvParams){

    static char py_msg[1];
    static char command[2];
    static char cmp_str[1];

    while(true){

        // read inputs from PC
        sciReceive(PC_UART, 3, py_msg);



        // parse serial command
        split(py_msg, ",", command, 2);

        // distribute values to appropriate pointers
        cmp_str[0] = command[0];
        this->agent1.msg = (int)strtol(cmp_str, (char **)NULL, 10);
        cmp_str[0] = command[1];
        this->agent2.msg = (int)strtol(cmp_str, (char **)NULL, 10);

        /* Send to all actor queues */
        xQueueSend(
            this->agent1_q,
            ( void * ) &this->agent1,
            ( TickType_t ) 1

        );
        xQueueSend(
            this->agent1_q,
            ( void * ) &this->agent2,
            ( TickType_t ) 1

        );

        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

