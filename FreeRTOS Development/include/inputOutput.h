/*
 * inputOutput.h
 *
 *  Created on: Dec 14, 2017
 *      Author: sormoh
 */

#ifndef SOURCE_INPUTOUTPUT_H_
#define SOURCE_INPUTOUTPUT_H_

#include "adc.h"
#include <stdio.h>
#include "sys_common.h"


#define ADC_DATA_CONVERT_NUM 1      //The total number of ADC pin used


// Declaration of global variables
extern adcData_t adc_data[ADC_DATA_CONVERT_NUM];    //ADC converted result stores here

typedef struct analogInputs {
    float throttleInput_V;
    float batteryVoltage_V;
    float batteryCurrent_A;
} AIN;
AIN VCU_AIN;

typedef struct digitalInputs {
    uint8 enableSignal;
    uint8 runSignal;
} DIN;
DIN VCU_DIN;

typedef struct analogOutputs {
    float throttleOutput_V;
} AOUT;
AOUT VCU_AOUT;

typedef struct digitalOutputs {
    uint8 motorControllerEnable;
    uint8 prechargeContactor;
    uint8 positiveLegContactor;
    uint8 negativeLegContactor;
} DOUT;
DOUT VCU_DOUT;

typedef struct internalDigtal {
    uint8 SEV2;
    uint8 SEV3;
} DIGInternal;
DIGInternal VCU_DIGInternal;

typedef struct internalAnalog {
    uint8 state;
} ANInternal;
ANInternal VCU_ANInternal;


typedef struct data {
    AIN VCU_AIN;
    DIN VCU_DIN;
    AOUT VCU_AOUT;
    DOUT VCU_DOUT;
    DIGInternal VCU_DIGInternal;
    ANInternal VCU_ANInternal;
} data;
extern data VCUData;


typedef struct linAnalogInputInit
{
    float raw;
    float rawLL;
    float rawHL;
    float euLL;
    float euHL;
    float sensorOutput;
} AINLinInit;

AINLinInit inputThrottle;

//Functions
void fxInitInputs(data* VCUDataPtr);
void fxInitLinAnalogInputs(void);
void fxSetScaling(AINLinInit* sensorPtr, float rawLL, float rawHL, float euLL, float euHL);
void fxComputeAnalogInput(AINLinInit* sensorPtr);
void fxReadAnalogInputs(data* VCUDataPtr);
void fxReadDigitalInputs(data* VCUDataPtr);

#endif /* SOURCE_INPUTOUTPUT_H_ */
