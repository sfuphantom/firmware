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
#include "mibspi.h"
#include "spi.h"
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
//#pragma DATA_SECTION(RX_Data_Slave,"NonCacheSect")
//#pragma DATA_SECTION(TX_Data_Slave,"NonCacheSect")

//uint16_t RX_Data_Slave[128]  = {0};
//uint16_t TX_Data_Slave[26]  = {1};

/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */

//uint16_t adc_mode_register[12] ={0x2800,0x2000,0x2000,0x2000,0x2000,0x2000,0x2000,0x2000,0x2000,0x2000,0x2000,0x2000}; // ADC runnning in Auto-1 mode
uint16_t adc_received_Data[12] = {0}; // For storing the ADC conversion result.
uint16_t threshold_temp = 0x003C; // 16-bit = 0x003C = 60
uint16 temperature_adc [12]={0}; // Temperature Result
uint16_t count=0; // For now just counting errors

/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */


        mibspiBASE_t *mibSpiReg3 = mibspiREG3; //Creating an instance of mibspi3 for initialization

        _enable_IRQ();  //Enables global interrupts

        mibspiInit();   // Initialize the mibspi3 module

        uint16_t adc_configuration [2]= {0x1000, 0x3FFF}; // ADC Program Register configuration - to run in Auto-1 Mode
        mibspiSetData(mibspiREG3, 0, adc_configuration);
        uint16_t adc_mode_register[12] = {0x2800,0x2800,0x2800,0x2800,0x2800,0x2800,0x2800,0x2800,0x2800,0x2800,0x2800,0x2800}; // ADC runnning in Auto-1 mode
        uint16 Data;




        // Configure Program Register of External ADC - Only needed once
        mibspiTransfer(mibSpiReg3, 0);
        while(!(mibspiIsTransferComplete(mibSpiReg3,0))){}; // Wait till you have the configured the ADC to run in Auto-1 mode
        Data = mibSpiReg3->BUF;
        mibspiSetData(mibspiREG3,1,&adc_mode_register[0]);


        //Now, we can talk to the ADC - in the while loop
        while(1)
        {
            

            mibspiTransfer(mibSpiReg3,1); // Initiated Transfer Group 1 transmission to the ADC
            while(!(mibspiIsTransferComplete(mibSpiReg3,1))){}; // Wait till you have the conversion results of all 12 ADC channels

            // Now, we read the conversion results from each of the 12 RXRAM buffer's RXDATA from the mibSPI3 multi-buffer RAM
            mibspiGetData(mibSpiReg3,1,&adc_received_Data[0]); // Get all the received data from the mibspiRAM's RXRAM block to the adc_recieved_Data

            uint32 i;
            for (i=0; i<12; i++)
            {
                
                adc_received_Data[i]&=~0xF000; // Clear the first 4 bits - the channel address

                uint32 resistance = 10000 * ((4095/adc_received_Data[i])-1);
                //temperature_adc[i]=0;
                temperature_adc[i] = resistance;  // For now we can compare to the datasheet graph // can convert to temp easily
                if (temperature_adc[i] >threshold_temp)
                    count++;
                else
                    continue;
            }
            Data = mibSpiReg3->BUF;

        }

/* USER CODE END */
}

/* USER CODE BEGIN (4) */
/* USER CODE END */
