/*
 * Current_transducer.c
 *
 *  Created on: Nov 2, 2021
 *      Author: Ryan Heo
 */

#include <Current_transducer.h>
#include "adc.h"
#include "stdlib.h"

double getHVsensorVoltage()
{
    adcData_t adc_data;   // ADC data structure
    adcData_t *adc_data_ptr = &adc_data;  // ADC data pointer
     // declare variables

    adcInit();   // Initialize the ADC module

    adcStartConversion(adcREG1, 1U);  // Start ADC conversion

    while(!adcIsConversionComplete(adcREG1, 1U)); //Wait for ADC conversion
    adcGetData(adcREG1, 1U, adc_data_ptr); //Store conversion into ADC pointer
    value = (unsigned int)adc_data_ptr->value;

    sensor_voltage = (double) value/adc_resolution*max_voltage;

    return sensor_voltage;
}

double getHVsensorCurrent()
{
    // if(voltage < Uref){     // negative current
    // if(voltage > Uref){     // positive current
    output_current  = (sensor_voltage - Uref)*I_PN/1.25;

    return output_current;
}

// Fault check method
_Bool HVcurrent_Range_Check()
{
    flag = false;

    if((output_current >=  MAX_POS_CURRENT) || (output_current <= MIN_NEGATIVE_CURRENT))
               flag =  true;

    return flag;
}
