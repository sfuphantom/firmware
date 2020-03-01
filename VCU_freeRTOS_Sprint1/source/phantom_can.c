/*
 * phantom_vcu.c
 *
 *  Created on: Feb 25, 2020
 *      Author: XingLu Wang
 */
#include "phantom_can.h"
#include "can.h"

#define D_COUNT 8
uint32 cnt = 0, error = 0, tx_done = 0;
char bms_data[D_COUNT] = { 0 };
char *bms_ptr = &bms_data[0];

volatile uint32_t transmitCounter = 0;
volatile uint32_t receiveVCUCounter = 0;

// Input an array of bytes of max size 8 to send over CAN to the BMS
void CANSend(uint8 can_msg[]){

    uint8 tx_data[D_COUNT] = {0};
    memcpy(tx_data, can_msg, D_COUNT);

    const uint8 *tx_ptr = &tx_data[0];

    for (cnt = 0; cnt < D_COUNT; cnt++)
        {
            canTransmit(canREG1, canMESSAGE_BOX1, tx_ptr); /* transmitting 8 different chunks 1 by 1 */
            while (tx_done == 0)
            {
            }; /* ... wait until transmit request is through */
            tx_done = 0;
            tx_ptr += 8; /* next chunk ...*/
        }
}

void canMessageNotification(canBASE_t *node, uint32 messageBox)
{

    //The following is executed when transmission is successful
    if ((node == canREG1) && (messageBox == canMESSAGE_BOX1))
    {
        tx_done = 1;
        transmitCounter++;
    }

    //The following is executed when reception is successful
    if ((node == canREG1) && (messageBox == canMESSAGE_BOX2))
    {
        while (!canIsRxMessageArrived(canREG1, canMESSAGE_BOX2))
            ;

        canGetData(canREG1, canMESSAGE_BOX2, bms_ptr); /* copy to RAM */
        bms_ptr += 8;
        receiveVCUCounter++;
    }
}

// Returns data received from the BMS
char getBMSMSG(void)
{
    return *bms_data;
}



