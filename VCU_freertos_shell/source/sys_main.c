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
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "os_task.h"
#include "os_queue.h"
#include "os_semphr.h"
#include "Phantom_sci.h"
#include "stdlib.h"
#include <stdio.h>
#include "adc.h"
#include "gio.h"
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
/*********************************************************************************
 *                          TASK HEADER DECLARATIONS
 *********************************************************************************/
static void vStateMachineTask(void *);  // This task will evaluate the state machine and decide whether or not to change states
static void vSensorReadTask(void *);    // This task will read all the sensors in the vehicle (except for the APPS which requires more critical response)
static void vThrottleTask(void *);      // This task reads the APPS, performs signal plausibility, and controls the inverter through a DAC
static void vDataLoggingTask(void *);   // This task will send any important data over CAN to the dashboard for logging onto the SD card

// task handle creation??? shouldn't they need to be passed into the xTaskCreate function?

/*********************************************************************************
 *                              TASK PRIORITIES
 *********************************************************************************/
#define THROTTLE_TASK_PRIORITY         2
#define SENSOR_READ_TASK_PRIORITY      1
#define STATE_MACHINE_TASK_PRIORITY    1
#define DATA_LOGGING_TASK_PRIORITY     0 // same as idle task

// there may also be interrupt/ISR priorities for:
// CAN messages
// GPIOs (ready to drive, shutdown circuit GPIOs..)

// would be nice to separate these into a separate priorities file

/*********************************************************************************
 *                          GLOBAL VARIABLE DECLARATIONS
 *********************************************************************************/
xQueueHandle xq;
adcData_t FP_data[2];
adcData_t *FP_data_ptr = &FP_data[0];
unsigned int FP_sensor_1_sum = 0;
unsigned int FP_sensor_1_avg;
unsigned int FP_sensor_2_sum = 0;
unsigned int FP_sensor_2_avg;

uint16 FP_sensor_1_min = 0;
uint16 FP_sensor_2_min = 0;

uint16 FP_sensor_1_max = 4095;
uint16 FP_sensor_2_max = 4095;
uint16 FP_sensor_1_percentage;
uint16 FP_sensor_2_percentage;
uint16 FP_sensor_diff;

uint8 i;
char command[8];
long xStatus;
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */


/*********************************************************************************
 *                          HALCOGEN PERIPHERAL INITIALIZATION
 *********************************************************************************/
    sciInit();
    gioInit();
    sciInit(); // Twice for some reason?
    adcInit();

/*********************************************************************************
 *                          freeRTOS TASK & QUEUE CREATION
 *********************************************************************************/

    // create a freeRTOS queue to pass data between tasks
    // this will be useful when passing the VCU data structure in between different tasks

    xq = xQueueCreate(5, sizeof(long));

    // freeRTOS API to create a task, takes in a task name, stack size, something, priority, something else
    if (xTaskCreate(vStateMachineTask, (const char*)"StateMachineTask",  240, NULL,  (STATE_MACHINE_TASK_PRIORITY), NULL) != pdTRUE)
    {
        // if xTaskCreate returns something != pdTRUE, then the task failed, wait in this infinite loop..
        // probably need a better error handler
        sciSend(scilinREG,23,(unsigned char*)"StateMachineTask Creation Failed.\r\n");
        while(1);
    }


    if (xTaskCreate(vThrottleTask, (const char*)"ThrottleTask",  240, NULL,  (THROTTLE_TASK_PRIORITY), NULL) != pdTRUE)
    {
        // if xTaskCreate returns something != pdTRUE, then the task failed, wait in this infinite loop..
        // probably need a better error handler
        sciSend(scilinREG,23,(unsigned char*)"ThrottleTask Creation Failed.\r\n");
        while(1);
    }


    if (xTaskCreate(vSensorReadTask, (const char*)"SensorReadTask",  240, NULL,  (SENSOR_READ_TASK_PRIORITY), NULL) != pdTRUE)
    {
        // if xTaskCreate returns something != pdTRUE, then the task failed, wait in this infinite loop..
        // probably need a better error handler
        sciSend(scilinREG,23,(unsigned char*)"SensorReadTask Creation Failed.\r\n");
        while(1);
    }
    if (xTaskCreate(vDataLoggingTask, (const char*)"DataLoggingTask",  240, NULL,  (DATA_LOGGING_TASK_PRIORITY), NULL) != pdTRUE)
    {
        // if xTaskCreate returns something != pdTRUE, then the task failed, wait in this infinite loop..
        // probably need a better error handler
        sciSend(scilinREG,23,(unsigned char*)"DataLoggingTask Creation Failed.\r\n");
        while(1);
    }

    // all tasks have been created successfully
    UARTSend(scilinREG, "Tasks created\r\n"); // We want to replace scilinREG with something like "PC_UART". and the BMS one to be "BMS_UART"
    // will need our own hardware defines file to do this for all the ports and pins we use..
    // will need to be different based on the launchpad or VCU being used. This can be changed via build configurations
    // so one build has all the right files/linker included, right debugger, right MCU

    // start freeRTOS task scheduler
    vTaskStartScheduler();


    // infinite loop to prevent code from ending. The scheduler will now pre-emptively switch between tasks.
    while(1);
