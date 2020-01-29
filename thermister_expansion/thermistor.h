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
#include "mibspi.h"


/*TERMISTOR INTERFACE FUNCTIONS************************************************************************************************************************************/

/*Setting up mibSPI communication with the ADC*/

void setup_mibspi_thermistor();        //prepare the thermistor to start reading

/*Validating usage status (0/1)*/

uint16_t         validate_usage_status_thermistor(uint16_t status );      //Inquires whether the car is charging or running while the thermistor is measuring?

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

/*mibspi Interrupts*/
void mibspiGroupNotification(mibspiBASE_t *mibspi, uint32 group);


#endif /* THERMISTOR_H_ */
