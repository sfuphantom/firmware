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
static void vBatteryTask(void *);
static void vThermistorTask(void *);
static void vGPIOTask(void *);
static void vBlinkyTask(void *);
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
    sciInit();
    gioInit();
    sciInit();
    adcInit();

    xq = xQueueCreate(5, sizeof(long));


    if (xTaskCreate(vBatteryTask, (const char*)"ChargeTask",  240, NULL,  (3 ), NULL) != pdTRUE)
    {
                     sciSend(scilinREG,23,(unsigned char*)"BatteryTask Creation Failed.\r\n");
                                 while(1);
    }
    if (xTaskCreate(vGPIOTask, (const char*)"ChargeTask",  240, NULL,  (1 ), NULL) != pdTRUE)
    {
                     sciSend(scilinREG,23,(unsigned char*)"GPIOTask Creation Failed.\r\n");
                                     while(1);
    }
    if (xTaskCreate(vThermistorTask, (const char*)"ChargeTask",  240, NULL,  (2 ), NULL) != pdTRUE)
    {
                     sciSend(scilinREG,23,(unsigned char*)"ThermistorTask Creation Failed.\r\n");
                                     while(1);
    }
    if (xTaskCreate(vBlinkyTask, (const char*)"ChargeTask",  240, NULL,  (2 ), NULL) != pdTRUE)
    {
                         sciSend(scilinREG,23,(unsigned char*)"ThermistorTask Creation Failed.\r\n");
                                         while(1);
    }

    UARTSend(scilinREG, "Tasks created\r\n");
    {
    vTaskStartScheduler();
    }
    while(1);
/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
static void vBatteryTask(void *pvParameters){
    uint32 lrval;
    char stbuf[64];
    int nchars;

    do{
    xStatus = xQueueReceive(xq, &lrval, 30);
    nchars = ltoa(lrval, stbuf);
    UARTSend(scilinREG, (char *)stbuf);
    UARTSend(scilinREG, "\r\n");

    vTaskDelay(10);
    }while(1);
}
static void vThermistorTask(void *pvParameters){
    do{
        gioToggleBit(gioPORTB, 1);
        vTaskDelay(200);
    }while(1);
}
static void vBlinkyTask(void *pvParameters){
    do{
            gioToggleBit(gioPORTB, 2);
            vTaskDelay(200);
    }while(1);

}
static void vGPIOTask(void *pvParameters){
    do{
                for(i=0; i<10; i++)
                {
                    adcStartConversion(adcREG1, 1U);
                    while(!adcIsConversionComplete(adcREG1, 1U));
                    adcGetData(adcREG1, 1U, FP_data_ptr);
                    FP_sensor_1_sum += (unsigned int)FP_data[0].value;
                    FP_sensor_2_sum += (unsigned int)FP_data[1].value;
                }

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


                if(FP_sensor_diff > 0.10)
                {
                    UARTSend(scilinREG, "SENSOR DIFFERENCE FAULT\r\n");
                }
                vTaskDelay(10);
    }while(1);
}
/* USER CODE END */
