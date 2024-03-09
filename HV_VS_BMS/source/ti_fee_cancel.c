/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  ti_fee_cancel.c
 *      Project:  Tms570_TIFEEDriver
 *       Module:  TIFEEDriver
 *    Generator:  None
 *
 *  Description:  This file implements the TI FEE Api TI_Fee_Cancel.
 *---------------------------------------------------------------------------------------------------------------------
 * Author:  Vishwanath Reddy
 *---------------------------------------------------------------------------------------------------------------------
 * Revision History
 *---------------------------------------------------------------------------------------------------------------------
 * Version        Date         Author               Change ID        Description
 *---------------------------------------------------------------------------------------------------------------------
 * 00.01.00       07Sept2012    Vishwanath Reddy     0000000000000    Initial Version
 * 00.01.01       14Sept2012    Vishwanath Reddy     0000000000000    Review changes
 * 00.01.02       30Nov2012     Vishwanath Reddy     SDOCM00097786    Misra Fixes, Memory segmentation changes.
 * 00.01.08		  05Apr2013	    Vishwanath Reddy     SDOCM00099152    Added feature :CRC check for unconfigured blocks,
																	  Main function modified to complete writes as fast
																	  as possible, Added Non polling mode support.
 * 00.01.10       11Jun2013	    Vishwanath Reddy     SDOCM00101845	  Fixed issue with job end notification call.
                                                                      Job end notification is only called if polling
																	  mode is OFF. 
 * 01.12.00		  13Dec2013     Vishwanath Reddy     SDOCM00105412    Traceability tags added. 
                                                                      MISRA C fixes.
                                                                      Changes for cancelling Job only when BUSY.
* 01.18.00		  12Oct2015     Vishwanath Reddy     SDOCM00119455    Update version history.																	  
* 01.18.01		  17Nov2015     Vishwanath Reddy     SDOCM00120161    Update version history.
* 01.18.02		  05Feb2016     Vishwanath Reddy     SDOCM00121158    Update version history.
* 01.18.03        30June2016    Vishwanath Reddy     SDOCM00122388    Update version history.
* 01.19.00        08Augu2016    Vishwanath Reddy     SDOCM00122592    Update version history.
* 01.19.01        12Augu2016    Vishwanath Reddy     SDOCM00122543    Update version history.
* 01.19.02        25Janu2017    Vishwanath Reddy     SDOCM00122832    Update version history. 
* 01.19.03        15May2017     Prathap Srinivasan   SDOCM00122917    Update version history.
* 01.19.04		  05Dec2017     Prathap Srinivasan   HERCULES_SW-5082 Update version history.
 *********************************************************************************************************************/

/*
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com  
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

 /*********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "ti_fee.h"

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_START_SEC_CODE
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"

/**********************************************************************************************************************
 *  TI_Fee_Cancel
 *********************************************************************************************************************/
/*! \brief      This functions cancels an ongoing operation
 *  \param[in]  none
 *  \param[out] none
 *  \return     none
 *  \return     none
 *  \context    Function could be called from task level
 *  \note       TI FEE API.
 *********************************************************************************************************************/
/* SourceId : HL_Fee_SourceId_8 */
/* DesignId : HL_FEE_DesignId_30 */
/* Requirements : HL_FEE_SR31, HL_FEE_SR32, HL_FEE_SR33 */
/*SAFETYMCUSW 61 D MR:8.10,8.11 <APPROVED> "Reason -  This API will be called by application."*/
void TI_Fee_Cancel(uint8 u8EEPIndex)
{
	/* Cancel Operations only if in BUSY state. If BUSY_INTERNAL, do not cancel
	   copy/erase operations */
	if(BUSY == TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState)
	{
		if(TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.WriteAsync==1U)
		{
			TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.WriteAsync=0U;
		}
		if(TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.WriteSync==1U)
		{
			TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.WriteSync=0U;
		}
		if(TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Read==1U)
		{
			TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Read=0U;
		}
		if(TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.EraseImmediate==1U)
		{
			TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.EraseImmediate=0U;
		}
		if(TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.InvalidateBlock==1U)
		{
			TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.InvalidateBlock=0U;
		}
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult=JOB_CANCELLED;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState=IDLE;
		#if(STD_OFF == TI_FEE_POLLING_MODE)
		TI_FEE_NVM_JOB_END_NOTIFICATION();
		#endif
	}
}

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_STOP_SEC_CODE
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"

/**********************************************************************************************************************
 *  END OF FILE: ti_fee_cancel.c
 *********************************************************************************************************************/

