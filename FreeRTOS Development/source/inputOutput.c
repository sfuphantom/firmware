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
#include "sci.h"
#include "sys_dma.h"
#include "gio.h"
#include "inputOutput.h"
#include <stdio.h>

#define ADC_DATA_CONVERT_NUM 4
#define ADC_MAX_DELAY_ITERATIONS    60


// Initialization
adcData_t adc_data[ADC_DATA_CONVERT_NUM] = {0};
uint8 adc_max_delay_iterations;

AIN VCU_AIN;
AOUT VCU_AOUT;
DIN VCU_DIN;
DOUT VCU_DOUT;
//data VCUData;


void fxInitInputs(data* VCUDataPtr){
    // Initialization of Analog Inputs
    VCUDataPtr->VCU_AIN.batteryCurrentLow_A.raw = 0.0;
    VCUDataPtr->VCU_AIN.batteryCurrentHigh_A.raw = 0.0;
    VCUDataPtr->VCU_AIN.batteryVoltage_V.raw = 0.0;
    VCUDataPtr->VCU_AIN.throttleInput_V.raw = 0.0;
    VCUDataPtr->VCU_AIN.batteryCurrentLow_A.sensorOutput = 0.0;
    VCUDataPtr->VCU_AIN.batteryCurrentHigh_A.sensorOutput = 0.0;
    VCUDataPtr->VCU_AIN.batteryVoltage_V.sensorOutput = 0.0;
    VCUDataPtr->VCU_AIN.throttleInput_V.sensorOutput = 0.0;

    // Initialization of Analog Outputs
    VCUDataPtr->VCU_AOUT.throttleOutput_V = 0.0;

    // Initialization of Digital Inputs
    VCUDataPtr->VCU_DIN.enableSignal = 0;
    VCUDataPtr->VCU_DIN.runSignal = 0;

    // Initialization of Digital Outputs
    VCUDataPtr->VCU_DOUT.motorControllerEnable = 0;
    VCUDataPtr->VCU_DOUT.prechargeContactor = 0;
    VCUDataPtr->VCU_DOUT.negativeLegContactor = 0;
    VCUDataPtr->VCU_DOUT.positiveLegContactor = 0;

    // Initialization of Digital Internals
    VCUDataPtr->VCU_DIGInternal.SEV1 = 0;
    VCUDataPtr->VCU_DIGInternal.SEV2 = 0;
    VCUDataPtr->VCU_DIGInternal.HighBatteryVoltageSev1 = 0;
    VCUDataPtr->VCU_DIGInternal.LowBatteryVoltageSev1 = 0;
    VCUDataPtr->VCU_DIGInternal.HighBatteryCurrentSev1 = 0;
    VCUDataPtr->VCU_DIGInternal.LowBatteryCurrentSev1 = 0;
    VCUDataPtr->VCU_DIGInternal.HighBatteryVoltageSev2 = 0;
    VCUDataPtr->VCU_DIGInternal.LowBatteryVoltageSev2 = 0;
    VCUDataPtr->VCU_DIGInternal.HighBatteryCurrentSev2 = 0;
    VCUDataPtr->VCU_DIGInternal.LowBatteryCurrentSev2 = 0;
    // Initialization of Analog Internals
    VCUDataPtr->VCU_ANInternal.state = 0;
    VCUDataPtr->VCU_ANInternal.batteryDischargeCurrent_A = 0;
}

void fxInitLinAnalogInputs(data* VCUDataPtr){

    //Throttle Input Init
    fxSetScaling( &(VCUDataPtr->VCU_AIN.throttleInput_V), 0, 5, 0, 5);

    // Voltage Transducer Init
    fxSetScaling( &(VCUDataPtr->VCU_AIN.batteryVoltage_V), 0, 5, 0, 1000);

    // Current Transucer Low Init
    fxSetScaling( &(VCUDataPtr->VCU_AIN.batteryCurrentLow_A), 0, 5, 0, 5);

    // Current Transucer High Init
    fxSetScaling( &(VCUDataPtr->VCU_AIN.batteryCurrentHigh_A), 0, 5, 0, 5);
}


void fxSetScaling(AINLinInit* sensorPtr, float rawLL, float rawHL, float euLL, float euHL){

    sensorPtr->rawLL = rawLL;
    sensorPtr->rawHL = rawHL;
    sensorPtr->euLL = euLL;
    sensorPtr->euHL = euHL;
}

