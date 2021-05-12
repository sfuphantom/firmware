/*
 * hv_voltage_sensor.c
 *
 *  Created on: Mar 16, 2021
 *      Author: Ryan Heo
 */

#include "sys_common.h"
#include "hv_voltage_sensor.h"
#include "mibspi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TransferGroup0 0
#define TransferGroup1 1

uint16 ADC_output;

/* Transfer Group 0 */
/* Initial data to be sent the very first time on power up to the ADC
 * NOTE: May or may not need to be changed
 *
 */
uint16 TX_Data_Master[1] = {0xAAAA};
uint16 TX_Data_Slave[1]  = {0};
uint16 RX_Data_Master[1] = {0};
uint16 RX_Data_Slave[1]  = {0};

uint16 RX_Yash_Master[1]   = {0};
uint16 RX_ADS7044_Slave[1] = {0};

bool TX_AVAILABLE = false;  // flags to only transfer mibspi data from slave when current transfer has finished
bool tx_master = false;     // flags to only transfer mibspi data from master when current transfer has finished

void hv_vs_process(uint8_t state)
{
    switch(state)
    {
        case HV_VS_BOTH_BOUNDS:
            hv_vs_both_bounds();
            break;
        case HV_VS_OUT_OF_RANGE:
            hv_vs_out_of_range();
            break;
        case HV_VS_AT_ZERO:
            hv_vs_at_zero();
            break;
        case HV_VS_SWEEP:
            hv_vs_sweep();
            break;
    }
}

static int twosComplement(int negative_output){
    negative_output=negative_output*(-1);
    int carry = 1;
    int binary[] ={1,0,0,0,0,0,0,0,0,0,0,0};
    int twoscomplement=0;
    int i;

    // converting to a binary value in ones complement form
    for (i=11;negative_output>0;i--){
        binary[i]=negative_output%2;
        negative_output=negative_output/2;
    }

    // converting to ones'complement
    for (i=1;i<=11;i++){
        if (binary[i]==0){
            binary[i]=1;
        }
        else if(binary[i]==1){
            binary[i]=0;
        }
    }

    // converting to twos'complement
    for (i=11;i>0;i--){
        if(binary[i] == 1 && carry == 1){
            binary[i] = 0;
        }
        else if(binary[i] == 0 && carry == 1){
            binary[i] = 1;
            carry = 0;
        }
        else{
            binary[i] = binary[i];
        }
    }

    // converting back to an unsigned decimal
    for (i=11;i>=0;i--){
        int exp =0;
        twoscomplement = twoscomplement+binary[i]*pow(2,exp);
        exp +=1;
    }
    return twoscomplement;
}

static int getADCdigital(int battery_voltage)
{
   int output_voltage;
   // convert accumulator voltage to ADC output in integer form
   if (battery_voltage >=144){
       output_voltage = (int)(((battery_voltage *(4.99/479.99))-1.5)*8.2/2.048*4096);
   }
   else{
       output_voltage = (int)((1.5-(battery_voltage *(4.99/479.99)))*8.2/(-2.048)*4096);
       if(output_voltage<0){
           output_voltage = twosComplement(output_voltage);
       }
   }
   return output_voltage;
}

static void hv_vs_both_bounds()
{
    //sending lower bound voltage of 125
    ADC_output = (uint16)getADCdigital(125);
    spiSetup(ADC_output);

    //Delay
    //sending upper bound voltage of 168
    ADC_output = (uint16)getADCdigital(168);
    spiSetup(ADC_output);
}

static void hv_vs_out_of_range()
{
    // HV_VS doesn't operate outside normal operating range between 125V and 168V
    //sending ADC output voltage below the lower bound voltage
    ADC_output = (uint16)getADCdigital(120);
    spiSetup(ADC_output);

    //Delay
    //sending ADC output voltage above the upper bound voltage
    ADC_output = (uint16)getADCdigital(170);
    spiSetup(ADC_output);
}

static void hv_vs_at_zero()
{
    // HV_VS indicate 0 voltage
    // sending ADC output voltage of 0
    ADC_output = (uint16)0;
    spiSetup(ADC_output);
}

static void hv_vs_sweep()
{
    //Sweep test with 1V increment from 125V to 168V
    int input_voltage = 125;
    while(input_voltage <=168){
        ADC_output = (uint16)getADCdigital(input_voltage);
        spiSetup(ADC_output);
        //Delay
        input_voltage += 1;
    }
}

static void spiSetup(uint16 voltage)
{
    mibspiSetData(mibspiREG3, TransferGroup1, &voltage);
    mibspiEnableGroupNotification(mibspiREG3, TransferGroup1, 0);
    mibspiTransfer(mibspiREG3,TransferGroup1);
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
