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
#include "stdint.h"

static uint16 HB_LED = 0;

BYTE SingleSlaveReading[BMSByteArraySize];
BYTE MultipleSlaveReading[BMSByteArraySize * (TOTALBOARDS)];

volatile BMS_FLAGS BMS = { { 0 }, { 0 }, { 0 }, { 0 }, { 0 }, { 0 } };
BMS_SLAVE_STATE bmsSlaveState[TOTALBOARDS];

extern bms_data *BMSDataPtr;
int nDev_ID;
int nRead, nSent, nTopFound = 0;
char buf[100];
uint32_t wTemp = 0;
uint8 totalCellCount = TOTALCELLS*TOTALBOARDS;
uint8 cellCount = TOTALCELLS;
uint8 voltageLoopCounter = TOTALCELLS*2+1;
uint8 auxLoopCounter = TOTALCELLS*2+1 + TOTALAUX*2;

void BMS_init()
{
    unsigned char command;

    //
    UARTprintf("log: WakeBit:%d FaultBit:%d\n\r", gioGetBit(hetPORT1, 9), gioGetBit(hetPORT1, 25));
    WakePL455();
    UARTprintf("log: WakeBit:%d FaultBit:%d\n\r", gioGetBit(hetPORT1, 9), gioGetBit(hetPORT1, 25));

    CommClear();
    CommReset();

    // Putting sci funcitons with the init function built in
    sciEnableNotification(PC_UART, SCI_RX_INT);
    sciReceive(PC_UART, 1, (unsigned char*) &command);

    Slave_autoAddressing();
    Board_stack_enable();
    AFE_config ();

}

void Slave_autoAddressing()
{
    // Turn on the downstream communications drivers on all devices in the chain
    for (nDev_ID = 0; nDev_ID < TOTALBOARDS; nDev_ID++)
    {
        nSent = WriteReg(nDev_ID, 12, 0x40, 1, FRMWRT_ALL_NR); //Send out broadcast pwrdown command
        delayms(5); //~5ms
        WakePL455(); //
        delayms(5); //~5ms
    }

    delayms(100);

    // Mask Customer Checksum Fault bit
    nSent = WriteReg(0, 107, 0x8000, 2, FRMWRT_ALL_NR);

    // clear all faults (Section 2.2.4)
    nSent = WriteReg(0, 82, 0xFFC0, 2, FRMWRT_ALL_NR); // clear all fault summary flags
    nSent = WriteReg(0, 81, 0x38, 1, FRMWRT_ALL_NR);   // clear fault flags in the system status register

    // Enable all communication interfaces on all boards in the stack (Section 1.2.1)
    nSent = WriteReg(0, 16, 0x10F8, 2, FRMWRT_ALL_NR); // set communication baud rate and enable RX/TX

    // Auto-address all boards (Section 1.2.2)
    nSent = WriteReg(0, 14, 0x19, 1, FRMWRT_ALL_NR); // set auto-address mode on all boards (set the ADDR_SEL bit) (Refer to 7.6.3.9)
    nSent = WriteReg(0, 12, 0x08, 1, FRMWRT_ALL_NR); // enable to enter auto address mode on all boards (set the AUTO-ADDRESS bit)

    // send out new addresses to all devices incrementing order starting at zero (Section 1.2.3)
    for (nDev_ID = 0; nDev_ID < TOTALBOARDS; nDev_ID++)
    {
        nSent = WriteReg(nDev_ID, 10, nDev_ID, 1, FRMWRT_ALL_NR); // send address to each board
    }

    // Default baud rate is set to 250000, but if another baud rate seems ideal, change the value of baud rate defined in pl455.h
    switch (BAUDRATE)
    {
        case 125000:
            nSent = WriteReg(0, 16, 0x00F8, 2, FRMWRT_ALL_NR); // set communication baud rate and enable all interfaces.
            delayms(1);
            sciSetBaudrate(BMS_UART, BAUDRATE);
            break;
        case 250000: // Already set by default
            delayms(1);
            sciSetBaudrate(BMS_UART, BAUDRATE);
            break;
        case 500000:
            nSent = WriteReg(0, 16, 0x20F8, 2, FRMWRT_ALL_NR);
            delayms(1);
            sciSetBaudrate(BMS_UART, BAUDRATE);
            break;
        case 1000000:
            nSent = WriteReg(0, 16, 0x30F8, 2, FRMWRT_ALL_NR);
            delayms(1);
            sciSetBaudrate(BMS_UART, BAUDRATE);
            break;
    }

}

