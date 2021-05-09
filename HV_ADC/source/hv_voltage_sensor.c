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

uint16 ADC_output;

void hv_vs_process(uint8_t state)
{
    switch(state)
    {
        case NORMAL_HV_VS_OPERATION:
            normal_hv_vs_operation();
            break;
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
    int binary[] = {1000000000000};
    int twoscomplement =0;
    int i;
    // converting to a binary value in ones complement form
    for (i=12;i>negative_output;i--){
        binary[i]=negative_output%2;
        negative_output=negative_output/2;
    }
    // converting to twos complement
    for (i=1;i<13;i++){
        if (binary[i]==0){
            binary[i]=1;
        }
        else if(binary[i]==1){
            binary[i]=0;
        }
    }
    for (i=12;i>0;i--){
        int exp =0;
        twoscomplement = twoscomplement+binary[i]*pow(2,exp);
    }
    twoscomplement = twoscomplement*(-1)+1;
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

static void normal_hv_vs_operation()
{
    // HV_VS operate between 123V and 168V range
       int current_voltage = 168;
       while (current_voltage >= 123)
            ADC_output = (uint16)getADCdigital(current_voltage);
            spiSetup(ADC_output);
            //time delay?
            current_voltage -= 5;
}

static void hv_vs_both_bounds()
{
    //sending lower bound voltage of 125
    ADC_output = (uint16)getADCdigital(125);
    spiSetup(ADC_output);

    //wait for some time after sending first data?
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

    //wait for some time after sending first data?
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
        //time delay?
        input_voltage += 1;
    }
}

static void spiSetup(uint16 voltage)
{
    mibspiSetData(mibspiREG3, 1, &voltage);
    mibspiEnableGroupNotification(mibspiREG3, 1, 0);
    mibspiTransfer(mibspiREG3,1);
}
