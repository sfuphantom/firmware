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
#include "system.h" // is this required?

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "os_task.h"
#include "os_queue.h"
#include "os_semphr.h"
#include "os_timer.h"
#include "Phantom_sci.h"
#include "stdlib.h" // stdlib.h has ltoa() which we use for our simple SCI printing routine.
#include <stdio.h>
#include "adc.h"
#include "gio.h"
#include "het.h"

#include "reg_het.h"

#include "MCP48FV_DAC_SPI.h" // DAC library written by Ataur Rehman
#include "LV_monitor.h"      // INA226 Current Sense Amplifier Library written by David Cao

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
#define TASK_PRINT  0
#define STATE_PRINT 0
#define APPS_PRINT  1 // if this is enabled, it hogs the whole cpu since the task it runs in is called every 10ms and is the highest priority. doesn't allow other tasks/interrupts to run
#define BSE_PRINT   1 // if this is enabled, it hogs the whole cpu since the task it runs in is called every 10ms and is the highest priority. doesn't allow other tasks/interrupts to run

/*********************************************************************************
 *                          TASK HEADER DECLARATIONS
 *********************************************************************************/
static void vStateMachineTask(void *);  // This task will evaluate the state machine and decide whether or not to change states
static void vSensorReadTask(void *);    // This task will read all the sensors in the vehicle (except for the APPS which requires more critical response)
static void vThrottleTask(void *);      // This task reads the APPS, performs signal plausibility, and controls the inverter through a DAC
static void vDataLoggingTask(void *);   // This task will send any important data over CAN to the dashboard for logging onto the SD card
static void vWatchdogTask(void *);      // This task will monitor all the threads and make sure they are all running, if not (code hangs/freezes or task doesn't get run)
                                        // it will fail to pet the watchdog and the watchdog timer will reset the MCU

// task handle creation??? shouldn't they need to be passed into the xTaskCreate function?

/*********************************************************************************
 *                              TASK PRIORITIES
 *********************************************************************************/
#define THROTTLE_TASK_PRIORITY         3
#define SENSOR_READ_TASK_PRIORITY      2
#define STATE_MACHINE_TASK_PRIORITY    1
#define DATA_LOGGING_TASK_PRIORITY     0 // same as idle task
#define WATCHDOG_TASK_PRIORITY         0 // same as idle task

// there may also be interrupt/ISR priorities for:
// CAN messages
// GPIOs (ready to drive, shutdown circuit GPIOs..)

// would be nice to separate these into a separate priorities file

/*********************************************************************************
 *                          SOFTWARE TIMER INITIALIZATION
 *********************************************************************************/
#define NUMBER_OF_TIMERS   2

/* array to hold handles to the created timers*/
TimerHandle_t xTimers[NUMBER_OF_TIMERS];

/* This timer is used to debounce the interrupts for the RTDS and SDC signals */
bool INTERRUPT_AVAILABLE = true;
bool THROTTLE_AVAILABLE = false; // used to only enable throttle after the buzzer has gone for 2 seconds

void Timer_300ms(TimerHandle_t xTimers);
void Timer_2s(TimerHandle_t xTimers);
/*********************************************************************************
 *                          STATE ENUMERATION
 *********************************************************************************/
typedef enum {TRACTIVE_OFF, TRACTIVE_ON, RUNNING, FAULT} State;

State state = TRACTIVE_OFF;
/*********************************************************************************
 *                          GLOBAL VARIABLE DECLARATIONS
 *********************************************************************************/
xQueueHandle xq;
adcData_t FP_data[3];
adcData_t *FP_data_ptr = &FP_data[0];
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

#define BLUE_LED  pwm1
#define GREEN_LED pwm2
#define RED_LED   pwm3

uint8 i;
char command[8]; // used for ADC printing.. this is an array of 8 chars, each char is 8 bits
long xStatus;

/*********************************************************************************
 *                               SYSTEM STATE FLAGS
 *********************************************************************************/
