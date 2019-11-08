/**
 * main.c
 */
#include <stdbool.h>
#include <stdint.h>
#include "driverlib/sysctl.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/can.h"
#include "inc/hw_ints.h"
#include "inc/hw_can.h"
#include "driverlib/interrupt.h"


/*
 * Define two CAN message objects;
 * MessageObject1  = Tx
 * MessageObject2  = RX Message from Node 1
 * MessageObject3  = RX Message from Node 2
 *
 */

tCANMsgObject canMsgObject1;
tCANMsgObject canMsgObject2;
tCANMsgObject canMsgObject3;

#define D_SIZE 6
uint8_t tx_Data[D_SIZE]={'N','O','D','E','-','3'};
uint8_t rx_DataNode1[D_SIZE]={0};
uint8_t rx_DataNode2[D_SIZE]={0};

uint32_t cnt=0, tx_done =0;

/*
 * Transmission/Receive Error Flag
 * Message object 2 recieved messsage flag
 * Message object 3 received message flag
 */
volatile bool errFlag =0; // Initially, no errors


void CAN_Init(void);
void CANIntHandler(void);


int main(void)
{

    // Set the system clock to be generated directly from the external oscillator
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    CAN_Init();

    // Enable Global Interrupts
    IntMasterEnable();

    /*
    * Load MsgObject2 & MsgObject3 into CAN0 message object 2 & 3.
    * Once loaded, CAN0 will receive any messages with MsgID = 2 & MsgID=1 into
    *  message objects 2 & 3, and request for servicing through RX-interrupt.
    */

    CANMessageSet(CAN0_BASE, 2, &canMsgObject2, MSG_OBJ_TYPE_RX);


    CANMessageSet(CAN0_BASE, 3, &canMsgObject3, MSG_OBJ_TYPE_RX);


    CANMessageSet(CAN0_BASE, 1, &canMsgObject1, MSG_OBJ_TYPE_TX);
    while(!tx_done); // wait until transmit completed;


    while(1);

}

void CAN_Init(void){

    // Enable clock access to Port B to configure its pins for CAN module
       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
       while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB));

    // Enable clock access to CAN0
       SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
       while(!SysCtlPeripheralReady(SYSCTL_PERIPH_CAN0));

    /* Configure GPIO pins for CAN mode  */

      // Configure PB4 as CAN0RX
      GPIOPinConfigure(GPIO_PB4_CAN0RX);
      // Configure PB5 as CAN0TX
      GPIOPinConfigure(GPIO_PB5_CAN0TX);

      GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);

      CANInit(CAN0_BASE);

      CANDisable(CAN0_BASE);

      /*
      * Set CAN0's bit rate for CAN bus - setting up the CAN bus timing.
      * Setting CAN0 bit rate @ 500KHz
      * SysCtlClockGet() used to determine clock rate used for clocking CAN module
      */
      CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);

      /*
       * Initialize  canMsgObject1 with the MessageID and Transmit message
       * canMsgObject1 MsgID = 3
       * CanMsgObject1 Mask for filtering msg, same as NODE1 and NODE2
       */
      canMsgObject1.ui32MsgID = 0x3;
      canMsgObject1.ui32MsgIDMask = 0x000007FF;
      canMsgObject1.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
      canMsgObject1.ui32MsgLen = sizeof(tx_Data);
      canMsgObject1.pui8MsgData = &tx_Data[0];


      /*
      * Initialize  canMsgObject2 with the MessageID = 1, for receiving message from Node1
      * canMsgObject1 MsgID = 1
      * CanMsgObject1 Mask for filtering msg, same as NODE1 and NODE2
      */
      canMsgObject2.ui32MsgID = 0x1;
      canMsgObject2.ui32MsgIDMask = 0x000007FF;
      canMsgObject2.ui32Flags = (MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER);
      canMsgObject2.ui32MsgLen = sizeof(rx_DataNode1);
      canMsgObject2.pui8MsgData = &rx_DataNode1[0];


      /*
      * Initialize  canMsgObject2 with the MessageID = 1, for receiving message from Node1
      * canMsgObject1 MsgID = 1
      * CanMsgObject1 Mask for filtering msg, same as NODE1 and NODE2
      */
      canMsgObject3.ui32MsgID = 0x2;
      canMsgObject3.ui32MsgIDMask = 0x000007FF;
      canMsgObject3.ui32Flags = MSG_OBJ_RX_INT_ENABLE;
      canMsgObject3.ui32MsgLen = sizeof(rx_DataNode2);
      canMsgObject3.pui8MsgData = &rx_DataNode2[0];


      CANEnable(CAN0_BASE);

      // Enable the NVIC interrupt
      IntEnable(INT_CAN0);
      CANIntClear(CAN0_BASE, CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE));

      /*
       * Enable Interrupts sources for CAN0
       * CAN_INT_MASTER = Enables CAN0 to generate interrupts
       * CAN_INT_ERROR = Enables CAN0 to generate Error interrupts
       * CAN_INT_STATUS = Enable CAN0 to generate interrupts on successful Transmission and/or Reception of messages
       *
       */
       CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);

}
void CANIntHandler(void){

    /*
     * Read CAN interrupt status to find the cause of interrupt
     */
    uint32_t intStatus = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);

    CANIntClear(CAN0_BASE, intStatus);

   if(intStatus == CAN_INT_INTID_STATUS){
       // Execute this block if the interrupt caused by CAN controller status
       // Get the status of the controller using CANStatusGet
       // Return from it is a field of status error bits - read API documentation for details about the
       // error status bits.
       // Reading the status clears the interrupt.

       intStatus = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);

       //Set a flag to indicate some error may have occurred.
       errFlag = 1;
   }else if (intStatus==(uint32_t)1){
       /*
        * if Interrupt was caused by CAN message object 1 - execute this block
        * Message object 1 is configured to Transmit a message on the CAN bus
        * Therefore, an interrupt set by message Object 1 means transmission complete
        * And Successful.
        *
        */
       tx_done=1;

       // Clear any error flags has the message was successfully sent
       errFlag = 0;

       // Clear the flag
       CANIntClear(CAN0_BASE, 1);
   }else if(intStatus==(uint32_t)2){
           /*
           * If Interrupt was caused by CAN message object 2 - execute this block
           * Message object 1 is configured to receive a message on the CAN bus
           * Therefore, an interrupt set by message Object 2 means a message has been received
           *
           */
           CANMessageGet(CAN0_BASE, 2, &canMsgObject2, 1);
           CANIntClear(CAN0_BASE, 2);

   }else if(intStatus==(uint32_t)3){
                  /*
                  * If Interrupt was caused by CAN message object 2 - execute this block
                  * Message object 1 is configured to receive a message on the CAN bus
                  * Therefore, an interrupt set by message Object 2 means a message has been received
                  *
                  */
           CANMessageGet(CAN0_BASE, 2, &canMsgObject3, 1);
           CANIntClear(CAN0_BASE, 3);
   }else{
        // Fake/fault interrupt can be handled here.
   }
}
