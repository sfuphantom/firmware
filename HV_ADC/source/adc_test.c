#include <math.h>
#include "sys_common.h"
#include "hv_voltage_sensor.h"

uint16 ADC_output;

// Static function prototypes
static uint16 normal_hv_vs_operation(int current_voltage);

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
            ADC_output = (uint16) getADCdigital(current_voltage);
            normal_hv_vs_operation(current_voltage-5);
            return ADC_output;
            //time delay?
       }
       return ADC_output;
}
