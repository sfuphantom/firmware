/** @file sys_main.c 
*   @brief Application main file
*   @date 21-May-2020
* */
#include "IMD.h"
#define SERIAL_SEND

// Global Variables
static const float FREQ_RUNNING_COUNTER = 10000000.00; // 10Mhz
static const uint32_t UINT32_MAX_ = 4294967295;
static uint32_t last_time1, time1, time2;
float period, time_on, frequency, duty_cycle, IMD_resistance;

// SCI variables
unsigned int NumberofCharsFreq, freq_value, NumberofCharsDuty, duty_value;
unsigned char freq_data[8];
unsigned char duty_data[8];
const float f_HCLK = 160.00;

IMDData_t IMDData = {Normal_Condition};
IMDStateEnum currentState;
IsolationStateEnum isolationState;

/*
* Fn: initalizeIMD
* Purpose: Initializes all functions required to make reading the IMD work
*/
void initalizeIMD(){
    hetInit();
    gioInit();
    rtiInit();
    sciInit();
    rtiResetCounter(rtiCOUNTER_BLOCK1);

    _enable_IRQ();

    edgeEnableNotification(hetREG1, edge0);
    gioEnableNotification(gioPORTA,5);
    rtiStartCounter(rtiCOUNTER_BLOCK1); // cant read register without this (RTI doesnt start?)
}

/*
* Fn: updateIMDState
* Purpose: Message Mapping for IMD Operation State
* To-do: Need to find what the tolerance is for frequency when testing (i.e. is it +- 5hz?)
*/
void updateIMDState(unsigned int freq_value, unsigned int duty_value){

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
}

/*
*   Fn: updateIsolationState
*   Purpose: Message Mapping for HV/LV Isolation State
*   Duty Cycle Mapping. If Duty Cycle is anything other than Normal, it means either the isolation is dropping
*   or that something is wrong with the IMD
*   ex. If IMD State is Normal or in UnderVoltage Condition and the IsolationState, that's fine
*   ex. But if IMD State is Normal and Duty Cycle is anything other than Normal, there is an isolation problem
*/
void updateIsolationState(unsigned int duty_value){
      if (duty_value >= 5 && duty_value <10) isolationState = Normal; //PWM is between 5-10%
      else if (duty_value >= 10 && duty_value <30) isolationState = Normal_75; //PWM is between 10-30%
      else if (duty_value >= 30 && duty_value <60) isolationState = Normal_50; //PWM is between 30-60%
      else if (duty_value >= 60 && duty_value <90) isolationState = Normal_25; //PWM is between 60-90%
      else if (duty_value >= 90 && duty_value <=95) isolationState = Isolation_Failure; //PWM is between 90-95%
      else isolationState = Unknown;

      IMDData.IsolationState = isolationState;
}

/*
* Fn: updateIMDData
* Purpose: Updates the message statuses for what is inside the IMDData Struct
*/
void updateIMDData()
    {
        // adding this 0.5 and then typecasting to an int (truncating all decimals)
        // basically acts as rounding the float to the nearest integer
        freq_value = (unsigned int) (frequency + 0.5);
        duty_value = (unsigned int) (duty_cycle*100.0 + 0.5);

        updateIMDState(freq_value,duty_value);
        updateIsolationState(duty_value);
    }

/*
* Fn: serialSendData
* Purpose: Sends the current Frequency and Duty Cycle read from the IMD
*/
void serialSendData() {
    NumberofCharsFreq = ltoa(freq_value, (char*) freq_data,10);
    NumberofCharsDuty = ltoa(duty_value, (char*) duty_data,10);

    sciSend(scilinREG, NumberofCharsFreq, freq_data);
    sciSend(scilinREG, 4, (unsigned char*)" Hz ");

    sciSend(scilinREG, NumberofCharsDuty, duty_data);
    sciSend(scilinREG, 4, (unsigned char*)" %\r\n");
}

/*
* Fn: getIMDData
* Purpose: Getter function for reading IMDData
* Returns: IMDData Struct
*/
IMDData_t getIMDData(){
    return IMDData;
}

/*
* Fn: getIMDResistance
* Purpose: Calculates and returns IMD Resistance
* The equation uses duty cycle as a variable for an equation found in the datasheet
* to calculate the resistance in Ohms
* Returns: IMD Resistance in Ohms
*/

float getIMDResistance(){
    // Equation from data sheet correlating duty cycle with resistance
   float IMD_resistance = 90.0*1200.0/(duty_cycle*100.0 - 5.0)-1200.0;
   return IMD_resistance;
}

/*
* Fn: edgeNotification
* Purpose: Interrupt handler for when a rising or falling edge occurs
* on the square wave that the IMD is outputting
*/
void edgeNotification(hetBASE_t * hetREG,uint32 edge)
{
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

            else // there is an overflow
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
