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

#define ADC_DATA_CONVERT_NUM 1
#define ADC_MAX_DELAY_ITERATIONS    60


// Initialization
adcData_t adc_data[ADC_DATA_CONVERT_NUM] = {0};
uint8 adc_max_delay_iterations;

AIN VCU_AIN;
AOUT VCU_AOUT;
DIN VCU_DIN;
DOUT VCU_DOUT;
//data VCUData;

AINLinInit inputThrottleInit;

void fxInitInputs(data* VCUDataPtr){
    // Initialization of Analog Inputs
    VCUDataPtr->VCU_AIN.batteryCurrent_A = 0.0;
    VCUDataPtr->VCU_AIN.batteryVoltage_V = 0.0;
    VCUDataPtr->VCU_AIN.throttleInput_V = 0.0;

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
    VCUDataPtr->VCU_DIGInternal.SEV2 = 0;
    VCUDataPtr->VCU_DIGInternal.SEV3 = 0;

    // Initialization of Analog Internals
    VCUDataPtr->VCU_ANInternal.state = 0;
}

void fxInitLinAnalogInputs(){

    AINLinInit *ptrAnalogInput;

    //Throttle Input Init
    ptrAnalogInput = &inputThrottleInit;
    fxSetScaling(ptrAnalogInput, 0, 5, 0, 5);

    // Voltage Transducer Init

    // Current Transucer Init

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

    // Input throttle voltage 0 - 2.1V
    ptrAnalogInput = &inputThrottleInit;
    ptrAnalogInput->raw = ((5.0*adc_data[0].value) / 4096.0);
    fxComputeAnalogInput(ptrAnalogInput);
    VCU_AIN.throttleInput_V =  ptrAnalogInput->sensorOutput;



    VCUDataPtr->VCU_AIN = VCU_AIN;

}


void fxReadDigitalInputs(data* VCUDataPtr){

    VCUDataPtr->VCU_DIN.enableSignal = gioGetBit(gioPORTA, 0);
    VCUDataPtr->VCU_DIN.runSignal = gioGetBit(gioPORTA, 1);

}

