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
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "os_task.h"
#include "os_queue.h"
#include "os_semphr.h"
#include "os_timer.h"
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
 *                          DEBUG PRINTING DEFINES
 *********************************************************************************/
#define TASK_PRINT 0
#define APPS_PRINT 0
#define BSE_PRINT  1
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
#define THROTTLE_TASK_PRIORITY         3
#define SENSOR_READ_TASK_PRIORITY      2
#define STATE_MACHINE_TASK_PRIORITY    1
#define DATA_LOGGING_TASK_PRIORITY     0 // same as idle task

// there may also be interrupt/ISR priorities for:
// CAN messages
// GPIOs (ready to drive, shutdown circuit GPIOs..)

// would be nice to separate these into a separate priorities file

/*********************************************************************************
 *                          SOFTWARE TIMER INITIALIZATION
 *********************************************************************************/
#define NUMBER_OF_TIMERS   1

/* array to hold handles to the created timers*/
TimerHandle_t xTimers[NUMBER_OF_TIMERS];

/* This timer is used to debounce the interrupts for the RTDS and SDC signals */
bool INTERRUPT_AVAILABLE = true;

void Timer_200ms(TimerHandle_t xTimers);
/*********************************************************************************
 *                          STATE ENUMERATION
 *********************************************************************************/
typedef enum {TRACTIVE_OFF, TRACTIVE_ON, RUNNING, FAULT} State;

State state = TRACTIVE_OFF;
/*********************************************************************************
 *                          GLOBAL VARIABLE DECLARATIONS
 *********************************************************************************/
xQueueHandle xq;
adcData_t FP_data;
adcData_t *FP_data_ptr = &FP_data;
unsigned int FP_sensor_1_sum = 0;
unsigned int FP_sensor_1_avg;
unsigned int FP_sensor_2_sum = 0;
unsigned int FP_sensor_2_avg;

unsigned int BSE_sensor_sum  = 0;
unsigned int BSE_sensor_avg  = 0;
unsigned int NumberOfChars;

uint16 FP_sensor_1_min = 0;
uint16 FP_sensor_2_min = 0;

uint16 FP_sensor_1_max = 4095; // 12-bit ADC
uint16 FP_sensor_2_max = 4095; // 12-bit ADC
uint16 FP_sensor_1_percentage;
uint16 FP_sensor_2_percentage;
uint16 FP_sensor_diff;

uint8 i;
char command[8]; // used for ADC printing.. this is an array of 8 chars, each char is 8 bits
long xStatus;

/*********************************************************************************
 *                               SYSTEM STATE FLAGS
 *********************************************************************************/
uint8_t TSAL = 1;
uint8_t RTDS = 0;
uint8_t BMS  = 1;
uint8_t IMD  = 1;
uint8_t BSPD = 1;
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */


/*********************************************************************************
 *                          HALCOGEN PERIPHERAL INITIALIZATION
 *********************************************************************************/
    sciInit();
    gioInit();
    adcInit();
/*********************************************************************************
 *                          freeRTOS SOFTWARE TIMER SETUP
 *********************************************************************************/
    xTimers[0] = xTimerCreate
            ( /* Just a text name, not used by the RTOS
             kernel. */
             "RTDS_Timer",
             /* The timer period in ticks, must be
             greater than 0. */
             pdMS_TO_TICKS(200),
             /* The timers will auto-reload themselves
             when they expire. */
             pdFALSE,
             /* The ID is used to store a count of the
             number of times the timer has expired, which
             is initialised to 0. */
             ( void * ) 0,
             /* Callback function for when the timer expires*/
             Timer_200ms
           );

    if( xTimers[0] == NULL )
    {
         /* The timer was not created. */
        UARTSend(scilinREG, "The timer was not created.\r\n");
    }
    else
    {
         /* Start the timer.  No block time is specified, and
         even if one was it would be ignored because the RTOS
         scheduler has not yet been started. */
         if( xTimerStart( xTimers[0], 0 ) != pdPASS )
         {
             /* The timer could not be set into the Active
             state. */
             UARTSend(scilinREG, "The timer could not be set into the active state.\r\n");
         }
    }
