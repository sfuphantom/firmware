/** @file sys_main.c 
*   @brief Application main file
*   @date 08-Feb-2017
*   @version 04.06.01
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
#include "sci.h"
#include "stdlib.h"
#include <stdio.h>
#include <het.h>
#include "gio.h"
#include "can.h"
#include "adc.h"
#include "sys_core.h"
#include "inputOutput.h"
#include "utilities.h"
#include "stateMachine.h"

/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
xQueueHandle VCUDataQueue;
xTaskHandle xTask1Handle,xTask2Handle;
xSemaphoreHandle binary_sem;
static void v100msTask(void *);
static void vRDUTask(void *);

void fxInitHardware();

uint32 tx_done = 0;
uint8 rx_data[8] = {0};
uint8 *rx_ptr = &rx_data[0];
uint32 cnt = 0;



/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */

    // Perform hardware Initialization
    fxInitHardware();

    // Do some sort of CRC Check?

    // Start the watchdog?

    // Queue used to pass messages between 100msTask and the RDUTask
    VCUDataQueue = xQueueCreate(1, sizeof(struct data));

    vSemaphoreCreateBinary(binary_sem);

    if (VCUDataQueue != NULL){
       /* The 100ms task does the following actions:
        *  1) Reads Analog Inputs
        *  2) Reads Digital Inputs
        *  3) Evaluates State Machine
        */

        if (xTaskCreate(v100msTask, (const signed char*)"100msTask",  configMINIMAL_STACK_SIZE, NULL,  (2 ), &xTask1Handle) != pdTRUE){
            sciSend(scilinREG,23,(unsigned char*)"Task1 Creation Failed.\r\n");
            while(1);
        }

        /*
        * The 500 ms Task does the following actions:
        *  2) Sends a CAN messages whenever it receives the semaphore from CAN receive ISR
        */
        if (xTaskCreate(vRDUTask, (const signed char*)"RDUTask",  configMINIMAL_STACK_SIZE, NULL,  (1 ), &xTask2Handle) != pdTRUE){
            sciSend(scilinREG,23,(unsigned char*)"Task2 Creation Failed.\r\n");
            while(1);
        }

        vTaskStartScheduler();
    }




    while(1){}


/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
static void v100msTask(void *pvParameters){
    /* Task Related Initialization */
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 100;
    portBASE_TYPE xStatus;

    // Initialize the xLastWakeTime  variable with the current time
    xLastWakeTime = xTaskGetTickCount();
    uint8_t taskCounter = 0;
    /******************************/

    data VCUData, *VCUDataPtr;
    VCUDataPtr = &VCUData;

    // Initialize Linear Analog Inputs
    fxInitLinAnalogInputs();
    // Initialize data structure
    fxInitInputs(VCUDataPtr);

    for( ;; )
         {
             // Wait for the next cycle.
             vTaskDelayUntil( &xLastWakeTime, xFrequency );


             // Perform action here.
             pwmSetDuty(hetRAM1, 0,  100 );

             gioSetBit(hetPORT1, 6, gioGetBit(hetPORT1, 6) ^ 1);
             vTaskDelay(100);


             fxReadAnalogInputs(VCUDataPtr);
             fxReadDigitalInputs(VCUDataPtr);
             fxStateMachine(VCUDataPtr);


             if (++taskCounter % 5 == 0){
                 xQueueReset(VCUDataQueue);
                 xStatus = xQueueSendToBack(VCUDataQueue,&VCUData,0);
                 sciSend(scilinREG,8,(unsigned char*)"Enque!\r\n");
                 /*
                 if (xStatus){
                     sciSend(scilinREG,9,(unsigned char*)"Send Ok    !\r\n");
                 }else{
                     sciSend(scilinREG,12,(unsigned char*)"Not okay !\r\n");
                     xQueueReset(analogInputsQueue);
                     xQueueSendToBack(analogInputsQueue,&analogInLin,0);

                 }
                  */
                 if (taskCounter == 250){
                     taskCounter = 0;
                 }
             }

             sciSend(scilinREG,9,(unsigned char*)"Task 1!\r\n");

         }

}

/* USER CODE BEGIN (4) */
static void vRDUTask(void *pvParameters){
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 500;
    const portTickType xTicksToWait = 100 / portTICK_RATE_MS;
    portBASE_TYPE xStatus;

    data VCUData;
    uint8 tx_data[8] = {0};
    uint8 *tx_ptr = &tx_data[0];

    // Initialize the xLastWakeTime  variable with the current time
    xLastWakeTime = xTaskGetTickCount();

    xSemaphoreTake(binary_sem,portMAX_DELAY );

    for( ;; )
         {

             // Wait for the next cycle.
             vTaskDelayUntil( &xLastWakeTime, xFrequency );

             // Perform action here.
             /* Taggle HET[1] with timer tick */

             // For some reason gioPORTA does not work
             gioSetBit(hetPORT1, 13, gioGetBit(hetPORT1, 13) ^ 1);
             vTaskDelay(100);

             if (xSemaphoreTake(binary_sem,portMAX_DELAY )){
                 xStatus = xQueueReceive(VCUDataQueue, &VCUData, xTicksToWait);
                 sciSend(scilinREG,8,(unsigned char*)"Deque!\r\n");
                 tx_data[0] = descaledF32ToU8(VCUData.VCU_AIN.throttleInput_V, -5.0, 0.1); // Offset = -5.0    Scaling = 0.1
                 canTransmit(canREG1, canMESSAGE_BOX1, tx_ptr);
                 sciSend(scilinREG,16,(unsigned char*)"Sending a MSG!\r\n");
                 while(tx_done == 0){

                     if (++cnt == 100){
                         sciSend(scilinREG,24,(unsigned char*)"Could not transmit.\r\n");
                         break;
                     }
                 };

                 tx_done=0;
                 cnt = 0;
             }

             sciSend(scilinREG,9,(unsigned char*)"Task 2!\r\n");
         }

}

void fxInitHardware(){

   sciInit();
   sciSend(scilinREG,18,(unsigned char*)"SCI initialized.\r\n");

   hetInit();
   sciSend(scilinREG,18,(unsigned char*)"HET initialized.\r\n");
   pwmSetDuty(hetRAM1, 0,  0 );

   adcInit();
   sciSend(scilinREG,18,(unsigned char*)"ADC initialized.\r\n");



   /* Set high end timer GIO port hetPort pin direction to all output */
   gioSetDirection(hetPORT1, 0xFFFFFFFF);


   /** - configuring CAN1 MB1,Msg ID-1 to transmit and CAN2 MB1 to receive */
    canInit();
    canEnableErrorNotification(canREG1);
    sciSend(scilinREG,18,(unsigned char*)"CAN initialized.\r\n");

}


void canMessageNotification(canBASE_t *node, uint32 messageBox)
{
     /* node 1 - transfer request */
     if( (node==canREG1) && (messageBox==canMESSAGE_BOX1) ){
       tx_done=1; /* confirm transfer request */
     }
     if( (node==canREG1) && (messageBox==canMESSAGE_BOX2) ){
       sciSend(scilinREG,19,(unsigned char*)"Recieved CAN Msg.\r\n");
       while(!canIsRxMessageArrived(canREG1, canMESSAGE_BOX2));
       canGetData(canREG1, canMESSAGE_BOX2, rx_ptr); /* copy to RAM */
       xSemaphoreGiveFromISR(binary_sem,NULL);
     }

    /* Note: since only message box 1 is used on both nodes we dont check it here.*/
}





/* USER CODE END */
