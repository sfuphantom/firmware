/*
 * pl455_voltage.c
 *
 *  Created on: Feb. 22, 2022
 *      Author: ryanh
 */

#include "pl455_voltage.h"
#include "gio.h"
#include "sci.h"
#include "can.h"
#include "reg_het.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sys_vim.h"
#include "sys_core.h"
#include "datatypes.h"
#include "bms_data.h"
#include "hwConfig.h"
#include "PL455.h"

static uint16 HB_LED = 0;

BYTE SingleSlaveReading[BMSByteArraySize];
BYTE MultipleSlaveReading[BMSByteArraySize * (TOTALBOARDS)];

volatile BMS_FLAGS BMS = { { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 } };
BMS_SLAVE_STATE bmsSlaveState[TOTALBOARDS];

extern bms_data *BMSDataPtr;
int nDev_ID;
int nRead, nSent, nTopFound = 0;

void BMS_init()
{
    uint32_t wTemp = 0;
    unsigned char command;

    //
    UARTprintf("log: WakeBit:%d FaultBit:%d\n\r", gioGetBit(hetPORT1, 9),
               gioGetBit(hetPORT1, 25));
    WakePL455();
    UARTprintf("log: WakeBit:%d FaultBit:%d\n\r", gioGetBit(hetPORT1, 9),
               gioGetBit(hetPORT1, 25));

    CommClear();
    CommReset();

    // Putting sci funcitons with the init function built in
    sciEnableNotification(PC_UART, SCI_RX_INT);
    sciReceive(PC_UART, 1, (unsigned char*) &command);

}

void Slave_config()
{
    // turn on the downstreat communications drivers on all devices in the chain
    for (nDev_ID = 0; nDev_ID < TOTALBOARDS; nDev_ID++)
    {
        nSent = WriteReg(nDev_ID, 12, 0x40, 1, FRMWRT_ALL_NR); //Send out broadcast pwrdown command
        delayms(5); //~5ms
        WakePL455(); //
        delayms(5); //~5ms
    }

    delayms(100);

    // Mask Customer Checksum Fault bit
    nSent = WriteReg(0, 107, 0x8000, 2, FRMWRT_ALL_NR); // clear all fault summary flags
    // clear all faults
    nSent = WriteReg(0, 82, 0xFFC0, 2, FRMWRT_ALL_NR); // clear all fault summary flags (Section 1.2.7)
    nSent = WriteReg(0, 81, 0x38, 1, FRMWRT_ALL_NR); // clear fault flags in the system status register

    // Auto-address all boards (Section 1.2.2)
    nSent = WriteReg(0, 14, 0x19, 1, FRMWRT_ALL_NR); // set auto-address mode on all boards
    nSent = WriteReg(0, 12, 0x08, 1, FRMWRT_ALL_NR); // enable to enter auto address mode on all boards

    // send out new addresses to all devices in crementing order starting at zero
    for (nDev_ID = 0; nDev_ID < TOTALBOARDS; nDev_ID++)
    {
        nSent = WriteReg(nDev_ID, 10, nDev_ID, 1, FRMWRT_ALL_NR); // send address to each board
    }

    // Enable all communication interfaces on all boards in the stack (Section 1.2.1)
    nSent = WriteReg(0, 16, 0x10F8, 2, FRMWRT_ALL_NR); // set communication baud rate and enable RX/TX

    // Default baudrate is set to 250000, but if another baud rate seems ideal, change the value of baud rate defined in pl455.h
    switch (BAUDRATE)
    {
        case 125000:
            nSent = WriteReg(0, 16, 0x00F8, 2, FRMWRT_ALL_NR); // set communication baud rate and enable all interfaces.
            delayms(1);
            sciSetBaudrate(BMS_UART, BAUDRATE);
            break;
        case 250000:
            nSent = WriteReg(0, 16, 0x20F8, 2, FRMWRT_ALL_NR);
            delayms(1);
            sciSetBaudrate(BMS_UART, BAUDRATE);
            break;
        case 500000:
            nSent = WriteReg(0, 16, 0x30F8, 2, FRMWRT_ALL_NR);
            delayms(1);
            sciSetBaudrate(BMS_UART, BAUDRATE);
            break;
        case 1000000:
            nSent = WriteReg(0, 16, 0x40F8, 2, FRMWRT_ALL_NR);
            delayms(1);
            sciSetBaudrate(BMS_UART, BAUDRATE);
            break;
    }

}



