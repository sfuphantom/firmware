/*
 * thermistor.c
 *
 *  Created on: Jan 9, 2020
 *      Author: JASKANWAL SINGH
 */

#include "thermistor.h"
#include "sys_vim.h"
#include "sys_core.h"
#include "sci.h"


/************************************************************************************************************************************************/
//Setting up mibSPI communication with the ADC
/************************************************************************************************************************************************/


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

static uint16
adc_configuration[11] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3C00, 0x3000, 0x9300};

static uint16
adc_mode[12]={0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000};

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

    /*
static uint16
adc_configuration[11] = {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3C00, 0x3000, 0x9300};
*
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

/*
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

    if (mibspi == mibspiREG3 && group == TransferGroup1 && adcConfigured == 1) {

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
/************************************************************************************************************************************************/
/*Validating usage status */
/************************************************************************************************************************************************/

uint8  measuring_charge_thermistor =   0;
uint8 measuring_run_thermistor =   0;

uint8_t validate_usage_status_thermistor(uint8_t status )      //Inquires whether the car is charging or running while the thermistor is measuring?
{
   (status == 0)   ?   (measuring_charge_thermistor = 1)   :   (measuring_run_thermistor = 1);
   return status;
}

/************************************************************************************************************************************************/
/*Reading, Extracting and Printing Thermistor values*/
/************************************************************************************************************************************************/

uint16_t    read_specific_mux_all_channels_thermistor(uint8_t mux_identity)     //reads and returns the thermistor values from a specific mux on all the channels
{
    while(adcConfigured){
                   mibspiSetData(mibspiREG3, TransferGroup1, adc_mode);
                   mibspiEnableGroupNotification(mibspiREG3, TransferGroup1, 0);
                   ReceivedData = 0;
                   mibspiTransfer(mibspiREG3, TransferGroup1);
                   while(!ReceivedData){}
            }

    //Printing the data received from the ADC
    extract_thermistor_readings_rx_data_buffer();


}

void    extract_thermistor_readings_rx_data_buffer()
{
    uint8_t i=0;
    for (;  i<12;   i++)
    {
        rxData_Buffer[i]    &=  0x0FFF;  //Masking to remove channel address from the data received from the ADC and
                                         //keeping only the Hex format of thermistor readings
    }
}

#define REFERENCE_VOLTAGE 2.5

void    print_thermistor_readings_voltage()
{
    sciInit();
    uint16_t value, voltage, numberOfChars, i=0;
    unsigned char command[8];


    for(;   i<12;   i++)
    {
        value   =   (uint16_t)rxData_Buffer[i];
        voltage =   ((1.0*value)/4095)*REFERENCE_VOLTAGE;

        numberOfChars   =   ltoa(voltage,(char *)command);
        sciSend(scilinREG,  10,  (unsigned char  *)"Channel : ");
        sciSend(scilinREG,  numberOfChars,  command);
    }
}