uint8_t TSAL = 0;
uint8_t RTDS = 0;
long RTDS_RAW = 0;
uint8_t BMS  = 1;
uint8_t IMD  = 1;
uint8_t BSPD = 1;
uint8_t BSE_FAULT = 0;

uint32_t blue_duty = 100;
uint32_t blue_flag = 0;

// change to better data type
int lv_current = 0;
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
/*********************************************************************************
 *                          HALCOGEN PERIPHERAL INITIALIZATION
 *********************************************************************************/
    _enable_IRQ();
    sciInit();
    gioInit();
    adcInit();
    hetInit();
    pwmStop(hetRAM1, pwm0); // stop the ready to drive buzzer PWM from starting automatically

    // turn off RGB LEDs
    pwmStart(hetRAM1, BLUE_LED); // blue
    pwmStart(hetRAM1, GREEN_LED); // green
    pwmStart(hetRAM1, RED_LED); // red
    // maybe this can be changed in halcogen?

    // initialize HET pins ALL to output.. may need to change this later
    gioSetDirection(hetPORT1, 0xFFFFFFFF);

/*********************************************************************************
 *                          PHANTOM LIBRARY INITIALIZATION
 *********************************************************************************/
    //using MCP48FV Library
    MCP48FV_Init();
//    MCP48FV_Set_Value(400);//500 =5.00V, 250= 2.5V

    // LV monitor library
    lv_monitorInit();
