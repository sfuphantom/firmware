

/**
 * main.c
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/adc.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "utils/uartstdio.c"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"

void InitConsole(void);
void setDisplay(int num, char port);
long map(long x, long in_min, long in_max, long out_min, long out_max);

int main(void)
{

       InitConsole();

       uint32_t pui32ADC0Value[1];
           UARTprintf("ADC ->\n");
           UARTprintf("  Type: Single Ended\n");
           UARTprintf("  Samples: One\n");
           UARTprintf("  Update Rate: 250ms\n");
           UARTprintf("  Input Pin: AIN0/PE3\n\n");


  SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN); // set up the clock
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);  // enable port F
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);  // enable port E
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);  // enable port B
  SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0); // enable ADC
  GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); // enable outputs on the launchpad LED pins
  GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4); // enable outputs on the launchpad LED pins
  GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3); // enable outputs on the launchpad LED pins
  GPIOPinTypeADC(GPIO_PORTB_BASE, GPIO_PIN_5);

  ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
  ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH11 | ADC_CTL_IE | ADC_CTL_END);
  ADCSequenceEnable(ADC0_BASE, 3);
  ADCIntClear(ADC0_BASE, 3);


  int numD = 0;
  int numE = 2;
  int numB = 7;

  char portE = 'E';
  char portD = 'D';
  char portB = 'B';

  //GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_3, GPIO_PIN_3);
 // GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_1|GPIO_PIN_2);
 // GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_1|GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2);
  do{
  ADCProcessorTrigger(ADC0_BASE, 3);

          //
          // Wait for conversion to be completed.
          //
          while(!ADCIntStatus(ADC0_BASE, 3, false))
          {
          }

          //
          // Clear the ADC interrupt flag.
          //
          ADCIntClear(ADC0_BASE, 3);

          //
          // Read ADC Value.
          //
          ADCSequenceDataGet(ADC0_BASE, 3, pui32ADC0Value);

          //
          // Display the AIN0 (PE3) digital value on the console.
          //
         int y = map(pui32ADC0Value[0], 0, 4096, 0, 999);

          UARTprintf("AIN11 = %4d\r", y);
          numD = (y/100)%10;
          numE = (y/10)%10;
          numB = (y/1)%10;

          setDisplay(numD, portD);
          setDisplay(numE, portE);
          setDisplay(numB, portB);

  SysCtlDelay(7000000);
  }while(1);

}

void setDisplay(int number, char port)
{
    switch (port)
    {
    case 'E':
        switch (number)
        {
        case 0:
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1, 0x00);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_2, 0x00);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3, 0x00);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4, 0x00);
            break;
        case 1:
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1, GPIO_PIN_1);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_2, 0x00);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3, 0x00);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4, 0x00);
            break;
        case 2:
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1, 0x00);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_2, GPIO_PIN_2);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3, 0x00);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4, 0x00);
            break;
        case 3:
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1, GPIO_PIN_1);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_2, GPIO_PIN_2);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3, 0x00);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4, 0x00);
            break;
        case 4:
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1, 0x00);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_2, 0x00);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3, GPIO_PIN_3);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4, 0x00);
            break;
        case 5:
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1, GPIO_PIN_1);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_2, 0x00);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3, GPIO_PIN_3);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4, 0x00);
            break;
        case 6:
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1, 0x00);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_2, GPIO_PIN_2);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3, GPIO_PIN_3);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4, 0x00);
            break;
        case 7:
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1, GPIO_PIN_1);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_2, GPIO_PIN_2);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3, GPIO_PIN_3);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4, 0x00);
            break;
        case 8:
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1, 0x00);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_2, 0x00);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3, 0x00);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4, GPIO_PIN_4);
            break;
        case 9:
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_1, GPIO_PIN_1);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_2, 0x00);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_3, 0x00);
            GPIOPinWrite(GPIO_PORTE_BASE,GPIO_PIN_4, GPIO_PIN_4);
            break;
        }
        break;
        case 'B':
            switch (number)
            {
            case 0:
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0, 0x00);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_1, 0x00);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2, 0x00);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_3, 0x00);
                break;
            case 1:
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0, GPIO_PIN_0);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_1, 0x00);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2, 0x00);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_3, 0x00);
                break;
            case 2:
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0, 0x00);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_1, GPIO_PIN_1);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2, 0x00);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_3, 0x00);
                break;
            case 3:
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0, GPIO_PIN_0);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_1, GPIO_PIN_1);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2, 0x00);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_3, 0x00);
                break;
            case 4:
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0, 0x00);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_1, 0x00);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2, GPIO_PIN_2);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_3, 0x00);
                break;
            case 5:
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0, GPIO_PIN_0);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_1, 0x00);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2, GPIO_PIN_2);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_3, 0x00);
                break;
            case 6:
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0, 0x00);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_1, GPIO_PIN_1);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2, GPIO_PIN_2);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_3, 0x00);
                break;
            case 7:
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0, GPIO_PIN_0);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_1, GPIO_PIN_1);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2, GPIO_PIN_2);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_3, 0x00);
                break;
            case 8:
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0, 0x00);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_1, 0x00);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2, 0x00);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_3, GPIO_PIN_3);
                break;
            case 9:
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_0, GPIO_PIN_0);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_1, 0x00);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_2, 0x00);
                GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_3, GPIO_PIN_3);
                break;
            }
            break;
            case 'D':
                switch (number)
                {
                case 0:
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_0, 0x00);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_1, 0x00);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2, 0x00);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_3, 0x00);
                    break;
                case 1:
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_0, GPIO_PIN_0);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_1, 0x00);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2, 0x00);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_3, 0x00);
                    break;
                case 2:
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_0, 0x00);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_1, GPIO_PIN_1);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2, 0x00);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_3, 0x00);
                    break;
                case 3:
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_0, GPIO_PIN_0);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_1, GPIO_PIN_1);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2, 0x00);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_3, 0x00);
                    break;
                case 4:
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_0, 0x00);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_1, 0x00);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2, GPIO_PIN_2);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_3, 0x00);
                    break;
                case 5:
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_0, GPIO_PIN_0);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_1, 0x00);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2, GPIO_PIN_2);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_3, 0x00);
                    break;
                case 6:
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_0, 0x00);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_1, GPIO_PIN_1);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2, GPIO_PIN_2);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_3, 0x00);
                    break;
                case 7:
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_0, GPIO_PIN_0);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_1, GPIO_PIN_1);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2, GPIO_PIN_2);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_3, 0x00);
                    break;
                case 8:
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_0, 0x00);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_1, 0x00);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2, 0x00);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_3, GPIO_PIN_3);
                    break;
                case 9:
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_0, GPIO_PIN_0);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_1, 0x00);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_2, 0x00);
                    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_3, GPIO_PIN_3);
                    break;
                }
                break;
    }
}

void
InitConsole(void)
{
    //
    // Enable GPIO port A which is used for UART0 pins.
    // TODO: change this to whichever GPIO port you are using.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    //
    // Configure the pin muxing for UART0 functions on port A0 and A1.
    // This step is not necessary if your part does not support pin muxing.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    //
    // Enable UART0 so that we can configure the clock.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    //
    // Use the internal 16MHz oscillator as the UART clock source.
    //
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    //
    // Select the alternate (UART) function for these pins.
    // TODO: change this to select the port/pin you are using.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Initialize the UART for console I/O.
    //
    UARTStdioConfig(0, 115200, 16000000);
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
