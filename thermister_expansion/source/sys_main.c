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
#include "mibspi.h"
#include <temperature_buff.h>
#include <temperature.h>
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */

/*uint16_t adc_mode_register[12] ={0x2800,0x2000,0x2000,0x2000,0x2000,0x2000,0x2000,0x2000,0x2000,0x2000,0x2000,0x2000};  ADC runnning in Auto-1 mode*/

#define TransferGroup0           0
#define TransferGroup1           1
#define Channels                 12

static volatile int
isTxComplete;

static uint16_t
TG0_dummydata[2];

static uint16_t
rxData_Buffer[12];

const uint16_t
adc_mode[12]={0x2800,0x2800,0x2800,0x2800,0x2800,0x2800,0x2800,0x2800,0x2800,0x2800,0x2800,0x2800};

temperature_t th;

static temperature_buff_t htemperature_buffer;
static uint16_t
htemperature_buff_data[Channels];


static volatile int
currentIndex;

/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */

        _enable_IRQ();  //Enables global interrupts
        mibspiInit();   //Initialize the mibspi3 module; mibspi3 = mibspiREG3

        uint16 rxADCdata;
        /*
         * Configuring ADS7952.
         */
        uint16 adc_configuration[2] = {0x1000, 0x3FF};  //ADC Program Register configuration - to run in Auto-1 Mode
        mibspiSetData(mibspiREG3, TransferGroup0, adc_configuration);
        mibspiEnableGroupNotification(mibspiREG3, TransferGroup0, 0);
        isTxComplete = 0;
        mibspiTransfer(mibspiREG3, TransferGroup0);
        while(!isTxComplete){}

        temperature_init(&th, Channels);
        currentIndex = 0;
        buff_init(&htemperature_buffer, htemperature_buff_data, Channels);

        mibspiSetData(mibspiREG3, TransferGroup1, (uint16*) adc_mode);
        mibspiEnableGroupNotification(mibspiREG3, TransferGroup1, 0);
        isTxComplete = 0;
        mibspiTransfer(mibspiREG3,TransferGroup1);
        while(!isTxComplete){}

        while(isTxComplete)
        {

            if (buff_get_full(&htemperature_buffer)) {    /* Check if anything in buffer now */
                while (buff_read(&htemperature_buffer, &rxADCdata, 1)) {
                    calculate_temperature(&th, &rxADCdata, currentIndex); /* Process channel-by-channel */
                }
            }

        }


/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */

void mibspiGroupNotification(mibspiBASE_t *mibspi, uint32 group)
{
    mibspiDisableGroupNotification(mibspiREG3, TransferGroup0);
    mibspiDisableGroupNotification(mibspiREG3, TransferGroup1);

    if (mibspi == mibspiREG3 && group == TransferGroup0) {
        if(mibspiIsTransferComplete(mibspi, group)){
                mibspiGetData(mibspi, group, (uint16*)TG0_dummydata);
                isTxComplete = 1;
        }
    }
    if (mibspi == mibspiREG3 && group == TransferGroup1 && isTxComplete==0) {

        if(mibspiIsTransferComplete(mibspi, group) && (buff_get_free(&htemperature_buffer)==12)){

            mibspiGetData(mibspi, group, rxData_Buffer);
            buff_write(&htemperature_buffer, rxData_Buffer, 12);
            isTxComplete = 1;
            mibspiSetData(mibspi, TransferGroup1, (uint16*)adc_mode);
            mibspiEnableGroupNotification(mibspi, group, 0);
            mibspiTransfer(mibspi, TransferGroup1);
        }
    }
    if (mibspi == mibspiREG3 && group == TransferGroup1 && isTxComplete==1) {

        if(mibspiIsTransferComplete(mibspi, group) && (buff_get_free(&htemperature_buffer)==12)){
              mibspiGetData(mibspi, group, (uint16*)rxData_Buffer);
              buff_write(&htemperature_buffer, (uint16*)rxData_Buffer, 12);
              mibspiSetData(mibspi, TransferGroup1, (uint16*)adc_mode);
              mibspiEnableGroupNotification(mibspi, group, 0);
              mibspiTransfer(mibspi, TransferGroup1);
        }
    }
}
/* USER CODE END */
