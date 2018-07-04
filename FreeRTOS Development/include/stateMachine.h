/*
 * stateMachine.h
 *
 *  Created on: Jun 29, 2018
 *      Author: sormoh
 */

#ifndef INCLUDE_STATEMACHINE_H_
#define INCLUDE_STATEMACHINE_H_

#include "inputOutput.h"

// state Enumerations
typedef enum _STATE {LOCKED, UNLOCKED, STANDBY, PRECHARGE, HIGH_VOLTAGE, RUNNING, SHUTDOWN } State;


// Global Variables
extern State state;

// Functions
void fxStateMachine (data* VCUDataPtr);
void fxCheckAlarms (data *VCUDataPtr);

#endif /* INCLUDE_STATEMACHINE_H_ */
