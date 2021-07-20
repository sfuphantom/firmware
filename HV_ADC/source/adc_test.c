#include <math.h>
#include "sys_common.h"
#include "hv_voltage_sensor.h"
#include<stdio.h>
#include<stdlib.h>

uint16 ADC_output;

// Static function prototypes
//static uint16 normal_hv_vs_operation(int current_voltage);
//static uint16 hv_vs_at_zero();

static int getADCdigital(int battery_voltage)
{
   int output_voltage;
   // convert accumulator voltage to ADC output in integer form
   if (battery_voltage >=144){
       output_voltage = (int)(((battery_voltage *(4.99/479.99))-1.5)*8.2/2.048*pow(2,12));
   }
   else {
       output_voltage = (int)((1.5-(battery_voltage *(4.99/479.99)))*8.2/(-2.048)*pow(2,12));
   }
   return output_voltage;
}

static uint16 normal_hv_vs_operation(int current_voltage)
{
    // HV_VS operate between 123V and 168V range
       while (current_voltage >= 123){
           int c, d;

           for (c = 1; c <= 32767; c++)
               for (d = 1; d <= 32767; d++)
               {
               ADC_output = (uint16) getADCdigital(current_voltage);
               normal_hv_vs_operation(current_voltage-5);
               return ADC_output;
               }
       }
       return ADC_output;
}

static uint16 hv_vs_at_zero()
{
    // HV_VS indicate 0 voltage
    // sending ADC output voltage of 0
    ADC_output = (uint16) getADCdigital(0);
    return ADC_output;
}
