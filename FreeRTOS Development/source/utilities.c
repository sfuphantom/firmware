/*
 * utilities.c
 *
 *  Created on: Jun 17, 2018
 *      Author: sormoh
 */



#include <stdio.h>
#include "utilities.h"



outF32ToU16 F32ToU16;

float descale(float in_F32, float offset_F32, float scaling_F32){

    float descale_F32 = 0;

    if (scaling_F32 != 0){
        descale_F32 = (in_F32 - offset_F32) / scaling_F32;
    } else {
        descale_F32 = 0;
    }

    return descale_F32;
}

uint8_t descaledF32ToU8(float in_F32, float offset_F32, float scaling_F32){

    uint16_t out_U8;

    if (scaling_F32 != 0){
        out_U8 = (uint8_t)(descale(in_F32,offset_F32,scaling_F32));
    } else {
        out_U8 = 0;
    }

    return out_U8;
}

outF32ToU16 *descaledF32ToU16(float in_F32, float offset_F32, float scaling_F32){

    outF32ToU16 *F32ToU16Ptr = &F32ToU16;

    uint16_t out_U16;
    if (scaling_F32 != 0){
        out_U16 = (uint16_t)(descale(in_F32,offset_F32,scaling_F32));
    } else {
        out_U16 = 0;
    }

    F32ToU16.outLSB_U8 = out_U16 & 0x0F;
    F32ToU16.outMSB_U8 = out_U16 & 0xF0;

    return F32ToU16Ptr;
}


