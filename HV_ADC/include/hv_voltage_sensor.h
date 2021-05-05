/*
 * hv_voltage_sensor.h
 *
 *  Created on: Nov 10, 2020 
 *      Author: Sumreen Rattan
 */

#ifndef PHANTOM_DRIVERS_INCLUDE_HV_VOLTAGE_SENSOR_H_
#define PHANTOM_DRIVERS_INCLUDE_HV_VOLTAGE_SENSOR_H_

#include "stdint.h"
#include "system.h"

extern uint16 TX_ADS7044_Slave[1];
void hv_vs_process(uint8_t state);
#endif /* PHANTOM_DRIVERS_INCLUDE_HV_VOLTAGE_SENSOR_H_ */
