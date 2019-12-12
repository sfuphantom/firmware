/*
 * main.c
 *
 *  Created on: Dec 10, 2019
 *      Author: Junaid
 */
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "driverlib/can.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "inc/hw_can.h"



#define RCV_ID1  1
#define RCV_ID2  2
#define XMT_ID   3

uint8_t static RCVData1[6]; // Received Data from Node 1 - for interrupt handler
uint8_t static RCVData2[6]; // Received Data from Node 2 - for interrupt handler

uint8_t static Processed_Node1 [6];
uint8_t static Processed_Node2 [6];

int static MailFlag1; // Set when new data arrives from Node 1
int static MailFlag2; // Set when new data arrives from Node 2

int volatile RCV1Count = 0;
int volatile RCV2Count = 0;


/*
 * Configures one of the 32 message objects.
 * The configured message object with ObjectID will
 * receive message frames with identifier of MessageID
 */
void static CAN0_Setup_Message_Object(uint32_t MesssageID, uint32_t MessageFlags,
                                      uint32_t MessageLength, uint8_t *MessageData,
                                      uint32_t ObjectID, tMsgObjType eMsgType){
    tCANMsgObject xTempObject;
    xTempObject.ui32MsgID = MesssageID; // 11 or 29 bit ID
    xTempObject.ui32MsgLen = MessageLength;
    xTempObject.pui8MsgData = MessageData;
    xTempObject.ui32Flags = MessageFlags;
    CANMessageSet(CAN0_BASE, ObjectID, &xTempObject, eMsgType);
}

void CAN_Init(void){

    MailFlag1 = false;
    MailFlag2 = false;

     // Enable clock access to CAN0
     SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
     while(!SysCtlPeripheralReady(SYSCTL_PERIPH_CAN0));

      // Enable clock access to CAN0
      SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
      while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE));

      // Configure PB4 as CAN0RX
      GPIOPinConfigure(GPIO_PE4_CAN0RX);
      // Configure PB5 as CAN0TX
      GPIOPinConfigure(GPIO_PE5_CAN0TX);

      GPIOPinTypeCAN(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);

      CANInit(CAN0_BASE);
      CANBitRateSet(CAN0_BASE, 800000000, 500000);
      CANEnable(CAN0_BASE);
      CANIntEnable(CAN0_BASE, CAN_INT_MASTER|CAN_INT_ERROR |CAN_INT_STATUS);

      // Configure Receive Box.
      CAN0_Setup_Message_Object(RCV_ID2,MSG_OBJ_RX_INT_ENABLE, 6, NULL, RCV_ID2, MSG_OBJ_TYPE_RX);
      CAN0_Setup_Message_Object(RCV_ID1,MSG_OBJ_RX_INT_ENABLE, 6, NULL, RCV_ID1, MSG_OBJ_TYPE_RX);
      IntEnable(INT_CAN0);
}

/*
 * Interrupt is generated when a frame of the appropriate ID is received.
 * The interrupt handler will search the 32 possible message objects for the one that caused the interrupt.
 */
void CANIntHandler(void){

    uint8_t data[6];
    int i;
    uint32_t uiIntStatus, uiIDStatus;
    tCANMsgObject xTempMsgObject;
    xTempMsgObject.pui8MsgData = data;
    uiIntStatus = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE); // Cause of interrupt?

    if(uiIntStatus & CAN_INT_INTID_STATUS){ // Received new data?
        uiIDStatus = CANIntStatus(CAN0_BASE, CAN_STS_NEWDAT);
        for(i=0; i<32; i++){ // test every bit of the mask
            if( (0x1 << i) & uiIDStatus ){ // if active, get data
                CANMessageGet(CAN0_BASE, (i+1), &xTempMsgObject, true);
                if(xTempMsgObject.ui32MsgID == RCV_ID1){
                    RCVData1[0] = data[0];
                    RCVData1[1] = data[1];
                    RCVData1[2] = data[2];
                    RCVData1[3] = data[3];
                    RCVData1[4] = data[4];
                    RCVData1[5] = data[5];
                    MailFlag1 = true;
                }
                if(xTempMsgObject.ui32MsgID == RCV_ID2){
                    RCVData2[0] = data[0];
                    RCVData2[1] = data[1];
                    RCVData2[2] = data[2];
                    RCVData2[3] = data[3];
                    RCVData2[4] = data[4];
                    RCVData2[5] = data[5];
                    MailFlag2 = true;
                }
            }
        }
    }
    CANIntClear(CAN0_BASE, uiIntStatus); // Acknowledge the interrupt.
}

/*
 * Use the Mailbox receiver to receive a message
 */
int CAN0_GetMailNonBlock(uint8_t data[6]){
    if(MailFlag1){
        data[0] = RCVData1[0];
        data[1] = RCVData1[1];
        data[2] = RCVData1[2];
        data[3] = RCVData1[3];
        data[4] = RCVData1[4];
        data[5] = RCVData1[5];
        MailFlag1 = false;
        return true;
    }
    if(MailFlag2){
        data[0] = RCVData2[0];
        data[1] = RCVData2[1];
        data[2] = RCVData2[2];
        data[3] = RCVData2[3];
        data[4] = RCVData2[4];
        data[5] = RCVData2[5];
        MailFlag2 = false;
        return true;
    }
    return false;
}

/*int CAN0_CheckMail(void){
    return MailFlag;
}
*/
void CAN0_SendData(uint8_t data[6]){
    CAN0_Setup_Message_Object(XMT_ID, NULL, 6, data, XMT_ID, MSG_OBJ_TYPE_TX);
}

int main(void){

    // Set the system clock to be generated directly from the external oscillator
      SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ); // This will run the Tm4c at 80 MHz

    // Initialize CAN Controller
      CAN_Init();

   // Enable Interrupts Globally

      IntMasterEnable();

      while(1){

          if(CAN0_GetMailNonBlock(Processed_Node1)){
              RCV1Count++;
          }
          if(CAN0_GetMailNonBlock(Processed_Node2)){
              RCV2Count++;
          }
      }

}