void Board_com_config (uint32 baudrate, uint64_t dwData)
{
    switch(baudrate)
    {
    case 125000:
        nSent = WriteReg(nDev_ID, 16, dwData, 2, FRMWRT_SGL_NR);         // enable comm-high, fault-high, comm-low and fault-low on all middle boards
        break;
    case 250000:
        nSent = WriteReg(nDev_ID, 16, dwData+4096, 2, FRMWRT_SGL_NR);    // enable comm-high, fault-high, comm-low and fault-low on all middle boards
        break;
    case 500000:
        nSent = WriteReg(nDev_ID, 16, dwData+8192, 2, FRMWRT_SGL_NR);    // enable comm-high, fault-high, comm-low and fault-low on all middle boards
        break;
    case 1000000:
        nSent = WriteReg(nDev_ID, 16, dwData+196608, 2, FRMWRT_SGL_NR);  // enable comm-high, fault-high, comm-low and fault-low on all middle boards
        break;
    }
}

void Board_stack_enable()
{
    for (nDev_ID = TOTALBOARDS - 1; nDev_ID >= 0; --nDev_ID)
    {
        //delayms(100);
        nRead = ReadReg(nDev_ID, 10, &wTemp, 1, 0); // 0ms timeout

        if(nRead == 0) // if nothing is read then this board doesn't exist
            nTopFound = 0;
        else // a response was received
            {
            if(nTopFound == 0)
            { // if the last board was not present but this one is, this is the top board
                if(nDev_ID == 0) // this is the only board
                    {
                    board_com_config (BAUDRATE, 0x0080); // enable only single-end comm port on board
                    }
                else // this is the top board of a stack (section 1.2.5)
                    {
                    board_com_config (BAUDRATE, 0x0028); // enable only comm-low and fault-low for the top board
                    nTopFound = 1;
                        }
                    }
                    else // this is a middle or bottom board
                    {
                        if(nDev_ID == 0) // this is a bottom board of a stack (section 1.2.6)
                        {
                            board_com_config (BAUDRATE, 0x00D0); // enable comm-high, fault-high and single-end comm port on bottom board
                        }
                        else // this is a middle board
                        {
                            board_com_config (BAUDRATE, 0x0078); // enable comm-high, fault-high, comm-low, and fault-low on all middle boards
                        }
                    }
                }
            }

    // Clear all faults (section 1.2.7)
    nSent = WriteReg(0, 81, 0x38, 1, FRMWRT_ALL_NR);   // clear fault flags in the system status register
    nSent = WriteReg(0, 82, 0xFFC0, 2, FRMWRT_ALL_NR); // clear all fault summary flags

    delayms(10);
}

