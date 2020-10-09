/*
 * BMS_Tester_Board_Thermistor_Firmware_mibSPI_x_mibSPI.h
 *
 *  Created on: Sep 24, 2020
 *      Author: jaska
 */

#ifndef INCLUDE_BMS_TESTER_BOARD_THERMISTOR_FIRMWARE_MIBSPI_X_MIBSPI_H_
#define INCLUDE_BMS_TESTER_BOARD_THERMISTOR_FIRMWARE_MIBSPI_X_MIBSPI_H_


#include "mibspi.h"
#include "sci.h"
#include "gio.h"
#include "sys_vim.h"
#include "stdlib.h"
#include "sys_common.h"
#include "sys_core.h"



uint8   verify_slave_connection();      //can be based on the master module in consideration -> Parameter eg.  mibspiBASE_t *mibspi


#endif /* INCLUDE_BMS_TESTER_BOARD_THERMISTOR_FIRMWARE_MIBSPI_X_MIBSPI_H_ */
