/*
 * stateMachine.c
 *
 *  Created on: Jun 29, 2018
 *      Author: sormoh
 */

#include <stdio.h>
#include "inputOutput.h"
#include "stateMachine.h"

  // Initialization
State state = UNLOCKED;
//data VCUData;

static uint8_t prechargeState3SecondsTimer = 0;
static uint8_t HVState1SecondTimer = 0;

// *************************************************************************
// Function:    fxStateMachine
// Purpose:     Main State Machine
// *************************************************************************

void fxStateMachine (data* VCUDataPtr){

   if (state == UNLOCKED) {
        VCUDataPtr->VCU_ANInternal.state = (uint8)state;
        fxCheckAlarms(VCUDataPtr);
        if (VCUDataPtr->VCU_DIN.enableSignal && !(VCUDataPtr->VCU_DIGInternal.SEV2)){
            state = STANDBY;
        }

    } else if (state == STANDBY) {
        VCUDataPtr->VCU_ANInternal.state = (uint8)state;
        fxCheckAlarms(VCUDataPtr);
        if (VCUDataPtr->VCU_DIN.enableSignal && VCUDataPtr->VCU_DIN.runSignal && !(VCUDataPtr->VCU_DIGInternal.SEV2)){
            state = PRECHARGE;
        }

    } else if (state == PRECHARGE) {
        VCUDataPtr->VCU_ANInternal.state = (uint8)state;
        fxCheckAlarms(VCUDataPtr);
        prechargeState3SecondsTimer++; //Each Increment is 100ms. So 30 increments is ~3sec
        if (VCUDataPtr->VCU_DIGInternal.SEV2 || !(VCUDataPtr->VCU_DIN.enableSignal) || !(VCUDataPtr->VCU_DIN.runSignal)){
            state = SHUTDOWN;
        }
        if (VCUDataPtr->VCU_DOUT.prechargeContactor && VCUDataPtr->VCU_DOUT.negativeLegContactor && (prechargeState3SecondsTimer == 30)) {
            state = HIGH_VOLTAGE;
            prechargeState3SecondsTimer = 0;
        }

    } else if (state == HIGH_VOLTAGE) {
        VCUDataPtr->VCU_ANInternal.state = (uint8)state;
        fxCheckAlarms(VCUDataPtr);
        HVState1SecondTimer++; //Each Increment is 100ms. So 10 increments is ~1sec
        if (VCUDataPtr->VCU_DIGInternal.SEV2 || !(VCUDataPtr->VCU_DIN.enableSignal) || !(VCUDataPtr->VCU_DIN.runSignal)){
            state = SHUTDOWN;
        }

        if (VCUDataPtr->VCU_DOUT.positiveLegContactor && VCUDataPtr->VCU_DOUT.negativeLegContactor && (HVState1SecondTimer == 10)) {
            state = RUNNING;
            HVState1SecondTimer = 0;
        }

    } else if (state == RUNNING) {
        VCUDataPtr->VCU_ANInternal.state = (uint8)state;
        fxCheckAlarms(VCUDataPtr);
        if (VCUDataPtr->VCU_DIGInternal.SEV2 || !(VCUDataPtr->VCU_DIN.enableSignal) || !(VCUDataPtr->VCU_DIN.runSignal)){
            state = SHUTDOWN;
        }

    } else if (state == SHUTDOWN) {
        VCUDataPtr->VCU_ANInternal.state = (uint8)state;
        fxCheckAlarms(VCUDataPtr);
        if ( (VCUDataPtr->VCU_DIN.enableSignal && VCUDataPtr->VCU_DIN.runSignal && !(VCUDataPtr->VCU_DIGInternal.SEV2)) || ( VCUDataPtr->VCU_ANInternal.batteryDischargeCurrent_A <= 3 ) ){
            state = STANDBY;

        }
    }


}


// *************************************************************************
// Function:    fxCheckAlarms
// Purpose:     Check Alarms
// *************************************************************************

