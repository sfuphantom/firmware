/*
 * DAC_SPI_dash.h
 *
 *  Created on: Feb 29, 2020
 *      Author: lenovo
 */

#ifndef DAC_SPI_DASH_H_
#define DAC_SPI_DASH_H_

#include "stdbool.h"
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_types.h"
#include "driverlib/ssi.h"

bool MCP48FV_init(); // Init the SSI communication

bool MCP48FV_setValue(uint16_t targetVoltage); //checking target Voltage

bool MCP48FV_write(uint32_t cmdString); //write command to the DAC

uint32_t cmdCreator(uint8_t address, uint8_t cmdReadWrite, uint8_t cmderr,
                    uint16_t dataBit); // setting command to interface to the DAC

uint16_t readRegister(uint8_t registerAddress);
uint16_t MCP48FV_Read();

void SSIDataSend24(uint32_t ui32Base, uint32_t ui32Data);

#endif /* DAC_SPI_DASH_H_ */
