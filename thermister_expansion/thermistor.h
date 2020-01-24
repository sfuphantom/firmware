/*
 * thermistor.h
 *
 *  Created on: Jan 9, 2020
 *      Author: JASKANWAL SINGH
 */

#ifndef THERMISTOR_H_
#define THERMISTOR_H_


/*
#define MAX_TEMP_CHARGING 45
#define MAX_TEMP_RUNNING  60
*/


#include "sys_common.h"


/*TERMISTOR INTERFACE FUNCTIONS************************************************************************************************************************************/

/*Setup*/

void setup_mibspi_thermistor();        //prepare the thermistor to start reading

/*Validating usage status (0/1)*/

bool        measuring_charge_thermistor();      //Usage status = 0; inquires whether the car is charging while the thermistor is measuring?
bool        measuring_run_thermistor();         //Usage status = 1; inquires whether the car is running while the thermistor is measuring?

/*Reading Thermistor values*/

uint16_t    read_all_muxes_all_channels_thermistor();               //reads and returns the thermistor values from all muxes on all channels
uint16_t    read_all_muxes_specific_channel_thermistor();           //reads and returns the thermistor values from all muxes on a specific channel
uint16_t    read_specific_mux_all_channels_thermistor();            //reads and returns the thermistor values from a specific mux on all the channels
uint16_t    read_specific_mux_specific_channel_thermistor();        //reads and returns the thermistor values from a specific mux on a specific channel

/*Converting Thermistor readings*/
void        convert_reading_thermistor ();        //converts thermistor reading into temperature

/*Reading faults*/

uint16_t    read_fault_thermistor();    //verifies if the operating temperatures are within acceptable limits

/*Fault Details*/

void        print_fault_details_thermistor();     //Identifies and prints details of usage status (0/1), mux and channel corresponding to the occurred fault
uint16_t    send_fault_signal_thermistor();       //flags a fault occurrence to the VCU and/or Dashboard or .....over SCI or something
uint16_t    send_fault_details_thermistor();      //sends fault details to the VCU and/or Dashboard or...... over SCI or something


#endif /* THERMISTOR_H_ */