/*********************************************************************************
 *                          freeRTOS SOFTWARE TIMER SETUP
 *********************************************************************************/
    xTimers[0] = xTimerCreate
            ( /* Just a text name, not used by the RTOS
             kernel. */
             "RTDS_Timer",
             /* The timer period in ticks, must be
             greater than 0. */
             pdMS_TO_TICKS(10),
             /* The timers will auto-reload themselves
             when they expire. */
             pdFALSE,
             /* The ID is used to store a count of the
             number of times the timer has expired, which
             is initialised to 0. */
             ( void * ) 0,
             /* Callback function for when the timer expires*/
             Timer_300ms
           );

    xTimers[1] = xTimerCreate
            ( /* Just a text name, not used by the RTOS
             kernel. */
             "RTDS_Timer",
             /* The timer period in ticks, must be
             greater than 0. */
             pdMS_TO_TICKS(2000),
             /* The timers will auto-reload themselves
             when they expire. */
             pdFALSE,
             /* The ID is used to store a count of the
             number of times the timer has expired, which
             is initialised to 0. */
             ( void * ) 0,
             /* Callback function for when the timer expires*/
             Timer_2s
           );


    // with more timers being added it's more worth it to do a for loop for initializing each one here at the start

    if( xTimers[0] == NULL )
    {
         /* The timer was not created. */
        UARTSend(sciREG, "The timer was not created.\r\n");
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
             UARTSend(sciREG, "The timer could not be set into the active state.\r\n");
         }
    }

    if( xTimers[1] == NULL )
    {
         /* The timer was not created. */
        UARTSend(sciREG, "The timer was not created.\r\n");
    }
    else
    {
         /* Start the timer.  No block time is specified, and
         even if one was it would be ignored because the RTOS
         scheduler has not yet been started. */
         if( xTimerStart( xTimers[1], 0 ) != pdPASS )
         {
             /* The timer could not be set into the Active
             state. */
             UARTSend(sciREG, "The timer could not be set into the active state.\r\n");
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
        sciSend(sciREG,23,(unsigned char*)"StateMachineTask Creation Failed.\r\n");
        while(1);
    }


    if (xTaskCreate(vThrottleTask, (const char*)"ThrottleTask",  240, NULL,  (THROTTLE_TASK_PRIORITY), NULL) != pdTRUE)
    {
        // if xTaskCreate returns something != pdTRUE, then the task failed, wait in this infinite loop..
        // probably need a better error handler
        sciSend(sciREG,23,(unsigned char*)"ThrottleTask Creation Failed.\r\n");
        while(1);
    }


    if (xTaskCreate(vSensorReadTask, (const char*)"SensorReadTask",  240, NULL,  (SENSOR_READ_TASK_PRIORITY), NULL) != pdTRUE)
    {
        // if xTaskCreate returns something != pdTRUE, then the task failed, wait in this infinite loop..
        // probably need a better error handler
        sciSend(sciREG,23,(unsigned char*)"SensorReadTask Creation Failed.\r\n");
        while(1);
    }


    if (xTaskCreate(vDataLoggingTask, (const char*)"DataLoggingTask",  240, NULL,  (DATA_LOGGING_TASK_PRIORITY), NULL) != pdTRUE)
    {
        // if xTaskCreate returns something != pdTRUE, then the task failed, wait in this infinite loop..
        // probably need a better error handler
        sciSend(sciREG,23,(unsigned char*)"DataLoggingTask Creation Failed.\r\n");
        while(1);
    }

    if (xTaskCreate(vWatchdogTask, (const char*)"WatchdogTask",  240, NULL,  WATCHDOG_TASK_PRIORITY, NULL) != pdTRUE)
    {
        // if xTaskCreate returns something != pdTRUE, then the task failed, wait in this infinite loop..
        // probably need a better error handler
        sciSend(sciREG,23,(unsigned char*)"WatchdogTask Creation Failed.\r\n");
        while(1);
    }

    // all tasks have been created successfully
    UARTSend(sciREG, "Tasks created\r\n"); // We want to replace scilinREG with something like "PC_UART". and the BMS one to be "BMS_UART"
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
    const TickType_t xFrequency = 100; // task frequency in ms

    // Initialize the xLastWakeTime variable with the current time;
    xLastWakeTime = xTaskGetTickCount();

    while(true)
    {
        // Wait for the next cycle
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

        // for timing:
        gioSetBit(hetPORT1, 9, 1);

        if (TASK_PRINT) {UARTSend(sciREG, "STATE MACHINE UPDATE TASK\r\n");}

//        UARTSend(scilinREG, (char *)xLastWakeTime);

        xStatus = xQueueReceive(xq, &lrval, 30);
        nchars = ltoa(lrval, stbuf);
//        if (TASK_PRINT) {UARTSend(scilinREG, (char *)stbuf);}
//        if (TASK_PRINT) {UARTSend(scilinREG, "\r\n");}


        // MAKE SOME LED BLINK ON THE VCU! TECHNICALLY U HAVE 6 DIFFERENT ONES U CAN BLINK
        // MAKE EACH TASK BLINK A DIFFERENT LED

/*********************** STATE MACHINE EVALUATION ***********************************/


        if (state == TRACTIVE_OFF)
        {
//            pwmSetDuty(hetRAM1, BLUE_LED, 50U); // blue LED
            pwmSetDuty(hetRAM1, GREEN_LED, 100U); // green LED
            pwmSetDuty(hetRAM1, RED_LED, 100U); // red LED

            hetSIGNAL_t dutycycle_and_period;
            dutycycle_and_period.duty = blue_duty;
            dutycycle_and_period.period = 1000;
//            = {(unsigned int)1, (double)100}; // duty cycle in %, period in us

            pwmSetSignal(hetRAM1, BLUE_LED, dutycycle_and_period);

            if (blue_duty <= 0)
            {
                blue_flag = 1; // 1 means rising
            }
            else if (blue_duty >= 100)
            {
                blue_flag = 0; // 0 means falling
            }

            if (blue_flag == 1)
            {
                blue_duty+= 5;
            }
            else
            {
                blue_duty-= 5;
            }


            if (STATE_PRINT) {UARTSend(sciREG, "********TRACTIVE_OFF********");}
            if (BMS == 1 && IMD == 1 && BSPD == 1 && TSAL == 1 && BSE_FAULT == 0)
            {
                // if BMS/IMD/BSPD = 1 then the shutdown circuit is closed
                // TSAL = 1 indicates that the AIRs have closed
                // tractive system should now be active
                state = TRACTIVE_ON;
            }
            else if (BSE_FAULT == 1)
            {
                state = FAULT;
            }
        }
        else if (state == TRACTIVE_ON)
        {
            pwmSetDuty(hetRAM1, GREEN_LED, 100U);
            pwmSetDuty(hetRAM1, RED_LED, 100U);
            pwmSetDuty(hetRAM1, BLUE_LED, 50U); // blue


            if (STATE_PRINT) {UARTSend(sciREG, "********TRACTIVE_ON********");}

            if (RTDS == 1)
            {
                // ready to drive signal is switched
                state = RUNNING;
            }

            // Mechanism to switch back to tractive off from this state? or into error state?
        }
        else if (state == RUNNING)
        {
            pwmSetDuty(hetRAM1, BLUE_LED, 100U); // blue LED
            pwmSetDuty(hetRAM1, RED_LED, 100U); // red LED
            pwmSetDuty(hetRAM1, GREEN_LED, 50U); // green LED

            if (STATE_PRINT) {UARTSend(sciREG, "********RUNNING********");}

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
            pwmSetDuty(hetRAM1, BLUE_LED, 100U); // blue LED
            pwmSetDuty(hetRAM1, RED_LED, 50U); // red LED
            pwmSetDuty(hetRAM1, GREEN_LED, 100U); // green LED

            if (STATE_PRINT) {UARTSend(sciREG, "********FAULT********");}
            // uhhh turn on a fault LED here??
            // how will we reset out of this?

            if (BSE_FAULT == 0)
            {
                state = TRACTIVE_OFF;
            }
        }

        if (STATE_PRINT) {UARTSend(sciREG, "\r\n");}

        // for timing:
        gioSetBit(hetPORT1, 9, 0);
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
    const TickType_t xFrequency = 100; // task frequency in ms

    // Initialize the xLastWakeTime variable with the current time;
    xLastWakeTime = xTaskGetTickCount();

    int nchars;
    char stbuf[64];

    while(true)
    {
        // Wait for the next cycle
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

        // for timing:
        gioSetBit(hetPORT1, 25, 1);

//        MCP48FV_Set_Value(100);

//        gioToggleBit(gioPORTA, 5);

        RTDS_RAW = gioGetBit(gioPORTA, 2);

        if ( gioGetBit(gioPORTA, 2) == 1)
        {
            RTDS = 0;
//            UARTSend(sciREG, "RTDS RAW IS READ AS 1, RESETTING RTDS SIGNAL\r\n");
        }
        else
        {
//            UARTSend(sciREG, "RTDS RAW IS READ AS 0, RESETTING RTDS SIGNAL\r\n");
        }

        if (TASK_PRINT) {UARTSend(sciREG, "SENSOR READING TASK\r\n");}
//        UARTSend(scilinREG, xTaskGetTickCount());
        // read high voltage

        // read HV current

        // IMD data (maybe this needs to be a separate interrupt?)

        // Shutdown GPIOs (will probably start with these non-interrupt and see if we need to later..)

        // TSAL state

        // CAN status from BMS (this may need an interrupt for when data arrives, and maybe stored in a buffer? maybe not.. we should try both)

        // read LV voltage, current

        lv_current = LV_reading(LV_current_register);

        // make sure state machine signal flags are updated

        // check for all errors here and update VCU data structure or state machine flags accordingly

        // will also need a lookup table or data structure that has error messages and LED codes for whatever fault flags are on

        // for timing:
        gioSetBit(hetPORT1, 25, 0);
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
    const TickType_t xFrequency = 10; // task frequency in ms

    // Initialize the xLastWakeTime variable with the current time;
    xLastWakeTime = xTaskGetTickCount();


    while(true)
    {
        // Wait for the next cycle
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

        // for timing:
        gioSetBit(hetPORT1, 5, 1);

        // read APPS signals
        if (TASK_PRINT) {UARTSend(sciREG, "THROTTLE CONTROL\r\n");}
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
        BSE_sensor_sum = (unsigned int)FP_data[0].value;
        FP_sensor_1_sum = (unsigned int)FP_data[1].value;
        FP_sensor_2_sum = (unsigned int)FP_data[2].value;




        // check for short to GND/5V on sensor 1
        // thresholds

        // check for short to GND/3V3 on sensor 2
        // thresholds

        // check for short to GND/5V on BSE
        if (BSE_sensor_sum < 409)
        {
            // if it's less than 0.5V, then assume shorted to GND as this is not normal range
            BSE_FAULT = 1;
        }
        else if (BSE_sensor_sum > 3685) // change from magic number to a #define BSE_MAX_VALUE
        {
            // if it's greater than 4.5V, then assume shorted to 5V as this is not normal range
            BSE_FAULT = 1;
        }
        else
        {
            // should be in normal range
            BSE_FAULT = 0;
        }

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

        // brake light (flickers if pedal is around 2000 and is noisily jumping above and below!)
        if (BSE_sensor_sum < 2000)
        {
            gioSetBit(gioPORTA, 6, 1);
        }
        else
        {
            gioSetBit(gioPORTA, 6, 0);
        }

        NumberOfChars = ltoa(BSE_sensor_sum,(char *)command);
        if (BSE_PRINT) {UARTSend(sciREG, "*****BSE**** ");}
        if (BSE_PRINT) {sciSend(sciREG, NumberOfChars, command);}
        if (BSE_PRINT) {UARTSend(sciREG, "   ");}

        NumberOfChars = ltoa(FP_sensor_1_sum,(char *)command);
        if (BSE_PRINT) {UARTSend(sciREG, "*****APPS 1**** ");}
        if (BSE_PRINT) {sciSend(sciREG, NumberOfChars, command);}
        if (BSE_PRINT) {UARTSend(sciREG, "   ");}

        NumberOfChars = ltoa(FP_sensor_2_sum,(char *)command);
        if (BSE_PRINT) {UARTSend(sciREG, "*****APPS 2**** ");}
        if (BSE_PRINT) {sciSend(sciREG, NumberOfChars, command);}
        if (BSE_PRINT) {UARTSend(sciREG, "\r\n");}

        xStatus = xQueueSendToBack(xq, &FP_sensor_1_avg, 0);
        xStatus = xQueueSendToBack(xq, &FP_sensor_2_avg, 0);


        // 10% APPS redundancy check
        if(FP_sensor_diff > 0.10)
        {
            UARTSend(sciREG, "SENSOR DIFFERENCE FAULT\r\n");
        }

        // need to do APPS plausibility check with BSE

        if (state == RUNNING && THROTTLE_AVAILABLE)
        {
            // send DAC to inverter
            unsigned int apps_avg = 0.5*(FP_sensor_1_sum + FP_sensor_2_sum); // averaging the two foot pedal signals
            unsigned int throttle = 0.23640662*apps_avg - 88.6524825; // equation mapping the averaged signals to 0->500 for the DAC driver
            // ^ this equation may need to be modified for the curtis voltage lower limit and upper limit
            // i.e. map from 0.6V (60) to 4.5V (450) or something like that, instead of 0->500 (0V -> 5V)


            MCP48FV_Set_Value(throttle); // send throttle value to DAC driver

            // Print out DAC output
            NumberOfChars = ltoa(throttle,(char *)command);

            // printing debug:
//            sciSend(sciREG, NumberOfChars, command);
//            UARTSend(sciREG, "\r\n");
        }
        else
        {
            // send 0 to DAC
            MCP48FV_Set_Value(0);
            THROTTLE_AVAILABLE = false;
        }

        // for timing:
        gioSetBit(hetPORT1, 5, 0);

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
    const TickType_t xFrequency = 500; // task frequency in ms

    // Initialize the xLastWakeTime variable with the current time;
    xLastWakeTime = xTaskGetTickCount();

    while(true)
    {
        // Wait for the next cycle
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

        // for timing:
        gioSetBit(hetPORT1, 4, 1);

//        MCP48FV_Set_Value(300);

//        gioToggleBit(gioPORTA, 7);
        if (TASK_PRINT) {UARTSend(sciREG, "------------->DATA LOGGING TO DASHBOARD\r\n");}
//            UARTSend(scilinREG, xTaskGetTickCount());
            //----> do we need to send battery voltage to dashboard?


            // log HV voltage, current TSAL state, shutdown circuit states to CAN
            // send to dashboard
            // this may or may not depend on state

        // for timing:
        gioSetBit(hetPORT1, 4, 0);
    }

}

/***********************************************************
 * @function                - vWatchdogTask
 *
 * @brief                   - This task will monitor all threads and pet the watchdog if everything is fine. Else it will let the watchdog reset the MCU
 *
 * @param[in]               - pvParameters
 *
 * @return                  - None
 * @Note                    - None
 ***********************************************************/

static void vWatchdogTask(void *pvParameters){

    // any initialization
    TickType_t xLastWakeTime;          // will hold the timestamp at which the task was last unblocked
    const TickType_t xFrequency = 300; // task frequency in ms
    // watchdog timeout is 1.6 seconds

    // Initialize the xLastWakeTime variable with the current time;
    xLastWakeTime = xTaskGetTickCount();

    while(true)
    {
        // Wait for the next cycle
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

        if (TASK_PRINT) {UARTSend(sciREG, "------------->WATCHDOG TASK\r\n");}
//            UARTSend(scilinREG, xTaskGetTickCount());

        gioToggleBit(hetPORT1, 2);
    }

}
void gioNotification(gioPORT_t *port, uint32 bit)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (19) */
//    UARTSend(sciREG, "---------Interrupt Request-------\r\n");
    if (port == gioPORTA && bit == 2 && INTERRUPT_AVAILABLE)
    {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;
        // RTDS switch
        UARTSend(sciREG, "---------Interrupt Active\r\n");
        if (RTDS == 0 && gioGetBit(gioPORTA, 2) == 0)
        {
            if (BSE_sensor_sum < 2000)
            {
                gioSetBit(gioPORTA, 6, 1);
                RTDS = 1; // CHANGE STATE TO RUNNING
                UARTSend(sciREG, "---------RTDS set to 1 in interrupt\r\n");

                // ready to drive buzzer, need to start a 2 second timer here
                pwmStart(hetRAM1, pwm0);

                // reset the 2 second timer to let the buzzer ring for 2 seconds
                if (xTimerResetFromISR(xTimers[1], xHigherPriorityTaskWoken) != pdPASS)// after 2s the timer will allow the interrupt to toggle the signal again
                {
                    // timer reset failed
                    UARTSend(sciREG, "---------Timer reset failed-------\r\n");
                }
            }
        }
//        else
//        {
//            UARTSend(sciREG, "---------RTDS set to 0 in interrupt\r\n");
//            RTDS = 0;
//        }

        INTERRUPT_AVAILABLE = false;
        if (xTimerResetFromISR(xTimers[0], xHigherPriorityTaskWoken) != pdPASS)// after 300ms the timer will allow the interrupt to toggle the signal again
        {
            // timer reset failed
            UARTSend(sciREG, "---------Timer reset failed-------\r\n");
        }
    }
}

/* Timer callback when it expires */
 void Timer_300ms(TimerHandle_t xTimers)
 {
     INTERRUPT_AVAILABLE = true;
 }

 /* Timer callback when it expires for the ready to drive sound */
 void Timer_2s(TimerHandle_t xTimers)
 {
     pwmStop(hetRAM1, pwm0);
     THROTTLE_AVAILABLE = true;
 }

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
