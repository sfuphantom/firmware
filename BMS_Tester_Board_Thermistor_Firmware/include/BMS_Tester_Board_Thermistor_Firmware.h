/*
 * BMS_Tester_Board_Thermistor_Firmware.h
 *
 *  Created on: Sep 17, 2020
 *      Author: Jaskanwal Singh
 */

#ifndef INCLUDE_BMS_TESTER_BOARD_THERMISTOR_FIRMWARE_H_
#define INCLUDE_BMS_TESTER_BOARD_THERMISTOR_FIRMWARE_H_



#include "mibspi.h"
#include "sci.h"
#include "gio.h"
#include "sys_vim.h"
#include "stdlib.h"
#include "sys_common.h"
#include "sys_core.h"


//function for simulating thermistor data
void send_simulated_thermistor_data (uint8 test_data_format_type);              //




#endif /* INCLUDE_BMS_TESTER_BOARD_THERMISTOR_FIRMWARE_H_ */
