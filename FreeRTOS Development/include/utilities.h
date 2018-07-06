/*
 * utilities.h
 *
 *  Created on: Jun 17, 2018
 *      Author: sormoh
 */

#ifndef INCLUDE_UTILITIES_H_
#define INCLUDE_UTILITIES_H_

#include <stdio.h>
#include "sys_common.h"

typedef struct descaleOutF32ToU16 {
    uint8_t outLSB_U8;
    uint8_t outMSB_U8;
} outF32ToU16;

float descale(float in_F32, float offset_F32, float scaling_F32);
uint8_t descaledF32ToU8(float in_F32, float offset_F32, float scaling_F32);
outF32ToU16 descaledF32ToU16(float in_F32, float offset_F32, float scaling_F32);


#endif /* INCLUDE_UTILITIES_H_ */
