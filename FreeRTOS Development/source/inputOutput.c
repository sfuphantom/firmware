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
#include "inputOutput.h"
#include <stdio.h>

#define ADC_DATA_CONVERT_NUM 1
#define ADC_MAX_DELAY_ITERATIONS    60


// Initialization
adcData_t adc_data[ADC_DATA_CONVERT_NUM] = {0};
uint8 adc_max_delay_iterations;

struct analogInput inputThrottle;

void initLinAnalogInputs(){

    struct analogInput *ptrAnalogInput;

    ptrAnalogInput = &inputThrottle;
    setScaling(ptrAnalogInput, 0, 5, 0, 5);

}


void setScaling(struct analogInput* sensorPtr, float rawLL, float rawHL, float euLL, float euHL){

    sensorPtr->rawLL = rawLL;
    sensorPtr->rawHL = rawHL;
    sensorPtr->euLL = euLL;
    sensorPtr->euHL = euHL;
}

void computeAnalogInput(struct analogInput* sensorPtr){

    sensorPtr->sensorOutput = ( sensorPtr->raw - sensorPtr->rawLL ) / ( sensorPtr->rawHL - sensorPtr->rawLL ) * ( sensorPtr->euHL - sensorPtr->euLL ) + sensorPtr->euLL;
}


// *************************************************************************
// Function:    fxReadAnalogInputs
// Purpose:     Reads analog inputs every 100 ms
// *************************************************************************

void fxReadAnalogInputs(void){

    struct analogInput *ptrAnalogInput;

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
    ptrAnalogInput = &inputThrottle;
    ptrAnalogInput->raw = ((5.0*adc_data[0].value) / 4096.0);
    computeAnalogInput(ptrAnalogInput);

}

