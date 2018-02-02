/** @file notification.c 
*   @brief User Notification Definition File
*   @date 08-Feb-2017
*   @version 04.06.01
*
*   This file  defines  empty  notification  routines to avoid
*   linker errors, Driver expects user to define the notification. 
*   The user needs to either remove this file and use their custom 
*   notification function or place their code sequence in this file 
*   between the provided USER CODE BEGIN and USER CODE END.
*
*/



/* Include Files */

#include "esm.h"
#include "sys_selftest.h"
#include "adc.h"
#include "can.h"
#include "gio.h"
#include "sci.h"
#include "het.h"
#include "rti.h"
#include "i2c.h"
#include "sys_dma.h"

/* USER CODE BEGIN (0) */


/*  User Included Files  */

#include "A_exception_handler.h"
#include "inputOutput.h"
#include "A_LCD.h"
#include "utilities.h"
#include <stdio.h>
#include "mainStateMachine.h"

// local variables
static uint32 lcd_cnt = 0;


/*  Function Signature Declaration     */

static void loop_delay_internal(uint32 val);


#pragma WEAK(rtiNotification)
void rtiNotification(uint32 notification)
{

    switch(notification){

        case 0x1:       //Executing every 101 ms



            fxReadAnalogInputs();
            fxAlarmCheck();

            fxStateMachine();
            fxWriteDigitalOutputs();
            fxWriteAnalogOutputs();


            if( (((++lcd_cnt) % 5) == 0) ){

                LcdUpdate_1();
               printf("VT: %f \r\n",batteryVoltage_V);
                //printf("EN: %d \r\n", enableSwitch);
                //printf("RUN: %d \r\n", runSwitch);
                printf("State: %d \r\n", state);
                //printf("SEV2: %d \r\n", SEV2);
                //printf("PreCharge: %d \r\n", isPreChargeContactorClosed);
                //printf("K1: %d \r\n", isPositiveLegContactorClosed);
                //printf("K2: %d \r\n", isNegativeLegContactorClosed);
                //printf("InputThrottle(V): %f \r\n", inputThrottle_V);
                //printf("OutputThrottle: %f \r\n", outputThrottle_pct);

                //printf("CT_LOW: %f \r\n", batteryDischargeCurrentLow_A);
                //printf("CT_HIGH: %f \r\n",batteryDischargeCurrentHigh_A);
                //printf("CT: %f \r\n", batteryDischargeCurrent_A);
            }




            break;

        case 0x2:       //  Reserved
            break;

        case 0x4:           //Only for PC debugging
            //fxSendDataToPC();

            break;


    case 0x8:           //Executing every 100 ms
        ++timer;
            break;

    default :
            break;
    }

}


#pragma WEAK(gioNotification)
void gioNotification(gioPORT_t *port, uint32 bit)
{

    loop_delay_internal(50);

    if (port == gioPORTA && bit == 0){
        enableSwitch = !gioGetBit(gioPORTA, 0);
    } else if (port == gioPORTA && bit ==1){
        runSwitch = !gioGetBit(gioPORTA, 1);
    }

}




static void loop_delay_internal(uint32 val){
    for(val += 10 ;val > 10; --val);
}







#pragma WEAK(esmGroup1Notification)
void esmGroup1Notification(uint32 channel)
{
}

#pragma WEAK(esmGroup2Notification)
void esmGroup2Notification(uint32 channel)
{
}

#pragma WEAK(memoryPort0TestFailNotification)
void memoryPort0TestFailNotification(uint32 groupSelect, uint32 dataSelect, uint32 address, uint32 data)
{
}

#pragma WEAK(memoryPort1TestFailNotification)
void memoryPort1TestFailNotification(uint32 groupSelect, uint32 dataSelect, uint32 address, uint32 data)
{
}

#pragma WEAK(adcNotification)
void adcNotification(adcBASE_t *adc, uint32 group)
{
}

#pragma WEAK(canErrorNotification)
void canErrorNotification(canBASE_t *node, uint32 notification)
{
}

#pragma WEAK(canStatusChangeNotification)
void canStatusChangeNotification(canBASE_t *node, uint32 notification)
{
}

#pragma WEAK(canMessageNotification)
void canMessageNotification(canBASE_t *node, uint32 messageBox)
{
}