// Section 2.1
// The analog front end (AFE) on each stacked board should be configured properly to scan the desired channels at the desired timing
// before reading voltages from daisy-chain networked boards.
void AFE_config ()
{
    // Configure the initial sampling delay (section 2.2.1)
    nDev_ID =0;
    nSent = WriteReg(nDev_ID, 60, 0x00, 1, FRMWRT_SGL_NR); // set 0 mux delay
    nSent = WriteReg(nDev_ID, 61, 0x00, 1, FRMWRT_SGL_NR); // set 0 initial delay

    // Configure voltage and internal sample period (section 2.2.2)
    nSent = WriteReg(nDev_ID, 62, 0xCC, 1, FRMWRT_SGL_NR); // set 99.92us ADC sampling period

    // Configure the Over-sampling Rate (section 2.2.3)
    nSent = WriteReg(nDev_ID, 7, 0x00, 1, FRMWRT_SGL_NR); // set no oversampling period

    // Clear and check faults (section 2.2.4)
    nSent = WriteReg(nDev_ID, 81, 0x38, 1, FRMWRT_SGL_NR);   // clear fault flags in the system status register
    nSent = WriteReg(nDev_ID, 82, 0xFFC0, 2, FRMWRT_SGL_NR); // clear all fault summary flags
    nRead = ReadReg(nDev_ID, 81 ,&wTemp, 1, 0); // 0ms timeout
    nRead = ReadReg(nDev_ID, 82, &wTemp, 2, 0); // 0ms timeout

    // Select number of ceels and channels to sample (section 2.2.5.1)
    nSent = WriteReg(nDev_ID, 13, 0x0A, 1, FRMWRT_ALL_NR);       // set number of cells to 16
    nSent = WriteReg(nDev_ID,  3, 0x03FFFFC0, 4, FRMWRT_ALL_NR); // set all AUX channels, internal digital die, and internal analog die temperatures

    // Set cell overvoltager and undervoltage thresholds (section 2.2.6.1)
    nSent = WriteReg(nDev_ID, 144, 0xD70A, 2, FRMWRT_SGL_NR); // set OV threshold = 4.2000V (4.2/5*(2^16-1) = 55050 = D70A)
    nSent = WriteReg(nDev_ID, 142, 0xA3D6, 2, FRMWRT_SGL_NR); // set UV threshold = 3.2000V (3.2/5*(2^16-1) = 41942 = A3D6)

    // Set GPIO direction for GPIO4 and GPIO[2:0] as outputs, GPIO3 and GPIO5 as inputs
    nSent = WriteReg(nDev_ID, 120, 0x17, 1, FRMWRT_ALL_NR);

    // Configure cell-balancing (datasheet section 7.6.3.13)
    nSent = WriteReg(nDev_ID, 19, 0x20, 1, FRMWRT_ALL_NR); // Set balance time for 1 minute whenever balancing function is called
                                                           // Disables balancing whenever Fault is detected
    // Configure test configuration (datasheet section 7.6.3.15)
    nSent = WriteReg(nDev_ID, 30, 0x0, 2, FRMWRT_ALL_NR); // Sets EN_SQUEEZE = 0 so BALANCE_EN controls the channels which are balancing

    for (nDev_ID = 0; nDev_ID < TOTALBOARDS; nDev_ID++){
        bmsSlaveState[nDev_ID] = SLAVE_CONNECTION_GOOD;
    }
}

/*
 * Read all values in all daisy-chained slaves and store slave voltage values in BMS data structure
 * @param       printToUART     set true to enable printing values to UART
 * @param       update          set true to query the slaves for new values, set false to obtain previously queried-values
 */
void BMS_Read_All(bool printToUART, bool update)
{
    int nDev_ID;

    if (update){
        int nSent = WriteReg(0, 2, TOTALBOARDS-1, 1, FRMWRT_ALL_R); // send sync sample command
        if (nSent != 1){
            for (nDev_ID = 0; nDev_ID < TOTALBOARDS; nDev_ID++){
                BMS.CELL_RW_ERROR_FLAG[nDev_ID]++;
            }
        }
        else {
            for (nDev_ID = 0; nDev_ID < TOTALBOARDS; nDev_ID++){
                BMS.CELL_RW_ERROR_FLAG[nDev_ID] = 0;
            }
        }

        //1 header, 10x2 cells, 2x8 Aux, 1 dig die (2 bytes), 1 ana die(2 bytes), 1 CRC (2 bytes)
        sciReceive(BMS_UART, BMSByteArraySize*TOTALBOARDS, MultipleSlaveReading); //Receive voltage/temperature data

        delayms(5); // for the TMS to record all the data first

    }
    cellVoltageRead(printToUART); // Check individual cell voltage reading and update error flags.
}

/*
 * Check individual cell voltage level from each board and update error flags
 * @param       printToUART     set true to enable printing values to UART
 */
void cellVoltageRead(bool printToUART){

    BMSDataPtr->Data.minimumCellVoltage = 5;
    uint8 i;
    uint8 j;

    for (i = TOTALBOARDS-1; i == 0; i--){
        for (j = 0; j < voltageLoopCounter; j+=2){
            if (j==0){
                if (printToUART){
                    snprintf(buf, 30, "Header -> Decimal: %d, HEX: %X\n\n\r", MultipleSlaveReading[j+BMSByteArraySize*i],MultipleSlaveReading[j+1+BMSByteArraySize*i]);
                    UARTSend(PC_UART, buf);
                }
                continue;
            }

            // Read a cell voltage in two bytes and convert them into a decimal value (ADC Conversion, 16 bits)
            uint32 tempVal = MultipleSlaveReading[j+BMSByteArraySize*i]*16*16 + MultipleSlaveReading[j+1+BMSByteArraySize*i];
            double div = tempVal/65535.0; //divide by FFFF
            double fin = div * 5.0; //multiply by full (max) voltage of 5V

            voltageLevelCheck(printToUART,fin,i,j,cellCount); //Check with thresholds and update flags
            totalCellCount--;
            cellCount--;
        }
        cellCount = TOTALCELLS;
    }
}
/*
 * Store cell voltages in corresponding slaves and update error flags
 * @param       UART     set true to enable printing values to UART
 * @param        i       current outer-loop board counter
 * @param        j       current inner-loop voltage cell counter
 * @param     cellCount  current cell number to check
 */
