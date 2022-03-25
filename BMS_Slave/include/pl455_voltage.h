/*
 * pl455_voltage.h
 *
 *  Created on: Feb. 22, 2022
 *      Author: ryanh
 */

#ifndef INCLUDE_PL455_VOLTAGE_H_
#define INCLUDE_PL455_VOLTAGE_H_

#include "datatypes.h"
#include "stdbool.h"
#include "pl455.h"
#include "hal_stdtypes.h"
#include "stdint.h"
#include "bms_data.h"

typedef enum{
    SLAVE_CONNECTION_GOOD,
    SLAVE_CONNECTION_BAD
    /*BMS_OPERATIONAL,
    BMS_TEMPERATURE_FAULT,
    BMS_VOLTAGE_FAULT,
    BMS_TEMPERATURE_VOLTAGE_FAULT,
    BMS_CRITICAL_FAULT*/
}BMS_SLAVE_STATE;

typedef struct BMS_FLAGS{
    bool CELL_OVERVOLTAGE_FLAG[CELLS_PER_BOARD];            // 1 if a cell in the board being evaluated is overvoltage. Else, 0
    bool CELL_UNDERVOLTAGE_FLAG[CELLS_PER_BOARD];           // 1 if a cell in the board being evaluated is undervoltage. Else, 0
    bool CELL_HIGH_TEMPRATURE_FLAG[CELLS_PER_BOARD];        // 1 if a cell in the board being evaluated has a high temperature. Else, 0
    uint16_t CELL_VOLTAGE_ERROR_COUNTER[CELLS_PER_BOARD];   // Incremented each time a cell in the board being evaluated is
                                                            // under/over voltage. Else, set to 0. If this flag is over 300 (has been
                                                            // consecutively incremented every 10ms for 3 seconds), 3SECOND_FLAG is set
    uint8_t TOTAL_CELL_ERROR_COUNTER;                       // Incremented each time a cell in the board being evaluated is under/over
                                                            // voltage or has a high temperature. If this flag is over 4, TOTAL_CELL_ERROR_FLAG
                                                            // is set
    uint8_t CELL_RW_ERROR_FLAG[TOTALBOARDS];                // Incremented each time there is a read/write error with a BMS slave. Else, 0
                                                            // If this flag is over 3 (3 consecutive read/write errors to a slave have been
                                                            // detected) and BMS state is SLAVE_CONNECTION_GOOD, attempt is made to reconnect slave.
                                                            // If this flag is over 3 and BMS state is SLAVE_CONNECTION_BAD,
                                                            // BAD_SLAVE_CONNECTION_FLAG is set
} BMS_FLAGS;
void BMS_init();
void Slave_autoAddressing();
void board_com_config (uint32 baudrate, uint64_t dwData);
void board_stack_enable();

#endif /* INCLUDE_PL455_VOLTAGE_H_ */