void fxComputeAnalogInput(AINLinInit* sensorPtr){

    sensorPtr->sensorOutput = ( sensorPtr->raw - sensorPtr->rawLL ) / ( sensorPtr->rawHL - sensorPtr->rawLL ) * ( sensorPtr->euHL - sensorPtr->euLL ) + sensorPtr->euLL;
}


// *************************************************************************
// Function:    fxReadAnalogInputs
// Purpose:     Reads analog inputs every 100 ms
// *************************************************************************

void fxReadAnalogInputs(data* VCUDataPtr){

    AINLinInit *ptrAnalogInput;

    adcStartConversion(adcREG1, adcGROUP1);

    adc_max_delay_iterations = (uint8)ADC_MAX_DELAY_ITERATIONS;

    while(   adcIsConversionComplete(adcREG1,adcGROUP1) == 0 ){

        if( !(--adc_max_delay_iterations) ){
         //   setError(ERR_ADC_RETRIEVE_DATA_OUT_OF_TIME);
            sciSend(scilinREG,25,(unsigned char*)"ADC Conversion Failed\r\n");
            return;
        }
    }

    if( adcGetData(adcREG1, 1U, adc_data) != ADC_DATA_CONVERT_NUM){
       // setError(ERR_ADC_PIN_LOST_CONNECTION);
        sciSend(scilinREG,23,(unsigned char*)"ADC Get Data Failed\r\n");
        return;
    }

    // Input throttle voltage
    ptrAnalogInput = &(VCUDataPtr->VCU_AIN.throttleInput_V);
    VCUDataPtr->VCU_AIN.throttleInput_V.raw = ((5.0*adc_data[0].value) / 4096.0);
    fxComputeAnalogInput(ptrAnalogInput);

    // Battery voltage 0 - 5V <-> 0 - 1000V
    ptrAnalogInput = &(VCUDataPtr->VCU_AIN.batteryVoltage_V);
    ptrAnalogInput->raw = ((5.0*adc_data[1].value) / 4096.0);
    fxComputeAnalogInput(ptrAnalogInput);


    // Battery voltage 0 - 5V <-> 0 - 5V
    ptrAnalogInput = &(VCUDataPtr->VCU_AIN.batteryCurrentLow_A);
    ptrAnalogInput->raw = ((5.0*adc_data[2].value) / 4096.0);
    fxComputeAnalogInput(ptrAnalogInput);


    // Battery voltage 0 - 5V <-> 0 - 5V
    ptrAnalogInput = &(VCUDataPtr->VCU_AIN.batteryCurrentHigh_A);
    ptrAnalogInput->raw = ((5.0*adc_data[3].value) / 4096.0);
    fxComputeAnalogInput(ptrAnalogInput);


    /*
       Calculate current:
                                   current high limit   supply voltage nominal
               current = offsetV * ------------------ * ----------------------*(1/G)
                                   offset voltage HL       supply voltage

    */


       float offsetVoltageLow = VCUDataPtr->VCU_AIN.batteryCurrentLow_A.sensorOutput - 2.5;
       float offsetVoltageHigh = VCUDataPtr->VCU_AIN.batteryCurrentHigh_A.sensorOutput - 2.5;

       float batteryDischargeCurrentLow_A =  offsetVoltageLow*(1/0.0667);
       float batteryDischargeCurrentHigh_A =  offsetVoltageHigh*(1/0.0057);


       // Calculate high range weighting factor
       float highRangeWeightingFactor = (0-1)/(30-40)*(batteryDischargeCurrentHigh_A-30)+ 0;

       if (highRangeWeightingFactor < 0)
           highRangeWeightingFactor = 0;
       else if (highRangeWeightingFactor > 1)
           highRangeWeightingFactor = 1;

       // Calculate raw stack voltage using a combination of the high and low range inputs
       VCUDataPtr->VCU_ANInternal.batteryDischargeCurrent_A = (highRangeWeightingFactor * (batteryDischargeCurrentHigh_A - batteryDischargeCurrentLow_A)) + batteryDischargeCurrentLow_A;



}

// *************************************************************************
// Function:    fxReadDigitalInputs
// Purpose:     Reads analog inputs every 100 ms
// *************************************************************************

void fxReadDigitalInputs(data* VCUDataPtr){

    VCUDataPtr->VCU_DIN.enableSignal = gioGetBit(gioPORTA, 0);
    VCUDataPtr->VCU_DIN.runSignal = gioGetBit(gioPORTA, 1);

}

