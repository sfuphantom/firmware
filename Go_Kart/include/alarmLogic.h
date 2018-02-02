/*
 * alarmLogic.h
 *
 *  Created on: Dec 14, 2017
 *      Author: sormoh
 */

#ifndef INCLUDE_ALARMLOGIC_H_
#define INCLUDE_ALARMLOGIC_H_

#include "can.h"
#include "gio.h"
#include "adc.h"
#include <stdio.h>
#include "A_exception_handler.h"
#include "sys_common.h"

// Declaration of global variables
extern uint8 SEV1;
extern uint8 SEV2;
extern uint8 warn_flag;

// Functions
void fxAlarmCheck ();
uint8 fxVt_exception();
uint8 fxCt_exception();
uint8 fxVt_warn();
uint8 fxCt_warn();

#endif /* INCLUDE_ALARMLOGIC_H_ */
