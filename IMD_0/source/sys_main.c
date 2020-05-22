/** @file sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
#include "het.h"
#include "gio.h"
#include "sys_vim.h"
#include "rti.h"
#include "sci.h"

#include "stdlib.h" // contains ltoa
#define SERIAL_SEND

/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
static const float FREQ_RUNNING_COUNTER = 10000000.00; // 10Mhz
static const uint32_t UINT32_MAX_ = 4294967295;

static uint32_t last_time1 = 0;
static uint32_t time1 = 0;
static uint32_t time2 = 0;
float period = 0.0;
float time_on = 0.0;
float frequency = 0.0;
float duty_cycle = 0.0;
float IMD_resistance = 1000000.0;

// DEFINE ENUM HERE FOR IMD MESSAGE MAPPING (it is called IMDState)
// message names are taken from IMD Datasheet
typedef enum{
    Short_Circuit,
    Normal_Condition,
    Undervoltage_Condition,
    Speed_Start_Measurement_Good, // related to start-up
    Speed_Start_Measurement_Bad, // related to start-up
    Device_Error,
    Connection_Fault_Earth,
    Bad_Info,
    Undefined_Fault
}IMDStateEnum;

typedef enum{
    Normal, // When Duty Cycle 5-10%
    Normal_75, // Usually when Duty Cycle 10-30%
    Normal_50, // Usually when Duty Cycle 30-60%
    Normal_25, // Usually when Duty Cycle 60-90%
    Isolation_Failure, //When Duty Cycle is 90-95%
    Unknown // Duty Cycle is outside of range (5-95%)
}IsolationStateEnum;

typedef struct{
    IMDStateEnum IMDState;
    IsolationStateEnum IsolationState;
}IMDData_t;

IMDData_t IMDData = {Normal_Condition};


// SCI variables
unsigned int NumberofCharsFreq, freq_value, NumberofCharsDuty, duty_value;
unsigned char freq_data[8];
unsigned char duty_data[8];
const float f_HCLK = 160.00;
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    // Initialization --
    hetInit();
    gioInit();
    rtiInit();
    sciInit();
    rtiResetCounter(rtiCOUNTER_BLOCK1);

    _enable_IRQ();

    edgeEnableNotification(hetREG1, edge0);
    gioEnableNotification(gioPORTA,5);
    rtiStartCounter(rtiCOUNTER_BLOCK1); // cant read register without this (RTI doesnt start?)
    IMDStateEnum currentState;
    IsolationStateEnum isolationState;

    while(1)
    {
        // adding this 0.5 and then typecasting to an int (truncating all decimals)
        // basically acts as rounding the float to the nearest integer
        freq_value = (unsigned int) (frequency + 0.5);
        duty_value = (unsigned int) (duty_cycle*100.0 + 0.5);

        /*
         * Message Mapping for IMD Operation State
         * Need to find what the tolerance is for frequency when testing (i.e. is it +- 5hz?)
        */
        if (freq_value <=5) currentState = Short_Circuit; //0Hz
        else if (freq_value > 5 && freq_value <=15) currentState = Normal_Condition; //10Hz, PWM is between 5-95%
        else if (freq_value > 15 && freq_value <=25) currentState = Undervoltage_Condition; //20Hz, PWM is between 5-95%
        else if (freq_value > 25 && freq_value <=35) //30Hz, PWM is between 5-10% (good) or 90-95% (bad)
        {
            if(duty_value >= 5 && duty_value <= 10) currentState = Speed_Start_Measurement_Good;
            else if(duty_value >= 90 && duty_value <= 95) currentState = Speed_Start_Measurement_Bad;
            else currentState = Undefined_Fault;
        }
        else if (freq_value > 35 && freq_value <=45 && duty_value >= 47 && duty_value <= 53) currentState = Device_Error; //40Hz, PWM is between 47.5-52.5%
        else if (freq_value > 45 && freq_value <=55 && duty_value >= 47 && duty_value <= 53) currentState = Connection_Fault_Earth; //50Hz, PWM is between 47.5-52.5%
        else currentState = Undefined_Fault; //Freq range outside known values
        IMDData.IMDState = currentState;


      /*
       *  Duty Cycle Mapping. If Duty Cycle is anything other than Normal, it means either the isolation is dropping
          or that something is wrong with the IMD

        ex. If IMD State is Normal or in UnderVoltage Condition and the IsolationState, that's fine
        ex. But if IMD State is Normal and Duty Cycle is anything other than Normal, there is an isolation problem
      *
      */

        if (duty_value >= 5 && duty_value <10) isolationState = Normal; //PWM is between 5-10%
        else if (duty_value >= 10 && duty_value <30) isolationState = Normal_75; //PWM is between 10-30%
        else if (duty_value >= 30 && duty_value <60) isolationState = Normal_50; //PWM is between 30-60%
        else if (duty_value >= 60 && duty_value <90) isolationState = Normal_25; //PWM is between 60-90%
        else if (duty_value >= 90 && duty_value <=95) isolationState = Isolation_Failure; //PWM is between 90-95%
        else isolationState = Unknown;

        IMDData.IsolationState = isolationState;

        #ifdef SERIAL_SEND
        NumberofCharsFreq = ltoa(freq_value, (char*) freq_data);
        NumberofCharsDuty = ltoa(duty_value, (char*) duty_data);

        sciSend(scilinREG, NumberofCharsFreq, freq_data);
        sciSend(scilinREG, 4, (unsigned char*)" Hz ");

        sciSend(scilinREG, NumberofCharsDuty, duty_data);
        sciSend(scilinREG, 4, (unsigned char*)" %\r\n");
        #endif // SERIAL_SEND
    }
