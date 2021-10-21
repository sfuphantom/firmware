/*
 * hv_driver.h
 *
 *  Created on: Oct. 20, 2021
 *      Author: Ryan H
 */

#ifndef HV_DRIVER_H_
#define HV_DRIVER_H_

/*============================================================================*/
/* Function Prototypes           */
/*============================================================================*/
static uint16 bitExtracted(uint16 number, uint8 k, uint8 p);
static void decToBinary(int n);;
static int binTwosComplementToSignedDecimal(uint8 binary[],uint8 significantBits);
static float Interpolate_input (int adc_input);
void UARTprintf(const char *_format, ...);
void adcVoltageTest();
void adcSlaveDataSetup();
void masterDataTranser();
float getADCdata(uint16 input);
void unitTesting();


#endif /* HV_DRIVER_H_ */
