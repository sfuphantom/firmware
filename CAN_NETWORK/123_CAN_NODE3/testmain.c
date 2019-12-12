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


#define D_SIZE 6
#define MSG_ID1 0x00000001
#define MSG_ID2 0x00000002
#define MSG_ID3 0x00000003

#define MSG_BOX1 (0x00000001)
#define MSG_BOX2 (0x00000002)
#define MSG_BOX3 (0x00000003)


uint8_t tx_Data[D_SIZE]={'N','O','D','E','-','3'};
uint8_t *tx_ptr  = &tx_Data[0];

uint8_t rx_DataNode1[D_SIZE] ={0};
uint8_t rx_DataNode2[D_SIZE] ={0};
uint8_t *rx_ptr1 = &rx_DataNode1[0];
uint8_t *rx_ptr2 = &rx_DataNode2[0];



/*
 * Transmission/Receive Error Flag
 * Message object 2 recieved messsage flag
 * Message object 3 received message flag
 */
static volatile bool errFlag =0; // Initially, no errors
static volatile bool messageSent =0;
static volatile bool RXFlag2 =0;
static volatile bool RXFlag3 =0;
static volatile uint32_t messageBox1Count =0;
static volatile uint32_t messageBox2Count =0;
static volatile uint32_t messageBox3Count =0;
static volatile uint32_t errCounter =0;
static volatile int TXbitCounter=0;
static volatile int RXbitCounter=0;


void CAN_Init(void);
void CANIntHandler(void);

static  tCANMsgObject canMsgObject1;
static  tCANMsgObject canMsgObject2;
static  tCANMsgObject canMsgObject3;



int main(void)
{
    // Set the system clock to be generated directly from the external oscillator
    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ); // This will run the Tm4c at 80 Mhz


    CAN_Init();

    // Enable Global Interrupts
    IntMasterEnable();

    /*
    * Load MsgObject2 & MsgObject3 into CAN0 MessageBoxes 2 & 3.
    * Once loaded, CAN0 will receive any messages with MsgID = 1 & MsgID=2 into
    *  message objects 2 & 3, and request for servicing through RX-interrupt.
    */
    CANMessageSet(CAN0_BASE, MSG_ID1, &canMsgObject1, MSG_OBJ_TYPE_TX);
    CANMessageSet(CAN0_BASE, MSG_ID2, &canMsgObject2, MSG_OBJ_TYPE_RX);
    CANMessageSet(CAN0_BASE, MSG_ID3, &canMsgObject3, MSG_OBJ_TYPE_RX);


    while(1){
        if(messageSent && (TXbitCounter<=sizeof(tx_Data))){
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
      CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);

      // Enable interrupts on the CAN peripheral.
       /*
        * Enable Interrupts sources for CAN0
        * CAN_INT_MASTER = Enables CAN0 to generate interrupts
        * CAN_INT_ERROR = Enables CAN0 to generate Error interrupts
        * CAN_INT_STATUS = Enable CAN0 to generate interrupts on successful Transmission and/or Reception of messages
        */
      CANIntEnable(CAN0_BASE, (CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS));

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
      canMsgObject1.ui32MsgIDMask = 0x000007FF;
      canMsgObject1.ui32Flags = (MSG_OBJ_TX_INT_ENABLE);
      canMsgObject1.ui32MsgLen = sizeof(tx_Data);
      canMsgObject1.pui8MsgData = tx_ptr;

      /*
      * Initialize  canMsgObject2 with the MessageID = 1, for receiving message from Node1
      * canMsgObject1 MsgID = 1
      * CanMsgObject1 Mask for filtering msg, same as NODE1 and NODE2
      */
      canMsgObject2.ui32MsgID = MSG_ID1;
      canMsgObject2.ui32MsgIDMask = 0x000007FF;
      canMsgObject2.ui32Flags = (MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER | MSG_OBJ_EXTENDED_ID );
      canMsgObject2.ui32MsgLen = 6;


      /*
      * Initialize  canMsgObject2 with the MessageID = 1, for receiving message from Node1
      * canMsgObject1 MsgID = 1
      * CanMsgObject1 Mask for filtering msg, same as NODE1 and NODE2
      */
      canMsgObject3.ui32MsgID = MSG_ID2;
      canMsgObject3.ui32MsgIDMask = 0x000007FF;
      canMsgObject3.ui32Flags = (MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER | MSG_OBJ_EXTENDED_ID);
      canMsgObject3.ui32MsgLen = 6;

}
void CANIntHandler(void){


    uint32_t interruptCause = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);

    if(interruptCause == CAN_INT_INTID_STATUS){ //Status Interrupt

       interruptCause  = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);  // Read Full CAN Controller Status

       if(interruptCause & CAN_STATUS_TXOK)
       {

           ++TXbitCounter;

       }else if(interruptCause & CAN_STATUS_RXOK){
           ++RXbitCounter;
       }else{
           errFlag=1;
           ++errCounter;
       }
    }else{


        switch (interruptCause){

                    case 1:
                        messageSent=1;
                        break;
                    case 2:   // Message Object 1 has completed its Transmission.
                       RXFlag2 = 1;
                       messageBox2Count++;
                       break;
                    case 3:
                        RXFlag3 =1;
                        messageBox3Count++;
                        break;
                    default:
                        errFlag = 1;
                        errCounter++;
                        break;

        }


    }
}
