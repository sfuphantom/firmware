/*
 * thermistor.h
 *
 *  Created on: Jan 9, 2020
 *      Author: JASKANWAL SINGH
 */

#ifndef THERMISTOR_H_
#define THERMISTOR_H_

#define MAX_TEMP_CHARGING 45
#define MAX_TEMP_RUNNING  60

#include "sys_common.h"


/*TERMISTOR INTERFACE FUNCTIONS***************************************************************************************************************/

/*Setup*/

void setup_thermistor ();               //prepare the thermistor to start reading

/*Assessing usage status*/

bool thermistor_measuring_charge ();    //inquire whether the thermistor is measuring while the car is charging?
bool thermistor_measuring_run ();       //inquire whether the thermistor is measuring while the car is running?

/*Reading Thermistor values*/

uint16_t read_thermistor ();            //reads and returns the thermistor values

/*Managing faults*/

uint16_t read_fault_thermistor ();    //verifies if the temperatures are within acceptable limits


bool flag_fault_thermistor ();          //flags a fault occurrence
void send_fault_details_thermistor ();  //sends fault details to the VCU or the Dashboard or...... over SCI or something



#endif /* THERMISTOR_H_ */
