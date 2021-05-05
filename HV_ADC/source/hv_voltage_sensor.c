/*
 * hv_voltage_sensor.c
 *
 *  Created on: Mar 16, 2021 
 *      Author: Ryan Heo
 */

#include <math.h>
#include "sys_common.h"
#include "hv_voltage_sensor.h"

uint16 ADC_output;

typedef enum
{
    NORMAL_HV_VS_OPERATION,
    HV_VS_BOTH_BOUNDS,
    HV_VS_OUT_OF_RANGE,
    HV_VS_AT_ZERO,
    HV_VS_SWEEP
} testcases_name;

// Static function prototypes
static void normal_hv_vs_operation();
static void hv_vs_both_bounds();
static void hv_vs_out_of_range();
static void hv_vs_both_bounds();
static void hv_vs_at_zero();
static void hv_vs_sweep();
static int getADCdigital(int battery_voltage);

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

static void normal_hv_vs_operation()
{
    // HV_VS operate between 123V and 168V range
       int current_voltage = 168;
       while(current_voltage >= 123)
            ADC_output = getADCdigital(current_voltage);
            TX_ADS7044_Slave[1] = ADC_output;
            //time delay?
            current_voltage -= 5;
}

static void hv_vs_both_bounds()
{
    //sending lower bound voltage of 125
    ADC_output = getADCdigital(125);
    TX_ADS7044_Slave[1] = ADC_output;
        
    //wait for some time after sending first data?
    //sending upper bound voltage of 168
    ADC_output = getADCdigital(168);
    TX_ADS7044_Slave[1] = ADC_output;
}

static void hv_vs_out_of_range()
{
    // HV_VS doesn't operate outside normal operating range between 125V and 168V
    //sending ADC output voltage below the lower bound voltage
    ADC_output = getADCdigital(120);
    TX_ADS7044_Slave[1] = ADC_output;
           
    //wait for some time after sending first data?
    //sending ADC output voltage above the upper bound voltage
    ADC_output = getADCdigital(170);
    TX_ADS7044_Slave[1] = ADC_output;
}

static void hv_vs_at_zero()
{
    // HV_VS indicate 0 voltage
    // sending ADC output voltage of 0
    ADC_output = 0;
    TX_ADS7044_Slave[1] = ADC_output;
}

static void hv_vs_sweep()
{
    //Sweep test with 1V increment from 125V to 168V
    int input_voltage = 125;
    while(input_voltage <=168){
        ADC_output = getADCdigital(input_voltage);
        TX_ADS7044_Slave[1] = ADC_output;
        //time delay?
        input_voltage += 1;
    }
}
