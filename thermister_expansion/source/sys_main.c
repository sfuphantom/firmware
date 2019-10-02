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
#include "sys_vim.h"
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

/*uint16_t adc_mode_register[12] ={0x2800,0x2000,0x2000,0x2000,0x2000,0x2000,0x2000,0x2000,0x2000,0x2000,0x2000,0x2000};  ADC runnning in Auto-1 mode*/

#define TransferGroup0           0x0
#define TransferGroup1           0x1
#define Channels                 12

static volatile int
isTxComplete;
static volatile int
adcConfigured;
static volatile int
ReceivedData;

static volatile int
Processed;

static uint16
TG0_dummydata[15];

static uint16
rxData_Buffer[12];

/*
 *  CS = 0
 *  Send = 0x3C00 - Request to enter Auto-2 Mode
 *  Receive = Invalid Data
 *  CS=1
 *
 *  CS=0
 *  Entered Auto-2 Mode
 *  Send = 0x92C0  - Program the Auto-2 Program Register; Selecting the last Channel to Scan starting at Ch0
 *  Receive = Invalid Data; But ADC acquires CH0 input in this frame, but samples in the next frame.
 *  CS=1
 */

static uint16
adc_configuration[15] = {0x000, 0x3C00,0x3000, 0x3000, 0x3000, 0x3000, 0x92C0, 0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000};


/*
 *   CS = 0
 *   Send = 0x3000 - Continue to operate in Auto-2 Mode
 *   Receive = Conversion Result of CH0, ADC acquires CH1 in this frame, but samples in the next frame
 *   CS = 1
 *
 *
 *   CS = 0
 *   Send = 0x3000 - Continue to operate in Auto-2 Mode
 *   Receive = Conversion Result of CH1, ADC acquires CH2 in this frame, but samples in the next frame
 *   CS = 1
 *
 *   Continue this till CH11 is sampled. At CH11 sampling, ADC selects CH0 and repeats the process.
 *
 */

static uint16
adc_mode[12]={0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000};



temperature_t th;

static temperature_buff_t htemperature_buffer;
static uint16
htemperature_buff_data[Channels];


static volatile int
currentIndex;

/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */

        _enable_IRQ();  //Enables global interrupts
        mibspiInit();   //Initialize the mibspi3 module; mibspi3 = mibspiREG3
        uint16_t rxADCdata;
        /*
         * Configuring ADS7952.
         */

        mibspiSetData(mibspiREG3, TransferGroup0, adc_configuration);
        mibspiEnableGroupNotification(mibspiREG3, TransferGroup0, 0);
        mibspiTransfer(mibspiREG3, TransferGroup0);
        adcConfigured = 0;
        while(!adcConfigured){}

        while(adcConfigured){
               mibspiSetData(mibspiREG3, TransferGroup1, adc_mode);
               mibspiEnableGroupNotification(mibspiREG3, TransferGroup1, 0);
               ReceivedData = 0;
               mibspiTransfer(mibspiREG3, TransferGroup1);
               while(!ReceivedData){}
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
                mibspiGetData(mibspi, group, TG0_dummydata);
                mibspiDisableGroupNotification(mibspiREG3, TransferGroup0);
                adcConfigured = 1;

    }

    if (mibspi == mibspiREG3 && group == TransferGroup1 && adcConfigured==1) {

       /*if((buff_get_free(&htemperature_buffer)==12)){*/
              mibspiGetData(mibspi, group, rxData_Buffer);
              /*int i = 0;
              for (;i<12;i++){
                  (rxData_Buffer[i])&=~0xF000; /* Clear the upper 4 bits - Channel Address
                   uint16 resistance = 10000 * ((4095/(rxData_Buffer[i])-1));
                   rxData_Buffer[i] = resistance;
              }*/
              //buff_write(&htemperature_buffer, &rxData_Buffer, 12);
              ReceivedData = 1;
              //Processed = 1;

        //}

    }
}

/* USER CODE END */
