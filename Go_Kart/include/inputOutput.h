/*
 * inputOutput.h
 *
 *  Created on: Dec 14, 2017
 *      Author: sormoh
 */

#ifndef SOURCE_INPUTOUTPUT_H_
#define SOURCE_INPUTOUTPUT_H_

#include "can.h"
#include "gio.h"
#include "adc.h"
#include "inputOutput.h"
#include <stdio.h>
#include "sys_common.h"


#define ADC_DATA_CONVERT_NUM 5      //The total number of ADC pin used


// Declaration of global variables
extern adcData_t adc_data[ADC_DATA_CONVERT_NUM];    //ADC converted result stores here
extern uint8 enableSwitch;
extern uint8 runSwitch;
extern float64 inputThrottle_V;
extern float64 outputThrottle_pct;
extern float64 batteryVoltage_V;
extern float64 batteryDischargeCurrent_A;
extern float64 batteryDischargeCurrentLow_A;
extern float64 batteryDischargeCurrentHigh_A;
extern uint8 isPreChargeContactorClosed;
extern uint8 isPositiveLegContactorClosed;
extern uint8 isNegativeLegContactorClosed;
extern adcData_t adc_data[ADC_DATA_CONVERT_NUM];

//Functions
void fxReadAnalogInputs(void);
void fxReadDigitalInputs(void);
void fxWriteDigitalOutputs(void);
void fxWriteAnalogOutputs(void);
void fxPreChargeContactor(uint8 val);
void fxPositiveLegContactor(uint8 val);
void fxNegativeLegContactor(uint8 val);



#endif /* SOURCE_INPUTOUTPUT_H_ */
