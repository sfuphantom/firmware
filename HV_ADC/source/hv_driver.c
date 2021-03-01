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
/*============================================================================*/
/* Function Prototypes           */
/*============================================================================*/
static uint16 bitExtracted(uint16 number, uint8 k, uint8 p);
static void decToBinary(int n);;
static int binTwosComplementToSignedDecimal(uint8 binary[],uint8 significantBits);
static float Interpolate_input (int adc_input);

/*============================================================================*/
/* Defintions           */
/*============================================================================*/
# define MAX_DATA_BITS  (12u)
# define SLOPE          (0.011875f)
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

float getADCdata(uint16 input)
{
    int conversion_dec;
    float otp;

    uint16 input_12bits = bitExtracted(input, MAX_DATA_BITS, START_INDEX ); // extracting 12 bits of data(the first 2 bits are 0)
    decToBinary(input_12bits);
    conversion_dec = binTwosComplementToSignedDecimal(binaryNum , MAX_DATA_BITS);
    otp = Interpolate_input(conversion_dec);

    return otp;
}

