/*  hv_driver.c
 *  Author : Ryan Heo
 *  Date   : 19 October, 2021
 */

 /*============================================================================*/
/* Includes           */
/*============================================================================*/
#include "sys_common.h"
#include <hv_driver.h>
#include <math.h>
#include <gio.h>
#include "sci.h"
#include "string.h"
#include "stdio.h"
#include "mibspi.h"

/*============================================================================*/
/* Definitions           */
/*============================================================================*/
#define TransferGroup0 0
#define TransferGroup1 1
# define MAX_DATA_BITS  (12u)               //Voltage data being sent is in 12 bits

// Definitions for the interpolation function for mapping HV battery voltage
# define SLOPE          (0.01173261f)
# define Y_INTERCEPT    (144.285f)
# define START_INDEX    (1u)

/* Transfer Group 0 */
/* Initial data to be sent the very first time on power up to the ADC
 */
static uint16 TX_Data_Master[1] = {0xAAAA};
static uint16 TX_Data_Slave[1]  = {0};
static uint16 RX_Data_Master[1] = {0};
static uint16 RX_Data_Slave[1]  = {0};

/* Transfer Group 1 */
/* Continuous data to send to the ADC
 */
static uint16 TX_BMS_Master[1]   = {0xF77F}; // how many bits do we need to send? 14 bits only are sent out
                                       // Example
                                       // 1111 0111 0111 1111
                                       // 0011 1101 1101 1111     (chopped off last 2 bits)
static uint16 TX_ADS7044_Slave[1] = {0};
static uint16 RX_BMS_Master[1]   = {0};
static uint16 RX_ADS7044_Slave[1] = {0};

bool TX_AVAILABLE = true;  // flags to only transfer mibspi data from slave when current transfer has finished
bool tx_master = false;     // flags to only transfer mibspi data from master when current transfer has finished
float adc_output = 0.0;
int i = 0;
int sign = 1;
static uint8 binaryNum[12];

void masterDataTranser(){
    //  /* Master Data */
        /* Here you are sending data from master to the slave, TX_Data_Master is the array being sent */
        mibspiSetData(mibspiREG1, TransferGroup0, TX_Data_Master);
        mibspiEnableGroupNotification(mibspiREG1, TransferGroup0, 0);
        mibspiTransfer(mibspiREG1, TransferGroup0);

    while(1){
        if (TX_AVAILABLE == true) /* Needed to enable slave data send */
                    {
                        TX_AVAILABLE = false;
                        adcVoltageTest(); /* Slave function: used for testing the measured voltage simulated by the ADC */

                        /* Master Data Sending */
                        if (tx_master == true)
                        {
                            /* Here you are sending data from master to the slave, TX_Master is the array being sent*/
                            mibspiSetData(mibspiREG1, TransferGroup1, TX_BMS_Master);
                            mibspiEnableGroupNotification(mibspiREG1, TransferGroup1, 0);
                            mibspiTransfer(mibspiREG1, TransferGroup1);

                            tx_master = false;
                        }

                        adc_output =  getADCdata(RX_BMS_Master[0]);
                    }
        }
}

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
            mibspiGetData(mibspi, group, RX_BMS_Master);
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

void adcVoltageTest()
    {
        TX_ADS7044_Slave[0] = 2021; //0x077F; // voltage data to be sent/tested

        mibspiSetData(mibspiREG3, TransferGroup1, TX_ADS7044_Slave);
        mibspiEnableGroupNotification(mibspiREG3, TransferGroup1, 0);
        mibspiTransfer(mibspiREG3, TransferGroup1);

    }

void adcSlaveDataSetup()
    {
        mibspiSetData(mibspiREG3, TransferGroup0, TX_Data_Slave);
        mibspiEnableGroupNotification(mibspiREG3, TransferGroup0, 0);
        mibspiTransfer(mibspiREG3, TransferGroup0);
    }

// Function to extract k bits from p position
// and returns the extracted value as integer */
static uint16 bitExtracted(uint16 number, uint8 k, uint8 p)
{
    return (((1 << k) - 1) & (number >> (p - 1)));
}

static void decToBinary(int n)
{
    int  idx = 0;
    // Size of an integer is assumed to be 12 bits
    for (idx = (MAX_DATA_BITS -1) ; idx >= 0; idx--)
    {
        int k = n >> idx;
        if (k & 1)
        {
            binaryNum[idx] = 1;
        }
        else
        {
            binaryNum[idx] = 0;
        }
    }
}

static float Interpolate_input (int adc_input) //change to uint_8
{
    float output_voltage;
    output_voltage = ((float)adc_input * SLOPE) + Y_INTERCEPT;

    return output_voltage;

}

static int binTwosComplementToSignedDecimal(uint8 binary[],uint8 significantBits)
{
    int power = pow(2,significantBits-1);
    int sum = 0;
    int i;

    for (i = significantBits-1; i >= 0; i--)
    {
        if ( i == (MAX_DATA_BITS -1) && binary[i]!= 0)
        {
            sum = power * -1;
        }
        else
        {
            sum += (binary[i])*power;
        }
        power /= 2;
    }

    return sum;
}

void UARTprintf(const char *_format, ...)
{
   char str[128];
   memset(str, '\0', 128 * sizeof(char));
   int8_t length = -1;

   va_list argList;
   va_start( argList, _format );

   length = vsnprintf(str, sizeof(str), _format, argList);
   str[127] = '\0';

   va_end( argList );

   if (length > 0)
   {
      sciSend(scilinREG, (unsigned)length, (unsigned char*)str);
   }
}

float getADCdata(uint16 input)
{
    int conversion_dec;
    float otp;

    uint16 input_12bits = bitExtracted(input, MAX_DATA_BITS, START_INDEX ); // extracting 12 bits of data (the first 2 bits are 0)
    decToBinary(input_12bits);
    conversion_dec = binTwosComplementToSignedDecimal(binaryNum , MAX_DATA_BITS);
    otp = Interpolate_input(conversion_dec);
    UARTprintf("otp value: \n\r");
    unsigned int adc_input = (int) (otp);
    int i,j;
    for (i = 2; i >= 0; i--)
    {
        uint8 bit = (int) (adc_input % 10);
        for (j = 3; j >= 0; j--)
        {
            uint8 t = (int) ((bit >> j) & 1);
            if (t == 0)
            {
                UARTprintf("0");
            }
            sciSend(scilinREG, 1, &t);
        }
        if (i == 2)
        {
            UARTprintf(" ");
            adc_input = (int) (adc_input/10);
        }
        if (i == 1)
        {
            UARTprintf(" ");
            adc_input = (int) (adc_input/10);
        }
    }
    UARTprintf("\n\r");
    return otp;
}

void unitTesting(){
    int output = getADCdata(2021);
    if (output <= 168 && output >= 167){
        UARTprintf("test1 pass");
        UARTprintf("\n\r");
    }
    output = getADCdata(231);
    if (output <= 148 && output >= 146){
            UARTprintf("test2 pass");
            UARTprintf("\n\r");
        }
    output = getADCdata(-1644);
    if (output <= 126 && output >= 124){
        UARTprintf("test3 pass\n");
        UARTprintf("\n\r");
    }
}
