/** @file sys_main.c
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/*
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com
*
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*    Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */


#include "FreeRTOS.h"
#include "os_task.h"
#include "os_queue.h"
#include "gio.h"
# include <stdlib.h>

/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */

#include "string.h"
#include "sci.h"
#include "stdio.h"

#include "common.h"

#include "Actor.h"
#include "Agent1.h"
#include "Agent2.h"
#include "TaskSim.h"
#include "Director.h"
#include "taskUART.h"
#include "het.h"
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */

void freeRTOSinit();


/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */

    /* Initialize UART communication */
    UARTInit(PC_UART, 9600);

    UARTprintf("Starting program...\r\n");

    gioInit();
    hetInit();
    freeRTOSinit();

    vTaskStartScheduler();

    while(true);

/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */

void freeRTOSinit()
{
    BaseType_t xReturned;
    #if DEBUG_MODE == 1
    TaskHandle_t debug_task; 
    xReturned = xTaskCreate(
                    vTaskDebugger,   /* Function that implements the task. */
                    "Debugger",      /* Text name for the task. */
                    64,              /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    1,               /* Priority at which the task is created. */
                    &debug_task /* Used to pass out the created task's handle. */
    );

    if(xReturned == pdFALSE){
        UARTprintf("Failed to create Debugger\r\n");
    }else{
        UARTprintf("Succcessfully created Debugger!\r\n");
    }

    QueueHandle_t debug_queue =  xQueueCreate( 5, sizeof( DebugStruct_t ) );

    debugger_init(debug_queue);
    debug_init(debug_queue);
    #endif



    /* Queue Creation */
    QueueHandle_t raw_digital_queue = xQueueCreate( 10, sizeof( AgentMessage_t ) );
    QueueHandle_t filtered_digital_queue = xQueueCreate( 10, sizeof( uint8_t ) );

    QueueArr_t director_queues = {
        .rx = filtered_digital_queue,
    };
    QueueArr_t actor_queues = {
        .rx = raw_digital_queue,
        .tx = filtered_digital_queue
    };

    QueueArr_t agent1_queues = {
        .tx = raw_digital_queue
    };
    QueueArr_t agent2_queues = {
        .tx = raw_digital_queue
    };

    /* Task Creation */
    Control_t ctrl_tasks;

    actorInit(actor_queues);

    if(filtered_digital_queue == NULL|| raw_digital_queue == NULL ){
        UARTprintf("Failed to create queues\r\n");
    }else{
        UARTprintf("Created queues successfully!\r\n");
    }

    TaskHandle_t task_handles[5];
    /* Task Creation*/    
    xReturned = xTaskCreate(
                    vTaskActor,       /* Function that implements the task. */
                    "Actor",          /* Text name for the task. */
                    64,      /* Stack size in words, not bytes. */
                    ( void * ) 2,    /* Parameter passed into the task. */
                    2,/* Priority at which the task is created. */
                    &ctrl_tasks.actor

    );

    if(xReturned == pdFALSE){
        UARTprintf("Failed to create Actor\r\n");
    }else{
        UARTprintf("Succcessfully created Actor!\r\n");
    }

    #if SIM_MODE == 0 
    agent1Init(agent1_queues);
    agent2Init(agent2_queues);
    xReturned = xTaskCreate(
                    vTaskAgent1,       /* Function that implements the task. */
                    "Agent1",          /* Text name for the task. */
                    64,      /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &ctrl_tasks.agent1

    );

    if(xReturned == pdFALSE){
        UARTprintf("Failed to create Agent1\r\n");
    }else{
        UARTprintf("Succcessfully created Agent1!\r\n");
    }

    xReturned = xTaskCreate(
                vTaskAgent2,       /* Function that implements the task. */
                "Agent2",          /* Text name for the task. */
                64,      /* Stack size in words, not bytes. */
                ( void * ) 1,    /* Parameter passed into the task. */
                1,/* Priority at which the task is created. */
                &ctrl_tasks.agent2

    );
    
    if(xReturned == pdFALSE){
        UARTprintf("Failed to create Agent2\r\n");
    }else{
        UARTprintf("Succcessfully created Agent2!\r\n");
    }

    #else

    simInit(agent1_queues, agent2_queues);
    xReturned = xTaskCreate(
                vTaskSim,       /* Function that implements the task. */
                "Sim",          /* Text name for the task. */
                64,      /* Stack size in words, not bytes. */
                ( void * ) 0,    /* Parameter passed into the task. */
                0,/* Priority at which the task is created. */
                &task_handles[SIM]

    );

    if(xReturned == pdFALSE){
        UARTprintf("Failed to create sim agent!\r\n");
    }else{
        UARTprintf("Succcessfully created sim agent!!\r\n");
    }


    #endif
    

    directorInit(director_queues, ctrl_tasks);
    xReturned = xTaskCreate(
                   vTaskDirector,   /* Function that implements the task. */
                   "Director",      /* Text name for the task. */
                   64,              /* Stack size in words, not bytes. */
                   ( void * ) 3,    /* Parameter passed into the task. */
                   3,               /* Priority at which the task is created. */
                   &task_handles[DIRECTOR] /* Used to pass out the created task's handle. */

   );

    if(xReturned == pdFALSE){
        UARTprintf("Failed to create Director\r\n");
    }else{
        UARTprintf("Succcessfully created Director!\r\n");
    }


}
/* USER CODE END */
