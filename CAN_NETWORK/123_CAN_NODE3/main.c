/*
 * main2.c  - From Phantom REPO
 *
 *  Created on: Jan 18, 2020
 *      Author: Junaid
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


#define D_SIZE 6
#define MSG_ID1 0x294
#define MSG_ID2 0x555
#define MSG_ID3 0x64A

uint8_t tx_Data[D_SIZE]={'N','O','D','E','-','3'};
uint8_t rx_DataNode1[D_SIZE] ={0};
uint8_t rx_DataNode2[D_SIZE] ={0};
uint8_t *tx_ptr  = &tx_Data[0];
uint8_t *rx_ptr1 = &rx_DataNode1[0];
uint8_t *rx_ptr2 = &rx_DataNode2[0];



/*
 * Transmission/Receive Error Flag
 * Message object 2 recieved messsage flag
 * Message object 3 received message flag
 */
volatile bool errFlag =0; // Initially, no errors
volatile bool messageSent =0;
volatile bool sentOnce = 0;
volatile bool RXFlag2 =0;
volatile bool RXFlag3 =0;
volatile uint32_t messageBox1Count =0;
volatile uint32_t messageBox2Count =0;
volatile uint32_t messageBox3Count =0;
volatile int bitCounter=0;



void CAN_Init(void);
void CANIntHandler(void);

tCANBitClkParms controllerBitTiming;
tCANMsgObject canMsgObject1;
tCANMsgObject canMsgObject2;
tCANMsgObject canMsgObject3;

