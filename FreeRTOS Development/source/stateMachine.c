/*
 * stateMachine.c
 *
 *  Created on: Jun 29, 2018
 *      Author: sormoh
 */


#include "inputOutput.h"
#include "stateMachine.h"

  // Initialization
State state = UNLOCKED;
//data VCUData;

// *************************************************************************
// Function:    fxStateMachine
// Purpose:     Main State Machine
// *************************************************************************

void fxStateMachine (data* VCUDataPtr){

   if (state == UNLOCKED) {
        if (VCUDataPtr->VCU_DIN.enableSignal && !(VCUDataPtr->VCU_DIGInternal.SEV2)){
            state = STANDBY;
        }
    }
    else if (state == STANDBY) {
        if (VCUDataPtr->VCU_DIN.enableSignal && VCUDataPtr->VCU_DIN.runSignal && !(VCUDataPtr->VCU_DIGInternal.SEV2)){
            state = PRECHARGE;
        }
    }

    else if (state == PRECHARGE) {
        if (VCUDataPtr->VCU_DIGInternal.SEV2 || !(VCUDataPtr->VCU_DIN.enableSignal) || !(VCUDataPtr->VCU_DIN.runSignal)){
            state = SHUTDOWN;
        }

        if (VCUDataPtr->VCU_DOUT.prechargeContactor && VCUDataPtr->VCU_DOUT.negativeLegContactor /* && 3 seconds timer */ ) {
          //  fxTimerDelay(2);
            state = HIGH_VOLTAGE;
        }
    }

    else if (state == HIGH_VOLTAGE) {
        if (VCUDataPtr->VCU_DIGInternal.SEV2 || !(VCUDataPtr->VCU_DIN.enableSignal) || !(VCUDataPtr->VCU_DIN.runSignal)){
            state = SHUTDOWN;
        }

        if (VCUDataPtr->VCU_DOUT.positiveLegContactor && VCUDataPtr->VCU_DOUT.negativeLegContactor /* && 1 second timer */) {
            state = RUNNING;
        }
    }

    else if (state == RUNNING) {
        if (VCUDataPtr->VCU_DIGInternal.SEV2 || !(VCUDataPtr->VCU_DIN.enableSignal) || !(VCUDataPtr->VCU_DIN.runSignal)){
            state = SHUTDOWN;
        }

    }

    else if (state == SHUTDOWN) {
        if ( (VCUDataPtr->VCU_DIN.enableSignal && VCUDataPtr->VCU_DIN.runSignal && !(VCUDataPtr->VCU_DIGInternal.SEV2)) || ( VCUDataPtr->VCU_AIN.batteryCurrent_A <= 3 ) ){
            state = STANDBY;
            VCUDataPtr->VCU_DIN.enableSignal = 0;
            VCUDataPtr->VCU_DIN.runSignal = 0;
        }
    }


   VCUDataPtr->VCU_ANInternal.state = (uint8)state;
}


