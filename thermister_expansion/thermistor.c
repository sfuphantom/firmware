/*
 * thermistor.c
 *
 *  Created on: Jan 9, 2020
 *      Author: JASKANWAL SINGH
 */

#include "thermistor.h"
#include "mibspi.h"
#include "sys_vim.h"
#include "stdbool.h"


void check_faults()
{
    if (temp > MAX_TEMP_CHARGING)
    {
        // throw GPIO fault here
    }


