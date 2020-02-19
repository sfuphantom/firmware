/*
 * thermistor.c
 *
 *  Created on: Jan 9, 2020
 *      Author: JASKANWAL SINGH
 */

#include "thermistor.h"



/************************************************************************************************************************************************/
//Setting up mibSPI communication with the ADC
/************************************************************************************************************************************************/

#define TransferGroup0           0x0
#define TransferGroup1           0x1
#define Channels                 12

static volatile int
isTxComplete;
volatile int
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

static volatile int
currentIndex;

void setup_mibspi_thermistor()        //prepare the thermistor to start reading
{
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

        while(adcConfigured){

            uint8 mux = 0;
            if (mux == 15)
            {
                mux = 0;
            }
            update_mux(mux);

               mibspiSetData(mibspiREG3, TransferGroup1, adc_mode);
               mibspiEnableGroupNotification(mibspiREG3, TransferGroup1, 0);
               ReceivedData = 0;
               mibspiTransfer(mibspiREG3, TransferGroup1);
               while(!ReceivedData){}

               extract_thermistor_readings_rx_data_buffer();
               update_thermistor_temperature_and_flag_structure(mux);
               mux++;
               print_thermistor_readings_voltage();

        }
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


            mibspiGetData(mibspi, group, rxData_Buffer);

              ReceivedData = 1;



        }
    }

/************************************************************************************************************************************************/
/*Validating usage status */
/************************************************************************************************************************************************/

uint8 measuring_charge_thermistor =   0;
uint8 measuring_run_thermistor =   0;

uint8_t validate_usage_status_thermistor(uint8_t status )      //Inquires whether the car is charging or running while the thermistor is measuring?
{
   (status == 0)   ?   (measuring_charge_thermistor = 1)   :   (measuring_run_thermistor = 1);
   return status;
}


/************************************************************************************************************************************************/
/*Reading, Extracting and Printing Thermistor values*/
/************************************************************************************************************************************************/


void    extract_thermistor_readings_rx_data_buffer()
{
    uint8 channel=0;
    for (;  channel<12;   channel++)
    {
        rxData_Buffer[channel]    &=  0x0FFF;  //Masking to remove channel address from the data received from the ADC and
                                               //keeping only the Hex format of thermistor readings
    }
}

#define REFERENCE_VOLTAGE 2.5
void    print_thermistor_readings_voltage()
{
    sciInit();
    uint16_t value,  numberOfChars, i=0;
    uint16_t voltage;
    unsigned char command[8];


    for(;   i<12;   i++)
    {
        value   =   (uint16_t)rxData_Buffer[i];
//      voltage =   (((float)value)/4095)*REFERENCE_VOLTAGE;
        voltage =   2.3;


//        printf("Channel : ");
//        printf("%d", i);
//        printf(" - ");
//        printf("%d", voltage);
//        printf("\n");

        numberOfChars   =   ltoa(value,(char *)command);
        sciSend(scilinREG,  16,  (unsigned char  *)"Voltage_MUX_1 : ");
        sciSend(scilinREG,  numberOfChars,  command);
        sciSend(scilinREG,  2,  (unsigned char  *)"\r\n");
    }

//        printf("\n");
        sciSend(scilinREG,  2,  (unsigned char  *)"\r\n");
        sciSend(scilinREG,  2,  (unsigned char  *)"\r\n");
        sciSend(scilinREG,  2,  (unsigned char  *)"\r\n");
}

/************************************************************************************************************************************************/
/*Updating the Temperature logging sructure*/
/************************************************************************************************************************************************/

void update_thermistor_temperature_and_flag_structure(int mux)
{
    uint8 channel = 0, MUX = mux*12;
    for (; channel < 12; channel++, MUX++)
    {
        //logging Temperature
        thermistor_temperature_and_flag_struct[MUX].temperature = DoCalculation( (((float)rxData_Buffer[channel])/4095)*REFERENCE_VOLTAGE);
        //Updating Flag
        (thermistor_temperature_and_flag_struct[MUX].temperature >= 60) ?  (thermistor_temperature_and_flag_struct[MUX].temperature_flag = 1) : (thermistor_temperature_and_flag_struct[MUX].temperature_flag = 0);
    }
}

