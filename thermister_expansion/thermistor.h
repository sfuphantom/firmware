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
#include "sys_vim.h"
#include "sys_core.h"
#include "sci.h"
#include "temperature_yash.h"
#include "gio.h"
#include "stdlib.h"

/*TERMISTOR INTERFACE FUNCTIONS************************************************************************************************************************************/

/*Setting up mibSPI communication with the ADC*/

void setup_mibspi_thermistor();        //prepare the thermistor to start reading

/*Validating usage status (0/1)*/

uint8_t         validate_usage_status_thermistor(uint8_t status );      //Inquires whether the car is charging or running while the thermistor is measuring?

/*Reading Thermistor values*/  /*following three functions might require transitioning back to Manual mode*/

uint16_t    read_all_muxes_all_channels_thermistor();                                                       //reads and returns the thermistor values from all muxes on all channels
uint16_t    read_all_muxes_specific_channel_thermistor(uint8_t channel_identity);                           //reads and returns the thermistor values from all muxes on a specific channel
uint16_t    read_specific_mux_all_channels_thermistor(uint8_t mux_identity);                                //reads and returns the thermistor values from a specific mux on all the channels
uint16_t    read_specific_mux_specific_channel_thermistor(uint8_t mux_identity, uint8_t channel_identity);  //reads and returns the thermistor values from a specific mux on a specific channel

/*Print ADC readings*/
void        extract_thermistor_readings_rx_data_buffer();
void        print_thermistor_readings_voltage(uint8 input);                   //prints using SCI

/*Converting Thermistor readings*/
void        convert_reading_thermistor ();        //converts thermistor reading into temperature

/*Structure for storing temperature and resistance values from the thermistor*/
struct thermistor_temperature_and_flag
{
    uint16 temperature;
    uint16 temperature_flag;       // 0 or 1
};

#define TOTAL_MUXES 96

struct thermistor_temperature_and_flag thermistor_temperature_and_flag_struct[TOTAL_MUXES];     //can be a double pointer

void update_thermistor_temperature_and_flag_structure(uint8 mux);

/*Update mux*/

void update_mux(uint8 current_mux);

/*Reading faults*/

uint16_t    read_fault_thermistor();    //verifies if the operating temperatures are within acceptable limits

/*Fault Details*/

void        print_fault_details_thermistor();     //Identifies and prints details of usage status (0/1), mux and channel corresponding to the occurred fault
uint16_t    send_fault_signal_thermistor();       //flags a fault occurrence to the VCU and/or Dashboard or .....over SCI or something
uint16_t    send_fault_details_thermistor();      //sends fault details to the VCU and/or Dashboard or...... over SCI or something

/*mibspi Interrupts*/
//void mibspiGroupNotification(mibspiBASE_t *mibspi, uint32 group);


#endif /* THERMISTOR_H_ */
