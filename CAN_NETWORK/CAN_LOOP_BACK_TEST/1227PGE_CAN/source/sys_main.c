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
/*
 *
 *  This project uses the internal Loop-back feature of CAN module.
 *  CAN1 MessageBox1 is configured as a transmitter
 *  CAN1 MessageBox2 is configured as  receiver with interrupts.
 *  The interrupt is handled in the notification.c file.
 *  The rx_data array is externally defined in the notification.c file to notify notification.c that there are external variables
 *  are being used in that file.
 *
 */
#include "can.h"
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
#include "esm.h"
#include "sys_core.h"
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
#define D_SIZE  8


uint8 tx_data[D_SIZE] = {'H','E','R','C','U','L','E','S'};
uint8 rx_data[D_SIZE] = {0};


/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    _enable_interrupt_();

    /*
     * Initialize the CAN 1 module
     */
    canInit();
    canEnableloopback(canREG1, Internal_Lbk);
    canEnableErrorNotification(canREG1);
    /*
     * Transmit on CAN 1
     */
    canTransmit(canREG1, canMESSAGE_BOX1, (const uint8 *)&tx_data[0]);


    while(1);
/* USER CODE END */

}


/* USER CODE BEGIN (4) */

/*
 * This is area in the program where:
 * 1- Handle interrupts
 * 2- Declare other functions
 *
 * Not using Interrupt in this program.
 * But the interrupt functions are defined below but they're not used.
 * They MUST be provided, even if not used. - WHY??
 */


/*
 * CAN error notification (NOT USED BUT MUST BE PROVIDED)
 */
void canErrorNotification(canBASE_t *node, uint32_t notification){
    return;
}

/*
 * ESM Group Notification (NOT USED BUT MUST BE PROVIDED)
 */
void esmGroup1Notification(unsigned channel){
    return;
}

/*
 * ESM Group2 Notification (NOT USED BUT BE PROVIDED)
 */
void esmGroup2Notification(unsigned channel){
    return;
}
/* USER CODE END */
