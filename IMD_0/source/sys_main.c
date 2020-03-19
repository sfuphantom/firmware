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
#include "het.h"
#include "gio.h"
#include "sys_vim.h"
#include "rti.h"
#include "sci.h"

#include "stdlib.h" // contains ltoa

#define RTI_Cycle

/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
static const float FREQ_RUNNING_COUNTER = 10000000.00; // 10Mhz
static uint8_t rise_flag = 0;
static const uint32_t UINT32_MAX_ = 4294967295;

#ifdef RTI_Cycle
static uint32_t time1 = 0;
static uint32_t time2 = 0;
float period = 0.0;
float frequency = 0.0;
#endif //RTI_Cycle

// SCI variables
unsigned int NumberofChars, value;
unsigned char command[8];
const float f_HCLK = 160.00;
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

int main(void)
{
/* USER CODE BEGIN (3) */
    // Initialization --
    hetInit();
    gioInit();
    rtiInit();
    sciInit();
    rtiResetCounter(rtiCOUNTER_BLOCK1);

    _enable_IRQ();

    gioEnableNotification(gioPORTA,5);
    rtiStartCounter(rtiCOUNTER_BLOCK1);

    while(1){

//        value = (unsigned int) rtiGetCurrentTick(rtiCOMPARE1);
//        value = (unsigned int) rtiREG1->CMP[1].COMPx;
//        value = (unsigned int) rtiREG1->CNT[1].FRCx;

        value = (unsigned int) (frequency + 0.5);
        // adding this 0.5 and then typecasting to an int (truncating all decimals)
        // basically acts as rounding the float to the nearest integer

        NumberofChars = ltoa(value, (char*) command);

        sciSend(scilinREG, NumberofChars, command);
        sciSend(scilinREG, 5, (unsigned char*)" Hz\r\n");
    }
/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
void gioNotification(gioPORT_t *port, uint32 bit)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (19) */

    if(port == gioPORTA && bit == 5) {

        //LED on board
        gioToggleBit(gioPORTB,2);

        // first rising edge
        if(rise_flag == 0){
            // -- Measurement Execution --
            #ifdef RTI_Cycle
//          time1 = rtiGetCurrentTick(rtiCOMPARE1);
            time1 = rtiREG1->CNT[1].FRCx;
            //rtiResetCounter(rtiCOUNTER_BLOCK1);
            #endif //RTI_Cycle
            rise_flag=1;
        }

        else {
            #ifdef RTI_Cycle
            time2 = rtiREG1->CNT[1].FRCx;
            if(time1 < time2) {
                period = ((float)time2 - (float)time1)/FREQ_RUNNING_COUNTER ; // free running counter is one tick every 10MHz
                frequency = 1/period;
            }
            // accounting for overflow? need to know max
            else {
                period = ((float)time2 + (UINT32_MAX_-(float)time1))/FREQ_RUNNING_COUNTER;
            }
            #endif //RTI_Cycle
            rise_flag=0;
        }
    }
}
/* USER CODE END */
