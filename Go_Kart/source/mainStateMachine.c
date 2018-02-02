/*
 * mainStateMachine.c
 *
 *  Created on: Dec 14, 2017
 *      Author: sormoh
 */
#include "mainStateMachine.h"
#include "alarmLogic.h"
#include "utilities.h"
#include "inputOutput.h"

// Initialization
State state = UNLOCKED;

// *************************************************************************
// Function:    fxStateMachine
// Purpose:     Main State Machine
// *************************************************************************

void fxStateMachine (void){

   if (state == UNLOCKED) {
      // lcdUpdate_2("UNLOCK", "");
        if (enableSwitch && !SEV2 ){
            state = STANDBY;
        }
    }
    else if (state == STANDBY) {
       // lcdUpdate_2("STANDBY", "");
        if (enableSwitch && runSwitch && !SEV2 ){
            state = PRECHARGE;
        }
    }

    else if (state == PRECHARGE) {
      //  lcdUpdate_2("PRECHARGE", "");

        if (SEV2 || !enableSwitch || !runSwitch){
            state = SHUTDOWN;
        }

        if (isPreChargeContactorClosed && isNegativeLegContactorClosed /* && 3 seconds timer */ ) {
            fxTimerDelay(2);
            state = HIGH_VOLTAGE;
        }
    }

    else if (state == HIGH_VOLTAGE) {
      //  lcdUpdate_2("HIGH_VOLTAGE", "");
        if (SEV2 || !enableSwitch || !runSwitch){
            state = SHUTDOWN;
        }

        if (isPositiveLegContactorClosed && isNegativeLegContactorClosed /* && 1 second timer */) {
            state = RUNNING;
        }
    }

    else if (state == RUNNING) {
     //   lcdUpdate_2("RUNNING ", "");
        if (SEV2 || !enableSwitch || !runSwitch){
            state = SHUTDOWN;
        }

    }

    else if (state == SHUTDOWN) {
       // lcdUpdate_2("SHUTDOWN", "");
        if ( (enableSwitch && runSwitch && !SEV2) || ( batteryDischargeCurrent_A <= 3 ) ){
            state = STANDBY;
            runSwitch = 0;
        }
    }







}