int main(void)
{
    // Set the system clock to be generated directly from the external oscillator
    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ); // This will run the Tm4c at 80 MHz

    CAN_Init();

    // Enable Global Interrupts
    IntMasterEnable();

    /*
    * Load MsgObject2 & MsgObject3 into CAN0 message object 2 & 3.
    * Once loaded, CAN0 will receive any messages with MsgID = 2 & MsgID=1 into
    *  message objects 2 & 3, and request for servicing through RX-interrupt.
    */
    CANMessageSet(CAN0_BASE, 1, &canMsgObject1, MSG_OBJ_TYPE_TX);
    CANMessageSet(CAN0_BASE, 2, &canMsgObject2, MSG_OBJ_TYPE_RX);
    CANMessageSet(CAN0_BASE, 3, &canMsgObject3, MSG_OBJ_TYPE_RX);


    while(1){
        if(messageSent && (bitCounter<=sizeof(tx_Data)) && (sentOnce==0)){
            tx_ptr += 8;
            CANMessageSet(CAN0_BASE,1, &canMsgObject1, MSG_OBJ_TYPE_TX);
            messageSent =0;
        }
        if(RXFlag2){
            canMsgObject2.pui8MsgData = rx_ptr1;
            CANMessageGet(CAN0_BASE, 2, &canMsgObject2, 1);
            RXFlag2 = 0;
            rx_ptr1 += 8;

        }
        if(RXFlag3){
            canMsgObject3.pui8MsgData = rx_ptr2;
            CANMessageGet(CAN0_BASE, 3, &canMsgObject3, 1);
            RXFlag3 = 0;
            rx_ptr2 += 8;
        }

    }



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
      /*
       * Set CAN0's bit rate for CAN bus - setting up the CAN bus timing.
       * Setting CAN0 bit rate @ 500KHz
       * SysCtlClockGet() used to determine clock rate used for clocking CAN module
       */
      CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 100000);


      // Enable interrupts on the CAN peripheral.
       /*
        * Enable Interrupts sources for CAN0
        * CAN_INT_MASTER = Enables CAN0 to generate interrupts
        * CAN_INT_ERROR = Enables CAN0 to generate Error interrupts
        * CAN_INT_STATUS = Enable CAN0 to generate interrupts on successful Transmission and/or Reception of messages
        */
      CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);

      // Enable the NVIC interrupt; Enable the CAN interrupt on the processor (NVIC).
      IntEnable(INT_CAN0);

      CANEnable(CAN0_BASE);



      /* CAN Hardware Configured Completed here. */

      /*
       * Initialize  canMsgObject1 with the MessageID and Transmit message
       * canMsgObject1 MsgID = 3
       * CanMsgObject1 Mask for filtering msg, same as NODE1 and NODE2
       */
      canMsgObject1.ui32MsgID = MSG_ID3;
      canMsgObject1.ui32MsgIDMask = 0;
      canMsgObject1.ui32Flags = (MSG_OBJ_TX_INT_ENABLE);
      canMsgObject1.ui32MsgLen = sizeof(tx_Data);
      canMsgObject1.pui8MsgData = tx_ptr;

      /*
      * Initialize  canMsgObject2 with the MessageID = 1, for receiving message from Node1
      * canMsgObject1 MsgID = 1
      * CanMsgObject1 Mask for filtering msg, same as NODE1 and NODE2
      */


      canMsgObject2.ui32MsgID = MSG_ID1;
      canMsgObject2.ui32MsgIDMask = 0x7FF;
      canMsgObject2.ui32Flags = (MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER);
      canMsgObject2.ui32MsgLen = 6;


      /*
      * Initialize  canMsgObject2 with the MessageID = 2, for receiving message from Node2
      * canMsgObject1 MsgID = 1
      * CanMsgObject1 Mask for filtering msg, same as NODE1 and NODE2
      */
      canMsgObject3.ui32MsgID = MSG_ID2;
      canMsgObject3.ui32MsgIDMask = 0x7FF;
      canMsgObject3.ui32Flags = (MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER);
      canMsgObject3.ui32MsgLen = 6;




}
void CANIntHandler(void){


    CANIntDisable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);
    /*
     * Read CAN interrupt status to find the cause of interrupt
     */
    uint32_t intCause = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE); // Cause of Interrupt; Either Controller Status or Message Object caused interrupt
    uint32_t intCause2 = CANIntStatus(CAN0_BASE, CAN_INT_STS_OBJECT); // returns a bit mask indicating which message objects have pending interrupts

    if(intCause == CAN_INT_INTID_STATUS){



        intCause = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);


    }else if(intCause==1){
               /*
                * if Interrupt was caused by CAN message object 1 - execute this block
                * Message object 1 is configured to Transmit a message on the CAN bus
                * Therefore, an interrupt set by message Object 1 means transmission complete
                * And Successful.
                */

            CANIntClear(CAN0_BASE, 1);

            if(bitCounter<sizeof(tx_Data) && (messageSent == 0)){ // Only transmitting 6 characters right now; Will fix it
               bitCounter++;
               // Clear any error flags has the message was successfully sent
               errFlag = 0;
               messageBox1Count++;
               messageSent=1;
            }else if(bitCounter==sizeof(tx_Data)){

               bitCounter=0;
               messageBox1Count++;
               tx_ptr = &tx_Data[0];
               //CANMessageSet(CAN0_BASE, 1, &canMsgObject1, MSG_OBJ_TYPE_TX);
               messageSent=0;
               // Clear any error flags has the message was successfully sent
               errFlag = 0;
               sentOnce = 1;

               }else{
                   errFlag=1;
               }

   }else if(intCause==2){
               /*
               * If Interrupt was caused by CAN message object 2 - execute this block
               * Message object 2 is configured to receive a message on the CAN bus
               * Therefore, an interrupt set by message Object 3 means a message has been received
               */
               CANIntClear(CAN0_BASE, 2);
               intCause = CANStatusGet(CAN0_BASE, CAN_STS_NEWDAT);
               if(intCause==2){

                   messageBox2Count++;
                   RXFlag2 = 1;
                   errFlag = 0;
               }
   }else if(intCause==3){
                  /*
                  * If Interrupt was caused by CAN message object 3 - execute this block
                  * Message object 3 is configured to receive a message on the CAN bus
                  * Therefore, an interrupt set by message Object 3 means a message has been received
                  */


           CANIntClear(CAN0_BASE, 3);
           intCause = CANStatusGet(CAN0_BASE, CAN_STS_NEWDAT);
           if(intCause==3){
               messageBox3Count++;
               RXFlag3 =1;
               errFlag =0;
           }

   }


    CANIntEnable(CAN0_BASE, (CAN_INT_MASTER | CAN_INT_ERROR |  CAN_INT_STATUS));
}



