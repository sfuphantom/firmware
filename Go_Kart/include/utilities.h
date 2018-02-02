/*
 * utilities.h
 *
 *  Created on: Dec 14, 2017
 *      Author: sormoh
 */

#ifndef INCLUDE_UTILITIES_H_
#define INCLUDE_UTILITIES_H_

#include "can.h"
#include "gio.h"
#include "adc.h"
#include <stdio.h>
#include "A_exception_handler.h"
#include "sys_common.h"


// Global variables
extern uint64 timer;                                //Local timer, keep track of time
extern uint8 lcd_en;
extern int16_t speed;                                //Speed of throttle generated


// Functions
void fxSendDataToPC (void);
void fxAlarmCheck (void);
void fxSpeedUpdate(int16_t val);
void fxTimerDelay(float val);
void fxLoopDelay(uint64 val);
uint8 LcdUpdate_1();
uint8 LcdUpdate_2(char *s1, char *s2);
float64 ramp(float64 rampSP, uint64 inclineTimeSec);

#endif /* INCLUDE_UTILITIES_H_ */
