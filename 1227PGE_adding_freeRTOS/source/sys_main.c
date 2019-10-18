/** @file sys_main.c 
*   @brief Application main file
*   @date 07-July-2017
*   @version 04.07.00
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2016 Texas Instruments Incorporated - www.ti.com 
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
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
#include "gio.h"
#include "system.h"
#include "reg_het.h"


#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "os_task.h"
#include "os_queue.h"
#include "sci.h"
#include "stdlib.h" // stdlib.h has ltoa() which we use for our simple SCI printing routine.
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
xQueueHandle xq; // freeRTOS queue we'll use to pass data between tasks
static void vSenderTask(void *); // sender task header
static void vReceiverTask(void *); // receiver task header
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    gioInit();
    gioSetDirection(hetPORT1, 0xFFFFFFFF); // set all HET1 pins to output.
    // turn all status LEDs off
    gioSetBit(hetPORT1, 8, 1);
    gioSetBit(hetPORT1, 26, 1);
    gioSetBit(hetPORT1, 28, 1);



    sciInit();
    sciSend(sciREG, 18, (unsigned char*)"SCI initialized.\r\n");

    xq = xQueueCreate(5, sizeof(long)); // is this queue created on the heap?, also what is sizeof(long)?

    if (xq != NULL)
    {
        xTaskCreate(vSenderTask, (const signed char*)"Sender 1", 240, (void*)100, 1, NULL);
        xTaskCreate(vSenderTask, (const signed char*)"Sender 2", 240, (void*)200, 1, NULL);
        xTaskCreate(vReceiverTask, (const signed char*)"Receiver", 240, NULL, 2, NULL);
        vTaskStartScheduler();
    }
    while(1);
/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
// the two created tasks differ in behaviour based on the parameter passed in
// in this case, our value of pvParameters.
// With our case, our "pointer" is just a straight integer and doesn't point to anything relevant in memory
static void vSenderTask(void *pvParameters) // pvParameters is a pointer to a number, could also point to a queue or mutex..
{
    long lval;
    portBASE_TYPE xStatus; // what is this port? looks like it is just a typedef for 'long'

    lval = (long) pvParameters;
    while(1)
    {
        xStatus = xQueueSendToBack(xq, &lval, 0);
        if (xStatus != pdPASS)
        {
            // turn on an LED?

        }
        gioToggleBit(hetPORT1, 8);
        taskYIELD();// WHAT IS THIS?
    }
}// end of Sender Task

static void vReceiverTask(void *pvParameters)
{
    long lrval;
    portBASE_TYPE xStatus;
    const portTickType xTicksToWait = 100 / portTICK_RATE_MS;
    char stbuf[64];
    int nchars;

    while(1)
    {
        gioToggleBit(hetPORT1, 28);
        if (uxQueueMessagesWaiting(xq) != 0)
        {
            // turn on an error LED?
        }

        xStatus = xQueueReceive(xq, &lrval, xTicksToWait);
        if (xStatus == pdPASS)
        {
            // dump value to SCI
            nchars = ltoa(lrval, stbuf);
            sciSend(sciREG, 10, (unsigned char*)"Received: ");
            sciSend(sciREG, nchars, (unsigned char*)stbuf);
            sciSend(sciREG, 2, (unsigned char*)"\r\n");
        }
        else
        {
            // turn on an error LED?
        }
    }
}// end of ReceiverTask

void vApplicationMallocFailedHook( void )
{
    // Error handling if malloc fails to allocate memory properly
    // Write some code here
}

/* configSUPPORT_STATIC_ALLOCATION is set to 1, so the application must provide an
implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
used by the Idle task. */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize )
{
/* If the buffers to be provided to the Idle task are declared inside this
function then they must be declared static – otherwise they will be allocated on
the stack and so not exists after this function exits. */
static StaticTask_t xIdleTaskTCB;
static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task’s
    state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task’s stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}
/*———————————————————–*/

/* configSUPPORT_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
application must provide an implementation of vApplicationGetTimerTaskMemory()
to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize )
{
/* If the buffers to be provided to the Timer task are declared inside this
function then they must be declared static – otherwise they will be allocated on
the stack and so not exists after this function exits. */
static StaticTask_t xTimerTaskTCB;
static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
    task’s state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task’s stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configTIMER_TASK_STACK_DEPTH is specified in words, not bytes. */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

/* USER CODE END */
