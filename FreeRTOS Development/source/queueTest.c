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
#include "sci.h"
#include "stdlib.h"
#include <stdio.h>
#include <het.h>

/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
xQueueHandle xq;
static void vSenderTask(void *);
static void vReceiverTask(void *);
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */

    sciInit();
    sciSend(scilinREG,18,(unsigned char*)"SCI initialized.\r\n");

    // Queue used to pass messages between tasks
    /*
     * Each queue requires RAM that is used to hold the queue state, and to hold the queue
     * state, and to hold the items that are contained in the queue (the queue storage area)
     * xQueueCreate() automatically allocated from the FreeRTOS heap. The  RAM is provided by
     * the application writer, which results in a greater number of parameters  but allows
     * the RAM to be statically allocated at compile time.
     */

    xq = xQueueCreate(5, sizeof(long));
    if (xq != NULL){
        xTaskCreate(vSenderTask, (const signed char*)"Sender1", 240,(void*)100,1,NULL);
        xTaskCreate(vSenderTask, (const signed char*)"Sender2", 240,(void*)200,1,NULL);
        xTaskCreate(vReceiverTask, (const signed char*)"Receiver", 240,NULL,2,NULL);
        vTaskStartScheduler();
    }

    while(1);



/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
static void vSenderTask(void *pvParameters){
    long lval;
    portBASE_TYPE xStatus;

    lval = (long) pvParameters;
    while(1){
        // Post an item to the back of a queue
        // The item is queued by copy, not by reference
        xStatus = xQueueSendToBack(xq,&lval,0);
        if (xStatus != pdPASS){
            //turn on an LED?
        }
        taskYIELD();
    }
}

static void vReceiverTask(void *pvParameters)
{
    long lrval;
    portBASE_TYPE xStatus;
    const portTickType xTicksToWait = 100 / portTICK_RATE_MS;
    char stbuf[64];
    int nchars;

    while(1){
        if (uxQueueMessagesWaiting(xq) != 0){
            // turn on an error LED?
        }

        // Receive an item from the queue
        xStatus = xQueueReceive(xq, &lrval, xTicksToWait);
        if (xStatus == pdPASS){
            //dump values to SCI
            nchars = itoa(lrval,stbuf);
            sciSend(scilinREG, 10, (unsigned char *)"Received: ");
            sciSend(scilinREG, 10, (unsigned char *)stbuf);
            sciSend(scilinREG, 10, (unsigned char *)"\r\n");
        } else {
            // turn on an error LED
        }
    }

}

/* itoa:  convert n to characters in s */
 void itoa(long n, char s[])
 {
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
 }

#include <string.h>

 /* reverse:  reverse string s in place */
 void reverse(char s[])
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }


/* USER CODE END */
