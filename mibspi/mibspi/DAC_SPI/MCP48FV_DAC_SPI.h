/*
 * MSP48FV_DAC_SPI.h
 *
 *  Created on: Oct 12, 2019
 *      Author: PTL
 */

#ifndef INCLUDE_DAC_SPI_MSP48FV_DAC_SPI_H_
#define INCLUDE_DAC_SPI_MSP48FV_DAC_SPI_H_
//modified mibspi.c to remove groupnotifications
#include "stdbool.h"
#include "mibspi.h"


bool MSP48FV_Init();
//Main DAC controller

bool MSP48FV_Set_Value(uint16_t targetVoltage);
//SPI write

bool MSP48FV_Write(uint32_t cmdString);

#endif /* INCLUDE_DAC_SPI_MSP48FV_DAC_SPI_H_ */
