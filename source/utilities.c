/*
 * utilities.c
 *
 *  Created on: Dec 14, 2017
 *      Author: sormoh
 */


/* Include Files */

#include "esm.h"
#include "sys_selftest.h"
#include "adc.h"
#include "gio.h"
#include "sci.h"
#include "rti.h"
#include "i2c.h"
#include "sys_dma.h"

/*  User Included Files  */

#include "A_exception_handler.h"
#include "mainStateMachine.h"
#include "alarmLogic.h"
#include "inputOutput.h"
#include "A_LCD.h"
#include <stdio.h>
#include "utilities.h"

#define TIME_SHIFT 10               //The shift value for variable "timer", it needs to shift for some reason


// Initialization
uint8 lcd_en= 0;
uint8 lcd_locker = 0;
uint64 timer = TIME_SHIFT;
int16_t speed = 0;






// *************************************************************************
// Function:    sendDataToPC
// Purpose:     Send data to PC by SCI2
// *************************************************************************
void fxSendDataToPC (void){



       uint8 buffer[2];
       buffer[0] = (speed & 0xFF00) >> 8U;
       buffer[1] = speed & 0xFF;

       sciSend(scilinREG, 2, buffer);


       sciSend(scilinREG, 45, buffer);
}



// *************************************************************************
// Function:    fxLcdUpdate_1
// Purpose:     Updates LCD_1
// *************************************************************************
uint8 LcdUpdate_1(){

    char s[50];

    setDevice(1);

    if( clearScreen() != 0){
        lcd_locker = 0;
        return 1;
    }

    if ( returnHome() != 0){
        lcd_locker = 0;
        return 1;
    }

    sprintf( s, "CT: %.2lf  VT:%.2lf", batteryDischargeCurrent_A,batteryVoltage_V);

    if(writeString(s, strlen(s)) != 0){
        lcd_locker = 0;
        return 1;
    }

    if( setPos(2, 0) != 0){
        lcd_locker = 0;
        return 1;
    }

    sprintf(s, "Throttle: %0.2lf", outputThrottle_pct);


    if(writeString(s, strlen(s)) != 0){
        lcd_locker = 0;
        return 1;
    }

    return 0;
}

// *************************************************************************
// Function:    fxLcdUpdate_2
// Purpose:     Updates LCD_2
// *************************************************************************
uint8 lcdUpdate_2(char *s1, char *s2){

    lcd_en = 0;
    uint32 max_loop = 800000;

    while(i2cIsBusBusy(i2cREG1) == true){
        if( -- max_loop == 10){

            return 1;
        }
    }

    setDevice(2);

    if( clearScreen() != 0){

        return 1;
    }

    if ( returnHome() != 0){

        return 1;
    }

    if(writeString(s1, strlen(s1)) != 0) {

        return 1;
    }

    if(strlen(s2) != 0){
        if( setPos(2, 0) != 0){

            return 1;
        }

        if(writeString(s2, strlen(s2)) != 0){

            return 1;
        }
    }


    lcd_en = 1;

    return 0;
}

// *************************************************************************
// Function:    fxSpeedUpdate
// Purpose:     Updates the speed
// *************************************************************************
void fxSpeedUpdate(int16_t throttleDutyCycle){

    pwmSetDuty(hetRAM1, 0,  throttleDutyCycle );

}


// *************************************************************************
// Function:    fxTimerDelay
// Purpose:     Delay timer
// *************************************************************************
void fxTimerDelay(float val){
    fxLoopDelay( (uint64)(10000000 * val) );
}

// *************************************************************************
// Function:    fxLoopDelay
// Purpose:     Delay timer
// *************************************************************************
void fxLoopDelay(uint64 val){
    for(;val > 0; --val);
}


float64 ramp(float64 rampSP, uint64 inclineTimeSec){
    float64 prevSP = rampSP;
    return ((rampSP - prevSP)/inclineTimeSec)*(timer/10);
}
