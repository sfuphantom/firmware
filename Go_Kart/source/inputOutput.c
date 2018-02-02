/*
 * inputOutput.c
 *
 *  Created on: Dec 14, 2017
 *      Author: sormoh
 */

/* Include Files */

#include "esm.h"
#include "sys_selftest.h"
#include "adc.h"
#include "can.h"
#include "gio.h"
#include "sci.h"
#include "het.h"
#include "rti.h"
#include "i2c.h"
#include "sys_dma.h"

#include <stdio.h>

#include "A_LCD.h"
#include "alarmLogic.h"
#include "utilities.h"
#include "mainStateMachine.h"
#include "A_exception_handler.h"


#define ADC_DATA_CONVERT_NUM 5
#define ADC_MAX_DELAY_ITERATIONS    60


// Initialization
uint8 enableSwitch = 0;
uint8 runSwitch = 0;
float64 inputThrottle_V = 0;
float64 outputThrottle_pct = 0;
float64 batteryVoltage_V = 0;
float64 batteryDischargeCurrent_A = 0;
float64 batteryDischargeCurrentLow_A = 0;
float64 batteryDischargeCurrentHigh_A = 0;
uint8 isPreChargeContactorClosed = 0;
uint8 isPositiveLegContactorClosed = 0;
uint8 isNegativeLegContactorClosed = 0;
adcData_t adc_data[ADC_DATA_CONVERT_NUM] = {0};

uint8 adc_max_delay_iterations;

// *************************************************************************
// Function:    fxPreChargeContactor
// Purpose:     Closes/Opens the pre-charge contactor
// *************************************************************************
void fxPreChargeContactor(uint8 val){

    gioSetBit(gioPORTA, 5, val);

    if (val > 0) {
        isPreChargeContactorClosed = 1;
    } else {
        isPreChargeContactorClosed = 0;
    }

}

// *************************************************************************
// Function:    fxPostiveLegContactor
// Purpose:     Closes/Opens the positive leg contactor
// *************************************************************************
void fxPostiveLegContactor(uint8 val){

    gioSetBit(gioPORTA, 6, val);

    if (val > 0) {
        isPositiveLegContactorClosed = 1;
     } else {
        isPositiveLegContactorClosed = 0;
     }
}

// *************************************************************************
// Function:    fxNegativeLegContactor
// Purpose:     Closes/Opens the negative leg contactor
// *************************************************************************
void fxNegativeLegContactor(uint8 val){

    gioSetBit(gioPORTA, 7, val);

    if ( val > 0 ) {
        isNegativeLegContactorClosed = 1;
     } else {
        isNegativeLegContactorClosed = 0;
     }
}


// *************************************************************************
// Function:    fxReadAnalogInputs
// Purpose:     Reads analog inputs every 100 ms
// *************************************************************************

