/*
 * DAC_SPI_dash.c
 *
 *  Created on: Feb 29, 2020
 *      Author: lenovo
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_types.h"
#include "driverlib/ssi.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"

#define DAC_LOWEST_VOlTAGE 0
#define DAC_HIGHEST_VOLTAGE 5

#define DAC0_REGISTER_ADDRESS 00
#define DAC1_REGISTER_ADDRESS 01
#define VREF_REGISTER_ADDRESS 08
#define POWER_DOWN_REGISTER 09
#define GAIN_STATUS_REGISTER 0x0A

#define DAC_READ_CMD 03 //0b11
#define DAC_WRITE_CMD 00


//init SSI function
void delayMs(uint32_t ui32Ms) {

    // 1 clock cycle = 1 / SysCtlClockGet() second
    // 1 SysCtlDelay = 3 clock cycle = 3 / SysCtlClockGet() second
    // 1 second = SysCtlClockGet() / 3
    // 0.001 second = 1 ms = SysCtlClockGet() / 3 / 1000

    SysCtlDelay(ui32Ms * (SysCtlClockGet() / 3 / 1000));
}
bool MCP48FV_init(){

        //enable SSI communication
        SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

        GPIOPinConfigure(GPIO_PA2_SSI0CLK);
        GPIOPinConfigure(GPIO_PA3_SSI0FSS);
        GPIOPinConfigure(GPIO_PA5_SSI0TX);
        GPIOPinTypeSSI(GPIO_PORTA_BASE,GPIO_PIN_5|GPIO_PIN_3|GPIO_PIN_2);

        //configure SSI mode on SSI0
        SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_3, SSI_MODE_MASTER, 10000, 12);
        SSIEnable(SSI0_BASE);

        return true;
}

//setting up command for the DAC
uint32_t cmdCreator(uint8_t address, uint8_t cmdReadWrite, uint8_t cmderr, uint16_t dataBit){
   // setting command to interface to the DAC
    return ((address<<19)+(cmdReadWrite<<17)+(cmderr<<16)+(0<<12)+dataBit);
}
void SSIDataSend24(uint32_t ui32Base, uint32_t ui32Data)

{

  //
  // Check the argument... do it yourself
  //
  //
  // Wait until there is space
  //
  while(!(HWREG(ui32Base + SSI_O_SR) & SSI_SR_TNF))
    {

    }


    //

    // Write the data to the SSI.

    //

    HWREG(ui32Base + SSI_O_DR) = (ui32Data & 0x00FFF000)>>12;

    HWREG(ui32Base + SSI_O_DR) = (ui32Data & 0x00000FFF);

   //SysCtlDelay(650); // allow delay to permit transmission and SSIFSS to rise up
    delayMs(2.5);

}
bool MCP48FV_write(uint32_t cmdString){//write command to the DAC
     uint8_t ui8Data[] ={(uint8_t) (cmdString>>16), (uint8_t) (cmdString>>8),(uint8_t) (cmdString>>0)};
//     SSIDataPut(SSI0_BASE,cmdString);

     SSIDataSend24(SSI0_BASE,cmdString);
     while(SSIBusy(SSI0_BASE));

//    int i =0;
//    for(i =0; i<3;i++){
//   uint8_t ui8data = (uint8_t)ui32Data[i];
//    SSIDataPut(SSI0_BASE, ui8Data[i]);
//    while(SSIBusy(SSI0_BASE));
//    }
//
//   SSIDataPut(SSI0_BASE,ui8Data);
//    SSIDataSend24(SSI0_BASE,cmdString);
//    while(SSIBusy(SSI0_BASE));
         uint8_t cmdSPI1= cmdString; // debug
         uint8_t cmdSPI2= (cmdString>>8);
         uint8_t cmdSPI3= (cmdString>>16);

/* //kinda work code
      SSIDataPut(SSI0_BASE,cmdSPI3);
      GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,0x00);
      SysCtlDelay(10);
      SSIDataPut(SSI0_BASE,cmdSPI2);
      GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,0x00);
      SysCtlDelay(10);
      SSIDataPut(SSI0_BASE,cmdSPI1);
      //deselect the Fss pin
      GPIOPinWrite(GPIO_PORTA_BASE,GPIO_PIN_3,0x00);
      while(SSIBusy(SSI0_BASE));

//*/



    return true;
}
/* Main DAC controller, configure to send 0-5V accordingly
  use 500 = 5V, 251 = 2.51V*/
bool MCP48FV_setValue(uint16_t targetVoltage){
    if (targetVoltage > 500){
        return false;
    }
    uint32_t enableBitPrecent= ((targetVoltage)*1000)/(DAC_HIGHEST_VOLTAGE*100); // getting percentage from the target voltage
    uint32_t dacRegister= (enableBitPrecent*0xFF)/1000; // convert to dac register-> send command
    MCP48FV_write(cmdCreator(DAC0_REGISTER_ADDRESS, DAC_WRITE_CMD,0,dacRegister));


    return true;
}






