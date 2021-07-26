/*  hv_driver.c
 *  Author : Yash Bhavnani
 *  Date   : 27 February, 2021
 */


/*============================================================================*/
/* Includes           */
/*============================================================================*/

#include "sys_common.h"


#include <hv_driver.h>
#include <math.h>
#include <gio.h>
#include "sci.h"
#include "string.h"
#include "stdio.h"

/*============================================================================*/
/* Function Prototypes           */
/*============================================================================*/
static uint16 bitExtracted(uint16 number, uint8 k, uint8 p);
static void decToBinary(int n);;
static int binTwosComplementToSignedDecimal(uint8 binary[],uint8 significantBits);
static float Interpolate_input (int adc_input);
void UARTprintf(const char *_format, ...);

/*============================================================================*/
/* Defintions           */
/*============================================================================*/
# define MAX_DATA_BITS  (12u)
# define SLOPE          (0.01173261f)
# define Y_INTERCEPT    (144.285f)
# define START_INDEX    (1u)

/*============================================================================*/
/* Global variables          */
/*============================================================================*/
static uint8 binaryNum[12];

/*============================================================================*/
/* Function Declarations        */
/*============================================================================*/

// Function to extract k bits from p position
// and returns the extracted value as integer */
static uint16 bitExtracted(uint16 number, uint8 k, uint8 p)
{
    return (((1 << k) - 1) & (number >> (p - 1)));
}


static void decToBinary(int n)
{
    int  idx = 0;
    // Size of an integer is assumed to be 12 bits
    for (idx = (MAX_DATA_BITS -1) ; idx >= 0; idx--)
    {
        int k = n >> idx;
        if (k & 1)
        {
            binaryNum[idx] = 1;
        }
        else
        {
            binaryNum[idx] = 0;
        }
    }
}


static float Interpolate_input (int adc_input) //change to uint_8
{
    float output_voltage;
    output_voltage = ((float)adc_input * SLOPE) + Y_INTERCEPT;

    return output_voltage;

}

static int binTwosComplementToSignedDecimal(uint8 binary[],uint8 significantBits)
{
    int power = pow(2,significantBits-1);
    int sum = 0;
    int i;

    for (i = significantBits-1; i >= 0; i--)
    {
        if ( i == (MAX_DATA_BITS -1) && binary[i]!= 0)
        {
            sum = power * -1;
        }
        else
        {
            sum += (binary[i])*power;
        }
        power /= 2;
    }

    return sum;
}
void UARTprintf(const char *_format, ...)
{
   char str[128];
   memset(str, '\0', 128 * sizeof(char));
   int8_t length = -1;

   va_list argList;
   va_start( argList, _format );

   length = vsnprintf(str, sizeof(str), _format, argList);
   str[127] = '\0';

   va_end( argList );

   if (length > 0)
   {
      sciSend(scilinREG, (unsigned)length, (unsigned char*)str);
   }
}
float getADCdata(uint16 input)
{
    int conversion_dec;
    float otp;

    uint16 input_12bits = bitExtracted(input, MAX_DATA_BITS, START_INDEX ); // extracting 12 bits of data(the first 2 bits are 0)
    decToBinary(input_12bits);
    conversion_dec = binTwosComplementToSignedDecimal(binaryNum , MAX_DATA_BITS);
    otp = Interpolate_input(conversion_dec);
    UARTprintf("otp value: \n\r");
    unsigned int adc_input = (int) (otp);
    int i,j;
    for (i = 2; i >= 0; i--)
    {
        uint8 bit = (int) (adc_input % 10);
        for (j = 3; j >= 0; j--)
        {
            uint8 t = (int) ((bit >> j) & 1);
            if (t == 0)
            {
                UARTprintf("0");
            }
            sciSend(scilinREG, 1, &t);
        }
        if (i == 2)
        {
            UARTprintf(" ");
            adc_input = (int) (adc_input/10);
        }
        if (i == 1)
        {
            UARTprintf(" ");
            adc_input = (int) (adc_input/10);
        }
    }
    UARTprintf("\n\r");
    return otp;
}

