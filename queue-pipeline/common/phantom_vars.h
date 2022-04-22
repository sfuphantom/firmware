/*
 * phantom_vars.h
 *
 *  Created on: Apr 11, 2022
 *      Author: Rafael
 */

#ifndef COMMON_PHANTOM_VARS_H_
#define COMMON_PHANTOM_VARS_H_

#include "phantom_config.h"
#include "stdio.h"
#include "stdint.h"
#include "FreeRTOS.h"
#include "os_task.h"
#include "os_queue.h"


// task ids

enum{
    DIRECTOR=0,
    ACTOR,
    AGENT_ONE,
    AGENT_TWO,
    SIM
};
typedef enum message_t{
    MSG_ONE=0,
    MSG_TWO,
}message_t;

typedef struct DebugStruct_t
{
    uint32_t data;
    uint8_t print_val;

}DebugStruct_t;



// typedef struct GlobalData{

//     TaskHandle_t task_handle_arr[4];
//     QueueHandle_t queue_handle_arr[2];

// }GlobalData_t;

typedef struct QueueArr_t
{
    QueueHandle_t tx;
    QueueHandle_t rx;
}QueueArr_t;


// struct for messages from agents
typedef struct AgentMessage{
    uint8_t id; // agent identifier
    uint8_t msg; // data from agent
}AgentMessage_t;

#endif /* COMMON_PHANTOM_VARS_H_ */
