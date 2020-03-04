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
#include"sci.h"
#include<stdlib.h>
#include<stdio.h>
#include<temperature.h>
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
static  char command;
float input_voltage = 0.0;
int temperature = 0;
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

void main(void)
{


/* USER CODE BEGIN (3) */
    /* Enable IRQ*/
    _enable_IRQ();

    /* Initialize SCI module */
    sciInit();

   // InitializeTemperature();

    /* Send your prompt */
    sciSend(scilinREG, 45,(unsigned char*)"Please press 1 for 1V, 2 for 1.5V, 3 for 2V !\r\n");


    char command1[5];
    /* Await user character */
    sciReceive(scilinREG, 5, (unsigned char*)&command);


//

    /* infinite loop */
   while(1);
/* USER CODE END */
}

void sciNotification(sciBASE_t *sci, uint32_t flags)
{
//    printf("The temperature is:");
//    fflush(stdout);
      /* Echo received character */
     sciSend(sci, 1, (unsigned char *)&command);

     /* await further character */
     sciReceive(sci,1,(unsigned char *)&command);

     if(command == '1'){
             input_voltage = 1;
      }
     else if(command == '2'){
             input_voltage = 1.5;
      }
     else if(command == '3'){
             input_voltage = 2;
      }
     temperature = DoCalculation(input_voltage);
  printf("The temperature is %d", temperature);
//     fflush (stdout);
}
/* USER CODE BEGIN (4) */
/* USER CODE END */
