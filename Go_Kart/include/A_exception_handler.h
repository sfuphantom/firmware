

#ifndef _A_EXCEPTION_HANDLER
#define _A_EXCEPTION_HANDLER


#include "het.h"
#include <stdio.h>

//Error--------------------------------------------------------

#define ERR_ENABLE_SWITCH_DISCONNECT       1U

#define ERR_ADC_PIN_LOST_CONNECTION         3U
#define ERR_STAT_MACHINE_LOST_CONNECTION    4U
#define ERR_CAN_MSG_RETRIEVE_OUT_OF_TIME    5U
#define ERR_ADC_MSG_NOT_RECEIVED            6U
#define ERR_CAN_MSG_MISS_TOO_MUCH            7U
#define ERR_ADC_RETRIEVE_DATA_OUT_OF_TIME   8U
#define ERR_GIO_CONNECTION_FAILED_TOO_MANY  9U


#define ERR_THROTTLE_INPUT_INCONSIST        10U  //--------

#define ERR_TRANSDUCER_VALUE_TOO_HIGH       11U


#define ERR_VT_HIGH                         20U
#define ERR_CT_HIGH                         21U
#define ERR_VT_LOW                          22U
#define ERR_CT_LOW                          23U


//Disconnection of 3 input switches
#define ERR_EN_MD_DISCONNECT                12U
#define ERR_EN_RUN_DISCONNECT               13U
#define ERR_BMS_SWITCH_DISCONNECT           14U




#define ERR_UNKNOWN_ERROR                   98U
#define ERR_MICRO_CONTROLLER_INTERNAL_ERROR               99U


//Warning--------------------------------------------------------
#define WARN_MISS_MOTOR_MSG                     101U
#define WARN_MISS_ADC_DATA                      102U
#define WARN_MISS_CAN_DATA                      103U

#define WARN_VT_HIGH                            104U
#define WARN_VT_LOW                            105U
#define WARN_CT_HIGH                            106U
#define WARN_CT_LOW                            107U

#define WARN_TOO_FAST                           108U




#define WARN_UNKNOWN_ISSUE                  150U


extern uint8 LCD_EN_2;


void setError(uint8 val);
void setWarnning(uint8 val);

uint8 lcdUpdate_2(char *s1, char *s2);

#endif

