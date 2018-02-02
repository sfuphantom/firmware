/*
 * mainStateMachine.h
 *
 *  Created on: Dec 14, 2017
 *      Author: sormoh
 */

#ifndef INCLUDE_MAINSTATEMACHINE_H_
#define INCLUDE_MAINSTATEMACHINE_H_

// state Enumerations
typedef enum _STATE {LOCKED, UNLOCKED, STANDBY, PRECHARGE, HIGH_VOLTAGE, RUNNING, SHUTDOWN } State;


// Global Variables
extern State state;



// Functions
void fxStateMachine (void);

#endif /* INCLUDE_MAINSTATEMACHINE_H_ */