void update_mux(uint8 current_mux)
{
    if (current_mux == 0)
    {
        gioSetBit(gioPORTA, 2, 0);
        gioSetBit(gioPORTA, 5, 0);
        gioSetBit(gioPORTA, 6, 0);
        gioSetBit(gioPORTA, 7, 0);
    }
    else if (current_mux == 1)
    {
        gioSetBit(gioPORTA, 2, 1);
        gioSetBit(gioPORTA, 5, 0);
        gioSetBit(gioPORTA, 6, 0);
        gioSetBit(gioPORTA, 7, 0);
    }
    else if (current_mux == 2)
        {
            gioSetBit(gioPORTA, 2, 0);
            gioSetBit(gioPORTA, 5, 1);
            gioSetBit(gioPORTA, 6, 0);
            gioSetBit(gioPORTA, 7, 0);
        }
    else if (current_mux == 3)
        {
            gioSetBit(gioPORTA, 2, 1);
            gioSetBit(gioPORTA, 5, 1);
            gioSetBit(gioPORTA, 6, 0);
            gioSetBit(gioPORTA, 7, 0);
        }
    else if (current_mux == 4)
        {
            gioSetBit(gioPORTA, 2, 0);
            gioSetBit(gioPORTA, 5, 0);
            gioSetBit(gioPORTA, 6, 1);
            gioSetBit(gioPORTA, 7, 0);
        }
    else if (current_mux == 5)
        {
            gioSetBit(gioPORTA, 2, 1);
            gioSetBit(gioPORTA, 5, 0);
            gioSetBit(gioPORTA, 6, 1);
            gioSetBit(gioPORTA, 7, 0);
        }
    else if (current_mux == 6)
        {
            gioSetBit(gioPORTA, 2, 0);
            gioSetBit(gioPORTA, 5, 1);
            gioSetBit(gioPORTA, 6, 1);
            gioSetBit(gioPORTA, 7, 0);
        }
    else if (current_mux == 7)
        {
            gioSetBit(gioPORTA, 2, 1);
            gioSetBit(gioPORTA, 5, 1);
            gioSetBit(gioPORTA, 6, 1);
            gioSetBit(gioPORTA, 7, 0);
        }
    else if (current_mux == 8)
        {
            gioSetBit(gioPORTA, 2, 0);
            gioSetBit(gioPORTA, 5, 0);
            gioSetBit(gioPORTA, 6, 0);
            gioSetBit(gioPORTA, 7, 1);
        }
    else if (current_mux == 9)
        {
            gioSetBit(gioPORTA, 2, 1);
            gioSetBit(gioPORTA, 5, 0);
            gioSetBit(gioPORTA, 6, 0);
            gioSetBit(gioPORTA, 7, 1);
        }
    else if (current_mux == 10)
        {
            gioSetBit(gioPORTA, 2, 0);
            gioSetBit(gioPORTA, 5, 1);
            gioSetBit(gioPORTA, 6, 0);
            gioSetBit(gioPORTA, 7, 1);
        }
    else if (current_mux == 11)
        {
            gioSetBit(gioPORTA, 2, 1);
            gioSetBit(gioPORTA, 5, 1);
            gioSetBit(gioPORTA, 6, 0);
            gioSetBit(gioPORTA, 7, 1);
        }
    else if (current_mux == 12)
        {
            gioSetBit(gioPORTA, 2, 0);
            gioSetBit(gioPORTA, 5, 0);
            gioSetBit(gioPORTA, 6, 1);
            gioSetBit(gioPORTA, 7, 1);
        }
    else if (current_mux == 13)
        {
            gioSetBit(gioPORTA, 2, 1);
            gioSetBit(gioPORTA, 5, 0);
            gioSetBit(gioPORTA, 6, 1);
            gioSetBit(gioPORTA, 7, 1);
        }
    else if (current_mux == 14)
        {
            gioSetBit(gioPORTA, 2, 0);
            gioSetBit(gioPORTA, 5, 1);
            gioSetBit(gioPORTA, 6, 1);
            gioSetBit(gioPORTA, 7, 1);
        }
    else if (current_mux == 15)
        {
            gioSetBit(gioPORTA, 2, 1);
            gioSetBit(gioPORTA, 5, 1);
            gioSetBit(gioPORTA, 6, 1);
            gioSetBit(gioPORTA, 7, 1);
        }
}





