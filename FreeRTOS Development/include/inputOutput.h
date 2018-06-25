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

struct analogInput
{
    float raw;
    float rawLL;
    float rawHL;
    float euLL;
    float euHL;
    float sensorOutput;
};

extern struct analogInput inputThrottle;

//Functions
void initLinAnalogInputs(void);
void setScaling(struct analogInput* sensorPtr, float rawLL, float rawHL, float euLL, float euHL);
void computeAnalogInput(struct analogInput* sensorPtr);
void fxReadAnalogInputs(void);


#endif /* SOURCE_INPUTOUTPUT_H_ */
