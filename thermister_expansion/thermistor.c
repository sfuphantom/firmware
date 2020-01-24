/*
 * thermistor.c
 *
 *  Created on: Jan 9, 2020
 *      Author: JASKANWAL SINGH
 */

#include "thermistor.h"
#include "sys_vim.h"
#include "sys_core.h"


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
TG0_dummydata[11];

static uint16
rxData_Buffer[12];


void setup_mibspi_thermistor()        //prepare the thermistor to start reading
{



/*
 *  CS = 0
 *  Send = 0x3C40 - Request to enter Auto-2 Mode with Vref = 2* Vref as I/P range
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
adc_configuration[11] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3C00, 0x3000, 0x9300};
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

/*
 * static uint16
adc_mode[12]={ 0x0000,0x0000, 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000 ,0x0000};
*/

static volatile int
currentIndex;

        _enable_IRQ();  //Enables global interrupts
        mibspiInit();   //Initialize the mibspi3 module; mibspi3 = mibspiREG3
        //uint16_t rxADCdata;
        /*
         * Configuring ADS7952.
         */

        mibspiSetData(mibspiREG3, TransferGroup0, adc_configuration);
        mibspiEnableGroupNotification(mibspiREG3, TransferGroup0, 0);
        mibspiTransfer(mibspiREG3, TransferGroup0);
        adcConfigured = 0;
        while(!adcConfigured){}

}

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


