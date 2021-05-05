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
/*
 * THIS PROJECT EMULATES AN ADS7044 IC BY ENABLING MIBSPIREG3 AS A SLAVE
 *
 * MIBSPIREG1 IS ENABLED AS A MASTER AND IS IN CHARGE OF CONTROLLING DATA FLOW BETWEEN THE MASTER AND SLAVE (ADS7044/MIBSPIREG3)
 *
 * TO ENABLE COMMUNICATION BETWEEN THEM, YOU NEED TO CONNECT SOME JUMPER CABLES:
 *
 *   MIBSPI1_NCS[0] --->  MIBSPI3_NCS[0]
 *   MIBSPI1CLK     --->  MIBSPI3CLK
 *   MIBSPI1SIMO    --->  MIBSPI3SIMO
 *   MIBSPI1SOMI    --->  MIBSPI3SOMI
 *
 */
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
#define TransferGroup0 0
#define TransferGroup1 1

#include "system.h"
#include "mibspi.h"
#include "gio.h"
#include "sys_vim.h"
#include "sys_core.h"
#include "hv_voltage_sensor.c"
//#include "adc_test.c"
#include "hv_voltage_sensor.h"
/* USER CODE END */

/* USER CODE BEGIN (2) */
//void adcVoltageRamp();
void adcSlaveDataSetup();

/* Transfer Group 0 */
/* Initial data to be sent the very first time on power up to the ADC
 * NOTE: May or may not need to be changed
 *
 */
uint16 TX_Data_Master[1] = {0xAAAA};
uint16 TX_Data_Slave[1]  = {0};
uint16 RX_Data_Master[1] = {0};
uint16 RX_Data_Slave[1]  = {0};

/* Transfer Group 1 */
/* Continuous data to send to the ADC
 *
 */
//uint16 TX_ADS7044_Slave[1] = {0};
uint16 RX_Yash_Master[1]   = {0};
uint16 RX_ADS7044_Slave[1] = {0};

bool TX_AVAILABLE = false;  // flags to only transfer mibspi data from slave when current transfer has finished
bool tx_master = false;     // flags to only transfer mibspi data from master when current transfer has finished

/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */

    _enable_IRQ();

    mibspiInit();

    /* Slave Data */

    adcSlaveDataSetup();


    while(1)
    {
        //adcVoltageRamp();
        hv_vs_process(NORMAL_HV_VS_OPERATION);
        // test functions for sending data to TX_ADS7044_Slave[1]
        //uint16 i;
        //i = normal_hv_vs_operation(168);
        //i =hv_vs_at_zero();
        //TX_ADS7044_Slave[0]= i;
    }

/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
/***************************************************************************************************************
 *                  MIBSPI INTERRUPTS
 * *************************************************************************************************************
 * THESE INTERRUPTS FIRE AS SOON AS A SEND TRANSFER IS COMPLETE!
 * I.E. WHEN MASTER (MIBSPIREG1) IS FINISHED A TRANSFER for TRANSFERGROUP1, it'll enter that specific if statement
 * THEN (BECAUSE SPI IS FULL DUPLEX, AND WE RECEIVED MISO DATA AT THE SAME TIME) WE CAN USE THE MIBSPIGETDATA FUNCTION
 * THIS THEN TRANSFERS WHATEVER MISO DATA WE RECEIVED (AND IS IN THE MCU's RX BUFFER), INTO AN ARRAY OF OUR CHOOSING
 *
 * Usually some array like RX_Yash_Master
 */

void mibspiGroupNotification(mibspiBASE_t *mibspi, uint32 group)
{

    if (mibspi == mibspiREG1 && group == TransferGroup0)
     {
         mibspiDisableGroupNotification(mibspiREG1, TransferGroup0);
         mibspiGetData(mibspi, group, RX_Data_Master);
         tx_master = true;
     }

    if (mibspi == mibspiREG1 && group == TransferGroup1)
    {
        mibspiDisableGroupNotification(mibspiREG1, TransferGroup1);
        mibspiGetData(mibspi, group, RX_Yash_Master);
        tx_master = true;
    }

    /**********************************
     *  TESTING FOR SLAVE FUNCTIONALITY
     ***********************************/

        if (mibspi == mibspiREG3 && group == TransferGroup1)
        {
            mibspiDisableGroupNotification(mibspiREG3, TransferGroup1);
            mibspiGetData(mibspi, group, RX_ADS7044_Slave);
            TX_AVAILABLE = true;
        }

        if (mibspi == mibspiREG3 && group == TransferGroup0)
        {
            mibspiDisableGroupNotification(mibspiREG3, TransferGroup0);
            TX_AVAILABLE = true;
        }
}

/*****************************************************************************
 *                 ADC SLAVE SETUP FUNCTIONS - DO NOT MODIFY
 *****************************************************************************/
/* used for ramping up and down the measured voltage simulated by the ADC */

void adcSlaveDataSetup()
{
    mibspiSetData(mibspiREG3, TransferGroup0, TX_Data_Slave);
    mibspiEnableGroupNotification(mibspiREG3, TransferGroup0, 0);
    mibspiTransfer(mibspiREG3, TransferGroup0);
}
/* USER CODE END */