/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */

/*********************************************************************************
 *                          freeRTOS TASK IMPLEMENTATIONS
 *********************************************************************************/

/***********************************************************
 * @function                - vStateMachineTask
 *
 * @brief                   - This task evaluates the state of the vehicle and controls any change of state
 *
 * @param[in]               - pvParameters
 *
 * @return                  - None
 * @Note                    - None
 ***********************************************************/
static void vStateMachineTask(void *pvParameters){
    uint32 lrval;
    char stbuf[64];
    int nchars;

    while(true)
    {
        xStatus = xQueueReceive(xq, &lrval, 30);
        nchars = ltoa(lrval, stbuf);
        UARTSend(scilinREG, (char *)stbuf);
        UARTSend(scilinREG, "\r\n");

        vTaskDelay(10);


        // need to evaluate the state machine here:
        // basically check what state we're in, based on that state, then check if any signals warrant a change of state
    }
}

/***********************************************************
 * @function                - vSensorReadTask
 *
 * @brief                   - This task will read all the sensors in the vehicle (except for the APPS which requires more critical response)
 *
 * @param[in]               - pvParameters
 *
 * @return                  - None
 * @Note                    - None
 ***********************************************************/
static void vSensorReadTask(void *pvParameters){

    // any initialization

    while(true)
    {
        gioToggleBit(gioPORTB, 1);
        vTaskDelay(200);

        // read high voltage

        // read HV current

        // IMD data (maybe this needs to be a separate interrupt?)

        // Shutdown GPIOs (will probably start with these non-interrupt and see if we need to later..)

        // TSAL state

        // CAN status from BMS (this may need an interrupt for when data arrives, and maybe stored in a buffer? maybe not.. we should try both)

        // read LV voltage, current

        // make sure state machine signal flags are updated

        // check for all errors here and update VCU data structure or state machine flags accordingly

        // will also need a lookup table or data structure that has error messages and LED codes for whatever fault flags are on
    }
}


/***********************************************************
 * @function                - vThrottleTask
 *
 * @brief                   - This task reads the APPS, performs signal plausibility, and controls the inverter through a DAC
 *
 * @param[in]               - pvParameters
 *
 * @return                  - None
 * @Note                    - None
 ***********************************************************/
static void vThrottleTask(void *pvParameters){
    while(true)
    {

        // read APPS signals

        // how was this i from 0 to 10 selected?
        for(i=0; i<10; i++)
        {
            adcStartConversion(adcREG1, 1U);
            while(!adcIsConversionComplete(adcREG1, 1U));
            adcGetData(adcREG1, 1U, FP_data_ptr);
            FP_sensor_1_sum += (unsigned int)FP_data[0].value;
            FP_sensor_2_sum += (unsigned int)FP_data[1].value;
        }

        // moving average signal conditioning.. worth it to graph this out and find a good filter time constant
        FP_sensor_1_avg = FP_sensor_1_sum/20;
        FP_sensor_2_avg = FP_sensor_2_sum/20;

        FP_sensor_1_sum = 0;
        FP_sensor_2_sum = 0;

        FP_sensor_1_percentage = (FP_sensor_1_avg-FP_sensor_1_min)/(FP_sensor_1_max-FP_sensor_1_min);
        FP_sensor_2_percentage = (FP_sensor_2_avg-FP_sensor_2_min)/(FP_sensor_2_max-FP_sensor_2_min);
        FP_sensor_diff = abs(FP_sensor_2_percentage - FP_sensor_1_percentage);

        ltoa(FP_sensor_1_avg,(char *)command);
        UARTSend(scilinREG, "0x");
        UARTSend(scilinREG, command);

        ltoa(FP_sensor_2_avg,(char *)command);
        UARTSend(scilinREG, "   0x");
        UARTSend(scilinREG, command);
        UARTSend(scilinREG, "\r\n");

        xStatus = xQueueSendToBack(xq, &FP_sensor_1_avg, 0);
        xStatus = xQueueSendToBack(xq, &FP_sensor_2_avg, 0);


        // 10% APPS redundancy check
        if(FP_sensor_diff > 0.10)
        {
            UARTSend(scilinREG, "SENSOR DIFFERENCE FAULT\r\n");
        }


        // need to do APPS plausibility check with BSE


        // based on state, send out DAC to inverter
        vTaskDelay(10);
    }
}

/***********************************************************
 * @function                - vDataLoggingTask
 *
 * @brief                   - This task will send any important data over CAN to the dashboard for logging onto the SD card
 *
 * @param[in]               - pvParameters
 *
 * @return                  - None
 * @Note                    - None
 ***********************************************************/

static void vDataLoggingTask(void *pvParameters){

    // any initialization

    while(true)
    {
            gioToggleBit(gioPORTB, 2);
            vTaskDelay(200); // will need to adjust this value

            // log HV voltage, current TSAL state, shutdown circuit states to CAN
            // send to dashboard
            // this may or may not depend on state
    }

}
/* USER CODE END */