void voltageLevelCheck(bool UART, uint32 Vin, uint8 i, uint8 j, uint8 cellCount)
{
    if (i==0){
        BMSDataPtr->SlaveVoltage.BMS_Slave_1[cellCount - 1] = Vin;
    }
    if (i==1){
        BMSDataPtr->SlaveVoltage.BMS_Slave_2[cellCount - 1] = Vin;
    }
    if (i==2){
        BMSDataPtr->SlaveVoltage.BMS_Slave_3[cellCount - 1] = Vin;
    }
    if (i==3){
        BMSDataPtr->SlaveVoltage.BMS_Slave_4[cellCount - 1] = Vin;
    }

    if (Vin < BMSDataPtr->Data.minimumCellVoltage){
        BMSDataPtr->Data.minimumCellVoltage = Vin;
    }

    if (UART){
       snprint(buf , 40, "Cell %d: Hex: %X %X voltage: %fV \n\r", totalCellCount, MultipleSlaveReading[j+BMSByteArraySize*i], MultipleSlaveReading[j+1+BMSByteArraySize], Vin);
       UARTSend(PC_UART, buf);
       UARTSend(PC_UART, "\n\r");
    }

    if (BMS.CELL_OVERVOLTAGE_FLAG[cellCount - 1]== true || BMS.CELL_UNDERVOLTAGE_FLAG[cellCount - 1] == true){
        BMS.CELL_VOLTAGE_ERROR_COUNTER[cellCount - 1]++;
    }
    else {
        BMS.CELL_VOLTAGE_ERROR_COUNTER[cellCount - 1] = 0;
    }
    if (BMS.CELL_VOLTAGE_ERROR_COUNTER[cellCount - 1] > 300) {
        BMSDataPtr->Flags.THREE_SECOND_FLAG = true;
    }
    // Increment the over voltage flag if the cell voltage being read is greater than 4.2V
    if (Vin > 4.2){
        BMS.CELL_OVERVOLTAGE_FLAG[cellCount - 1] = true;
        BMS.TOTAL_CELL_ERROR_COUNTER++;

        if(UART){
            snprint(buf, 20, "Cell %d Overvoltage\n\r", totalCellCount);
            UARTSend(PC_UART, buf);
            UARTSend(PC_UART, "\n\r");
        }
    }
    // Increment the under voltage flag if the cell voltage being read is less than 3.2V
    else if (Vin < 3.2){
        BMS.CELL_UNDERVOLTAGE_FLAG[cellCount - 1] = true;
        BMS.TOTAL_CELL_ERROR_COUNTER++;

        if(UART){
            snprint(buf, 21, "Cell %d Undervoltage\n\r", totalCellCount);
            UARTSend(PC_UART, buf);
            UARTSend(PC_UART, "\n\r");
        }
    }
    // Increment the cell voltage error counter if either over or under voltage flag is detected
    if (BMS.CELL_OVERVOLTAGE_FLAG[cellCount - 1] == true || BMS.CELL_UNDERVOLTAGE_FLAG[cellCount - 1] == true){
        BMS.CELL_VOLTAGE_ERROR_COUNTER[cellCount - 1]++;
    }
    else{
        BMS.CELL_VOLTAGE_ERROR_COUNTER[cellCount - 1] = 0;
    }
    // Increment three second flag is the voltage error counter lasts longer than 3 seconds
    if (BMS.CELL_VOLTAGE_ERROR_COUNTER[cellCount - 1] > 300){
        BMSDataPtr->Flags.THREE_SECOND_FLAG =true;
    }
}


