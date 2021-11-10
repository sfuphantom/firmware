/*
 * Current_transducer.h
 *
 *  Created on: Nov 2, 2021
 *      Author: Ryan Heo
 */

#ifndef PHANTOM_DRIVERS_CURRENT_TRANSDUCER_CURRENT_TRANSDUCER_H_
#define PHANTOM_DRIVERS_CURRENT_TRANSDUCER_CURRENT_TRANSDUCER_H_

#define MAX_POS_CURRENT 200
#define MIN_NEGATIVE_CURRENT -200
#define I_PN 200    // primary nominal current
#define Uref 2.5

#define bool int;
#define true 1
#define false 0

// global variables
static float IpLow;
static float IpHigh;
static bool flag ; // fault check for exceeding current level
static unsigned int max_voltage = 5;
static unsigned int adc_resolution = 4096;
static double sensor_voltage; // sensor voltage range 0 to 5V
static double output_current;
static char command[8];
static unsigned int NumberOfChars, value;
static double ADC_voltage, accumulator_current;
// methods
double getHVsensorVoltage();
double getHVsensorCurrent();
_Bool HVcurrent_Range_Check(); // Fault check method

#endif /* PHANTOM_DRIVERS_CURRENT_TRANSDUCER_CURRENT_TRANSDUCER_H_ */
