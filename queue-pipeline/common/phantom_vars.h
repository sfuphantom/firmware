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

/* Index of Debugging Messages  */
typedef enum message_t{
    MSG_ONE=0,
    MSG_TWO,
}message_t;

typedef enum agentid_t{
    AGENT_ONE,
    AGENT_TWO,
}agentid_t;

/* Data received by Debug Actor  */
typedef struct DebugStruct_t
{
    uint32_t data;
    uint8_t print_val;
}DebugStruct_t;

/* Agent Message Structure */
typedef struct AgentMessage{
    uint8_t id;  // agent identifier
    uint8_t msg; // data from agent
}AgentMessage_t;

typedef struct QueueArr_t
{
    QueueHandle_t tx;
    QueueHandle_t rx;
}QueueArr_t;

#endif /* COMMON_PHANTOM_VARS_H_ */
