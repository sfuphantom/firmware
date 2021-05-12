/*
 * hv_voltage_sensor.h
 *
 *  Created on: Nov 10, 2020 
 *      Author: Sumreen Rattan
 *  Modified by: Ryan Heo
 */

#ifndef PHANTOM_DRIVERS_INCLUDE_HV_VOLTAGE_SENSOR_H_
#define PHANTOM_DRIVERS_INCLUDE_HV_VOLTAGE_SENSOR_H_

#include "sys_common.h"
#include "stdint.h"
#include "mibspi.h"
#include "gio.h"
#include "sys_vim.h"
#include "sys_core.h"

typedef enum
{
    NORMAL_HV_VS_OPERATION,
    HV_VS_BOTH_BOUNDS,
    HV_VS_OUT_OF_RANGE,
    HV_VS_AT_ZERO,
    HV_VS_SWEEP
} testcases_name;

// Static function prototypes
static void hv_vs_both_bounds();
static void hv_vs_out_of_range();
static void hv_vs_both_bounds();
static void hv_vs_at_zero();
static void hv_vs_sweep();
static int getADCdigital(int battery_voltage);
static void spiSetup(uint16 voltage);
void hv_vs_process(uint8_t state);
static int twosComplement(int negative_output);
void mibspiGroupNotification(mibspiBASE_t *mibspi, uint32 group);
void adcSlaveDataSetup();

#endif /* PHANTOM_DRIVERS_INCLUDE_HV_VOLTAGE_SENSOR_H_ */