/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
// getter function for reading IMDData
IMDData_t getIMDData(){
    return IMDData;
}

// getter function for reading IMDData Resistance
float getIMDResistance(){
    // Equation from data sheet correlating duty cycle with resistance
   float IMD_resistance = 90.0*1200.0/(duty_cycle*100.0 - 5.0)-1200.0;
   return IMD_resistance;
}

// interrupt handler for when a rising or falling edge occurs
void edgeNotification(hetBASE_t * hetREG,uint32 edge)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (37) */

    // if rising edge
    if(hetREG == hetREG1 && edge == 0)
    {
        //LED on board
        gioToggleBit(gioPORTB,2);

        // pinStatus indicates if it is a rising or falling edge
        uint32 pinStatus = gioGetBit(hetPORT1, 20);

        //if it is a rising edge, record the time (time1 = rising edge timestamp)
        if(pinStatus == 1) time1 = rtiREG1->CNT[1].FRCx;

        // else it is a falling edge
        else
        {
            // time2 = falling edge timestamp
            time2 = rtiREG1->CNT[1].FRCx;

            // if there is no overflow for time 1 (rising edge)
            //last_time1 is the last rising edge, time_1 is latest rising edge
            if(last_time1 <= time1)
            {
                // free running counter is one tick every 10MHz
                period = ((float)time1 - (float)last_time1)/FREQ_RUNNING_COUNTER;
                frequency = 1/period;

                // checks if there is overflow for time2 (falling edge)
                // if no overflow
                if(time1 <= time2) time_on = ((float)time2 - (float)time1)/FREQ_RUNNING_COUNTER;

                else
                // overflow occurred in time2
                {
                    time_on = ((float)time2 + (UINT32_MAX_-(float)time1))/FREQ_RUNNING_COUNTER;
                }

                duty_cycle = (time_on/period);
                last_time1=time1;
            }

            else
            {
                // overflow occurred in time_1
                period = ((float)time1 + (UINT32_MAX_-(float)last_time1))/FREQ_RUNNING_COUNTER;
                frequency = 1/period;


                // if time2 is still ahead of time1
                if(time1 <= time2) time_on = ((float)time2 - (float)time1)/FREQ_RUNNING_COUNTER;

                // handles if time_2 overflowed and time1 did not
                // we are already in the else statement where time1 overflowed so:
                // THIS SHOULD NEVER HAPPEN *something probably went wrong*
                else
                {
                    // some error occurred, should trigger an undefined fault
                    time_on = ((float)time2 + (UINT32_MAX_-(float)time1))/FREQ_RUNNING_COUNTER;
                }

                duty_cycle = (time_on/period);
                last_time1=time1;
            }
        }
    }
}
/* USER CODE END */
