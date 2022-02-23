/*
 *  @file pl455.h
 *
 *  @author Stephen Holland - Texas Instruments Inc.
 *  @date June 2015
 *  @version 1.0 Initial version
 *  @note Built with CCS for Hercules Version: 5.5.0
 */

/*****************************************************************************
**
**  Copyright (c) 2011-2015 Texas Instruments
**
******************************************************************************/


#ifndef PL455_H_
#define PL455_H_

#include "datatypes.h"
#include "hal_stdtypes.h"
#include "stdint.h"
#include "stdbool.h"

// User defines
#define FRMWRT_SGL_R    0x00 // single device write with response
#define FRMWRT_SGL_NR   0x10 // single device write without response
#define FRMWRT_GRP_R    0x20 // group broadcast with response
#define FRMWRT_GRP_NR   0x30 // group broadcast without response
#define FRMWRT_ALL_R    0x60 // general broadcast with response
#define FRMWRT_ALL_NR   0x70 // general broadcast without response

#define TOTALBOARDS 4
#define BAUDRATE 250000

// Function Prototypes
void ResetPL455();
void WakePL455();
void CommClear(void);
void CommReset(void);
BOOL GetFaultStat();

bool getBMSinitFlag(void);
void setBMSinitFlag(bool state);

uint16  B2SWORD(uint16 wIN);
uint32 B2SDWORD(uint32 dwIN);
uint32 B2SINT24(uint32 dwIN24);

int  WriteReg(BYTE bID, uint16 wAddr, uint64 dwData, BYTE bLen, BYTE bWriteType);
int  ReadReg(BYTE bID, uint16 wAddr, void * pData, BYTE bLen, uint32 dwTimeOut);

int  WriteFrame(BYTE bID, uint16 wAddr, BYTE * pData, BYTE bLen, BYTE bWriteType);
int  ReadFrameReq(BYTE bID, uint16 wAddr, BYTE bByteToReturn);
int  WaitRespFrame(BYTE *pFrame, BYTE bLen, uint32 dwTimeOut);

void delayms(uint16 ms);
void delayus(uint16 us);

#endif /* PL455_H_ */
//EOF
