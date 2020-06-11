/*
 * IMD.h
 *
 *  Created on: May 21, 2020
 *      Author: Sumreen Rattan
 */
#ifndef SOURCE_IMD_H_
#define SOURCE_IMD_H_

/* Include Files */
#include "het.h"
#include "gio.h"
#include "sys_vim.h"
#include "rti.h"
#include "sci.h"
#include "stdlib.h" // contains ltoa
#include "sys_common.h"

// ENUMS FOR IMD MESSAGE MAPPING

// IMD State Enum
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

// Isolation State Enum
typedef enum{
    Normal, // When Duty Cycle 5-10%
    Normal_75, // Usually when Duty Cycle 10-30%
    Normal_50, // Usually when Duty Cycle 30-60%
    Normal_25, // Usually when Duty Cycle 60-90%
    Isolation_Failure, //When Duty Cycle is 90-95%
    Unknown // Duty Cycle is outside of range (5-95%)
}IsolationStateEnum;


// IMDData Struct which contains the status of the IMD and Isolation
typedef struct{
    IMDStateEnum IMDState;
    IsolationStateEnum IsolationState;
}IMDData_t;

/*
-------------------------------------------------------
                       FUNCTIONS
-------------------------------------------------------
*/


/* Fn: initalizeIMD
* Purpose: Initializes all functions required to make reading the IMD work
*/
void initalizeIMD();


/* Fn: updateIMDState
* Purpose: Message Mapping for IMD Operation State
* To-do: Need to find what the tolerance is for frequency when testing (i.e. is it +- 5hz?)
*/
void updateIMDState(unsigned int freq_value, unsigned int duty_value);

/*   Fn: updateIsolationState
*   Purpose: Message Mapping for HV/LV Isolation State
*   Duty Cycle Mapping. If Duty Cycle is anything other than Normal, it means either the isolation is dropping
*   or that something is wrong with the IMD
*   ex. If IMD State is Normal or in UnderVoltage Condition and the IsolationState, that's fine
*   ex. But if IMD State is Normal and Duty Cycle is anything other than Normal, there is an isolation problem
*/
void updateIsolationState(unsigned int duty_value);



/* Fn: updateIMDData
* Purpose: Updates the messages inside the IMDData Struct
*/
void updateIMDData();


/* Fn: serialSendData
* Purpose: Sends the current Frequency and Duty Cycle read from the IMD
*/
void serialSendData();


/* Fn: getIMDData
* Purpose: Getter function for reading IMDData
* Returns: IMDData Struct
* */
IMDData_t getIMDData();


/* Fn: getIMDResistance
* Purpose: Calculates and returns IMD Resistance
* The equation uses duty cycle as a variable for an equation found in the datasheet
* to calculate the resistance in Ohms
* Returns: IMD Resistance in Ohms
* */
float getIMDResistance();


#endif /* SOURCE_IMD_H_ */