void fxReadAnalogInputs(void){


    // Throttle local variables
    float64 outputThrottleSp_pct = 0;


    // Current transducer local variables
    float64 batteryDischargeCurrentLowSupplyVoltage_V = 0;
    float64 batteryDischargeCurrentHighSupplyVoltage_V = 0;
    float64 offsetVoltageHigh = 0;
    float64 offsetVoltageLow = 0;
    float64 highRangeWeightingFactor = 0;

    adcStartConversion(adcREG1, adcGROUP1);

    adc_max_delay_iterations = (uint8)ADC_MAX_DELAY_ITERATIONS;

    while(   adcIsConversionComplete(adcREG1,adcGROUP1) == 0 ){

        if( !(--adc_max_delay_iterations) ){
            setError(ERR_ADC_RETRIEVE_DATA_OUT_OF_TIME);
            return;
        }
    }

    if( adcGetData(adcREG1, 1U, adc_data) != ADC_DATA_CONVERT_NUM){
        setError(ERR_ADC_PIN_LOST_CONNECTION);
        return;
    }

    // Input throttle voltage 0 - 2.1V
    inputThrottle_V = ((5.0*adc_data[0].value) / 4096.0);


    // Convert Input throttle voltage to a percentage
    outputThrottle_pct = (100/2.6)*inputThrottle_V; //throttle percent setpoint - input to the ramp

    if (outputThrottle_pct <= 2)
        outputThrottle_pct = 0;
    else if (outputThrottle_pct >= 100)
        outputThrottle_pct = 100;


   // outputThrottle_pct = ramp(outputThrottleSp_pct, 1); // 1 second ramp function

    // Voltage Transducer 0-5V -> 0-1000V
    batteryVoltage_V = (1000/5) * ((5*(double)adc_data[1].value) / 4096.0);


 /*
    Calculate current:
                                current high limit   supply voltage nominal
            current = offsetV * ------------------ * ----------------------*(1/G)
                                offset voltage HL       supply voltage

 */

    batteryDischargeCurrentLowSupplyVoltage_V = ((5*(double)adc_data[2].value) / 4096);
    batteryDischargeCurrentHighSupplyVoltage_V = ((5*(double)adc_data[3].value) / 4096);

    //printf("CT_L_SupplyVoltage: %f \r\n", batteryDischargeCurrentLowSupplyVoltage_V);
    //printf("CT_H_SupplyVoltage: %f \r\n", batteryDischargeCurrentHighSupplyVoltage_V);

    offsetVoltageLow = batteryDischargeCurrentLowSupplyVoltage_V - 2.5;
    offsetVoltageHigh = batteryDischargeCurrentHighSupplyVoltage_V - 2.5;

    batteryDischargeCurrentLow_A =  offsetVoltageLow*(1/0.0667);
    batteryDischargeCurrentHigh_A =  offsetVoltageHigh*(1/0.0057);


    // Calculate high range weighting factor
    highRangeWeightingFactor = (0-1)/(30-40)*(batteryDischargeCurrentHigh_A-30)+ 0;

    if (highRangeWeightingFactor < 0)
        highRangeWeightingFactor = 0;
    else if (highRangeWeightingFactor > 1)
        highRangeWeightingFactor = 1;

    // Calculate raw stack voltage using a combination of the high and low range inputs
    batteryDischargeCurrent_A = (highRangeWeightingFactor * (batteryDischargeCurrentHigh_A - batteryDischargeCurrentLow_A)) + batteryDischargeCurrentLow_A;






}

// *************************************************************************
// Function:    fxWriteDigitalOutputs
// Purpose:     Write digital outputs every 100 ms
// *************************************************************************

void fxWriteDigitalOutputs (void){

    switch(state){
        case UNLOCKED:
            fxPreChargeContactor(0);
            fxPostiveLegContactor(0);
            fxNegativeLegContactor(0);
                break;

        case STANDBY:
            fxPreChargeContactor(0);
            fxPostiveLegContactor(0);
            fxNegativeLegContactor(0);
                break;

        case PRECHARGE:
            fxPreChargeContactor(1);
            fxPostiveLegContactor(0);
            fxNegativeLegContactor(1);

                break;

        case HIGH_VOLTAGE:
            fxPreChargeContactor(1);
            fxPostiveLegContactor(1);
            fxNegativeLegContactor(1);
                break;

        case RUNNING:
            fxPreChargeContactor(1);
            fxPostiveLegContactor(1);
            fxNegativeLegContactor(1);
                break;

        case SHUTDOWN:
            fxPreChargeContactor(1);
            fxPostiveLegContactor(1);
            fxNegativeLegContactor(1);
                break;
     }

}

// *************************************************************************
// Function:    fxWriteAnalogOutputs
// Purpose:     Write Analog outputs every 100 ms
// *************************************************************************

void fxWriteAnalogOutputs (void){

    switch(state){

         case RUNNING:
             fxSpeedUpdate(outputThrottle_pct);
                 break;

         default :
             fxSpeedUpdate(0);
                 break;
      }



 }