void fxCheckAlarms (data *VCUDataPtr){

    uint8 BatteryVoltageException = (VCUDataPtr->VCU_AIN.batteryVoltage_V.sensorOutput > 65.0) ? 2 : (VCUDataPtr->VCU_AIN.batteryVoltage_V.sensorOutput < 40.0) ? 1 : 0;
    uint8 BatteryVoltageWarning =  (VCUDataPtr->VCU_AIN.batteryVoltage_V.sensorOutput >= 50.0) ? 2 :  (VCUDataPtr->VCU_AIN.batteryVoltage_V.sensorOutput <= 44.0) ? 1 : 0;
    uint8 BatteryCurrentException = (VCUDataPtr->VCU_ANInternal.batteryDischargeCurrent_A > 40.0) ? 2 : (VCUDataPtr->VCU_ANInternal.batteryDischargeCurrent_A < -3.0) ? 1 : 0;
    uint8 BatteryCurrentWarning =  (VCUDataPtr->VCU_ANInternal.batteryDischargeCurrent_A >= 30.0) ? 2 : 0;

    if ( (BatteryVoltageException == 0) && (BatteryCurrentException == 0 ) ){
        VCUDataPtr->VCU_DIGInternal.SEV2 = 0;
        VCUDataPtr->VCU_DIGInternal.HighBatteryCurrentSev2 = 0;
        VCUDataPtr->VCU_DIGInternal.LowBatteryCurrentSev2 = 0;
        VCUDataPtr->VCU_DIGInternal.HighBatteryVoltageSev2 = 0;
        VCUDataPtr->VCU_DIGInternal.LowBatteryCurrentSev2 = 0;
    } else {
        if (BatteryVoltageException == 2){
            VCUDataPtr->VCU_DIGInternal.SEV2 = 1;
            VCUDataPtr->VCU_DIGInternal.HighBatteryVoltageSev2 = 1;
        } else if (BatteryVoltageException == 1){
            VCUDataPtr->VCU_DIGInternal.SEV2 = 1;
            VCUDataPtr->VCU_DIGInternal.LowBatteryVoltageSev2 = 1;
        } else if (BatteryCurrentException == 2){
            VCUDataPtr->VCU_DIGInternal.SEV2 = 1;
            VCUDataPtr->VCU_DIGInternal.HighBatteryCurrentSev2 = 1;
        } else if (BatteryCurrentException == 1){
            VCUDataPtr->VCU_DIGInternal.SEV2 = 1;
            VCUDataPtr->VCU_DIGInternal.LowBatteryCurrentSev2 = 1;
        }
    }


    if ( BatteryVoltageWarning == 0 && BatteryCurrentWarning == 0 ){
        VCUDataPtr->VCU_DIGInternal.SEV1 = 0;
        VCUDataPtr->VCU_DIGInternal.HighBatteryCurrentSev1 = 0;
        VCUDataPtr->VCU_DIGInternal.LowBatteryCurrentSev1 = 0;
        VCUDataPtr->VCU_DIGInternal.HighBatteryVoltageSev1 = 0;
        VCUDataPtr->VCU_DIGInternal.LowBatteryCurrentSev1 = 0;
    } else {
        if (BatteryVoltageWarning == 2){
            VCUDataPtr->VCU_DIGInternal.SEV1 = 1;
            VCUDataPtr->VCU_DIGInternal.HighBatteryVoltageSev1 = 1;
        } else if (BatteryVoltageWarning == 1){
            VCUDataPtr->VCU_DIGInternal.SEV2 = 1;
            VCUDataPtr->VCU_DIGInternal.LowBatteryVoltageSev1 = 1;
        } else if (BatteryCurrentWarning == 2){
            VCUDataPtr->VCU_DIGInternal.SEV2 = 1;
            VCUDataPtr->VCU_DIGInternal.HighBatteryCurrentSev1 = 1;
        } else if (BatteryCurrentWarning == 1){
            VCUDataPtr->VCU_DIGInternal.SEV2 = 1;
            VCUDataPtr->VCU_DIGInternal.LowBatteryCurrentSev1 = 1;
        }

    }
}
