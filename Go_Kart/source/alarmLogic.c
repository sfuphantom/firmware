/*
 * alarmLogic.c
 *
 *  Created on: Dec 14, 2017
 *      Author: sormoh
 */
#include "mainStateMachine.h"
#include "utilities.h"
#include "inputOutput.h"
#include "alarmLogic.h"

// Initialization
uint8 warn_flag = 0;
uint8 SEV1 = 0;
uint8 SEV2 = 0;


// *************************************************************************
// Function:    fxAlarmCheck
// Purpose:     Checks the status of each alarm every 100 ms
// *************************************************************************
void fxAlarmCheck (void){
    int val;
    // Severity 2 conditions for battery voltage reading
    if ( val = fxVt_exception() ) {
        if( val == 2 ){
            setError(ERR_VT_HIGH);
        } else if(val == 1){
           setError(ERR_VT_LOW);
        }

        SEV2 = 1;

    } else {

        SEV2 = 0;
        setError(0);
    }

    // Severity 2 conditions for battery discharge current reading
    if( (val = fxCt_exception()) ){

        if(val == 2){
            setError(ERR_CT_HIGH);
        }else{
            setError(ERR_CT_LOW);
        }

        SEV2 = 1;
    } else {
        SEV2 = 0;
        setError(0);
    }


    // Severity 1 conditions for battery voltage reading

     if( (val = fxVt_warn()) && !SEV2){
         if(val == 2){

             setWarnning(WARN_VT_HIGH);
         }else{
             setWarnning(WARN_VT_LOW);
         }
         SEV1 = 1;

     } else {
         SEV1 = 0;
         setWarnning(0);
     }

     // Severity 1 conditions for battery discharge current reading
     if( (val =  fxCt_warn()) && !SEV2){
         if(val == 2){
             setWarnning(WARN_CT_HIGH);
         }else{
             setWarnning(WARN_CT_LOW);
         }
         SEV1 = 1;

     } else {
         SEV1 = 0;
         setWarnning(0);
     }

}


// *************************************************************************
// Function:    vt_exception
// Purpose:     Returns High/Low battery voltage SEV2 alarms
// *************************************************************************
uint8 fxVt_exception(){
    return (batteryVoltage_V > 65.0) ? 2 : (batteryVoltage_V < 40.0) ? 1 : 0;
}

// *************************************************************************
// Function:    ct_exception
// Purpose:     Returns High/Low Current discharge current SEV2 alarms
// *************************************************************************
uint8 fxCt_exception(){
    return (batteryDischargeCurrent_A > 40.0)? 2 :  (batteryDischargeCurrent_A < -3.0) ? 1 : 0;
}

// *************************************************************************
// Function:    vt_warn
// Purpose:     Returns High/Low battery voltage SEV1 warning
// *************************************************************************
uint8 fxVt_warn(){
    return (batteryVoltage_V <= 44.0) ? 1 : (batteryVoltage_V >= 50.0) ? 2 : 0;
}

// *************************************************************************
// Function:    ct_warn
// Purpose:     Returns High/Low battery discharge current SEV1 warning
// *************************************************************************
uint8 fxCt_warn(){
    return (batteryDischargeCurrent_A >= 30.0) ? 2 : 0;
}
