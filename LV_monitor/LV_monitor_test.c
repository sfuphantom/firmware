/** @file sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
#include "i2c.h"
#include "het.h"
#include "gio.h"
#include "stdlib.h"

#include "sci.h"
/* Stores user character */
static unsigned char command;

/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
#define DATA_COUNT  2

#define Master_Address 0x26
#define Slave_Address  0x40
#define Slave_Word_address 0x00
#define Shunt_Voltage_Register = 0x01
#define Receive_data_setup 0x1

uint8_t TX_Data_Master[2] = { 0x10,0x11};//,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19};


uint8_t Calibration[4] = {0x14,0x00}; // 5120->0x1400


//uint8_t Calibration[4] = {0x1400}; // 5120->0x1400
//uint8_t Calibration[4] = {0x05,0x76};
uint8_t RX_Data_Master[2] = { 0 };

uint8_t TX_Data_Slave[10] = { 0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29};
uint8_t RX_Data_Slave[10] = { 0 };





/* USER CODE END */

int main(void)
{
    uint8_t RX_Data_Master1[2];
/* USER CODE BEGIN (3) */

    //Testing SCI
    _enable_IRQ();
    /* Initialize SCI module */
    sciInit();
    /* Send user prompt */
    // sciSend(sciREG, 21, (unsigned char *)"Please press a key!\r\n");

    //unsigned char* num = "77";
    //uint8 numValue[3] = {65,66,67};
    //uint8* num2Adress = &numValue;

    //uint8* = numberofChars;

//    uint8_t  number = 2;
//    char buffer[30];
//
//    uint32 numberofChars;
//    numberofChars = ltoa(number,buffer);   // here 2 means binary
////
////
//    sciSend(sciREG,numberofChars, (unsigned char*) buffer);

    //void sciSend(sciBASE_t *sci, uint32 length, uint8 * data)
    /* Await user character */
    //sciReceive(sciREG, 1, (unsigned char *)&command);
//    /* Infinite loop */
//    //while(1);


    //~~~ SCI test end


    gioInit();
    gioSetBit(gioPORTA,6,1);
    //gioToggleBit(gioPORTA, 6); //need to test this out
    int repeat = 0; int delay =1000000;
    int i = 0;
        for (i = 0; i < delay; i++);


    /* I2C Init as per GUI
     *  Mode = Master - Transmitter
     *  baud rate = 100KHz
     *  Count = 10
     *  Bit Count = 8bit
     */
    i2cInit();


    /*****************************************/
    //// Setting Calibration values
    /*****************************************/

//
    /* Configure address of Slave to talk to */
    i2cSetSlaveAdd(i2cREG1, Slave_Address);

    /* Set direction to Transmitter */
    /* Note: Optional - It is done in Init */
    i2cSetDirection(i2cREG1, I2C_TRANSMITTER);

    /* Configure Data count */
    /* Slave address + Word address write operation before reading */
    i2cSetCount(i2cREG1,3);

    /* Set mode as Master */
    i2cSetMode(i2cREG1, I2C_MASTER);

    /* Set Stop after programmed Count */
    i2cSetStop(i2cREG1);

    /* Transmit Start Condition */
    i2cSetStart(i2cREG1);

    /* Send the Word Address */
    i2cSendByte(i2cREG1, 0x05); //0x05 is Calibration register

    i2cSend(i2cREG1,2,Calibration);
    //i2cSend(i2cBASE_t *i2c, uint32 length, uint8 * data);

    /* Wait until Bus Busy is cleared */
    while(i2cIsBusBusy(i2cREG1) == true);

    /* Wait until Stop is detected */
    while(i2cIsStopDetected(i2cREG1) == 0);

    /* Clear the Stop condition */
    i2cClearSCD(i2cREG1);

    while(i2cIsMasterReady(i2cREG1) != true); //added


    //~~~~~~~~~~~~~~~~

while(true){

    ///////////////////////////////////////////////////////////////
    //        Master Receive Functionality                      //
    ///////////////////////////////////////////////////////////////

    /*****************************************/
    //// Setup Slave to receving the data
    /*****************************************/

    /* wait until MST bit gets cleared, this takes
     * few cycles after Bus Busy is cleared */
    //while(i2cIsMasterReady(i2cREG1) != true); //added

    /* Configure address of Slave to talk to */
    i2cSetSlaveAdd(i2cREG1, Slave_Address);

    /* Set direction to Transmitter */
    /* Note: Optional - It is done in Init */
    i2cSetDirection(i2cREG1, I2C_TRANSMITTER);

    /* Configure Data count */
    /* Slave address + Word address write operation before reading */
    i2cSetCount(i2cREG1,1);

    /* Set mode as Master */
    i2cSetMode(i2cREG1, I2C_MASTER);

    /* Set Stop after programmed Count */
    i2cSetStop(i2cREG1);

    /* Transmit Start Condition */
    i2cSetStart(i2cREG1);

    /* Send the Word Address */
    i2cSendByte(i2cREG1, 0x02);//setting the slave register to read from, 0x02 is bus voltage
    //i2cSendByte(i2cREG1, 0x01);//setting the slave register to read from, 0x01 is shunt voltage
    //i2cSendByte(i2cREG1, 0x00);

    /* Wait until Bus Busy is cleared */
    while(i2cIsBusBusy(i2cREG1) == true);

    /* Wait until Stop is detected */
    while(i2cIsStopDetected(i2cREG1) == 0);

    /* Clear the Stop condition */
    i2cClearSCD(i2cREG1);

    /*****************************************/
    //// Start receving the data From Slave
    /*****************************************/

    /* wait until MST bit gets cleared, this takes
     * few cycles after Bus Busy is cleared */
    while(i2cIsMasterReady(i2cREG1) != true);

    /* Configure address of Slave to talk to */
    i2cSetSlaveAdd(i2cREG1, Slave_Address);

    /* Set direction to receiver */
    i2cSetDirection(i2cREG1, I2C_RECEIVER);

    /* Configure Data count */
    /* Note: Optional - It is done in Init, unless user want to change */
    i2cSetCount(i2cREG1, DATA_COUNT); //only need to receive 1 value

    /* Set mode as Master */
    i2cSetMode(i2cREG1, I2C_MASTER);

    /* Set Stop after programmed Count */
    i2cSetStop(i2cREG1);

    /* Transmit Start Condition */
    i2cSetStart(i2cREG1);

    /* Tranmit DATA_COUNT number of data in Polling mode */
    i2cReceive(i2cREG1, DATA_COUNT, RX_Data_Master1); //location of stored data?

    /* Wait until Bus Busy is cleared */
    while(i2cIsBusBusy(i2cREG1) == true);

    /* Wait until Stop is detected */
    while(i2cIsStopDetected(i2cREG1) == 0);

    /* Clear the Stop condition */
    i2cClearSCD(i2cREG1);


//    char buffer[10];
//    uint32 numberofChars;
//    numberofChars = ltoa(RX_Data_Master1[0],buffer);   // here 2 means binary
//    sciSend(sciREG,numberofChars, (unsigned char*) buffer);
//
//    char buffer2[10];
//    uint32 numberofChars2;
//    numberofChars2 = ltoa(RX_Data_Master1[1],buffer2);   // here 2 means binary
//    sciSend(sciREG,numberofChars2, (unsigned char*) buffer2);




    uint16 MSB_data = RX_Data_Master1[0];
    uint16 LSB_data = RX_Data_Master1[1];
    MSB_data <<=8;
    uint16 data = MSB_data | LSB_data;

    float dataAfterMath = data*1.25;

    /*  DECIMAL      LSB Value    VALUE
     * Shunt Voltage *2.5uV   => Voltage(mV)
     * Bus Voltage   *1.25mv  => Voltage (V)
     * Current       *1mA     => Current(A)
     * Power         *25mW    => Watt(W)
     */

    char buffer3[10];
    uint32 numberofChars3;
    numberofChars3 = ltoa(dataAfterMath,buffer3);   // here 2 means binary
    sciSend(sciREG,12, (unsigned char*) "bus voltage = ");
    sciSend(sciREG,numberofChars3, (unsigned char*) buffer3);
    sciSend(sciREG,2, (unsigned char*) "\r\n");


   // while(i2cIsMasterReady(i2cREG1) != true);

    for (i = 0; i < delay; i++);



//COMENT UNTIL HERE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//    //FOR current
//
//    /*****************************************/
//    //// Setup Slave to receving the data FOR CURRENT
//    /*****************************************/
//
    /* wait until MST bit gets cleared, this takes
     * few cycles after Bus Busy is cleared */
    while(i2cIsMasterReady(i2cREG1) != true); //added

    /* Configure address of Slave to talk to */
    i2cSetSlaveAdd(i2cREG1, Slave_Address);

    /* Set direction to Transmitter */
    /* Note: Optional - It is done in Init */
    i2cSetDirection(i2cREG1, I2C_TRANSMITTER);

    /* Configure Data count */
    /* Slave address + Word address write operation before reading */
    i2cSetCount(i2cREG1,1);

    /* Set mode as Master */
    i2cSetMode(i2cREG1, I2C_MASTER);

    /* Set Stop after programmed Count */
    i2cSetStop(i2cREG1);

    /* Transmit Start Condition */
    i2cSetStart(i2cREG1);

    /* Send the Word Address */
    i2cSendByte(i2cREG1, 0x04);//setting the slave register to read from, 0x04 is current

    //i2cSend(i2cREG1,2,TX_Data_Master);
    //i2cSend(i2cBASE_t *i2c, uint32 length, uint8 * data);

    /* Wait until Bus Busy is cleared */
    while(i2cIsBusBusy(i2cREG1) == true);

    /* Wait until Stop is detected */
    while(i2cIsStopDetected(i2cREG1) == 0);

    /* Clear the Stop condition */
    i2cClearSCD(i2cREG1);

    /*****************************************/
    //// Start receving the data From Slave
    /*****************************************/

    /* wait until MST bit gets cleared, this takes
     * few cycles after Bus Busy is cleared */
    while(i2cIsMasterReady(i2cREG1) != true);

    /* Configure address of Slave to talk to */
    i2cSetSlaveAdd(i2cREG1, Slave_Address);

    /* Set direction to receiver */
    i2cSetDirection(i2cREG1, I2C_RECEIVER);

    /* Configure Data count */
    /* Note: Optional - It is done in Init, unless user want to change */
    i2cSetCount(i2cREG1, DATA_COUNT); //only need to receive 1 value

    /* Set mode as Master */
    i2cSetMode(i2cREG1, I2C_MASTER);

    /* Set Stop after programmed Count */
    i2cSetStop(i2cREG1);

    /* Transmit Start Condition */
    i2cSetStart(i2cREG1);

    /* Tranmit DATA_COUNT number of data in Polling mode */
    i2cReceive(i2cREG1, DATA_COUNT, RX_Data_Master); //location of stored data?

    /* Wait until Bus Busy is cleared */
    while(i2cIsBusBusy(i2cREG1) == true);

    /* Wait until Stop is detected */
    while(i2cIsStopDetected(i2cREG1) == 0);

    /* Clear the Stop condition */
    i2cClearSCD(i2cREG1);



    uint16 MSB_data2 = RX_Data_Master[0];
    uint16 LSB_data2 = RX_Data_Master[1];
    MSB_data2 <<=8;
    uint16 data2 = MSB_data2 | LSB_data2;

    float dataAfterMath2 = data2;

    /*  DECIMAL      LSB Value    VALUE
     * Shunt Voltage *2.5uV   => Voltage(mV)
     * Bus Voltage   *1.25mv  => Voltage (V)
     * Current       *1mA     => Current(A)
     * Power         *25mW    => Watt(W)
     */


    char buffer2[10];
    uint32 numberofChars2;
    numberofChars2 = ltoa(dataAfterMath2,buffer2);   // here 2 means binary
    sciSend(sciREG,12, (unsigned char*) "current = ");
    sciSend(sciREG,numberofChars2, (unsigned char*) buffer2);
    sciSend(sciREG,1, (unsigned char*) "  ");


while(i2cIsMasterReady(i2cREG1) != true); //added

}
//
//    //FOR POWER
//
//    /*****************************************/
//    //// Setup Slave to receving the data FOR CURRENT
//    /*****************************************/
//
//    /* wait until MST bit gets cleared, this takes
//     * few cycles after Bus Busy is cleared */
//    while(i2cIsMasterReady(i2cREG1) != true); //added
//
//    /* Configure address of Slave to talk to */
//    i2cSetSlaveAdd(i2cREG1, Slave_Address);
//
//    /* Set direction to Transmitter */
//    /* Note: Optional - It is done in Init */
//    i2cSetDirection(i2cREG1, I2C_TRANSMITTER);
//
//    /* Configure Data count */
//    /* Slave address + Word address write operation before reading */
//    i2cSetCount(i2cREG1,1);
//
//    /* Set mode as Master */
//    i2cSetMode(i2cREG1, I2C_MASTER);
//
//    /* Set Stop after programmed Count */
//    i2cSetStop(i2cREG1);
//
//    /* Transmit Start Condition */
//    i2cSetStart(i2cREG1);
//
//    /* Send the Word Address */
//    i2cSendByte(i2cREG1, 0x03);//setting the slave register to read from, 0x03 is power
//
//    //i2cSend(i2cREG1,2,TX_Data_Master);
//    //i2cSend(i2cBASE_t *i2c, uint32 length, uint8 * data);
//
//    /* Wait until Bus Busy is cleared */
//    while(i2cIsBusBusy(i2cREG1) == true);
//
//    /* Wait until Stop is detected */
//    while(i2cIsStopDetected(i2cREG1) == 0);
//
//    /* Clear the Stop condition */
//    i2cClearSCD(i2cREG1);
//
//    /*****************************************/
//    //// Start receving the data From Slave
//    /*****************************************/
//
//    /* wait until MST bit gets cleared, this takes
//     * few cycles after Bus Busy is cleared */
//    while(i2cIsMasterReady(i2cREG1) != true);
//
//    /* Configure address of Slave to talk to */
//    i2cSetSlaveAdd(i2cREG1, Slave_Address);
//
//    /* Set direction to receiver */
//    i2cSetDirection(i2cREG1, I2C_RECEIVER);
//
//    /* Configure Data count */
//    /* Note: Optional - It is done in Init, unless user want to change */
//    i2cSetCount(i2cREG1, DATA_COUNT); //only need to receive 1 value
//
//    /* Set mode as Master */
//    i2cSetMode(i2cREG1, I2C_MASTER);
//
//    /* Set Stop after programmed Count */
//    i2cSetStop(i2cREG1);
//
//    /* Transmit Start Condition */
//    i2cSetStart(i2cREG1);
//
//    /* Tranmit DATA_COUNT number of data in Polling mode */
//    i2cReceive(i2cREG1, DATA_COUNT, RX_Data_Master); //location of stored data?
//
//    /* Wait until Bus Busy is cleared */
//    while(i2cIsBusBusy(i2cREG1) == true);
//
//    /* Wait until Stop is detected */
//    while(i2cIsStopDetected(i2cREG1) == 0);
//
//    /* Clear the Stop condition */
//    i2cClearSCD(i2cREG1);


    asm(" nop");
    asm(" nop");
    asm(" nop");

    while(1);

/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
void sciNotification(sciBASE_t *sci, uint32 flags)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (29) */
    /* Echo received character */
    sciSend(sci, 1,(unsigned char *)&command);
    /* Await further character */
    sciReceive(sci, 1,(unsigned char *)&command);

//    ESM interrupt notification (not ued but must be provided)
//    void esmGroup1Notification(int bit)
//    {
//        return;
//    }
//    void esmGroup2Notification(int bit)
//    {
//        return;
//    }
}
/* USER CODE END */