/*********************************************************************************
 *                          freeRTOS TASK & QUEUE CREATION
 *********************************************************************************/

    // create a freeRTOS queue to pass data between tasks
    // this will be useful when passing the VCU data structure in between different tasks

    xq = xQueueCreate(5, sizeof(long));

    // need to do an "if queue != NULL"

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

    TickType_t xLastWakeTime;          // will hold the timestamp at which the task was last unblocked
    const TickType_t xFrequency = 500; // task frequency in ms

    // Initialize the xLastWakeTime variable with the current time;
    xLastWakeTime = xTaskGetTickCount();

    while(true)
    {
        // Wait for the next cycle
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

        if (TASK_PRINT) {UARTSend(scilinREG, "STATE MACHINE UPDATE TASK\r\n");}

//        UARTSend(scilinREG, (char *)xLastWakeTime);

        xStatus = xQueueReceive(xq, &lrval, 30);
        nchars = ltoa(lrval, stbuf);
        if (TASK_PRINT) {UARTSend(scilinREG, (char *)stbuf);}
        if (TASK_PRINT) {UARTSend(scilinREG, "\r\n");}


        // MAKE SOME LED BLINK ON THE VCU! TECHNICALLY U HAVE 6 DIFFERENT ONES U CAN BLINK
        // MAKE EACH TASK BLINK A DIFFERENT LED

/*********************** STATE MACHINE EVALUATION ***********************************/

        if (state == TRACTIVE_OFF)
        {
            if (TASK_PRINT) {UARTSend(scilinREG, "TRACTIVE_OFF");}
            if (BMS == 1 && IMD == 1 && BSPD == 1 && TSAL == 1)
            {
                // if BMS/IMD/BSPD = 1 then the shutdown circuit is closed
                // TSAL = 1 indicates that the AIRs have closed
                // tractive system should now be active
                state = TRACTIVE_ON;
            }
        }
        else if (state == TRACTIVE_ON)
        {
            if (TASK_PRINT) {UARTSend(scilinREG, "TRACTIVE_ON");}
            if (RTDS == 1)
            {
                // ready to drive signal is switched
                state = RUNNING;
            }
        }
        else if (state == RUNNING)
        {
            if (TASK_PRINT) {UARTSend(scilinREG, "RUNNING");}
            if (RTDS == 0)
            {
                // read to drive signal switched off
                state = TRACTIVE_ON;
            }
            if (BMS == 0 || IMD == 0 || BSPD == 0 || TSAL == 0)
            {
                // FAULT in shutdown circuit, or AIRs have opened from TSAL
                state = FAULT;
            }

        }
        else if (state == FAULT)
        {
            if (TASK_PRINT) {UARTSend(scilinREG, "FAULT");}
            // uhhh turn on a fault LED here??
            // how will we reset out of this?
        }

        if (TASK_PRINT) {UARTSend(scilinREG, "\r\n");}
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
    TickType_t xLastWakeTime;          // will hold the timestamp at which the task was last unblocked
    const TickType_t xFrequency = 500; // task frequency in ms

    // Initialize the xLastWakeTime variable with the current time;
    xLastWakeTime = xTaskGetTickCount();

    while(true)
    {
        // Wait for the next cycle
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

        gioToggleBit(gioPORTB, 1);

        if (TASK_PRINT) {UARTSend(scilinREG, "SENSOR READING TASK\r\n");}
//        UARTSend(scilinREG, xTaskGetTickCount());
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

    TickType_t xLastWakeTime;          // will hold the timestamp at which the task was last unblocked
    const TickType_t xFrequency = 250; // task frequency in ms

    // Initialize the xLastWakeTime variable with the current time;
    xLastWakeTime = xTaskGetTickCount();


    while(true)
    {
        // Wait for the next cycle
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

        // read APPS signals
        if (TASK_PRINT) {UARTSend(scilinREG, "THROTTLE CONTROL\r\n");}
//        UARTSend(scilinREG, xTaskGetTickCount());

        // how was this i from 0 to 10 selected?
//        for(i=0; i<10; i++)
//        {
//            adcStartConversion(adcREG1, adcGROUP1);
//            while(!adcIsConversionComplete(adcREG1, adcGROUP1));
//            adcGetData(adcREG1, 1U, FP_data_ptr);
//            FP_sensor_1_sum += (unsigned int)FP_data[0].value;
//            FP_sensor_2_sum += (unsigned int)FP_data[1].value;
//            BSE_sensor_sum  += (unsigned int)FP_data[2].value;
//        }

        adcStartConversion(adcREG1, adcGROUP1);
        while(!adcIsConversionComplete(adcREG1, adcGROUP1));
        adcGetData(adcREG1, 1U, FP_data_ptr);
        BSE_sensor_sum = (unsigned int)FP_data_ptr->value;



        // check for short to GND/5V on sensor 1
        // thresholds

        // check for short to GND/3V3 on sensor 2
        // thresholds

        // moving average signal conditioning.. worth it to graph this out and find a good filter time constant
//        FP_sensor_1_avg = FP_sensor_1_sum/10;
//        FP_sensor_2_avg = FP_sensor_2_sum/10;
//        BSE_sensor_avg  = BSE_sensor_sum;

//        FP_sensor_1_sum = 0;
//        FP_sensor_2_sum = 0;
//        BSE_sensor_sum  = 0;

//        BSE_sensor_sum  = (unsigned int)FP_data[2].value;

//        FP_sensor_1_percentage = (FP_sensor_1_avg-FP_sensor_1_min)/(FP_sensor_1_max-FP_sensor_1_min);
//        FP_sensor_2_percentage = (FP_sensor_2_avg-FP_sensor_2_min)/(FP_sensor_2_max-FP_sensor_2_min);
//        FP_sensor_diff = abs(FP_sensor_2_percentage - FP_sensor_1_percentage);

//        ltoa(FP_sensor_1_avg,(char *)command);
//        if (APPS_PRINT) {UARTSend(scilinREG, "0x");}
//        if (APPS_PRINT) {UARTSend(scilinREG, command);}
//
//        ltoa(FP_sensor_2_avg,(char *)command);
//        if (APPS_PRINT) {UARTSend(scilinREG, "   0x");}
//        if (APPS_PRINT) {UARTSend(scilinREG, command);}
//        if (APPS_PRINT) {UARTSend(scilinREG, "\r\n");}

        NumberOfChars = ltoa(BSE_sensor_sum,(char *)command);
        if (BSE_PRINT) {UARTSend(scilinREG, "*****BSE**** ");}
        if (BSE_PRINT) {sciSend(scilinREG, NumberOfChars, command);}
        if (BSE_PRINT) {UARTSend(scilinREG, "\r\n");}

        xStatus = xQueueSendToBack(xq, &FP_sensor_1_avg, 0);
        xStatus = xQueueSendToBack(xq, &FP_sensor_2_avg, 0);


        // 10% APPS redundancy check
        if(FP_sensor_diff > 0.10)
        {
            UARTSend(scilinREG, "SENSOR DIFFERENCE FAULT\r\n");
        }

        // need to do APPS plausibility check with BSE

        if (state == RUNNING)
        {
            // send DAC to inverter
        }
        else
        {
            // send 0 to DAC
        }

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
    TickType_t xLastWakeTime;          // will hold the timestamp at which the task was last unblocked
    const TickType_t xFrequency = 2000; // task frequency in ms

    // Initialize the xLastWakeTime variable with the current time;
    xLastWakeTime = xTaskGetTickCount();

    while(true)
    {
        // Wait for the next cycle
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

        gioToggleBit(gioPORTB, 2);
        if (TASK_PRINT) {UARTSend(scilinREG, "------------->DATA LOGGING TO DASHBOARD\r\n");}
//            UARTSend(scilinREG, xTaskGetTickCount());
            //----> do we need to send battery voltage to dashboard?


            // log HV voltage, current TSAL state, shutdown circuit states to CAN
            // send to dashboard
            // this may or may not depend on state
    }

}

void gioNotification(gioPORT_t *port, uint32 bit)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (19) */
//    UARTSend(scilinREG, "---------Interrupt Request-------\r\n");
    if (port == gioPORTA && bit == 2 && INTERRUPT_AVAILABLE)
    {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        // RTDS switch
//        UARTSend(scilinREG, "---------Interrupt Active\r\n");
        if (RTDS == 0)
        {
            if (BSE_sensor_avg > 1000)
            {
                RTDS = 1; // CHANGE STATE TO RUNNING
            }
        }
        else
        {
            RTDS ^= 1;
        }

        INTERRUPT_AVAILABLE = false;
        if (xTimerResetFromISR(xTimers[0], xHigherPriorityTaskWoken) != pdPASS)// after 200ms the timer will allow the interrupt to toggle the signal again
        {
            // timer reset failed
            UARTSend(scilinREG, "---------Timer reset failed-------\r\n");
        }
    }
}

/* Timer callback when it expires */
 void Timer_200ms(TimerHandle_t xTimers)
 {
     INTERRUPT_AVAILABLE = true;
 }
/* USER CODE END */
