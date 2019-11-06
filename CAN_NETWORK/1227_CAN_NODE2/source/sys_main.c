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
#include "sys_core.h"
#include "esm.h"
#include "can.h"
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */

#define TRANSMIT 0
#define D_COUNT 6
uint32 cnt=0, error =0, tx_done =0;
uint8 tx_data[D_COUNT] = {'N','O','D','E','-','2'};
uint8 rx_data[D_COUNT] = {0};
uint8 *tx_ptr = &tx_data[0];
uint8 *rx_ptr = &rx_data[0];
uint8 *dptr=0;


void dumpSomeData();
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

    /* enable irq interrupt in Cortex R4 */
    _enable_interrupt_();


    /** - writing a random data in RAM - to transmit */
    //dumpSomeData();


    /** - configuring CAN1 MB1,Msg ID-1 to transmit and CAN2 MB1 to receive */
    canInit();


    /** - enabling error interrupts */
    canEnableErrorNotification(canREG1);

#if TRANSMIT
    /* - starting transmission */
     for(cnt=0;cnt<D_COUNT;cnt++)
     {
      canTransmit(canREG1, canMESSAGE_BOX1, tx_ptr); /* transmitting 8 different chunks 1 by 1 */
       while(tx_done == 0){};                 /* ... wait until transmit request is through        */
      tx_done=0;
      tx_ptr +=8;    /* next chunk ...*/
      }
    /** - check the received data with the one that was transmitted */
    tx_ptr = &tx_data[0];
    rx_ptr = &rx_data[0];


    for(cnt=0;cnt<63;cnt++)
     {
          if(*tx_ptr++ != *rx_ptr++)
          {
               error++; /* data error */
          }
     }

#endif
    while(1){}; /* wait forever after tx-rx complete. */

/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */

void dumpSomeData()
{
     uint32 tmp = 0x11;


     cnt = (D_COUNT*8)-1;
     dptr = &tx_data[0];
     *dptr = tmp;


     while(cnt--)
     {
        tmp = *dptr++;
        *dptr = tmp + 0x11;
     }
}

void canMessageNotification(canBASE_t *node, uint32 messageBox)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (15) */


    if((node==canREG1) && (messageBox==canMESSAGE_BOX1)){
        tx_done=1;
    }

    if((node==canREG1) && (messageBox==canMESSAGE_BOX2)){
        while(!canIsRxMessageArrived(canREG1, canMESSAGE_BOX2));
             canGetData(canREG1, canMESSAGE_BOX2, rx_ptr); /* copy to RAM */
             rx_ptr +=8;
    }
}

/* USER CODE END */
