/*
 * thermistor.h
 *
 *  Created on: Jan 9, 2020
 *      Author: JASKANWAL SINGH
 */

#ifndef THERMISTOR_H_
#define THERMISTOR_H_

#include "sys_common.h"


/*Thermistor Interface Functions*/
void setup_thermistor ();               //prepare the thermistor to start reading
bool thermistor_measuring_charge ();    //inquire whether the thermistor is measuring while the car is charging?
bool thermistor_measuring_run ();       //inquire whether the thermistor is measuring while the car is running?
uint16_t read_thermistor ();            //reads and returns the thermistor values
uint16_t verify_fault_thermistor ();    //verifies if the temperatures are within acceptable limits
bool flag_fault_thermistor ();          //flags a fault occurrence
void send_fault_details_thermistor ();  //sends fault details to the VCU or the Dashboard or...... over SCI or something



#endif /* THERMISTOR_H_ */
