/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  ti_fee_util.c
 *      Project:  Tms570_TIFEEDriver
 *       Module:  TIFEEDriver
 *    Generator:  None
 *
 *  Description:  This file implements the TI FEE Api, Miscellanous API's.
 *---------------------------------------------------------------------------------------------------------------------
 * Author:  Vishwanath Reddy
 *---------------------------------------------------------------------------------------------------------------------
 * Revision History
 *---------------------------------------------------------------------------------------------------------------------
 * Version        Date         Author               Change ID        Description
 *---------------------------------------------------------------------------------------------------------------------
 * 00.01.00       31Aug2012    Vishwanath Reddy     0000000000000    Initial Version 
 * 00.01.01       29Oct2012    Vishwanath Reddy     0000000000000    Changes for implementing Error Recovery
 * 00.01.02       30Nov2012    Vishwanath Reddy     SDOCM00097786    Misra Fixes, Memory segmentation changes.
 * 00.01.04		  12Feb2012	   Vishwanath Reddy     SDOCM00099152    Integration issues fix. 
 * 00.01.05		  04Mar2013	   Vishwanath Reddy     SDOCM00099152    Added Deleting a block feature, bug fixes. 
 * 00.01.06		  11Mar2013	   Vishwanath Reddy     SDOCM00099152    Added feature : copying of unconfigured blocks.
 * 00.01.07		  15Mar2013	   Vishwanath Reddy     SDOCM00099152    Added feature : Number of 8 bytes writes, fixed 
																	 issue with copy blocks. 
 * 00.01.08		  05Apr2013	   Vishwanath Reddy     SDOCM00099152    Added feature : CRC check for unconfigured blocks,
																	 Main function modified to complete writes as fast
																	 as possible, Added Non polling mode support.
 * 00.01.09		  19Apr2013	   Vishwanath Reddy     SDOCM00099152    Warning removal, Added feature comparision of
                                                                     data during write.			
 * 00.01.10       11Jun2013	   Vishwanath Reddy     SDOCM00101845	 Added newstatus toknow if erase started/completed.
 * 00.01.11       05Jul2013	   Vishwanath Reddy     SDOCM00101643	 Fixed issue when VS are more than 2. If number of
                                                                     VS are more than 2, state machine was getting 
																	 stuck to BUSY_INTERNAL. This is fixed now.
 * 01.12.00		  13Dec2013    Vishwanath Reddy     SDOCM00105412    Traceability tags added. 
 *                                                                   MISRA C fixes.																	 
 * 01.13.00       30Dec2013	   Vishwanath Reddy     SDOCM00105795	 Limit access of FEE to EEPROM bank.
 * 01.13.01       19May2014	   Vishwanath Reddy     SDOCM00107913	 In TI_FeeInternal_FeeManager, reset 
 *                                                                   u8VirtualSectorIndex[u8EEPIndex] to zero, if blank
 *                                                                   check failed.      
 *                                                  SDOCM00107622    Changes for Unexpected Job Result. Set Job result
 *                                                                   before changing module state. 
 * 01.13.02       12Jun2014	   Vishwanath Reddy     SDOCM00108238	 In TI_FeeInternal_FeeManager, change the state to
 *                                                                   IDLE, after completing the copy operation.   
 * 01.14.00		  26Mar2014    Vishwanath Reddy 	SDOCM00107161    Update jobresult before updaing module state. 
 * 01.15.00		  06Jun2014    Vishwanath Reddy 	                 Support for TMS570LCx.
 * 01.16.00		  15Jul2014    Vishwanath Reddy 	SDOCM00112141    Remove  MISRA warnings.
 * 01.16.01		  12Sep2014	   Vishwanath Reddy     SDOCM00112930    New API TI_Fee_SuspendResumeErase Added.
 *                                                                   TI_FeeInternal_FindInvalidVirtualSector modified
 *                                                                   to resume erase, if suspended.
 *                                                                   TI_FeeInternal_FindReadyForEraseVirtualSector
 *                                                                   modified to resume erase, if suspended.
 * 01.17.00		  15Oct2014    Vishwanath Reddy     SDOCM00113379    RAM Optimization changes.
 * 01.17.01		  30Oct2014    Vishwanath Reddy     SDOCM00113536    If multiple physical sectors are combined in to 
 *                                                                   a larger virtual sector, some sectors were not 
 *                                                                   getting erased. This is fixed now.
 * 01.17.02		  26Dec2014    Vishwanath Reddy     SDOCM00114102    FLEE Errata Fix. Add new API
 *                                                                   TI_FeeInternal_EnableRequiredFlashSector.
 *                                                  SDOCM00114423	 New API TI_FeeInternal_PopulateStructures added.
 *                                                                   This API populates device specific and virtual 
 *                                                                   sector structure elements.
 *                                                                   Following API's modified to support above feature.
 *																	 TI_FeeInternal_GetVirtualSectorParameter,
 *                                                                   TI_FeeInternal_WriteDataF021,
 *                                                                   TI_FeeInternal_BlankCheck,
 *                                                                   TI_FeeInternal_GetVirtualSectorIndex,
 *                                                                   TI_FeeInternal_GetCurrentBlockAddress.
 * 01.18.00		  12Oct2015    Vishwanath Reddy     SDOCM00119455    Update TI_FeeInternal_UpdateBlockOffsetArray API.
 *                                                                   Bugfix for "If morethan one data set is config-
 *                                                                   ured, then a valid block may get invalidated if
 *                                                                   multiple valid blocks are present in FEE memory. 
 * 01.18.01		  17Nov2015    Vishwanath Reddy     SDOCM00120161    In TI_FeeInternal_FeeManager, do not change the 
 *                                                                   state to IDLE,after completing the copy operation.
 * 01.18.02		  05Feb2016    Vishwanath Reddy     SDOCM00121158    Update version history.
 *                                                                   Add a call of TI_FeeInternal_PollFlashStatus()
 *                                                                   before reading data from FEE bank in
 *                                                                   TI_FeeInternal_UpdateBlockOffsetArray().
 *                                                                   In TI_FeeInternal_FeeManager, change the state to
 *                                                                   IDLE,after completing the copy operation, if code
 *                                                                   is not used in Auotsar context.
 * 01.18.03       30June2016   Vishwanath Reddy     SDOCM00122388    Update version history.
 *                                                                   Changes related to supporting of configuring
 *                                                                   data set numbers instead of block numbers.
 *                                                                   TI_FeeInternal_GetBlockNumber,
 *                                                                   TI_FeeInternal_GetArrayIndex,
 *                                                                   TI_FeeInternal_FeeManager API's are modified.
 *                                                                   TI_FEE_FLASH_CRC_ENABLE is renamed to 
 *                                                                   TI_FEE_FLASH_CHECKSUM_ENABLE. 
 *                                                                   TI_Fee_u16UnconfiguredBlocksToCopy - Global 
 *                                                                   static variable is initialized to zero.
 * 01.19.00       08Augu2016   Vishwanath Reddy     SDOCM00122592    Code for using of partial erased sector will be 
 *                                                                   under compile switch TI_FEE_USEPARTIALERASEDSECTOR
 *                                                                   TI_FeeInternal_UpdateBlockOffsetArray modified to 
 *                                                                   update write addresses correctly, if FEE did not
 *                                                                   find a valid write address. 
 *                                                                   TI_FeeInternal_WriteDataF021 API updated for LE 
 *                                                                   system for updating correct ECC.
 * 01.19.01       12Augu2016   Vishwanath Reddy     SDOCM00122543    TI_FeeInternal_UpdateBlockOffsetArray modified
 *                                                                   to update correct address of copy VS, in case 
 *                                                                   of copy write address exceeding end of VS.
 *                                                                   TI_FeeInternal_FeeManager modified to update block
 *                                                                   copy status of unconfigured blocks correctly.
 *                                                                   TI_FeeInternal_WriteDataF021 updated to check
 *                                                                   if copy source address is within Bank7 address.
 * 01.19.02       25Janu2017   Vishwanath Reddy     SDOCM00122832    In API TI_Fee_ErrorRecovery, added polling for
 *                                                                   flash status before calling TI_Fee_Init.
 * 01.19.03       15May2017    Prathap Srinivasan   SDOCM00122917    Removed Block Size interpretaion for Blocks that 
 *                                                                   are not Valid, Invalid or Empty. 
 * 01.19.04       15Dec2017    Prathap Srinivasan   HERCULES_SW-5082 Fixed TI_Fee_SuspendResumeErase function to store    
 *                                                                   and restore FEE_ModuleState, when entering suspend 
 *                                                                   and resuming.
 *                                                  HERCULES_SW-5083 Fixed TI_FeeInternal_FeeManager() to pass correct 
 *																	 parameters for CRC calculation.
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

/**********************************************************************************************************************
 *  INTERNAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
static void TI_FeeInternal_InvlalidateEraseInitialize(TI_Fee_AddressType oFlashNextAddress, uint8 u8EEPIndex);
static uint8 TI_FeeInternal_FindReadyForEraseVirtualSector(uint8 u8EEPIndex);
static uint8 TI_FeeInternal_FindInvalidVirtualSector(uint8 u8EEPIndex);
static void TI_FeeInternal_CopyInitialize(boolean bBlockStatus, TI_Fee_AddressType oFlashNextAddress, uint8 u8EEPIndex,
                                          uint8 u8SingleBitError);
static void TI_FeeInternal_ConfigureBlockHeader(uint8 u8EEPIndex, uint8 u8BlockState,uint16 Fee_BlockSize_u16,
                                                uint16 u16BlockNumber);
static void TI_FeeInternal_ConfigureVirtualSectorHeader(uint8  FeeVirtualSectorNumber,
                                                        VirtualSectorStatesType VsState,  uint8 u8EEPIndex);
														
/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_START_SEC_VAR_INIT_UNSPECIFIED  
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"

#if (TI_FEE_NUMBER_OF_UNCONFIGUREDBLOCKSTOCOPY != 0U)
static uint16 TI_Fee_u16UnconfiguredBlocksToCopy[TI_FEE_NUMBER_OF_EEPS] = {0U};
#endif


/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_STOP_SEC_VAR_INIT_UNSPECIFIED  
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_START_SEC_CODE
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"

/**********************************************************************************************************************
 *  TI_FeeInternal_GetVirtualSectorParameter
 *********************************************************************************************************************/
/*! \brief      This function can return either the start address of the sector or length of the sector
 *  \param[in]	Fapi_FlashSectorType oSector
 *  \param[in]	uint16 u16Bank
 *  \param[in]	boolean VirtualSectorInfo
 *  \param[in]	uint8 u8EEPIndex
 *  \param[out] none
 *  \return		Virtual sector start address
 *  \return 	Virtual sector Length 
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
 uint32 TI_FeeInternal_GetVirtualSectorParameter(Fapi_FlashSectorType oSector, uint16 u16Bank, 
                                                 boolean VirtualSectorInfo, uint8 u8EEPIndex)
{	
	uint32 u32VirtualSectorParameter  =  0xFFFFFFFFU;
	uint16 u16LoopIndex  =  0U;
	boolean bFoundParameter  =  FALSE;
	boolean bExceed  =  FALSE;
	
	#if (TI_FEE_GENERATE_DEVICEANDVIRTUALSECTORSTRUC == STD_ON)
	for(u16LoopIndex = 0U ; u16LoopIndex<TI_Fee_MaxSectors ; u16LoopIndex++)
	#else
	for(u16LoopIndex = 0U ; u16LoopIndex<DEVICE_BANK_MAX_NUMBER_OF_SECTORS ; u16LoopIndex++)
	#endif
	{
		/* Check if the Sector specified matches the Sector name in the Device configuration */
		if(oSector  ==  Device_FlashDevice.Device_BankInfo[u16Bank].Device_SectorInfo[u16LoopIndex].Device_Sector)
		{
			/* If VirtualSectorInfo is TRUE return the address, else return the length */
			if(VirtualSectorInfo  ==  TRUE)  
			{
				u32VirtualSectorParameter  =  Device_FlashDevice.Device_BankInfo[u16Bank].Device_SectorInfo[u16LoopIndex].Device_SectorStartAddress;
			}
			else
			{
				u32VirtualSectorParameter  =  Device_FlashDevice.Device_BankInfo[u16Bank].Device_SectorInfo[u16LoopIndex].Device_SectorLength;
			}
			bFoundParameter  =  TRUE;
		}		
		if((Device_FlashDevice.Device_BankInfo[u16Bank].Device_SectorInfo[u16LoopIndex].Device_SectorStartAddress) == 0xFFFFFFFFU)
		{
			/* Exceeded the number of sectors on the bank */
			bExceed  =  TRUE;
		}		
		if((bExceed  ==  TRUE)||(bFoundParameter  ==  TRUE))
		{
			break;
		}		
	}
	if((u32VirtualSectorParameter == 0xFFFFFFFFU) || (bExceed == TRUE))
	{			
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error  =  Error_InvalidVirtualSectorParameter;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus  =  TI_FEE_ERROR;						
	}	
	return(u32VirtualSectorParameter);
}

/**********************************************************************************************************************
 *  TI_FeeInternal_WriteVirtualSectorHeader
 *********************************************************************************************************************/
/*! \brief      This function writes the Virtual Sector Header
 *  \param[in]	uint16  FeeVirtualSectorNumber
 *  \param[in]	VirtualSectorStatesType VsState
 *  \param[in]	uint8 u8EEPIndex 
 *  \param[out] none 
 *  \return 	none
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
 void TI_FeeInternal_WriteVirtualSectorHeader(uint8  FeeVirtualSectorNumber, VirtualSectorStatesType VsState, 
                                              uint8 u8EEPIndex)
{	
	/* Configure the Virtual Sector Header State*/
	TI_FeeInternal_ConfigureVirtualSectorHeader(FeeVirtualSectorNumber,VsState, u8EEPIndex);	
		
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress  =  TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress;
	/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
	/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8Data  =  (uint8 *)(&TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorStateValue[0]); 	
	
	(void)TI_FeeInternal_WriteDataF021(FALSE,(uint16)8U,u8EEPIndex);	
	if(VsState_Empty != VsState)
	{
		/* Write the remaining of the VS header in Main function */
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWriteVSHeader = TRUE;
	}	
}

/**********************************************************************************************************************
 *  TI_FeeInternal_ConfigureVirtualSectorHeader
 *********************************************************************************************************************/
/*! \brief      This functions configures the Virtual Sector Header. It also stores the write address of the VS in 
 *				variable Fee_oCurrentAddress
 *  \param[in]	uint8  FeeVirtualSectorNumber
 *  \param[in]	VirtualSectorStatesType VsState
 *  \param[in]	uint8 u8EEPIndex 
 *  \param[out] none 
 *  \return 	none
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
static void TI_FeeInternal_ConfigureVirtualSectorHeader(uint8  FeeVirtualSectorNumber, VirtualSectorStatesType VsState, uint8 u8EEPIndex)
{
	uint16 u16LoopIndex  =  0U;
	uint16 u16LoopIndex1  =  0U;
	uint16 u16VirtualSectorIndex  =  0U;
	Fapi_FlashSectorType oSector;
	
	if(0U == u8EEPIndex)
	{
		u16LoopIndex = 0U;	
		u16LoopIndex1 = (uint16)(TI_FEE_NUMBER_OF_VIRTUAL_SECTORS - TI_FEE_NUMBER_OF_VIRTUAL_SECTORS_EEP1);
	}
	else
	{
		u16LoopIndex = TI_FEE_NUMBER_OF_VIRTUAL_SECTORS_EEP1;
		u16LoopIndex1 = TI_FEE_NUMBER_OF_VIRTUAL_SECTORS;	
	}
	
	/* Determine the Virtual Sector index */	
	for(u16LoopIndex = 0U ; u16LoopIndex<u16LoopIndex1 ; u16LoopIndex++)
	{
		if(FeeVirtualSectorNumber  ==  Fee_VirtualSectorConfiguration[u16LoopIndex].FeeVirtualSectorNumber)
		{
			u16VirtualSectorIndex  =  u16LoopIndex;
			break;
		}		
	}

	/* Virtual Sector information record */			
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorStateValue[3]  =  0xFF000000U | TI_FEE_VIRTUAL_SECTOR_VERSION;				
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorStateValue[3] |= (TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorEraseCount[u16VirtualSectorIndex]<<0x4U);				
	/* Determine the start address of the Virtual Sector */	
	oSector  =  Fee_VirtualSectorConfiguration[u16VirtualSectorIndex].FeeStartSector;					
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress  =  TI_FeeInternal_GetVirtualSectorParameter(oSector,
	                                                             (uint16)FEE_BANK,
									                             (boolean)TRUE, u8EEPIndex);
	/* Configure the Virtual Sector Header depending on the State */
	/* Also determine, which Virtual sector need to be erased, add them to the internal queue */
	/* If two EEP's are configured, VS number's 1 and 2 are used by EEP1, 3 and 4 are used by EEP2 */
	if(VsState  ==  VsState_Active)
	{		
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorStateValue[0] = ActiveVSLo;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorStateValue[1] = ActiveVSHi;						
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorStateValue[2] = 0x00000000U;
		/* Remove the entry from Internal Erase Queue */
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32InternalEraseQueue = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32InternalEraseQueue & (~(0x1U<<(uint32)u16VirtualSectorIndex));
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16VirtualSectorIndex]=VsState_Active;		
	}
	else if(VsState == VsState_Invalid)
	{		
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorStateValue[0] = InvalidVSLo;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorStateValue[1] = InvalidVSHi;		
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorStateValue[2] = 0xFFFFFFFFU;
		/* Add the entry to Internal Erase Queue */
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32InternalEraseQueue |=  0x1U<<(uint32)u16VirtualSectorIndex;		
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16VirtualSectorIndex] = VsState_Invalid;							
	}
	else if(VsState == VsState_Empty)
	{		
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorStateValue[0] = EmptyVSLo;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorStateValue[1] = EmptyVSHi;				
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorStateValue[2] = 0xFFFFFFFFU;
		/* Removal of the entry from Internal Erase Queue will be done in Fee_Manager after writing complete VS
           Header */		
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16VirtualSectorIndex] = VsState_Empty;					
	}
	else if(VsState == VsState_Copy)
	{		
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorStateValue[0] = CopyVSLo;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorStateValue[1] = CopyVSHi;		
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorStateValue[2] = 0x0000FFFFU;
		/* Remove the entry from Internal Erase Queue */
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32InternalEraseQueue = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32InternalEraseQueue & (~(0x1U<<(uint32)u16VirtualSectorIndex));
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16VirtualSectorIndex] = VsState_Copy;					
	}
	else
	{			
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorStateValue[0] = ReadyforEraseVSLo;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorStateValue[1] = ReadyforEraseVSHi;			
		/* Add the entry to Internal Erase Queue */
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32InternalEraseQueue |= 0x1U<<(uint32)u16VirtualSectorIndex;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16VirtualSectorIndex] = VsState_ReadyForErase;							
	}
}

/**********************************************************************************************************************
 *  TI_FeeInternal_WriteDataF021
 *********************************************************************************************************************/
/*! \brief      This functions writes data into Flash.
 *  \param[in]	boolean bCopy
 *  \param[in]	uint16 u16WriteSize
 *  \param[in]	uint8 u8EEPIndex 
 *  \param[out] none 
 *  \return 	Number of bytes written onto Flash.
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
uint8 TI_FeeInternal_WriteDataF021(boolean bCopy,uint16 u16WriteSize, uint8 u8EEPIndex)
{	
	uint8 * pu8Data=0U;
	uint8 u8ActualWriteSize = 0x8U;	
	uint8 u8Offset = 0U;
	TI_Fee_AddressType Fee_WriteAddress=0U;
	uint32 u32FwpWriteDwordAccessor_temp = 0U;
	/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here.*/
	/*SAFETYMCUSW 93 S MR:6.1,6.2,10.1,10.2,10.3,10.4 <APPROVED> "Reason -  FWPWRITE_BYTE_ACCESSOR_ADDRESS is macro."*/
	FwpWriteByteAccessorType * oFwpWriteByteAccessor[16];	
	/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here.*/
	/*SAFETYMCUSW 93 S MR:6.1,6.2,10.1,10.2,10.3,10.4 <APPROVED> "Reason -  FWPWRITE_ECC_BYTE_ACCESSOR_ADDRESS is macro."*/
	#ifndef _L2FMC
	FwpWriteByteAccessorType * oFwpWriteEccByteAccessor = FWPWRITE_ECC_BYTE_ACCESSOR_ADDRESS;
	#endif	
	FwpWriteDWordAccessorType * oFwpWriteDwordAccessor[4];	
	uint32 u32Index=0U;	
	
	for(u32Index=0U;u32Index<4U;u32Index++)
	{
		oFwpWriteDwordAccessor[u32Index] = FWPWRITE_DWORD_ACCESSOR_ADDRESS+u32Index;
	}			
	
	for(u32Index=0U;u32Index<16U;u32Index++)
	{
		oFwpWriteByteAccessor[u32Index] = FWPWRITE_BYTE_ACCESSOR_ADDRESS+u32Index;
	}
			
	if((bCopy == TRUE))
	{
		Fee_WriteAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyWriteAddress;									
		/*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Reason -  Fee_pu8CopyData is assigned a value and it can't be NULL."*/
		/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here.*/
		if(NULL_PTR != TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8CopyData)
		{
			#if(TI_FEE_CHECK_BANK7_ACCESS == STD_ON)
				if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyCurrentAddress >= Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[0].Device_SectorStartAddress) &&
				#if (TI_FEE_GENERATE_DEVICEANDVIRTUALSECTORSTRUC == STD_ON)
				(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyCurrentAddress < Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[TI_Fee_MaxSectors-1U].Device_SectorStartAddress+
				Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[TI_Fee_MaxSectors-1U].Device_SectorLength))
				#else
				(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyCurrentAddress < Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[DEVICE_BANK_MAX_NUMBER_OF_SECTORS-1U].Device_SectorStartAddress+
				Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[DEVICE_BANK_MAX_NUMBER_OF_SECTORS-1U].Device_SectorLength))
				#endif
			#endif
			{
				pu8Data = TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8CopyData;
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8CopyData += u8ActualWriteSize;
			}
		}			
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyWriteAddress += u8ActualWriteSize;		
	}	
	else
	{
		Fee_WriteAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress;						
		/*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Reason -  Fee_pu8Data is assigned a value and it can't be NULL."*/
		/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here.*/
		if(NULL_PTR != TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8Data)
		{
			pu8Data = TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8Data;
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8Data += u8ActualWriteSize;
		}			
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress += u8ActualWriteSize;
	}		
	/*SAFETYMCUSW 114 S MR:12.6,13.2 <APPROVED> "Reason -  Eventhough expression is not boolean, 
	  we check for the function return value."*/
	/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/	
	/*SAFETYMCUSW 114 S MR:12.6,13.2 <APPROVED> "Reason -  LDRA does not understand macro 
      FAPI_CHECK_FSM_READY_BUSY."*/
	/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  ( pFapi_FmcRegistersType ) ( 0xFFF87000U ) ) casting 
	  is done in F021 library.*/
	if(FAPI_CHECK_FSM_READY_BUSY == Fapi_Status_FsmReady)
	{		
		/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/
        /*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here.*/		
		FLASH_CONTROL_REGISTER->Fbprot.u32Register = 1U;
		/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/
		/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here.*/		
		FLASH_CONTROL_REGISTER->Fbse.u32Register = 0xFFFFU;
		/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/
		/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here.*/		
		FLASH_CONTROL_REGISTER->Fbprot.u32Register = 0U;
		
		/*Unlock FSM registers for writing */
		/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/	
		/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here.*/
		FLASH_CONTROL_REGISTER->FsmWrEna.u32Register = 0x5U;		
		/* Set command to "Clear the Status Register" */
		/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/
		/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here.*/	
		FLASH_CONTROL_REGISTER->FsmCommand.FSM_COMMAND_BITS.FSMCMD = Fapi_ClearStatus;		
		/* Execute the Clear Status command */
		/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/	
		/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here.*/
		FLASH_CONTROL_REGISTER->FsmExecute.FSM_EXECUTE_BITS.FSMEXECUTE = 0x15U;				
		#if(TI_FEE_CHECK_BANK7_ACCESS == STD_ON)
		if((Fee_WriteAddress >= Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[0].Device_SectorStartAddress) && 
			#if (TI_FEE_GENERATE_DEVICEANDVIRTUALSECTORSTRUC == STD_ON)
			(Fee_WriteAddress < Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[TI_Fee_MaxSectors-1U].Device_SectorStartAddress+
			Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[TI_Fee_MaxSectors-1U].Device_SectorLength))
			#else
			(Fee_WriteAddress < Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[DEVICE_BANK_MAX_NUMBER_OF_SECTORS-1U].Device_SectorStartAddress+
			Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[DEVICE_BANK_MAX_NUMBER_OF_SECTORS-1U].Device_SectorLength))
			#endif				
		#endif	
		{
			/* Write address to FADDR register */
			/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/
			/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here.*/					
			FLASH_CONTROL_REGISTER->Faddr.u32Register = Fee_WriteAddress;		
			/* Check for correct offset address */
			/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/	
			/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here.*/
			u8Offset = (uint8)(Fee_WriteAddress & 0x08U) * (WIDTH_EEPROM_BANK >> 0x04U);
		
			/* Check if the number of bytes to write are less than 8. */
			u16WriteSize = (u16WriteSize < u8ActualWriteSize) ? u16WriteSize : u8ActualWriteSize;

			#ifdef _L2FMC
			FLASH_CONTROL_REGISTER->Ftctrl.FTCTRL_BITS.AutoCalc_EN=1U;
			#endif
			
			/* Copy the data into Flash Registers */
			for(u32Index=0U;u32Index<u16WriteSize;u32Index++)
			{				
				#if defined(_L2FMC) && defined(_BIG_ENDIAN)
				/*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Reason -  pu8Data is assigned a value and it can't be NULL."*/
				/*SAFETYMCUSW 436 S MR:17.1,17.4 <APPROVED> "Reason - Only limited index's at oFwpWriteDwordAccessor
				  are accessed."*/
				*oFwpWriteByteAccessor[L2EI8(u32Index+u8Offset)] = pu8Data[u32Index];
				#else
				/*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Reason -  pu8Data is assigned a value and it can't be NULL."*/			
				/*SAFETYMCUSW 436 S MR:17.1,17.4 <APPROVED> "Reason - Only limited index's at oFwpWriteDwordAccessor 
				  are accessed."*/			  
				*oFwpWriteByteAccessor[u32Index+u8Offset] = pu8Data[u32Index];
				#endif
			}	
			
			/* Supply the address where ECC is being calculated */
			/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/	
			/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here.*/
			FLASH_CONTROL_REGISTER->FemuAddr.u32Register = Fee_WriteAddress;

			#ifdef _LITTLE_ENDIAN
			/* Supply the upper 32bit word */			
			if(u8Offset != 0U)
			{
				/*SAFETYMCUSW 134 S MR:11.3 <APPROVED> "Reason -  Volatile variable usage is required here  */	
				u32FwpWriteDwordAccessor_temp = *oFwpWriteDwordAccessor[2];
			}
			else
			{
				/*SAFETYMCUSW 134 S MR:11.3 <APPROVED> "Reason -  Volatile variable usage is required here  */	
				u32FwpWriteDwordAccessor_temp = *oFwpWriteDwordAccessor[0];
			}
			FLASH_CONTROL_REGISTER->FemuDlsw.u32Register = u32FwpWriteDwordAccessor_temp;		
			/* Supply the lower 32bit word */			
			if(u8Offset != 0U)
			{
				/*SAFETYMCUSW 134 S MR:11.3 <APPROVED> "Reason -  Volatile variable usage is required here  */	
				u32FwpWriteDwordAccessor_temp = *oFwpWriteDwordAccessor[3];
			}
			else
			{
				/*SAFETYMCUSW 134 S MR:11.3 <APPROVED> "Reason -  Volatile variable usage is required here  */	
				u32FwpWriteDwordAccessor_temp = *oFwpWriteDwordAccessor[1];
			}
			FLASH_CONTROL_REGISTER->FemuDmsw.u32Register = u32FwpWriteDwordAccessor_temp;			
			#else
			/* Supply the upper 32bit word */					
			if(u8Offset != 0U)
			{
				/*SAFETYMCUSW 134 S MR:11.3 <APPROVED> "Reason -  Volatile variable usage is required here  */	
				u32FwpWriteDwordAccessor_temp = *oFwpWriteDwordAccessor[2];
			}
			else
			{
				/*SAFETYMCUSW 134 S MR:11.3 <APPROVED> "Reason -  Volatile variable usage is required here  */	
				u32FwpWriteDwordAccessor_temp = *oFwpWriteDwordAccessor[0];
			}
			FLASH_CONTROL_REGISTER->FemuDlsw.u32Register = u32FwpWriteDwordAccessor_temp;
			/* Supply the lower 32bit word */					
			if(u8Offset != 0U)
			{
				/*SAFETYMCUSW 134 S MR:11.3 <APPROVED> "Reason -  Volatile variable usage is required here  */	
				u32FwpWriteDwordAccessor_temp = *oFwpWriteDwordAccessor[3];
			}
			else
			{
				/*SAFETYMCUSW 134 S MR:11.3 <APPROVED> "Reason -  Volatile variable usage is required here  */	
				u32FwpWriteDwordAccessor_temp = *oFwpWriteDwordAccessor[1];
			}
			FLASH_CONTROL_REGISTER->FemuDmsw.u32Register = u32FwpWriteDwordAccessor_temp;
			#endif			
			#ifndef _L2FMC
			/* Place the Wrapper calculated ECC into FWPWRITE_ECC */
			/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/	
			/*SAFETYMCUSW 114 S MR:12.6,13.2 <APPROVED> "Reason -  Eventhough expression is not boolean, 
			  we check for the function return value."*/
			/*SAFETYMCUSW 436 S MR:17.1,17.4 <APPROVED> "Reason - Only limited index's at oFwpWriteEccByteAccessor 
			  are accessed."*/			  
			/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here.*/
			oFwpWriteEccByteAccessor[EI8(u8Offset?1:0)] = FLASH_CONTROL_REGISTER->FemuEcc.FEMU_ECC_BITS.EMU_ECC;
			#endif
			/* Set command to "Program" */
			/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/	
			/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here.*/
			FLASH_CONTROL_REGISTER->FsmCommand.FSM_COMMAND_BITS.FSMCMD = Fapi_ProgramData;		
			/* Execute the Program command */
			/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/	
			/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here.*/
			FLASH_CONTROL_REGISTER->FsmExecute.FSM_EXECUTE_BITS.FSMEXECUTE = 0x15U;		
		}				
		/* re-lock FSM registers to prevent writing */
		/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/	
		/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here.*/
		FLASH_CONTROL_REGISTER->FsmWrEna.u32Register = 0x2U;		
	}		
	return(u8ActualWriteSize);	
}

/**********************************************************************************************************************
 *  TI_FeeInternal_AlignAddressForECC
 *********************************************************************************************************************/
/*! \brief      This functions aligns address for ECC.
 *  \param[in]	TI_Fee_AddressType oAddress  
 *  \param[out] none 
 *  \return 	TI_Fee_AddressType oAddress
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
TI_Fee_AddressType TI_FeeInternal_AlignAddressForECC(TI_Fee_AddressType oAddress)
{	
	if((oAddress%0x08U)!=0U)
	{
		oAddress+=(0x08U-(oAddress%0x08U));
	}	
	return(oAddress);
}

/**********************************************************************************************************************
 *  TI_FeeInternal_WriteInitialize
 *********************************************************************************************************************/
/*! \brief      This functions initializes thw write buffers.
 *  \param[in]	TI_Fee_AddressType oFlashNextAddress
 *  \param[in]	uint8* DataBufferPtr
 *  \param[in]	uint8 u8EEPIndex 
 *  \param[out] none 
 *  \return 	none
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
void TI_FeeInternal_WriteInitialize(TI_Fee_AddressType oFlashNextAddress, uint8* DataBufferPtr, uint8 u8EEPIndex)
{	
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWriteBlockHeader = FALSE;	
	/* Determine the current Block Header Address */
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentBlockHeader = oFlashNextAddress;		
	/* Determine the next Address to which the data is to be written */
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress = oFlashNextAddress+TI_FEE_BLOCK_OVERHEAD;				
	/*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Reason -  DataBufferPtr is assigned a value and it can't be NULL."*/
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8DataStart = DataBufferPtr;	
	/*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Reason -  Fee_pu8DataStart is assigned a value and it can't be NULL."*/
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8Data = TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8DataStart;			
}

/**********************************************************************************************************************
 *  TI_FeeInternal_InvlalidateEraseInitialize
 *********************************************************************************************************************/
/*! \brief      This functions initializes the Invalidate or Erase of blocks.
 *  \param[in]	TI_Fee_AddressType oFlashNextAddress 
 *  \param[in]	uint8 u8EEPIndex 
 *  \param[out] none 
 *  \return 	none
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
static void TI_FeeInternal_InvlalidateEraseInitialize(TI_Fee_AddressType oFlashNextAddress, uint8 u8EEPIndex)
{
	/* Determine the next Address to which the data is to be written */	
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress = oFlashNextAddress;	
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWriteData = TRUE;	
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize = 0U;	
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentBlockHeader = 0x00000000U;	
}
/**********************************************************************************************************************
 *  TI_FeeInternal_CopyInitialize
 *********************************************************************************************************************/
/*! \brief      This functions initializes the copy of blocks.
 *  \param[in]	TI_Fee_AddressType oFlashNextAddress 
 *  \param[in]	uint8 u8EEPIndex 
 *  \param[out] none 
 *  \return 	none
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
static void TI_FeeInternal_CopyInitialize(boolean bBlockStatus, TI_Fee_AddressType oFlashNextAddress, uint8 u8EEPIndex,
                                          uint8 u8SingleBitError)
{		
	uint16 u16ArrayIndex = 0U;
	
	/* If Block is Valid, then copy it */
	if(bBlockStatus == TRUE)
	{
		/* Get the block index from Fee_u16BlockCopyIndex*/
		u16ArrayIndex = TI_FeeInternal_GetArrayIndex(0U, 0U, u8EEPIndex, FALSE);
		/* Determine the Block Size */
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16CopyBlockSize = TI_FeeInternal_GetBlockSize(u16ArrayIndex);
		/* Decrement block size by 8 since we already updated 8 bytes of block status*/
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16CopyBlockSize -= 8U;
		/* Initialize the Write Address & the pointer */		
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyWriteAddress = oFlashNextAddress;		
		/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
		/*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Reason -  TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyCurrentAddress 
		  is checked for NULL."*/
		/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here.*/
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8CopyData = (uint8 *)(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyCurrentAddress);		
		
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au16BlockOffset[TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockCopyIndex] = (uint16)((TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyNextAddress - (TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress))& 0x0000FFFFU);
		/* Update the next free write address */		
		if(0U == u8SingleBitError)
		{
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyNextAddress += TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16CopyBlockSize+8U;		
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyNextAddress;	
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextCopyVSwriteaddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyNextAddress;	
		}
		#if(TI_FEE_FLASH_ERROR_CORRECTION_HANDLING == TI_Fee_Fix)
		else
		{
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress += TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16CopyBlockSize;			
		}		
		#endif
	}
	else
	{
		/* Invalid Blocks are not copied */
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16CopyBlockSize = 0U;		
	}		
}

/**********************************************************************************************************************
 *  TI_FeeInternal_PollFlashStatus
 *********************************************************************************************************************/
/*! \brief      This function polls for Command status.
 *  \param[in]	none 
 *  \param[out] none 
 *  \return 	Status of Flash
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
 uint32 TI_FeeInternal_PollFlashStatus(void)
{
	uint32 u32FlashStatus = 0U;
	uint32 u32FlashBusy = 1U;
	uint32 u32Count = 0U;
	/* wait till FSM is Busy */
	while(u32FlashBusy == 1U)
	{
		/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/	
		/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here.*/
		u32FlashStatus = FAPI_GET_FSM_STATUS;			
		u32FlashBusy=(u32FlashStatus & 0x00000100U)>>8U;
		u32Count++;
		/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Reason - This is necessary.Wait untill FSM is BUSY."*/	
		if(u32Count>0xFFFF0000U)
		{
			u32FlashBusy = 0U;
		}		
	}
	return(u32FlashStatus);
}

/**********************************************************************************************************************
 *  TI_FeeInternal_GetBlockSize
 *********************************************************************************************************************/
/*! \brief      This functions returns the size of the Block including Block Header.
 *  \param[in]	uint16 BlockIndex 
 *  \param[out] none 
 *  \return 	Size of the block.
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
uint16 TI_FeeInternal_GetBlockSize(uint16 BlockIndex)
{
	uint16 u16BlockSize = 0U;
	/* Get the block size for the Block*/
	u16BlockSize=(Fee_BlockConfiguration[BlockIndex].FeeBlockSize);	
	/* Determine the BlockSize */	
	u16BlockSize+=(TI_FEE_BLOCK_OVERHEAD);	
	return(u16BlockSize);
}

/**********************************************************************************************************************
 *  TI_FeeInternal_FindNextVirtualSector
 *********************************************************************************************************************/
/*! \brief      This functions finds the next Virtual Sector to be marked Active.
 *  \param[in]	uint8 u8EEPIndex
 *  \param[out] none 
 *  \return 	Virtual sector
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
 uint8 TI_FeeInternal_FindNextVirtualSector(uint8 u8EEPIndex)
{
	uint8 u8ActiveVirtualSector = 0U;
	uint16 u16LoopIndex = 0U;
	uint16 u16LoopIndex1 = 0U;
	uint32 u32VirtualSectorStartAddress = 0U;
	uint32 u32VirtualSectorEndAddress = 0U;	
	Fapi_FlashSectorType oSectorStart,oSectorEnd;		
	
	if(0U == u8EEPIndex)
	{
		u16LoopIndex = 0U;	
		u16LoopIndex1 = (uint16)(TI_FEE_NUMBER_OF_VIRTUAL_SECTORS - TI_FEE_NUMBER_OF_VIRTUAL_SECTORS_EEP1);	
	}
	else
	{
		u16LoopIndex = TI_FEE_NUMBER_OF_VIRTUAL_SECTORS_EEP1;
		u16LoopIndex1 = TI_FEE_NUMBER_OF_VIRTUAL_SECTORS;	
	}		
	
	for(; u16LoopIndex<u16LoopIndex1 ; u16LoopIndex++)
	{		
		/* Find if any VS is empty and if found make it Active */
		if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16LoopIndex] == VsState_Empty)
		{
			/* Determine the Start & End Address for this Virtual Sector */			
			oSectorStart = Fee_VirtualSectorConfiguration[u16LoopIndex].FeeStartSector;
			oSectorEnd = Fee_VirtualSectorConfiguration[u16LoopIndex].FeeEndSector;				
			/*SAFETYMCUSW 91 D MR:16.10 <APPROVED> "Reason - Return value is used in following code."*/
			u32VirtualSectorStartAddress = TI_FeeInternal_GetVirtualSectorParameter(oSectorStart,
			                                                    (uint16)FEE_BANK,
														        (boolean)TRUE, u8EEPIndex);
            /* To avoid MISRA warning */
			u32VirtualSectorStartAddress = u32VirtualSectorStartAddress; 																	
			u32VirtualSectorEndAddress = TI_FeeInternal_GetVirtualSectorParameter(oSectorEnd,
			                                                     (uint16)FEE_BANK,
						                                         (boolean)TRUE, u8EEPIndex);
			/*SAFETYMCUSW 91 D 0 MR:16.10 <APPROVED> "Reason - Return value is used in following code."*/
			u32VirtualSectorEndAddress += TI_FeeInternal_GetVirtualSectorParameter(oSectorEnd,
			                                                     (uint16)FEE_BANK,
													              (boolean)FALSE, u8EEPIndex);
			/* To avoid MISRA warning */
			u32VirtualSectorEndAddress=u32VirtualSectorEndAddress;	
			/* Check for any non severe errors */		
			TI_FeeInternal_CheckForError(u8EEPIndex);
						
			if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error == Error_Nil)
			{				
				u8ActiveVirtualSector = Fee_VirtualSectorConfiguration[u16LoopIndex].FeeVirtualSectorNumber;											
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16LoopIndex]=VsState_Active;										
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress = u32VirtualSectorStartAddress;
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorEndAddress = u32VirtualSectorEndAddress;
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorStartAddress = u32VirtualSectorStartAddress;
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorEndAddress = u32VirtualSectorEndAddress;										
				break;				
			}			
		}		
	}

	/* No Empty Virtual Sector Found..then search for INVALID Virtual Sector which is Blank*/
	if(u8ActiveVirtualSector == 0U)
	{
		u8ActiveVirtualSector = TI_FeeInternal_FindInvalidVirtualSector(u8EEPIndex);
	}	

	/* All Invalid Sectors are not Blank, so find the next Invalid or Ready for Erase Virtual Sector  */
	/* Erase it and make it Active */
	if(u8ActiveVirtualSector == 0U)
	{
		u8ActiveVirtualSector = TI_FeeInternal_FindReadyForEraseVirtualSector(u8EEPIndex);
	}		
	if(u8ActiveVirtualSector == 0U)
	{		
		/* Update which of the VS's are Active. From Configuration, Application has to find which of the 
		   configured VS's need to be erased. */
		if(0 != TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector)
		{
			TI_Fee_u32ActCpyVS = 0x1U << (TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector-1U);
		}
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus = TI_FEE_ERROR;		
	}	
	return(u8ActiveVirtualSector);
}

/**********************************************************************************************************************
 *  TI_FeeInternal_BlankCheck
 *********************************************************************************************************************/
/*! \brief      This functions perform blank check of the VS.
 *  \param[in]	uint32 u32StartAddress
 *  \param[in]	uint32 u32EndAddress
 *  \param[in]	uint16 u16Bank
 *  \param[in]	uint8 u8EEPIndex
 *  \param[out] none 
 *  \return 	none
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
/*SAFETYMCUSW 61 D MR:8.10,8.11 <APPROVED> "Reason -  Cannot be static since it is used in format API."*/
 boolean TI_FeeInternal_BlankCheck(uint32 u32StartAddress, uint32 u32EndAddress, uint16 u16Bank, uint8 u8EEPIndex)
{
	Fapi_StatusType FlashStatus;
	boolean bFlashStatus = FALSE;
	Fapi_StatusType FlashECCStatus;
	boolean bFlashECCStatus = FALSE;	
	Fapi_FlashStatusWordType FlashStatusWord, *poFlashStatusWord = &FlashStatusWord;	
	uint32 u32ECCStartAddress=0U;
	uint32 u32ECCEndAddress=0U;
	uint16 u16LoopIndex=0U;
	boolean bSectorcheck = FALSE;
	
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_oBlankFailAddress = 0x0U;
	
	/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
	/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here.*/
	FlashStatus = Fapi_doBlankCheck((uint32_t *)(u32StartAddress),
	                                ((u32EndAddress-u32StartAddress)>>0x2U),
                                    /*SAFETYMCUSW 69 D MR:9.1 <APPROVED> "Reason -  poFlashStatusWord is a pointer 
									  to structure FlashStatusWord which is filled by Fapi_doBlankCheck."*/
									poFlashStatusWord
                                   );
	if(FlashStatus == Fapi_Status_Success)
	{
		bFlashStatus = TRUE;
	}
	else
	{
		bFlashStatus = FALSE;
	}

	/* Check if ECC for EEPROM is also blank, only if EEPROM blankcheck is successfull.*/	
	/*SAFETYMCUSW 433 S MR:6.1,6.2,10.1,10.2,10.3,10.4  <APPROVED> "Reason - LDRA Version
      problem. Latest version do not have this warning."*/
	/*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/
	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Reason - This is necessary."*/	
	if(TRUE == bFlashStatus)
	{		
		#if (TI_FEE_GENERATE_DEVICEANDVIRTUALSECTORSTRUC == STD_ON)
		for(u16LoopIndex = 0U ; u16LoopIndex<TI_Fee_MaxSectors ; u16LoopIndex++)
		#else
		for(u16LoopIndex = 0U ; u16LoopIndex<DEVICE_BANK_MAX_NUMBER_OF_SECTORS ; u16LoopIndex++)
		#endif	
		{
			/* Check if the Sector specified matches the Sector name in the Device configuration */
			if(u32StartAddress  ==  Device_FlashDevice.Device_BankInfo[u16Bank].Device_SectorInfo[u16LoopIndex].Device_SectorStartAddress)	
			{
				u32ECCStartAddress = Device_FlashDevice.Device_BankInfo[u16Bank].Device_SectorInfo[u16LoopIndex].Device_EccAddress;			
				u32ECCEndAddress = u32ECCStartAddress + ((Device_FlashDevice.Device_BankInfo[u16Bank].Device_SectorInfo[u16LoopIndex].Device_EccLength));
				/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
				/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here.*/
				FlashECCStatus = Fapi_doBlankCheck((uint32_t *)(u32ECCStartAddress),
										((u32ECCEndAddress-u32ECCStartAddress)>>0x2U),
										poFlashStatusWord
									   );
				bSectorcheck = TRUE;					   
			
				if(FlashECCStatus == Fapi_Status_Success)
				{				
					bFlashECCStatus = TRUE;
				}
				else
				{
					bFlashECCStatus = FALSE;
				}
				break;
			}	
		}
	}

	/*SAFETYMCUSW 433 S MR:6.1,6.2,10.1,10.2,10.3,10.4  <APPROVED> "Reason - LDRA Version
      problem. Latest version do not have this warning."*/
	/*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/  
	if(TRUE == bSectorcheck	)
	{
		/*SAFETYMCUSW 114 S MR:12.6,13.2 <APPROVED> "Reason -  Eventhough expression is not boolean, 
		  we get either TRUE or FALSE."*/
		bFlashStatus = (bFlashStatus && bFlashECCStatus);
	}	
	if(bFlashStatus == FALSE)
	{		
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_oBlankFailAddress = FlashStatusWord.au32StatusWord[0];		
	}	
	return(bFlashStatus);
}

/**********************************************************************************************************************
 *  TI_FeeInternal_FindInvalidVirtualSector
 *********************************************************************************************************************/
/*! \brief      This function finds the next Invalid Virtual Sector to be marked as Active 
 *  \param[in]	uint8 u8EEPIndex
 *  \param[out] none 
 *  \return 	Virtual sector
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
static uint8 TI_FeeInternal_FindInvalidVirtualSector(uint8 u8EEPIndex)
{
	uint16 u16LoopIndex = 0U;
	uint16 u16LoopIndex1 = 0U;
	uint8 u8ActiveVirtualSector = 0U;	
	Fapi_FlashSectorType oSectorStart,oSectorEnd;	
	uint32 u32VirtualSectorEndAddress=0U;
	boolean bFlashStatus=0U;
	#if(TI_FEE_USEPARTIALERASEDSECTOR==STD_ON)
	uint32 **ppu32ReadHeader = 0U;
	uint32 u32VirtualSectorHeaderAddress = 0U;
	#endif
	

	if(0U == u8EEPIndex)
	{
		u16LoopIndex = 0U;	
		u16LoopIndex1 = (uint16)(TI_FEE_NUMBER_OF_VIRTUAL_SECTORS - TI_FEE_NUMBER_OF_VIRTUAL_SECTORS_EEP1);	
	}
	else
	{
		u16LoopIndex = TI_FEE_NUMBER_OF_VIRTUAL_SECTORS_EEP1;
		u16LoopIndex1 = TI_FEE_NUMBER_OF_VIRTUAL_SECTORS;	
	}
	
	for( ; u16LoopIndex<u16LoopIndex1 ; u16LoopIndex++)	
	{		
		/* Check if the Virtual Sector is in Invalid State */
		if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16LoopIndex] == VsState_Invalid)
		{
			/* Determine the Start & End Address for this Virtual Sector */				
			oSectorStart = Fee_VirtualSectorConfiguration[u16LoopIndex].FeeStartSector;
			oSectorEnd = Fee_VirtualSectorConfiguration[u16LoopIndex].FeeEndSector;			
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress = TI_FeeInternal_GetVirtualSectorParameter(oSectorStart,(uint16)FEE_BANK,(boolean)TRUE,u8EEPIndex);			
			u32VirtualSectorEndAddress = TI_FeeInternal_GetVirtualSectorParameter(oSectorEnd,
			                                                     (uint16)FEE_BANK,
															     (boolean)TRUE, u8EEPIndex);
			/*SAFETYMCUSW 91 D MR:16.10 <APPROVED> "Reason - Return value is used in following code."*/
			u32VirtualSectorEndAddress+=TI_FeeInternal_GetVirtualSectorParameter(oSectorEnd,
			                                                     (uint16)FEE_BANK,
												                 (boolean)FALSE, u8EEPIndex);
            /* To avoid MISRA warning */  																		
			u32VirtualSectorEndAddress=u32VirtualSectorEndAddress;
			TI_FeeInternal_GetVirtualSectorIndex(oSectorStart,oSectorEnd,
			                                    (uint16)FEE_BANK,
			                                    (boolean)TRUE,(uint8)u8EEPIndex);
			
			/* Check for any non severe errors */		
			TI_FeeInternal_CheckForError(u8EEPIndex);
			
			if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error == Error_Nil)
			{
				/* If Erase was suspended, Resume Erase */
				if(TRUE == TI_Fee_bEraseSuspended)
				{
					/*Resuming Erase when it was not suspended has no effect */
					(void)Fapi_issueAsyncCommand(Fapi_EraseResume);
					TI_Fee_bEraseSuspended = FALSE;
					/*Polling is required here since erasing takes time. Since this API is called either from INI or cyclic container,
					  higher priority tasks are not blocked. */
					/*SAFETYMCUSW 91 D MR:16.10 <APPROVED> "Reason - Return value is not required."*/
					(void)TI_FeeInternal_PollFlashStatus();
				}

				/* Check if it is Blank */
				bFlashStatus = TI_FeeInternal_BlankCheck(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress,
				                            u32VirtualSectorEndAddress,
				                            (uint16)FEE_BANK,											
											u8EEPIndex
				                           );

				/* If it is Blank, Make this Active */
				/*SAFETYMCUSW 433 S MR:6.1,6.2,10.1,10.2,10.3,10.4  <APPROVED> "Reason - LDRA Version
                  problem. Latest version do not have this warning."*/
				/*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/
				if(TRUE == bFlashStatus)
				{					
					u8ActiveVirtualSector = Fee_VirtualSectorConfiguration[u16LoopIndex].FeeVirtualSectorNumber;					
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorEndAddress = u32VirtualSectorEndAddress;
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16LoopIndex]=VsState_Active;
					/*SAFETYMCUSW 409 S MR:14.6 <APPROVED> "Reason -  break statement is intentionally used twice."*/	
					break;
				}
				else 
				{
					#if(TI_FEE_USEPARTIALERASEDSECTOR==STD_ON)
					u32VirtualSectorHeaderAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress+8U;
					/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
					/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
					ppu32ReadHeader = (uint32 **)&u32VirtualSectorHeaderAddress;
					if(((TI_Fee_GlobalVariables[u8EEPIndex].Fee_oBlankFailAddress < (TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress+8U)) &&
						((**ppu32ReadHeader) == 0xFFFFFFFFU)) ||
						(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oBlankFailAddress >= (TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress+12U))
					  )					
					{
						/* If blank check failed at first eight bytes of VS Header status and if the next four bytes of VS header are F's, 
							or if the blankcheck failed at address other than VS header, then VS can still be used */
						u8ActiveVirtualSector = Fee_VirtualSectorConfiguration[u16LoopIndex].FeeVirtualSectorNumber;					
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorEndAddress = u32VirtualSectorEndAddress;
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16LoopIndex]=VsState_Active;
						/*SAFETYMCUSW 409 S MR:14.6 <APPROVED> "Reason -  break statement is intentionally used twice."*/	
						break;					
					}
					#endif
				}				
			}			
		}		
	}
	return(u8ActiveVirtualSector);
}

/**********************************************************************************************************************
 *  TI_FeeInternal_FindReadyForEraseVirtualSector
 *********************************************************************************************************************/
/*! \brief      This function finds the next Ready for Erase Virtual Sector to be marked as Active.
 *  \param[in]	uint8 u8EEPIndex
 *  \param[out] none 
 *  \return 	Virtual sector 
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
static uint8 TI_FeeInternal_FindReadyForEraseVirtualSector(uint8 u8EEPIndex)
{
	uint16 u16LoopIndex = 0U;
	uint16 u16LoopIndex1 = 0U;
	uint8 u8ActiveVirtualSector = 0U;	
	uint8 u8Index = 0U;
	Fapi_FlashSectorType oSectorStart,oSectorEnd;	
	uint32 u32VirtualSectorEndAddress = 0U;
	boolean bFlashStatus = 0U;
	#if(TI_FEE_USEPARTIALERASEDSECTOR==STD_ON)
	uint32 **ppu32ReadHeader = 0U;
	uint32 u32VirtualSectorHeaderAddress = 0U;
	#endif

	uint8 u8VirtualSectorLimit = 0U;
	
	if(0U == u8EEPIndex)
	{
		u16LoopIndex = 0U;	
		u16LoopIndex1 = (uint16)(TI_FEE_NUMBER_OF_VIRTUAL_SECTORS - TI_FEE_NUMBER_OF_VIRTUAL_SECTORS_EEP1);	
	}
	else
	{
		u16LoopIndex = TI_FEE_NUMBER_OF_VIRTUAL_SECTORS_EEP1;
		u16LoopIndex1 = TI_FEE_NUMBER_OF_VIRTUAL_SECTORS;	
	}

	/* If Erase was suspended, Resume Erase */
	if(TRUE == TI_Fee_bEraseSuspended)
	{
		/*Resuming Erase when it was not suspended has no effect */
		(void)Fapi_issueAsyncCommand(Fapi_EraseResume);
		TI_Fee_bEraseSuspended = FALSE;
		/*Polling is required here since erasing takes time. Since this API is called either from INI or cyclic container,
		  higher priority tasks are not blocked. */
		/*SAFETYMCUSW 91 D MR:16.10 <APPROVED> "Reason - Return value is not required."*/
		(void)TI_FeeInternal_PollFlashStatus();
	}

	for(;u16LoopIndex<u16LoopIndex1;u16LoopIndex++)
	{		
		/* Check if the Virtual Sector is in Ready for Erase or Invalid State */
		if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16LoopIndex] == VsState_ReadyForErase) ||
		   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16LoopIndex] == VsState_Invalid))
		{
			/* Determine the Start & End Address for this Virtual Sector */				
			oSectorStart = Fee_VirtualSectorConfiguration[u16LoopIndex].FeeStartSector;
			oSectorEnd = Fee_VirtualSectorConfiguration[u16LoopIndex].FeeEndSector;
			
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress = TI_FeeInternal_GetVirtualSectorParameter(oSectorStart,(uint16)FEE_BANK,(boolean)TRUE, u8EEPIndex );			
			u32VirtualSectorEndAddress = TI_FeeInternal_GetVirtualSectorParameter(oSectorEnd,(uint16)FEE_BANK,(boolean)TRUE,u8EEPIndex);
			/*SAFETYMCUSW 91 D MR:16.10 <APPROVED> "Reason - Return value is used in following code."*/
			/*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/
			u32VirtualSectorEndAddress += TI_FeeInternal_GetVirtualSectorParameter(oSectorEnd,(uint16)FEE_BANK,FALSE,(uint8)u8EEPIndex);
			/* To avoid MISRA warning */
			u32VirtualSectorEndAddress=u32VirtualSectorEndAddress;
			TI_FeeInternal_GetVirtualSectorIndex(oSectorStart,oSectorEnd,
			                                     (uint16)FEE_BANK,
												 (boolean)TRUE,u8EEPIndex);
			
			/* Check for any non severe errors */		
			TI_FeeInternal_CheckForError(u8EEPIndex);
			
			if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error == Error_Nil)
			{
				u8VirtualSectorLimit = (TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8VirtualSectorEnd-TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8VirtualSectorStart) + 1U;
				/* Erase the Virtual Sector and make it Active */
				for(u8Index = 0U; u8Index < u8VirtualSectorLimit; u8Index++)
				{				  	
				  	TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress = Device_FlashDevice.Device_BankInfo[FEE_BANK].Device_SectorInfo[TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8VirtualSectorEnd].Device_SectorStartAddress;					
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8VirtualSectorEnd -= 1U; 
					(void)Fapi_setActiveFlashBank(Device_FlashDevice.Device_BankInfo[FEE_BANK].Device_Core);
					/* Errata : Enable only required sector to erase. */
					TI_FeeInternal_EnableRequiredFlashSector(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress);		
					/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
					/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
					if(Fapi_issueAsyncCommandWithAddress(Fapi_EraseSector,
												 (uint32_t *)TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress
												)==Fapi_Status_Success)
					{
						/* Nothing to be done here */
					}
					/*Polling is required here since erasing takes time. Since this API is called either from INI or cyclic container,
					  higher priority tasks are not blocked. */
					/*SAFETYMCUSW 91 D MR:16.10 <APPROVED> "Reason - Return value is not required."*/
					(void)TI_FeeInternal_PollFlashStatus();
					/* Errata : Enable all sector's since only required sector was enabled for erase .*/
					(void)Fapi_enableEepromBankSectors(FEE_ENABLE_SECTORS_31_00, FEE_ENABLE_SECTORS_63_32);
				}				
				/* Check if it is Blank */
				bFlashStatus = TI_FeeInternal_BlankCheck(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress,
				                                         u32VirtualSectorEndAddress,
											             (uint16)FEE_BANK,
									                     u8EEPIndex);
				/*SAFETYMCUSW 433 S MR:6.1,6.2,10.1,10.2,10.3,10.4  <APPROVED> "Reason - LDRA Version
                  problem. Latest version do not have this warning."*/
				/*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/
				if(TRUE == bFlashStatus)
				{
					/* Mark it as Active VS */					
					u8ActiveVirtualSector = Fee_VirtualSectorConfiguration[u16LoopIndex].FeeVirtualSectorNumber;					
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorEndAddress = u32VirtualSectorEndAddress;
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorEraseCount[u16LoopIndex]++;
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16LoopIndex]=VsState_Active;
					/*SAFETYMCUSW 409 S MR:14.6 <APPROVED> "Reason -  break statement is intentionally used twice."*/	
					break;
				}
				else
				{
					#if(TI_FEE_USEPARTIALERASEDSECTOR==STD_ON)
					u32VirtualSectorHeaderAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress+8U;
					/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
					/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
					ppu32ReadHeader = (uint32 **)&u32VirtualSectorHeaderAddress;
					if(((TI_Fee_GlobalVariables[u8EEPIndex].Fee_oBlankFailAddress < (TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress+8U)) &&
						((**ppu32ReadHeader) == 0xFFFFFFFFU)) ||
						(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oBlankFailAddress >= (TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress+12U))
					  )
					{
						/* If blank check failed at first eight bytes of VS Header status and if the next 
						   four bytes of VS header are F's, or if the blankcheck failed at address other 
						   than VS header, then VS can still be used */
						u8ActiveVirtualSector = Fee_VirtualSectorConfiguration[u16LoopIndex].FeeVirtualSectorNumber;					
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorEndAddress = u32VirtualSectorEndAddress;
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorEraseCount[u16LoopIndex]++;
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16LoopIndex]=VsState_Active;
						/*SAFETYMCUSW 409 S MR:14.6 <APPROVED> "Reason -  break statement is intentionally used twice."*/	
						break;								
					} 
					else
					#endif
					{
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error = Error_EraseVS;
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_FAILED;
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus = TI_FEE_ERROR;
						TI_Fee_u8ErrEraseVS = 0x1U << (Fee_VirtualSectorConfiguration[u16LoopIndex].FeeVirtualSectorNumber-1U);
					}	
				}
			}			
		}		
	}
	return(u8ActiveVirtualSector);
}


/**********************************************************************************************************************
 *  TI_FeeInternal_GetVirtualSectorIndex
 *********************************************************************************************************************/
/*! \brief      This function returns the Virtual Sector index for the Start & End Sectors of a Virtual Sector
 *  \param[in]	Fapi_FlashSectorType oSectorStart
 *  \param[in]	Fapi_FlashSectorType oSectorEnd
 *  \param[in]	uint16 u16Bank
 *  \param[in]	boolean bOperation
 *  \param[in]	uint8 u8EEPIndex
 *  \param[out] none 
 *  \return 	none 
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
/*SAFETYMCUSW 61 X MR:1.4,5.1 <APPROVED> "Reason -  TI_FeeInternal_GetVirtualSectorIndex name is required here."*/
/*SAFETYMCUSW 61 D MR:8.10,8.11 <APPROVED> "Reason -  Cannot be static since it is used in format API."*/
void TI_FeeInternal_GetVirtualSectorIndex(Fapi_FlashSectorType oSectorStart, Fapi_FlashSectorType oSectorEnd,
                                           uint16 u16Bank, boolean bOperation, uint8 u8EEPIndex)
{
	uint8 u8Index = 0U;
	uint8  u8Status = 0U;
	boolean bExceed = FALSE;	
	
	#if (TI_FEE_GENERATE_DEVICEANDVIRTUALSECTORSTRUC == STD_ON)
	for(u8Index = 0U ; u8Index<TI_Fee_MaxSectors ; u8Index++)
	#else
	for( u8Index = 0U ; u8Index<DEVICE_BANK_MAX_NUMBER_OF_SECTORS ; u8Index++)
	#endif
	{
		/* Check if the Sector specified matches the Start Sector name in the Device configuration */
		if(oSectorStart == Device_FlashDevice.Device_BankInfo[u16Bank].Device_SectorInfo[u8Index].Device_Sector)
		{
			if(bOperation == TRUE)
			{
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8VirtualSectorStart = u8Index;
			}
			else
			{
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8InternalVirtualSectorStart = u8Index;
			}
			u8Status++;
		}		
		/* Check if the Sector specified matches the End Sector name in the Device configuration */
		if(oSectorEnd == Device_FlashDevice.Device_BankInfo[u16Bank].Device_SectorInfo[u8Index].Device_Sector)
		{
			if(bOperation == TRUE)
			{
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8VirtualSectorEnd = u8Index;
			}
			else
			{
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8InternalVirtualSectorEnd = u8Index;
			}
			u8Status++;
		}		
		if(Device_FlashDevice.Device_BankInfo[u16Bank].Device_SectorInfo[u8Index].Device_SectorStartAddress == 0xFFFFFFFFU)
		{
			/* Exceeded the number of sectors on the bank */
			bExceed = TRUE;
		}		
		if((u8Status == 2U)||(bExceed == TRUE))
		{
			break;
		}		
	}
	if(bExceed == TRUE)
	{
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error = Error_ExceedSectorOnBank;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus = TI_FEE_ERROR;
	}		
}

/**********************************************************************************************************************
 *  TI_FeeInternal_GetBlockNumber
 *********************************************************************************************************************/
/*! \brief      This functions returns the Block number after removing the DataSet Bits.
 *  \param[in]	uint16 BlockNumber 
 *  \param[out] none 
 *  \return 	uint16 BlockNumber 
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
 uint16 TI_FeeInternal_GetBlockNumber(uint16 BlockNumber)
{
	uint16 u16BlockNumber = BlockNumber;
	/*SAFETYMCUSW 334 S MR:10.5 <APPROVED> "Reason -  ~ operator usage is required here."*/
	#if (TI_FEE_VARIABLE_DATASETS == STD_ON)
	u16BlockNumber = (BlockNumber & (~TI_Fee_u8DataSets));
	u16BlockNumber = u16BlockNumber >> TI_FEE_DATASELECT_BITS;
	#endif
	return(u16BlockNumber);
}

/**********************************************************************************************************************
 *  TI_FeeInternal_GetBlockIndex
 *********************************************************************************************************************/
/*! \brief      This function returns the Array index for a particular Block.
 *  \param[in]	uint16 BlockNumber 
 *  \param[out] none 
 *  \return 	uint16 BlockIndex
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
uint16 TI_FeeInternal_GetBlockIndex(uint16 BlockNumber)
{
	uint16 u16BlockIndex = 0xFFFFU;
	uint16 u16LoopIndex =0U;

	/* find out the index of Block Number in the Block Configuration */
	for(u16LoopIndex=0U ; u16LoopIndex<TI_FEE_NUMBER_OF_BLOCKS ; u16LoopIndex++)	
	{
		if(BlockNumber == Fee_BlockConfiguration[u16LoopIndex].FeeBlockNumber)
		{
			u16BlockIndex = u16LoopIndex;
			break;
		}		
	}	
	return(u16BlockIndex);
}

/**********************************************************************************************************************
 *  TI_FeeInternal_GetDataSetIndex
 *********************************************************************************************************************/
/*! \brief      This functions returns the DataSet index after removing the Block number.
 *  \param[in]	uint16 BlockNumber 
 *  \param[out] none 
 *  \return 	uint16 u16DataSetIndex
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
 uint16 TI_FeeInternal_GetDataSetIndex(uint16 BlockNumber)
{
	uint16 u16DataSetIndex = 0U;
	u16DataSetIndex=(BlockNumber & TI_Fee_u8DataSets);
	return(u16DataSetIndex);
}

/**********************************************************************************************************************
 *  TI_FeeInternal_GetArrayIndex
 *********************************************************************************************************************/
/*! \brief      This function returns the Block index for a particular Block.
 *  \param[in]	uint16 BlockNumber 
 *  \param[in]	uint16 DataSetNumber
 *  \param[out] none 
 *  \return 	uint16 u16RetValue
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
uint16 TI_FeeInternal_GetArrayIndex(uint16 BlockNumber, uint16 DataSetNumber, uint8 u8EEPIndex, boolean bCallContext)
{
	uint16 u16ArrayIndex = 0U;
	uint16 u16LoopIndex = 0U;
	uint16 u16RetValue = 0U;

	if(TRUE == bCallContext)
	{
		/* find out the index of Block Number in the Block Configuration */
		for(u16LoopIndex=0U ; u16LoopIndex<TI_FEE_NUMBER_OF_BLOCKS ; u16LoopIndex++)	
		{			
			if(BlockNumber == Fee_BlockConfiguration[u16LoopIndex].FeeBlockNumber)
			{
				#if (TI_FEE_VARIABLE_DATASETS == STD_ON)
				u16ArrayIndex += DataSetNumber;
				#endif
				break;
			}
			u16ArrayIndex += Fee_BlockConfiguration[u16LoopIndex].FeeNumberOfDataSets;
		}
		u16RetValue=u16ArrayIndex;	
	}
	else
	{
		for(u16LoopIndex=0U ; u16LoopIndex<TI_FEE_NUMBER_OF_BLOCKS ; u16LoopIndex++)	
		{					
			u16ArrayIndex += Fee_BlockConfiguration[u16LoopIndex].FeeNumberOfDataSets;	
			
			if(u16ArrayIndex > TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockCopyIndex)
			{
				break;
			}
		}
		u16RetValue=u16LoopIndex;	
	}
	return(u16RetValue);
}
/**********************************************************************************************************************
 *  TI_FeeInternal_UpdateBlockOffsetArray
 *********************************************************************************************************************/
/*! \brief      This function initializes the Block Offset Array
 *  \param[in]	uint8 u8VirtualSector
 *  \param[in]	uint8 u8EEPIndex
 *  \param[in]	boolean bActCpyVS
 *  \param[out] none 
 *  \return 	none
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
void TI_FeeInternal_UpdateBlockOffsetArray(uint8 u8EEPIndex, boolean bActCpyVS, uint8 u8VirtualSector)
{
	uint32 au32BlockAddress[2];
	uint32 au32BlockStatus[2];
	uint32 u32BlockStartAddress = 0U;
	uint32 u32VirtualSectorEndAddress = 0U;
	uint32 u32VirtualSectorStartAddress = 0U;
	uint32 u32BlockNumberTemp;
	uint32 **ppu32ReadHeader = 0U;
	uint16 u16BlockNumber = 0U;
	uint16 u16BlockNumberWithoutDataset = 0U;
	uint16 u16BlockIndex = 0U;
	uint16 u16BlockSize = 0U;				
	uint16 u16DataSetNumber = 0U;
	uint16 u16Index = 0U;
	uint16 u16Index1 = 0U;
	uint16 u16ArrayIndex = 0U;
	Fapi_FlashSectorType oSectorStart =Fapi_FlashSector63;
	Fapi_FlashSectorType oSectorEnd = Fapi_FlashSector63;
	uint8 u8cnt=0U;
	uint32 u32BlockStartAddresstemp = 0U;	
	boolean bFlashStatus = FALSE;
	uint16 u16LoopIndex = 0U;	
	boolean bBlockFoundInConfig = FALSE;
	#if (TI_FEE_NUMBER_OF_UNCONFIGUREDBLOCKSTOCOPY != 0U)
	static uint16 u16UnconfiguredBlockcnt = 0U;
	static uint16 u16UnconfiguredBlockstoCopy[TI_FEE_NUMBER_OF_UNCONFIGUREDBLOCKSTOCOPY];
	boolean bDoNotCopy = FALSE;
	uint16 u16LoopIndex1 = 0U;
	#endif
	
	if(0U==u8EEPIndex)
	{
		u16Index = 0U;
		u16Index1 = (uint16)(TI_FEE_NUMBER_OF_VIRTUAL_SECTORS - TI_FEE_NUMBER_OF_VIRTUAL_SECTORS_EEP1);
	}
	else
	{
		u16Index = TI_FEE_NUMBER_OF_VIRTUAL_SECTORS_EEP1;
		u16Index1 = TI_FEE_NUMBER_OF_VIRTUAL_SECTORS;
	}
	
	for(; u16Index < u16Index1 ; u16Index++)	
	{
		if(u8VirtualSector == Fee_VirtualSectorConfiguration[u16Index].FeeVirtualSectorNumber)
		{
			oSectorStart = Fee_VirtualSectorConfiguration[u16Index].FeeStartSector;
			oSectorEnd = Fee_VirtualSectorConfiguration[u16Index].FeeEndSector;
			break;
		}
	}	
	u32VirtualSectorStartAddress = TI_FeeInternal_GetVirtualSectorParameter(oSectorStart,
	                                  (uint16)FEE_BANK,(boolean)TRUE, u8EEPIndex);
	u32VirtualSectorEndAddress = TI_FeeInternal_GetVirtualSectorParameter(oSectorEnd,
	                                  (uint16)FEE_BANK,(boolean)TRUE, u8EEPIndex);
	u32VirtualSectorEndAddress += TI_FeeInternal_GetVirtualSectorParameter(oSectorEnd,
	                                 (uint16)FEE_BANK,(boolean)FALSE, u8EEPIndex);

	/* First block starts after VS header */
	u32BlockStartAddress  =  u32VirtualSectorStartAddress+TI_FEE_VIRTUAL_SECTOR_OVERHEAD + 16U; 	
	
	/* Scan the sector until empty block is found and update the block offset array */
	while(u32BlockStartAddress < u32VirtualSectorEndAddress)
	{																				  
		/* Wait till FSM is READY */
		(void)TI_FeeInternal_PollFlashStatus();
		/* read the block number and get block details */						
		/* Block number is last two bytes of block header. If block header is 24 bytes(0-23), 
		   22 and 23 bytes are block number */		
		u32BlockStartAddress += (((TI_FEE_BLOCK_OVERHEAD >> 2U)-1U) << 2U);		
		/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
		/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
		ppu32ReadHeader = (uint32 **)&u32BlockStartAddress;								
		u32BlockNumberTemp = **ppu32ReadHeader;		 
		u16BlockNumber  =  (uint16)u32BlockNumberTemp;
		u32BlockStartAddress -= (((TI_FEE_BLOCK_OVERHEAD >> 2U)-1U) << 2U);
		if(u32BlockStartAddresstemp != u32BlockStartAddress)
		{
			u32BlockStartAddresstemp = u32BlockStartAddress;
			u8cnt=0U;	
		}	
		if((u16BlockNumber != 0xFFFFU) && (u16BlockNumber != 0x0000U))
		{		
			/*SAFETYMCUSW 91 D MR:16.10 <APPROVED> "Reason - Return value is used in following code."*/
			u16DataSetNumber  =  TI_FeeInternal_GetDataSetIndex(u16BlockNumber);
			/* To avoid MISRA warning */
			u16DataSetNumber=u16DataSetNumber;
			u16BlockNumberWithoutDataset  =  TI_FeeInternal_GetBlockNumber(u16BlockNumber);
			/*SAFETYMCUSW 91 D MR:16.10 <APPROVED> "Reason - Return value is used in following code."*/
			u16BlockIndex  =  TI_FeeInternal_GetBlockIndex(u16BlockNumberWithoutDataset);						
			/* To avoid MISRA warning */
			u16BlockIndex=u16BlockIndex;
			u16ArrayIndex = TI_FeeInternal_GetArrayIndex(u16BlockNumberWithoutDataset, u16DataSetNumber, u8EEPIndex, TRUE);
			/* To avoid MISRA warning */
			u16ArrayIndex=u16ArrayIndex;
		}					
		/* Read block status from block header */
		au32BlockAddress[0]  =  u32BlockStartAddress;
		au32BlockAddress[1]  =  au32BlockAddress[0]+4U;	
		/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
		/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
		ppu32ReadHeader = (uint32 **)&au32BlockAddress[0];
		au32BlockStatus[0] = **ppu32ReadHeader;
		/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
		/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
		ppu32ReadHeader=(uint32 **)&au32BlockAddress[1];
		au32BlockStatus[1] = **ppu32ReadHeader;		
		
		/* Check if the block is configired */		
		for(u16LoopIndex=0U ; u16LoopIndex<TI_FEE_NUMBER_OF_BLOCKS ; u16LoopIndex++)	
		{
			if(u16BlockNumberWithoutDataset == Fee_BlockConfiguration[u16LoopIndex].FeeBlockNumber)
			{
				bBlockFoundInConfig = TRUE;					
				break;	
			}
			else
			{
				bBlockFoundInConfig = FALSE;
			}	
		}		
		
		/* If block is configured, read block size from configuration, else read it from block header */
		/*SAFETYMCUSW 433 S MR:6.1,6.2,10.1,10.2,10.3,10.4  <APPROVED> "Reason - LDRA Version
          problem. Latest version do not have this warning."*/
		/*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/
		if(TRUE == bBlockFoundInConfig)
		{
			/*SAFETYMCUSW 91 D MR:16.10 <APPROVED> "Reason - Return value is used in following code."*/
			u16BlockSize  =  TI_FeeInternal_GetBlockSize(u16BlockIndex);
			/* To avoid MISRA warning */
			u16BlockSize=u16BlockSize;
		}				
		else
		{
			/* If some blocks were previously written but deleted from configuration, read the block size from EEP */
			/* Length of the block is present in 2 bytes of last 4 bytes*/		
			/* If block header is 24 bytes(0-23), 20-21 bytes are block size */
			u32BlockStartAddress += (((TI_FEE_BLOCK_OVERHEAD >> 2U)-1U) << 2U);
			/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/	
			/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
			ppu32ReadHeader = (uint32 **)&u32BlockStartAddress;
			u16BlockSize = (uint16)(((**ppu32ReadHeader)&0xFFFF0000U)>>16U);
			/*TI_FeeInternal_GetBlockSize will return block size+block header. Since here blocksize is directly read from 
			  EEP, Block Overhead nees to be added */
			u16BlockSize += TI_FEE_BLOCK_OVERHEAD;
			u32BlockStartAddress -= (((TI_FEE_BLOCK_OVERHEAD >> 2U)-1U) << 2U);
		}	
		
		if((au32BlockStatus[0] == ValidBlockLo) && (au32BlockStatus[1] == ValidBlockHi))
		{ 			
			/* Update block copied status */
			if(bActCpyVS == FALSE)
			{					
				/* If previously copy operation was started and only 8/16 bytes of block header were copied, then increment the address by 
				   block header size and start copying data */
				if(0xFFFFU == u16BlockSize)
				{
					u16BlockSize += TI_FEE_BLOCK_OVERHEAD;						
				}
				/*SAFETYMCUSW 433 S MR:6.1,6.2,10.1,10.2,10.3,10.4  <APPROVED> "Reason - LDRA Version
                  problem. Latest version do not have this warning."*/
				/*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/
				else if(TRUE == bBlockFoundInConfig)										
				{
					if(0x0BADU != TI_Fee_GlobalVariables[u8EEPIndex].Fee_au16BlockOffset[u16ArrayIndex])	
					{		
						/* This means the block is present in Copy VS and Active VS */
						/* Mark the block as Invalid in Active VS */
						TI_FeeInternal_ConfigureBlockHeader(u8EEPIndex,Block_Invalid,0U,0U);
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorStartAddress + TI_Fee_GlobalVariables[u8EEPIndex].Fee_au16BlockOffset[u16ArrayIndex];
						/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
						/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8Data=(uint8 *)&TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[0];					
						(void)TI_FeeInternal_WriteDataF021(FALSE,(uint16)8U,u8EEPIndex);						
						/* Update new valid block address */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_au16BlockOffset[u16ArrayIndex] = (uint16)((u32BlockStartAddress - (TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyVirtualSectorStartAddress))& 0x0000FFFFU);
						/* Block is copied */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8BlockCopyStatus[u16ArrayIndex] = 1U;
					}					
					else
					{
						/* Valid block found. Update offset address */			
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_au16BlockOffset[u16ArrayIndex] = (uint16)((u32BlockStartAddress-(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyVirtualSectorStartAddress))& 0x0000FFFFU);
						/* Block is copied */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8BlockCopyStatus[u16ArrayIndex] = 1U;
					}					
				}
				#if (TI_FEE_NUMBER_OF_UNCONFIGUREDBLOCKSTOCOPY != 0U)
				else
				{					
					for(; u16LoopIndex1<TI_Fee_u16NumberOfUnconfiguredBlocks[u8EEPIndex]; u16LoopIndex1++)
					{
						/* Check if the block is already copied */
						if(u16UnconfiguredBlockstoCopy[u16LoopIndex1] == u16BlockNumber)
						{
							bDoNotCopy = TRUE;								
							/*SAFETYMCUSW 409 S MR:14.6 <APPROVED> "Reason -  break statement is intentionally used twice."*/	
							break;
						}
					}
					if(TRUE == bDoNotCopy)
					{						
						/* Update the address of the unconfigured block which is already copied to Copy VS */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_au16UnConfiguredBlockAddress[u16LoopIndex1] = (uint16)((u32BlockStartAddress-(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyVirtualSectorStartAddress))& 0x0000FFFFU);
						/* Update the copy status of the unconfigured block which is already copied to Copy VS */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8UnConfiguredBlockCopyStatus[u16LoopIndex1] = 1U;
						u16LoopIndex1++;
						u16UnconfiguredBlockcnt++;	
						TI_Fee_u16UnconfiguredBlocksToCopy[u8EEPIndex] -= 1U;	
					}						
				}
				#else
				else
				{
					/* MISRA C Compliance */
				}
				#endif
			}
			else
			{					
				/*SAFETYMCUSW 433 S MR:6.1,6.2,10.1,10.2,10.3,10.4  <APPROVED> "Reason - LDRA Version
                  problem. Latest version do not have this warning."*/
				/*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/
				if(TRUE == bBlockFoundInConfig) 
				{					
					if(0x0BADU != TI_Fee_GlobalVariables[u8EEPIndex].Fee_au16BlockOffset[u16ArrayIndex])	
					{				
						/* This means the either the block is present in Copy VS and Active VS or Multiple blocks are valid.*/
						/* Mark the block as Invalid in Active VS / old block */
						TI_FeeInternal_ConfigureBlockHeader(u8EEPIndex,Block_Invalid,0U,0U);
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorAddress + TI_Fee_GlobalVariables[u8EEPIndex].Fee_au16BlockOffset[u16ArrayIndex];
						/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
						/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8Data=(uint8 *)&TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[0];					
						(void)TI_FeeInternal_WriteDataF021(FALSE,(uint16)8U,u8EEPIndex);
						/* Update new valid block address */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_au16BlockOffset[u16ArrayIndex] = (uint16)((u32BlockStartAddress - (TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorAddress))& 0x0000FFFFU);
					}					
					else
					{
						/* Valid block found. Update offset address */			
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_au16BlockOffset[u16ArrayIndex]  =  (uint16)((u32BlockStartAddress - (TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorAddress))& 0x0000FFFFU);
						/* Block need to be copied */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8BlockCopyStatus[u16ArrayIndex]= 0U;
					}	
				}
				else if(0xFFFFU == u16BlockSize)
				{
					u16BlockSize += TI_FEE_BLOCK_OVERHEAD;						
				}
				#if (TI_FEE_NUMBER_OF_UNCONFIGUREDBLOCKSTOCOPY != 0U)
				else
				{
					if(u16UnconfiguredBlockcnt < TI_FEE_NUMBER_OF_UNCONFIGUREDBLOCKSTOCOPY)
					{
						/* Update the address of the unconfigured block */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_au16UnConfiguredBlockAddress[u16UnconfiguredBlockcnt] = (uint16)((u32BlockStartAddress - (TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorAddress)) & 0x0000FFFFU);
						/* Update the copy status of the unconfigured block. Block needs to be copied */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8UnConfiguredBlockCopyStatus[u16UnconfiguredBlockcnt] = 0U;
						u16UnconfiguredBlockcnt++;
						TI_Fee_u16NumberOfUnconfiguredBlocks[u8EEPIndex]++;
						TI_Fee_u16UnconfiguredBlocksToCopy[u8EEPIndex]++;
						/* Store the block number of the unconfigured block */
						u16UnconfiguredBlockstoCopy[u16LoopIndex1] = u16BlockNumber;
						u16LoopIndex1++;
					}	
				}
				#else
				else
				{
					/* MISRA C Compliance */
				}
				#endif
			}			
		}
		else if(((au32BlockStatus[0] == InvalidBlockLo) && (au32BlockStatus[1] == InvalidBlockHi))
                || ((au32BlockStatus[0] == CorruptBlockLo) && (au32BlockStatus[1] == CorruptBlockHi)))				
		{
			/*SAFETYMCUSW 433 S MR:6.1,6.2,10.1,10.2,10.3,10.4  <APPROVED> "Reason - LDRA Version
              problem. Latest version do not have this warning."*/
			/*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/
			if(TRUE == bBlockFoundInConfig) 
			{
				/* If the valid address for block was already found, do not update address */
				if(0x0BADU == TI_Fee_GlobalVariables[u8EEPIndex].Fee_au16BlockOffset[u16ArrayIndex])
				{
					/* InValid block found. Update offset address */			
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_au16BlockOffset[u16ArrayIndex] = 0x0BADU;
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8BlockCopyStatus[u16ArrayIndex] = 2U;
				}	
			}
			else if(0xFFFFU == u16BlockSize)
			{
				u16BlockSize += TI_FEE_BLOCK_OVERHEAD;						
			}
			else
			{
				/* MISRA C Compliance */
			}	
		}
		else if((au32BlockStatus[0] == EmptyBlockLo) && (au32BlockStatus[1] == EmptyBlockHi))
		{
			bFlashStatus = TI_FeeInternal_BlankCheck(u32BlockStartAddress,u32VirtualSectorEndAddress, 0U, u8EEPIndex);

			/*SAFETYMCUSW 433 S MR:6.1,6.2,10.1,10.2,10.3,10.4  <APPROVED> "Reason - LDRA Version
              problem. Latest version do not have this warning."*/
			/*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/
			if(TRUE == bFlashStatus)
			{
				/* VS if free */
				/* There are no blocks after empty program block status */
				/* Empty block found. Memorize this address as next write address */
				if(bActCpyVS == TRUE)
				{
					/*  Next free address in Active VS */
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextActiveVSwriteaddress = u32BlockStartAddress;
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextActiveVSwriteaddress;
				}
				else
				{
					/*  Next free address in Copy VS */
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextCopyVSwriteaddress = u32BlockStartAddress;
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress =  TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextCopyVSwriteaddress;
				}
				/*SAFETYMCUSW 409 S MR:14.6 <APPROVED> "Reason -  break statement is intentionally used twice."*/	
				break;
			}
			else
			{
				/*Get the address where blank check failed */
				if(u32BlockStartAddress <= TI_Fee_GlobalVariables[u8EEPIndex].Fee_oBlankFailAddress)
				{
					/* Update bank fail address only if it is less than block address.*/
					u32BlockStartAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oBlankFailAddress;
					/* Since block header is eight bytes, and blank check check's returns address where it finds
					   non F's, we have to decrement address by 8 and start checking for block status */
					u32BlockStartAddress = u32BlockStartAddress & 0xFFFFFFF8U;
					u32BlockStartAddresstemp = u32BlockStartAddress;
				}
				else
				{
					if(bActCpyVS == TRUE)
					{
						/*  Next free address in Active VS */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextActiveVSwriteaddress = u32BlockStartAddress;
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextActiveVSwriteaddress;
					}
					else
					{
						/*  Next free address in Copy VS */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextCopyVSwriteaddress = u32BlockStartAddress;
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress =  TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextCopyVSwriteaddress;
					}
					/*SAFETYMCUSW 409 S MR:14.6 <APPROVED> "Reason -  break statement is intentionally used twice."*/	
					break;
				}

				u16BlockSize = 0U;
				u8cnt++;
				if(2U==u8cnt)
				{
					/* There is a block with valid block header after u32BlockStartAddress+8U. If the counter is two, 
					   this means code is at same memory location. Advance by 8.*/
					u32BlockStartAddress += 8U;
					u8cnt=0U;
				}
			}
		}
			/* If previously only 8bytes of start program block status were written, check if there are
			   any blocks adjacent to it immediately. */
			/* Read block status from block header */
			/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
			/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
			/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
			/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/

				/*SAFETYMCUSW 32 S MR:14.5 <APPROVED> "Reason -  Removal of this statement results in lot of 
				  code changes."*/
		else 
		{
		    /* Header is not Valid, Invalid or Empty hence skip by 8 Bytes and look for next Header */
		    u16BlockSize = 8U;
		}
		/* Jump to next block */						
		u32BlockStartAddress+=u16BlockSize;
		u32BlockStartAddress = TI_FeeInternal_AlignAddressForECC(u32BlockStartAddress);		
		/* If during scanning of VS, if the block address is almost at the end of VS(only 32 bytes left in VS), 
		   then stop scanning since no blocks would be available. */
		if((u32VirtualSectorEndAddress - u32BlockStartAddress) <= 0x1FU)
		{
			if(bActCpyVS == TRUE)
			{
				/*  Next free address in Active VS */
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextActiveVSwriteaddress = u32BlockStartAddress;
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextActiveVSwriteaddress;
			}
			else
			{
				/*  Next free address in Copy VS */
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextCopyVSwriteaddress = u32BlockStartAddress;
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress =  TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextCopyVSwriteaddress;
			}
			/*SAFETYMCUSW 409 S MR:14.6 <APPROVED> "Reason -  break statement is intentionally used twice."*/	
			break;
		}
		else if(u32BlockStartAddress > u32VirtualSectorEndAddress)
		{
			u32BlockStartAddress -= u16BlockSize;
			u32BlockStartAddress += TI_FEE_BLOCK_OVERHEAD;
			u32BlockStartAddress = TI_FeeInternal_AlignAddressForECC(u32BlockStartAddress);
		}
		else		
		{
			/* MISRA C Compliance */
		}	
		u16BlockSize=0U;
		u16DataSetNumber = 0U;
		u16BlockNumberWithoutDataset = 0U;
		u16BlockIndex = 0U;
	}
	if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextActiveVSwriteaddress == 0U) ||
	   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextActiveVSwriteaddress >= u32VirtualSectorEndAddress)
	  )
	{
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextActiveVSwriteaddress = u32VirtualSectorEndAddress - 8U;;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextActiveVSwriteaddress;
	}
	if(bActCpyVS == FALSE)
	{
		if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextCopyVSwriteaddress == 0U) ||
			   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextCopyVSwriteaddress >= u32VirtualSectorEndAddress)
			  )
			{
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextCopyVSwriteaddress = u32VirtualSectorEndAddress - 8U;;
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextCopyVSwriteaddress;
			}
	}	
}

/**********************************************************************************************************************
 *  TI_FeeInternal_CheckModuleState
 *********************************************************************************************************************/
/*! \brief      This functions checks the module state to determine whether any new operation can be handled.  
 *  \param[in]	uint8 u8EEPIndex 
 *  \param[out] none 
 *  \return 	E_OK
 *  \return 	E_NOT_OK
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
Std_ReturnType TI_FeeInternal_CheckModuleState(uint8 u8EEPIndex)
{
	/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be fixed 
	  outside of FEE."*/
	Std_ReturnType oResult = E_OK;
	/* To remove remark 880-D*/
	u8EEPIndex=u8EEPIndex;

	/* Check if the Fee module is currently Busy */
	if((TI_Fee_GlobalVariables[0].Fee_ModuleState == BUSY)
		#if(TI_FEE_NUMBER_OF_EEPS==2U)
		|| (TI_Fee_GlobalVariables[1].Fee_ModuleState == BUSY)
		#endif
		)
	{		
		/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be 
		  fixed outside of FEE."*/
		oResult = (uint8)E_NOT_OK;
	}
	/* Check if the Fee module is currently doing some internal operations */
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == BUSY_INTERNAL)
			#if(TI_FEE_NUMBER_OF_EEPS==2U)
			|| (TI_Fee_GlobalVariables[1].Fee_ModuleState == BUSY_INTERNAL)
			#endif
			)	
	{		
		oResult = (uint8)E_NOT_OK;		
	}
	else
	{
		/* MISRA C Compliance */
	}	
	return(oResult);
}

/**********************************************************************************************************************
 *  TI_FeeInternal_CheckReadParameters
 *********************************************************************************************************************/
/*! \brief      This function checks whether the parameters passed to the Read command are proper or not.
 *  \param[in]	uint32 u32BlockSize
 *  \param[in]	uint16 BlockOffset
 *  \param[in]	const uint8* DataBufferPtr
 *  \param[in]	uint16 Length
 *  \param[in]	uint8 u8EEPIndex 
 *  \param[out] none 
 *  \return 	E_OK
 *  \return 	E_NOT_OK
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
 Std_ReturnType TI_FeeInternal_CheckReadParameters(uint32 u32BlockSize,uint16 BlockOffset,
                                                   const uint8* DataBufferPtr,uint16 Length, uint8 u8EEPIndex)
{
	/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be fixed outside 
	  of FEE."*/
	Std_ReturnType oResult = E_OK;

	/* Check if BlockOffset does not exceed the BlockSize */
	if((uint32)BlockOffset>u32BlockSize)
	{		
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error = Error_BlockOffsetGtBlockSize;
		/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be fixed 
		  outside of FEE."*/
		oResult = (uint8)E_NOT_OK;
	}
	/* check if the Length is greater than 0 and within the Block Size */
	else if((Length != 0xFFFFU) && ((Length <= 0U) || ((uint32)(BlockOffset+Length) > (u32BlockSize))))
	{		
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error = Error_LengthParam;
		/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be fixed 
		  outside of FEE."*/
		oResult = (uint8)E_NOT_OK;
	}
	/* Check if the DataBufferPtr is a Null pointer */
	else if(DataBufferPtr == 0U)
	{		
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error = Error_NullDataPtr;
		/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be 
		  fixed outside of FEE."*/
		oResult = (uint8)E_NOT_OK;
	}
	else
	{
		/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be 
		  fixed outside of FEE."*/
		oResult = (uint8)E_OK;
	}
	/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be 
	  fixed outside of FEE."*/
	if(oResult == (uint8)E_NOT_OK)
	{
		TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Read = 0U;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_FAILED;
	}		
	return(oResult);
}


/**********************************************************************************************************************
 *  TI_FeeInternal_GetCurrentBlockAddress
 *********************************************************************************************************************/
/*! \brief      This function returns the current Flash memory address for the specified BlockNumber.
 *  \param[in]	uint16 BlockNumber
 *  \param[in]	uint16 DataSetNumber 
 *  \param[in]	uint8 u8EEPIndex 
 *  \param[out] none 
 *  \return 	Address of the requested block.
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
TI_Fee_AddressType TI_FeeInternal_GetCurrentBlockAddress(uint16 BlockNumber,uint16 DataSetNumber, uint8 u8EEPIndex)
{
	TI_Fee_AddressType oCurrentBlockAddress=0U;
	TI_Fee_AddressType oBankStartAddress=0U;
	TI_Fee_AddressType oBankEndAddress=0U;			
	
	oCurrentBlockAddress  =  TI_Fee_GlobalVariables[u8EEPIndex].Fee_au16BlockOffset[BlockNumber];
	
	if((0x0BADU != oCurrentBlockAddress) && (0xABCDU != oCurrentBlockAddress))
	{
		oCurrentBlockAddress  =  TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorAddress + TI_Fee_GlobalVariables[u8EEPIndex].Fee_au16BlockOffset[BlockNumber];
	}

	/* Get the start and end address of the configured sectors */
	oBankStartAddress = Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[0].Device_SectorStartAddress;
	#if (TI_FEE_GENERATE_DEVICEANDVIRTUALSECTORSTRUC == STD_ON)
	oBankEndAddress = Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[TI_Fee_MaxSectors-1U].Device_SectorStartAddress;
	oBankEndAddress += Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[TI_Fee_MaxSectors-1U].Device_SectorLength;
	#else
	oBankEndAddress = Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[DEVICE_BANK_MAX_NUMBER_OF_SECTORS-1U].Device_SectorStartAddress;
	oBankEndAddress += Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[DEVICE_BANK_MAX_NUMBER_OF_SECTORS-1U].Device_SectorLength;
	#endif	
	/* Check if the current block address is valid */
	if((oCurrentBlockAddress<oBankStartAddress) || (oCurrentBlockAddress>oBankEndAddress))
	{
		oCurrentBlockAddress = 0x00000000U;
	}	
	return(oCurrentBlockAddress);
}

/**********************************************************************************************************************
 *  TI_FeeInternal_GetNextFlashAddress
 *********************************************************************************************************************/
/*! \brief      This function returns the current Flash memory address for the specified BlockNumber.
 *  \param[in]	uint8 u8EEPIndex  
 *  \param[out] none 
 *  \return 	Next free address.
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
TI_Fee_AddressType TI_FeeInternal_GetNextFlashAddress(uint8 u8EEPIndex)
{	
	TI_Fee_AddressType oFeeNextAddress;

	/* Initialize oFeeNextAddress to the first unreserved memory location after all the blocks*/	
	/* Copying is not in progress */
	oFeeNextAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextActiveVSwriteaddress;
	
	oFeeNextAddress = TI_FeeInternal_AlignAddressForECC(oFeeNextAddress);		
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress = oFeeNextAddress;	
	return(oFeeNextAddress);
}

/**********************************************************************************************************************
 *  TI_FeeInternal_SanityCheck
 *********************************************************************************************************************/
/*! \brief      This function checks if the Flash is free for writing the block.
  *  \param[in]	uint16 BlockSize
 *  \param[in]	uint8 u8EEPIndex  
 *  \param[out] none 
 *  \return 	none
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
void TI_FeeInternal_SanityCheck(uint16 BlockSize, uint8 u8EEPIndex)
{
	boolean bValid = TRUE;
	uint32 u32FlashNextAddress;

	while(bValid == TRUE)
	{
		if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress+BlockSize) > (TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorEndAddress))
		{
			bValid = FALSE;
		}
		if(bValid == TRUE)
		{
			u32FlashNextAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress+(uint32)BlockSize;
			bValid = TI_FeeInternal_BlankCheck(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress,u32FlashNextAddress,(uint16)FEE_BANK,u8EEPIndex);

			if(bValid == FALSE)
			{				
				if(((TI_Fee_GlobalVariables[u8EEPIndex].Fee_oBlankFailAddress & (uint32)0xFU)== (uint32)0U) || ((TI_Fee_GlobalVariables[u8EEPIndex].Fee_oBlankFailAddress & (uint32)0xFU)==(uint32)8U))
				{
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oBlankFailAddress+0x8U;
				}
				else
				{
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oBlankFailAddress+0x4U;
				}
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress = TI_FeeInternal_AlignAddressForECC(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress);
			}
		}
		if(bValid == FALSE)
		{
			if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress+BlockSize) > TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorEndAddress)
			{
				bValid = FALSE;
				/*SAFETYMCUSW 409 S MR:14.6 <APPROVED> "Reason -  break statement is intentionally used twice."*/	
				break;
			}
			else
			{
				bValid = TRUE;
			}
		}
		else
		{
			/*SAFETYMCUSW 409 S MR:14.6 <APPROVED> "Reason -  break statement is intentionally used twice."*/	
			break;
		}
	}
}
/**********************************************************************************************************************
 *  TI_FeeInternal_SetClearCopyBlockState
 *********************************************************************************************************************/
/*! \brief      Set/Clear the block copy status of all blocks.  
 *  \param[in]	uint8 u8EEPIndex  
 *  \param[out] none 
 *  \return 	none
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
 void TI_FeeInternal_SetClearCopyBlockState(uint8 u8EEPIndex, boolean bSetClear)
{
	uint16 u16LoopIndex=0U;
	
	/* Set the block copy status to copied. 1 Indicates block has been copied  */
	for(u16LoopIndex = 0U ; u16LoopIndex<TI_FEE_TOTAL_BLOCKS_DATASETS ; u16LoopIndex++)
	{			
		if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8BlockCopyStatus[u16LoopIndex]!=2U)
		{	
			if(bSetClear==FALSE)
			{
				/* Block needs to be copied */
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8BlockCopyStatus[u16LoopIndex]=0U;
			}	
			else
			{
				/* Block is copied */
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8BlockCopyStatus[u16LoopIndex]=1U;
			}				
		}			
	}
}


/**********************************************************************************************************************
 *  TI_FeeInternal_FeeManager
 *********************************************************************************************************************/
/*! \brief      This function handles the internal operations like copying data blocks from Active VS to Copy VS, 
 *				erasing of VS .  
 *  \param[in]	uint8 u8EEPIndex  
 *  \param[out] none 
 *  \return 	TI_Fee_StatusType
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
TI_Fee_StatusType TI_FeeInternal_FeeManager(uint8 u8EEPIndex)
{
	static uint8 u8VirtualSectorIndex[TI_FEE_NUMBER_OF_EEPS];	
	static uint32 u32VirtualSectorStartAddress[TI_FEE_NUMBER_OF_EEPS];	
	static uint16 u16Index[TI_FEE_NUMBER_OF_EEPS];	
	static uint16 u16Bank = 0U;
	static uint8 u8VSHeaderWriteCounter[TI_FEE_NUMBER_OF_EEPS];	
	static boolean bVSHeaderWrite[TI_FEE_NUMBER_OF_EEPS];	
	static uint32 u32VSWriteAddressTemp[TI_FEE_NUMBER_OF_EEPS];	
	static boolean bEraseCommandIssued[TI_FEE_NUMBER_OF_EEPS];
	static boolean bDoBlankCheck[TI_FEE_NUMBER_OF_EEPS];	
	static uint32 u32CopyBlockAddress = 0U;
	static boolean bBlankCheckTest = FALSE;	
	static uint32 TI_Fee_u32SectorEraseState[2];
	#if (TI_FEE_NUMBER_OF_UNCONFIGUREDBLOCKSTOCOPY != 0U)
	static boolean bCopyBlock = FALSE;	
	static uint16 u16UnconfiguredBlockCopySize = 0U;	
	#endif
	
	#if((TI_FEE_FLASH_CHECKSUM_ENABLE == STD_ON) && (TI_FEE_NUMBER_OF_UNCONFIGUREDBLOCKSTOCOPY != 0U))
	uint32 u32ReadCheckSum = 0U;
	uint32 u32CalculateCheckSum = 0U;
	uint32 u32UnConfiguredBlockAddress = 0U;
	#endif
	
	#if((TI_FEE_FLASH_ERROR_CORRECTION_HANDLING == TI_Fee_Fix) || \
	    ((TI_FEE_FLASH_CHECKSUM_ENABLE == STD_ON) && (TI_FEE_NUMBER_OF_UNCONFIGUREDBLOCKSTOCOPY != 0U)))
	uint16 u16BlockSize=0U;	
	#endif

	uint16 u16LoopIndex = 0U;
	#if(TI_FEE_FLASH_ERROR_CORRECTION_HANDLING == TI_Fee_Fix)
	uint16 u16LoopIndex1 = 0U;		
	#endif
	uint32 u32VirtualSectorEndAddress = 0U;
	uint32 au32BlockAddress[2];
	uint32 au32BlockStatus[2];
	uint32 **ppu32ReadHeader=0U;
	Fapi_FlashSectorType oSectorStart,oSectorEnd;	
	boolean bFlashStatus=FALSE;
	boolean bBlockStatus=FALSE;
	uint8 u8CopyWriteCount = 0U;			
	uint32 u32WriteAddressTemp=0U;
	uint8 * u8WriteDataptrTemp=0U;	
	#if(TI_FEE_USEPARTIALERASEDSECTOR==STD_ON)
	uint32 u32VirtualSectorHeaderAddress = 0U;
	#endif
	boolean bDoNotStartBlackChk = FALSE;
		
	
	/*SAFETYMCUSW 114 S MR:21.1 <APPROVED> "Reason -  Eventhough expression is not boolean,
	we check for the function return value."*/	
	/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/	
	/*SAFETYMCUSW 114 S MR:12.6,13.2 <APPROVED> "Reason -  LDRA does not understand macro 
	  FAPI_CHECK_FSM_READY_BUSY."*/
	/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  ( pFapi_FmcRegistersType ) ( 0xFFF87000U ) ) casting 
	  is done in F021 library.*/  
	if(FAPI_CHECK_FSM_READY_BUSY == Fapi_Status_FsmReady)
	{
		/* check if Copy is in Progress */
		if(TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Copy == 1U)
		{
			/* Set the module state to Busy Internal */
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = BUSY_INTERNAL;		
			
			if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockCopyIndex == 0xFFFFU)
			{
				/* Determine which Block to be copied*/
				for(u16LoopIndex = 0U ; u16LoopIndex<TI_FEE_TOTAL_BLOCKS_DATASETS ; u16LoopIndex++)
				{					
					/* 0 indicates that the Block has not been copied, 3 indicates block is corrupted and also 
					   needs to be copied */
					if ((TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8BlockCopyStatus[u16LoopIndex]==0U) ||
						 (TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8BlockCopyStatus[u16LoopIndex]==3U))
					{
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockCopyIndex = u16LoopIndex;						
						break;
					}											
				}			
				if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockCopyIndex != 0xFFFFU)
				{
					/* Find out the Start Address of the block to be copied */					
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyCurrentAddress = TI_FeeInternal_GetCurrentBlockAddress(
					                                          TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockCopyIndex,
					                                          TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16DataSetIndex, 
															  u8EEPIndex);
					
					/* Initialize the next address in copy VS */
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyNextAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextCopyVSwriteaddress;										
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyNextAddress = TI_FeeInternal_AlignAddressForECC(
					                                     TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyNextAddress);
														
					/* Read the Block status from Block Header and check if it is valid */
					au32BlockAddress[0]  =  TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyCurrentAddress;
					au32BlockAddress[1]  =  TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyCurrentAddress+4U;	
					/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
					/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
					ppu32ReadHeader = (uint32 **)&au32BlockAddress[0];
					au32BlockStatus[0] = **ppu32ReadHeader;
					/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
					/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
					ppu32ReadHeader = (uint32 **)&au32BlockAddress[1];
					au32BlockStatus[1] = **ppu32ReadHeader;					
					
					/* Read the valid status and determine whether it is valid or not */
					/* If invalid, don't copy the block */
					if((au32BlockStatus[0] == ValidBlockLo) && (au32BlockStatus[1] == ValidBlockHi))
					{
						/* Block is valid */
						bBlockStatus = TRUE;						
						/* Update the write address */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyWriteAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyNextAddress;	
						/* Store the block start address */
						u32CopyBlockAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyNextAddress;
						/* Update the status as start program block in Copy VS */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[0] = StartProgramBlockLo;
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[1] = StartProgramBlockHi;	
						/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
						/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
						/*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Reason -  Fee_pu8CopyData is assigned a value and it can't be NULL."*/
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8CopyData = (uint8 *)&TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[0];					
						/* Write block status as start program block */	
						u8CopyWriteCount = TI_FeeInternal_WriteDataF021((boolean)TRUE,(uint16)8U, u8EEPIndex);
						/* To avoid MISRA warning */
						u8CopyWriteCount = u8CopyWriteCount;
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyCurrentAddress += 8U;
					}
					else
					{
						/* Block is invalid */
						bBlockStatus = FALSE;
					}						
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16CopyBlockNumber = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockCopyIndex;
					TI_FeeInternal_CopyInitialize(bBlockStatus,
					                              TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyNextAddress+8U,
											      u8EEPIndex, 0U);
				}
				#if (TI_FEE_NUMBER_OF_UNCONFIGUREDBLOCKSTOCOPY != 0U)
				else if(TI_Fee_u16UnconfiguredBlocksToCopy[u8EEPIndex] != 0U)
				{
					if(FALSE == bCopyBlock)
					{
						for(u16LoopIndex = 0U; u16LoopIndex < TI_FEE_NUMBER_OF_UNCONFIGUREDBLOCKSTOCOPY; u16LoopIndex++)
						{
							if(0U == TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8UnConfiguredBlockCopyStatus[u16LoopIndex])
							{
								/* If Checksum is enabled, before copying the non configured blocks, recalculate the Checksum of the block. 
								   Only if Checksum matches, copy blocks. */
								#if(TI_FEE_FLASH_CHECKSUM_ENABLE == STD_ON)						
								/* Read the Checksum */
								/* If block header is 24 bytes(0-23), 12-15 bytes are Checksum */
								u32UnConfiguredBlockAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_au16UnConfiguredBlockAddress[u16LoopIndex] + 
								                              TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorAddress;
								u32UnConfiguredBlockAddress += (((TI_FEE_BLOCK_OVERHEAD >> 2U)-3U) << 2U);
								/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/									 
								ppu32ReadHeader = (uint32 **)&u32UnConfiguredBlockAddress;
								u32ReadCheckSum = **ppu32ReadHeader;
								u32UnConfiguredBlockAddress -= (((TI_FEE_BLOCK_OVERHEAD >> 2U)-3U) << 2U);									

								/* Read the block size */								
								/* Length of the block is present in 2 bytes of last 4 bytes*/		
								/* If block header is 24 bytes(0-23), 20-21 bytes are block size */
								u32UnConfiguredBlockAddress += (((TI_FEE_BLOCK_OVERHEAD >> 2U)-1U) << 2U);
								/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/									 
								ppu32ReadHeader = (uint32 **)&u32UnConfiguredBlockAddress;
								u16BlockSize = (uint16)(((**ppu32ReadHeader)&0xFFFF0000U)>>16U);								
								u32UnConfiguredBlockAddress -= (((TI_FEE_BLOCK_OVERHEAD >> 2U)-1U) << 2U);

								/* Check data integrity by recalculating the Checksum of the block */   
								u8WriteDataptrTemp = (uint8 *)(u32UnConfiguredBlockAddress) + TI_FEE_BLOCK_OVERHEAD;
								u32CalculateCheckSum = TI_FeeInternal_Fletcher16(u8WriteDataptrTemp, u16BlockSize);
								u32CalculateCheckSum |= (0xFFFF << 0x10U) ;									
								/* Copy the block only if checksum matches*/
								if(u32CalculateCheckSum == u32ReadCheckSum)
								{								
									bCopyBlock = TRUE;
									break;
								}
								#else
								bCopyBlock = TRUE;
								break;
								#endif	
							}
						}
						if(TRUE == bCopyBlock)
						{
							/* Read the Block address and get the block size */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyCurrentAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_au16UnConfiguredBlockAddress[u16LoopIndex] + 
							                                                             TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorAddress;
							/* Get the block size */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyCurrentAddress += (((TI_FEE_BLOCK_OVERHEAD >> 2U)-1U) << 2U);
							/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
							/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
							ppu32ReadHeader = (uint32 **)&TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyCurrentAddress;
							u16UnconfiguredBlockCopySize = (uint16)(((**ppu32ReadHeader)&0xFFFF0000U)>>16U);
							/* Add block header size to block size */
							u16UnconfiguredBlockCopySize += TI_FEE_BLOCK_OVERHEAD;
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyCurrentAddress -= (((TI_FEE_BLOCK_OVERHEAD >> 2U)-1U) << 2U);
							/* Align address for ECC */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyNextAddress = TI_FeeInternal_AlignAddressForECC(
							                               TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress);
							/* Initialize destination address */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyWriteAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyNextAddress;							
							/* Store the block start address */
							u32CopyBlockAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyNextAddress;
							/* Update the status as start program block in Copy VS */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[0] = StartProgramBlockLo;
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[1] = StartProgramBlockHi;	
							/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/							
							/*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Reason -  Fee_pu8CopyData is assigned a value and it can't be NULL."*/
							/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8CopyData = (uint8 *)&TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[0];					
							/* Write block status  as startprogram block */	
							/*SAFETYMCUSW 91 D MR:16.10 <APPROVED> "Reason - u8CopyWriteCount value is used in following code."*/
							u8CopyWriteCount = TI_FeeInternal_WriteDataF021((boolean)TRUE,(uint16)8U, u8EEPIndex);
							/* To avoid MISRA warning */
							u8CopyWriteCount=u8CopyWriteCount;
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyCurrentAddress += 8U;						
							/* Initialize pointer to source */
							/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/							
							/*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Reason -  Fee_pu8CopyData is assigned a value and it can't be NULL."*/
							/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8CopyData = (uint8 *)(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyCurrentAddress);
							/* Update the new address of the block */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_au16UnConfiguredBlockAddress[u16LoopIndex] = (uint16)((TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyNextAddress -
							                                                                                            (TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress)) & 0x0000FFFFU);
							/* Set the status indicating block as copied*/
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8UnConfiguredBlockCopyStatus[u16LoopIndex] = 1U;
							/* Update the next free write address */								
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyNextAddress += u16UnconfiguredBlockCopySize;
							/* Reduce the block size by 8 since we have aleady updated the status */
							u16UnconfiguredBlockCopySize -= 8U;
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyNextAddress;	
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextCopyVSwriteaddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyNextAddress;							
						}	
					}					
					if(0U != u16UnconfiguredBlockCopySize)
					{												
						for(u16LoopIndex=0U;u16LoopIndex<TI_FEE_NUMBER_OF_EIGHTBYTEWRITES;u16LoopIndex++)
						{
							/*SAFETYMCUSW 114 S MR:12.6,13.2 <APPROVED> "Reason -  LDRA does not understand macro 
		                      FAPI_CHECK_FSM_READY_BUSY."*/
							/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  ( pFapi_FmcRegistersType ) ( 0xFFF87000U ) ) casting 
		                      is done in F021 library.*/  
							if(FAPI_CHECK_FSM_READY_BUSY == Fapi_Status_FsmReady)
							{
								u8CopyWriteCount = TI_FeeInternal_WriteDataF021((boolean)TRUE,(uint16)8U, u8EEPIndex);		
								if(u16UnconfiguredBlockCopySize <= u8CopyWriteCount)
								{
									u16UnconfiguredBlockCopySize = 0U;
									break;									
								}
								else
								{
									u16UnconfiguredBlockCopySize -= u8CopyWriteCount;
									/*Update source address so that it can be checked for invalid address during copying the data in  TI_FeeInternal_WriteDataF021( )*/
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyCurrentAddress += u8CopyWriteCount;
								}
							}
							else if(u16LoopIndex!=0U)								
							{
								/*SAFETYMCUSW 55 D MR:13.6 <APPROVED> "Reason -  modification is necessary here."*/
								--u16LoopIndex;
							}
							else
							{
								/* MISRA C Compliance */
							}	
						}							
					}
					else
					{
						/* Mark the block as valid */
						/* Update the write address */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyWriteAddress = u32CopyBlockAddress;								
						/* Update the status of block as valid in Copy VS */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[0] = ValidBlockLo;
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[1] = ValidBlockHi;	
						/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
						/*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Reason -  Fee_pu8CopyData is assigned a value and it can't be NULL."*/
						/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8CopyData = (uint8 *)&TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[0];					
						/* Write complete block status */	
						/*SAFETYMCUSW 91 D MR:16.10 <APPROVED> "Reason - u8CopyWriteCount value is used in following code."*/
						u8CopyWriteCount = TI_FeeInternal_WriteDataF021((boolean)TRUE,(uint16)8U, u8EEPIndex);						
						/* To avoid MISRA warning */
						u8CopyWriteCount=u8CopyWriteCount;
						/* Block is copied. Update status. */
						bCopyBlock = FALSE;							
						/* Decrement the copy block counter by one */
						TI_Fee_u16UnconfiguredBlocksToCopy[u8EEPIndex] -= 1U;
					}	
				}
				#endif
				else if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorAddress != TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyVirtualSectorAddress)
				{
					/* Finished copying all the blocks */
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyVirtualSectorAddress;
					/* Mark the Active Virtual Sector for Erase */					
					TI_FeeInternal_WriteVirtualSectorHeader(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector,
					                                        VsState_ReadyForErase, u8EEPIndex);
					/* Mark this VS is now started Erasing */	
					TI_Fee_u32SectorEraseState[0] = 0x00000000U;
					TI_Fee_u32SectorEraseState[1] = 0x0000FFFFU;
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress  =  TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress + 16U;
					/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
					/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8Data  =  (uint8 *)(&TI_Fee_u32SectorEraseState[0]); 			
					/* Wait till FSM is ready to accept new write */
					(void)TI_FeeInternal_PollFlashStatus();
					(void)TI_FeeInternal_WriteDataF021(FALSE,(uint16)8U,u8EEPIndex);
					
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8WriteCopyVSHeader = 0U;
				}
				else if (TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8CopyVirtualSector != 0U)
				{
					/* Configure the Copy Virtual Sector as Active after all the blocks are copied */					
					TI_FeeInternal_WriteVirtualSectorHeader(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8CopyVirtualSector,
					                                        VsState_Active, u8EEPIndex);
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8CopyVirtualSector;
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8CopyVirtualSector = 0U;
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8WriteCopyVSHeader = 0U;	
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextActiveVSwriteaddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress;
					#if(TI_FEE_NUMBER_OF_EEPS==2U)
					if(((0U == u8EEPIndex) && ((TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector == (uint8)(TI_FEE_NUMBER_OF_VIRTUAL_SECTORS - TI_FEE_NUMBER_OF_VIRTUAL_SECTORS_EEP1)) ||(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector == (uint8)1U)))
						|| ((1U == u8EEPIndex) && ((TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector == (uint8)TI_FEE_NUMBER_OF_VIRTUAL_SECTORS) ||
						(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector == (uint8)((TI_FEE_NUMBER_OF_VIRTUAL_SECTORS  - TI_FEE_NUMBER_OF_VIRTUAL_SECTORS_EEP1)+1U)))))
					#elif(TI_FEE_NUMBER_OF_EEPS==1U)
					if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector == (uint8)TI_FEE_NUMBER_OF_VIRTUAL_SECTORS) || 
					   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector == (uint8)1U))
					#endif
					{
						/* Mark that other VS is now started Erasing */
						TI_Fee_u32SectorEraseState[0] = 0x0000FFFFU;
						TI_Fee_u32SectorEraseState[1] = 0xFFFFFFFFU;
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress  =  TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress + 16U;
						/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
						/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8Data  =  (uint8 *)(&TI_Fee_u32SectorEraseState[0]); 			
						/* Wait till FSM is ready to accept new write */
						(void)TI_FeeInternal_PollFlashStatus();
						(void)TI_FeeInternal_WriteDataF021(FALSE,(uint16)8U,u8EEPIndex);
					}
				}
				else
				{
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8WriteCopyVSHeader = 0U;
					TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Copy = 0U;
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16CopyBlockNumber = 0U;
					/* No blocks left to be copied */
					TI_FeeInternal_SetClearCopyBlockState(u8EEPIndex,(boolean)TRUE);
					/* Change the state to IDLE, only if active sector is not 1 or not the last configured sector. */
					#if((TI_FEE_DRIVER == 0U) && (TI_FEE_NUMBER_OF_EEPS!=2U))
					if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector != (uint8)TI_FEE_NUMBER_OF_VIRTUAL_SECTORS) ||
						(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector != (uint8)1U))
					{
						if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult == JOB_PENDING)
						{
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_OK;
							#if(STD_OFF == TI_FEE_POLLING_MODE)
							TI_FEE_NVM_JOB_END_NOTIFICATION();
							#endif
						}
						/* Set the module state to IDLE */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = IDLE;
					}
					#endif
					/* Change the state to IDLE, if driver is not used in Autosar context.*/					
					#if (TI_FEE_DRIVER == 1U)
					{
						if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult == JOB_PENDING)
						{
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_OK;
							#if(STD_OFF == TI_FEE_POLLING_MODE)
							TI_FEE_NVM_JOB_END_NOTIFICATION();
							#endif
						}
						/* Set the module state to IDLE */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = IDLE;
					}
					#endif
					#if (TI_FEE_NUMBER_OF_UNCONFIGUREDBLOCKSTOCOPY != 0U)
					/* Restore the count of number of unconfigured blocks to be copied */
					TI_Fee_u16UnconfiguredBlocksToCopy[u8EEPIndex] = TI_Fee_u16NumberOfUnconfiguredBlocks[u8EEPIndex];
					/* Restore the block copy status of the unconfigured blocks */
					for(u16LoopIndex=0U; u16LoopIndex<TI_FEE_NUMBER_OF_UNCONFIGUREDBLOCKSTOCOPY; u16LoopIndex++)
					{				
						if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8UnConfiguredBlockCopyStatus[u16LoopIndex]== 1U)
						{
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8UnConfiguredBlockCopyStatus[u16LoopIndex]= 0U;
						}
					}
					#endif
				}
			}			
			/* Copy the data from the Active Virtual Sector to the Copy Virtual Sector */
			if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockCopyIndex != 0xFFFFU)
			{				
				/* Copy data for each Block till the Block Size is zero */
				if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16CopyBlockSize != 0U)
				{												
					for(u16LoopIndex=0U;u16LoopIndex<TI_FEE_NUMBER_OF_EIGHTBYTEWRITES;u16LoopIndex++)
					{
						/*SAFETYMCUSW 114 S MR:12.6,13.2 <APPROVED> "Reason -  LDRA does not understand macro 
		                  FAPI_CHECK_FSM_READY_BUSY."*/
						/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  ( pFapi_FmcRegistersType ) ( 0xFFF87000U ) ) 
						  casting is done in F021 library.*/
						/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/						  
						if(FAPI_CHECK_FSM_READY_BUSY == Fapi_Status_FsmReady)
						{
							/*SAFETYMCUSW 91 D MR:16.10 <APPROVED> "Reason - Return value is used in following code."*/
							u8CopyWriteCount = TI_FeeInternal_WriteDataF021((boolean)TRUE,
							                                   TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16CopyBlockSize,
												               u8EEPIndex);
							/* To avoid MISRA warning */
							u8CopyWriteCount = u8CopyWriteCount;									
							if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16CopyBlockSize <= 8U)
							{							
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16CopyBlockSize = 0U;
								break;								
							}
							else
							{
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16CopyBlockSize -= u8CopyWriteCount;
								/*Update source address so that it can be checked for invalid address during copying the data in  TI_FeeInternal_WriteDataF021( )*/
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyCurrentAddress += u8CopyWriteCount;
							}															
						}
						else if(u16LoopIndex!=0U)								
						{
							/*SAFETYMCUSW 55 D MR:13.6 <APPROVED> "Reason -  u16LoopIndex modification is necessary 
							  to write complete data."*/
							--u16LoopIndex;
						}
						else
						{
							/* MISRA C Compliance */
						}	
					}	
				}
				if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16CopyBlockSize == 0U)
				{					
					u8CopyWriteCount = 0U;
					/*SAFETYMCUSW 28 D <APPROVED> "Reason -  u8CopyWriteCount will not be 0 made FALSE after writing */
					while(u8CopyWriteCount < 8U)
					{
						/*SAFETYMCUSW 114 S MR:12.6,13.2 <APPROVED> "Reason -  LDRA does not understand macro 
		                  FAPI_CHECK_FSM_READY_BUSY."*/
						/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  ( pFapi_FmcRegistersType ) ( 0xFFF87000U ) ) 
						  casting is done in F021 library.*/  
						  /*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/	
						if(FAPI_CHECK_FSM_READY_BUSY == Fapi_Status_FsmReady)
						{				
							/* Mark the block as valid */
							/* Update the write address */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyWriteAddress = u32CopyBlockAddress;								
							/* Update the status of block as valid in Copy VS */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[0] = ValidBlockLo;
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[1] = ValidBlockHi;	
							/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
							/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8CopyData = (uint8 *)&TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[0];					
							/* Write complete block status */	
							u8CopyWriteCount = TI_FeeInternal_WriteDataF021((boolean)TRUE,(uint16)8U, u8EEPIndex);	
							/* Set the status indicating block as copied*/
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8BlockCopyStatus[TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockCopyIndex] = 1U;
							/* Set the index to 0xFFFF to find out the next Block to be copied */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockCopyIndex = 0xFFFFU;				
						}
					}					
				}
			}				
		}
		#if(TI_FEE_FLASH_ERROR_CORRECTION_HANDLING == TI_Fee_Fix)
		else if(TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.SingleBitError == 1U)
		{
			/* Set the module state to Busy Internal */
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = BUSY_INTERNAL;
			
			if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockCopyIndex == 0xFFFFU)
			{
				/* Determine which Block to be copied*/
				for(u16LoopIndex = 0U ; u16LoopIndex<TI_FEE_TOTAL_BLOCKS_DATASETS ; u16LoopIndex++)
				{					
					/* 3 indicates that the Block needs to be copied */
					if (TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8BlockCopyStatus[u16LoopIndex]==3U)
					{
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockCopyIndex = u16LoopIndex;							
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16DataSetIndex = u16LoopIndex1;
						break;
					}
					if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockCopyIndex != 0xFFFFU)
					{
						break;
					}						
				}			
				if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockCopyIndex != 0xFFFFU)
				{
					u16BlockSize = TI_FeeInternal_GetBlockSize((uint16)TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockIndex);
					/* Find out the Start Address of the block to be copied */					
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyCurrentAddress = TI_FeeInternal_GetCurrentBlockAddress(
					                                          TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockCopyIndex,
					                                          TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16DataSetIndex, 
															  u8EEPIndex);
					
					/* Initialize the next address */
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyNextAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress;										
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyNextAddress = TI_FeeInternal_AlignAddressForECC(
					                                           TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyNextAddress);
					/* If VS size exceeds because of this write, find next VS */
					if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyNextAddress+u16BlockSize) > TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorEndAddress)
					{
						/* Find the next Virtual Sector to write to */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8CopyVirtualSector = TI_FeeInternal_FindNextVirtualSector(u8EEPIndex);
					
						/* Configure it as a Copy Virtual Sector */
						if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8CopyVirtualSector!=0U)&&(TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error == Error_Nil))
						{
							/* Immediately Update the VS state to COPY */
							TI_FeeInternal_WriteVirtualSectorHeader(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8CopyVirtualSector,
							                                        VsState_Copy, u8EEPIndex);																								
													
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyVirtualSectorAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress;
							/* Next data write happens after VS Header */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextCopyVSwriteaddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress+TI_FEE_VIRTUAL_SECTOR_OVERHEAD+16U;
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress  =  TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextCopyVSwriteaddress;
							/* Clear the block copy status of all blocks. All blocks need to be copied in background */
							TI_FeeInternal_SetClearCopyBlockState(u8EEPIndex,(boolean)FALSE);
							/* update the block copy status for current block to copy. */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8BlockCopyStatus[u16LoopIndex]=0U;
							/* Update Next write address */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextCopyVSwriteaddress;									
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress = TI_FeeInternal_AlignAddressForECC(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress);										
							/* Update the status to COPY. This will enable copying of all blocks from Active VS to Copy VS in background*/
							TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Copy = 1U;																
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockCopyIndex=0xFFFFU;
							TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.SingleBitError = 0U;
						}
					}
					else
					{					
						/* Read the Block status from Block Header and check if it is valid */
						au32BlockAddress[0]  =  TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyCurrentAddress;
						au32BlockAddress[1]  =  TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyCurrentAddress+4U;	
						
						ppu32ReadHeader = (uint32 **)&au32BlockAddress[0];
						au32BlockStatus[0] = **ppu32ReadHeader;
						
						ppu32ReadHeader = (uint32 **)&au32BlockAddress[1];
						au32BlockStatus[1] = **ppu32ReadHeader;					
						
						/* Read the valid status and determine whether it is valid or not */
						/* If invalid, don't copy the block */
						if((au32BlockStatus[0] == ValidBlockLo) && (au32BlockStatus[1] == ValidBlockHi))
						{
							/* Block is valid */
							bBlockStatus = TRUE;
						}
						else
						{
							/* Block is invalid */
							bBlockStatus = FALSE;
						}
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16CopyBlockNumber = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockCopyIndex;					
						TI_FeeInternal_CopyInitialize(bBlockStatus,TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyNextAddress,u8EEPIndex, (uint8)1U);					
					}	
				}								
				else
				{					
					TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.SingleBitError = 0U;
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16CopyBlockNumber = 0U;
					/* No blocks left to be copied */
					TI_FeeInternal_SetClearCopyBlockState(u8EEPIndex,(boolean)TRUE);
				}
			}
			/* Copy the data from the Corrupt block location to new location */
			if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockCopyIndex != 0xFFFFU)
			{				
				/* Copy data for each Block till the Block Size is zero */
				if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16CopyBlockSize != 0U)
				{					
					if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16CopyBlockSize < (uint16)WIDTH_EEPROM_BANK)
					{						
						u8CopyWriteCount = TI_FeeInternal_WriteDataF021((boolean)TRUE,TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16CopyBlockSize, u8EEPIndex);
						if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16CopyBlockSize < u8CopyWriteCount)
						{
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16CopyBlockSize = 0U;
						}
						else
						{
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16CopyBlockSize -= u8CopyWriteCount;
						}			
					}
					else
					{
						u8CopyWriteCount = TI_FeeInternal_WriteDataF021((boolean)TRUE,
						                   (uint16)WIDTH_EEPROM_BANK, u8EEPIndex);
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16CopyBlockSize -= u8CopyWriteCount;
					}					
				}
				else
				{			
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyCurrentAddress;	
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[0] = CorruptBlockLo;
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[1] = CorruptBlockHi;	
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8Data = (uint8 *)&TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[0];					
					/* Mark the block as Corrupt */	
					TI_FeeInternal_WriteDataF021(FALSE,(uint16)8U, u8EEPIndex);					
					/* Set the status indicating block as copied*/
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8BlockCopyStatus[TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockCopyIndex] = 1U;
					TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.SingleBitError = 0U;								
				}
			}				
		}
		#endif
		#if(TI_FEE_NUMBER_OF_EEPS==2U)
		else if(((0U == u8EEPIndex) && ((TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector == (uint8)(TI_FEE_NUMBER_OF_VIRTUAL_SECTORS - TI_FEE_NUMBER_OF_VIRTUAL_SECTORS_EEP1)) ||(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector == (uint8)1U)))
                || ((1U == u8EEPIndex) && ((TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector == (uint8)TI_FEE_NUMBER_OF_VIRTUAL_SECTORS) ||
                   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector == (uint8)((TI_FEE_NUMBER_OF_VIRTUAL_SECTORS  - TI_FEE_NUMBER_OF_VIRTUAL_SECTORS_EEP1)+1U)))))
		#elif(TI_FEE_NUMBER_OF_EEPS==1U)
		else if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector == (uint8)TI_FEE_NUMBER_OF_VIRTUAL_SECTORS) || 
		(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector == (uint8)1U))
		#endif		
		{
			if((FALSE == TI_Fee_bEraseSuspended) && (TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32InternalEraseQueue != 0U))
			{				
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = BUSY_INTERNAL;
				TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Erase = 1U;
				bVSHeaderWrite[u8EEPIndex] = TRUE;					
				if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error != Error_EraseVS)
				{
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error = Error_Nil;
				}				
				/* Find out which Virutal Sector to be erased */
				if((0U == u8VirtualSectorIndex[u8EEPIndex]) && (0U == u8VSHeaderWriteCounter[u8EEPIndex]) && (bDoBlankCheck[u8EEPIndex] == FALSE))
				{
					while(((TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32InternalEraseQueue & (0x1U<<(uint32)u16Index[u8EEPIndex]))>>(uint32)u16Index[u8EEPIndex])!=0x1U)
					{
						u16Index[u8EEPIndex]++;					
					}
					/* Determine the Start and End Sectors for the Virtual Sector */				
					u16Bank = FEE_BANK;					
					oSectorStart = Fee_VirtualSectorConfiguration[u16Index[u8EEPIndex]].FeeStartSector;
					oSectorEnd = Fee_VirtualSectorConfiguration[u16Index[u8EEPIndex]].FeeEndSector;								
					/*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/
					TI_FeeInternal_GetVirtualSectorIndex(oSectorStart,oSectorEnd,u16Bank,FALSE, u8EEPIndex);					
				}				
				if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32InternalEraseQueue != 0U)
				{
					/* Check for any non severe errors */		
					TI_FeeInternal_CheckForError(u8EEPIndex);
					
					if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error == Error_Nil)
					{
						/*SAFETYMCUSW 433 S MR:6.1,6.2,10.1,10.2,10.3,10.4  <APPROVED> "Reason - LDRA Version
                          problem. Latest version do not have this warning."*/
						/*SAFETYMCUSW 433 S MR:6.1,6.2,10.1,10.2,10.3,10.4  <APPROVED> "Reason - LDRA Version
                          problem. Latest version do not have this warning."*/  
						if((0U == u8VSHeaderWriteCounter[u8EEPIndex]) && 
						   /*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/	  
						   (FALSE == bEraseCommandIssued[u8EEPIndex]) && 
						   /*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/	  
						   (FALSE == bDoBlankCheck[u8EEPIndex]))
						{
							/*SAFETYMCUSW 52 S MR:12.9 <APPROVED> "Reason -  Subtraction is required here."*/
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8InternalVirtualSectorEnd = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8InternalVirtualSectorEnd-u8VirtualSectorIndex[u8EEPIndex];			 		
						}	
						if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8InternalVirtualSectorEnd >= TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8InternalVirtualSectorStart))  
						{
							/*SAFETYMCUSW 433 S MR:6.1,6.2,10.1,10.2,10.3,10.4  <APPROVED> "Reason - LDRA Version
                              problem. Latest version do not have this warning."*/
							/*SAFETYMCUSW 433 S MR:6.1,6.2,10.1,10.2,10.3,10.4  <APPROVED> "Reason - LDRA Version
                              problem. Latest version do not have this warning."*/ 
							/*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/	  
							if((FALSE == bEraseCommandIssued[u8EEPIndex])&& 
							   (FALSE == bDoBlankCheck[u8EEPIndex]) && 
							   (0U == u8VSHeaderWriteCounter[u8EEPIndex]))
							{
								/* Find out the Sector Start Address*/
								u32VirtualSectorStartAddress[u8EEPIndex] = Device_FlashDevice.Device_BankInfo[u16Bank].Device_SectorInfo[TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8InternalVirtualSectorEnd].Device_SectorStartAddress;
								/* Erase one sector of the Virtual Sector at a time */						
								(void)Fapi_setActiveFlashBank(Device_FlashDevice.Device_BankInfo[FEE_BANK].Device_Core);
								/* Errata : Enable only required sector to erase. */
								TI_FeeInternal_EnableRequiredFlashSector(u32VirtualSectorStartAddress[u8EEPIndex]);
								/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
								/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
								if(Fapi_issueAsyncCommandWithAddress(Fapi_EraseSector,
															 (uint32_t *)u32VirtualSectorStartAddress[u8EEPIndex]
															)==Fapi_Status_Success)
								{
									bDoBlankCheck[u8EEPIndex] = TRUE;
									/* Do not start Blank Check in same iteration */
									bDoNotStartBlackChk = TRUE;
									if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8InternalVirtualSectorEnd == TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8InternalVirtualSectorStart)
									{
										bEraseCommandIssued[u8EEPIndex] = TRUE;
										bVSHeaderWrite[u8EEPIndex] = FALSE;
									}	
								}							
							}	
							/*SAFETYMCUSW 114 S MR:21.1 <APPROVED> "Reason -  Eventhough expression is not boolean, 
							  we need this check."*/														
							/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  ( pFapi_FmcRegistersType ) ( 0xFFF87000U ) ) casting 
		                      is done in F021 library.*/  
							/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/	
							if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error == Error_Nil) && 
							   (0U == u8VSHeaderWriteCounter[u8EEPIndex]) && 							   
							   /*SAFETYMCUSW 114 S MR:12.6,13.2 <APPROVED> "Reason -  LDRA does not understand macro 
								 FAPI_CHECK_FSM_READY_BUSY."*/
							   /*Order changed to remove MISRA warning */	 
							   (FAPI_CHECK_FSM_READY_BUSY == Fapi_Status_FsmReady) &&
							   (FALSE == bDoNotStartBlackChk))
							{
								/*Once Erase is completed, Check if it is Blank */
								/*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/	
								u32VirtualSectorEndAddress = u32VirtualSectorStartAddress[u8EEPIndex]+TI_FeeInternal_GetVirtualSectorParameter((Fapi_FlashSectorType)TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8InternalVirtualSectorEnd,u16Bank,FALSE, u8EEPIndex);
								/* Errata : Enable all sector's since only required sector was enabled for erase .*/
								(void)Fapi_enableEepromBankSectors(FEE_ENABLE_SECTORS_31_00, FEE_ENABLE_SECTORS_63_32);
								bFlashStatus = TI_FeeInternal_BlankCheck(u32VirtualSectorStartAddress[u8EEPIndex],
								                                         u32VirtualSectorEndAddress,
																		 u16Bank,u8EEPIndex);				
								if(bFlashStatus == TRUE)
								{
									if(0U == u8VirtualSectorIndex[u8EEPIndex])
									{
										u8VirtualSectorIndex[u8EEPIndex]++;
									}	
									bDoBlankCheck[u8EEPIndex] = FALSE;
									bEraseCommandIssued[u8EEPIndex] = FALSE;
									bBlankCheckTest = TRUE;
								}
								else
								{									
									#if(TI_FEE_USEPARTIALERASEDSECTOR==STD_ON)
									/* If blank check failed at first eight bytes of VS Header status and if the next 
									   four bytes of VS header are F's, or if the blankcheck failed at address other 
									   than VS header, then VS can still be used */
									u32VirtualSectorHeaderAddress = u32VirtualSectorStartAddress[u8EEPIndex]+8U;
									/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required 
									   here."*/
						            /*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required 
									   here."*/
									ppu32ReadHeader = (uint32 **)&u32VirtualSectorHeaderAddress;									
									if(((TI_Fee_GlobalVariables[u8EEPIndex].Fee_oBlankFailAddress < (u32VirtualSectorStartAddress[u8EEPIndex]+8U)) &&
									   ((**ppu32ReadHeader) == 0xFFFFFFFFU)) ||
									   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_oBlankFailAddress >= (u32VirtualSectorStartAddress[u8EEPIndex]+12U))
									  )
									{
										if(0U == u8VirtualSectorIndex[u8EEPIndex])
										{
											u8VirtualSectorIndex[u8EEPIndex]++;
										}
										bDoBlankCheck[u8EEPIndex] = FALSE;
										bEraseCommandIssued[u8EEPIndex] = FALSE;			
										bBlankCheckTest = TRUE;
									}
									else
									#endif	
									{
										u8VirtualSectorIndex[u8EEPIndex] = 0U;									
										bDoBlankCheck[u8EEPIndex] = FALSE;
										bEraseCommandIssued[u8EEPIndex] = FALSE;										
										/* Blank check test failed */
										bBlankCheckTest = FALSE;
										/* Store the sector state as Invalid so that it can be erased again during finding next VS */
										TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16Index[u8EEPIndex]] = VsState_Invalid;
										/* Remove it from the Erase list. */
										TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32InternalEraseQueue = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32InternalEraseQueue & (~(0x1U<<(uint32)u16Index[u8EEPIndex]));
										TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus = TI_FEE_ERROR;										
										if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult == JOB_PENDING)
										{
											TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_OK;
											#if(STD_OFF == TI_FEE_POLLING_MODE)
											TI_FEE_NVM_JOB_END_NOTIFICATION();
											#endif
										}										
										/* Set the module state to IDLE */
										TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = IDLE;
										TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Erase=0U;										
										u16Index[u8EEPIndex] = 0U;
									}	
								}
							}							
						}
						else
						{
							u8VirtualSectorIndex[u8EEPIndex] = 0U;
							u16Index[u8EEPIndex] = 0U;
						}
					}
					else
					{
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus = TI_FEE_ERROR;												
						TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Erase=0U;
						if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult == JOB_PENDING)
						{
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_OK;
							#if(STD_OFF == TI_FEE_POLLING_MODE)
							TI_FEE_NVM_JOB_END_NOTIFICATION();
							#endif
						}
						/* Set the module state to IDLE */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = IDLE;
					}
					/*SAFETYMCUSW 433 S MR:6.1,6.2,10.1,10.2,10.3,10.4  <APPROVED> "Reason - LDRA Version
                      problem. Latest version do not have this warning."*/
					/*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/	  
					if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error == Error_Nil) && (TRUE == bBlankCheckTest))
					{
						if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8InternalVirtualSectorEnd == TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8InternalVirtualSectorStart)
						{
							/* Finished erasing the entire Virtual Sector */		
							/* Increment the erase count of VS and update the VS staus as EMPTY */
							if(0U == u8VSHeaderWriteCounter[u8EEPIndex])
							{								
								/*SAFETYMCUSW 433 S MR:6.1,6.2,10.1,10.2,10.3,10.4  <APPROVED> "Reason - LDRA Version
                                  problem. Latest version do not have this warning."*/
								/*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/
								if(TRUE == bVSHeaderWrite[u8EEPIndex])
								{
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16Index[u8EEPIndex]] = VsState_Empty;
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorEraseCount[u16Index[u8EEPIndex]]++;
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress = u32VirtualSectorStartAddress[u8EEPIndex];
									TI_FeeInternal_WriteVirtualSectorHeader((uint8)u16Index[u8EEPIndex]+1U,VsState_Empty, u8EEPIndex);							
									/* Eight bytes of VS Header are written in above function call. */
									u8VSHeaderWriteCounter[u8EEPIndex] = 8U;
									u32VSWriteAddressTemp[u8EEPIndex] =  TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress + 8U;
								}	
							}	
							else if(8U == u8VSHeaderWriteCounter[u8EEPIndex])
							{
								/* Remaining Eight bytes of the VS header are written here */
								u32WriteAddressTemp = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress;
								/*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Reason -  u8WriteDataptrTemp is assigned a value and it can't be NULL."*/
								u8WriteDataptrTemp = TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8Data;								
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress  =  u32VSWriteAddressTemp[u8EEPIndex];								
								/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
								/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8Data  =  (uint8 *)(&TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorStateValue[2]); 	
								(void)TI_FeeInternal_WriteDataF021(FALSE,(uint16)8U, u8EEPIndex);
								/* Remove it from the Erase list. */
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32InternalEraseQueue = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32InternalEraseQueue & (~(0x1U<<(uint32)u16Index[u8EEPIndex]));
								if(0U == TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32InternalEraseQueue)
								{
									/* Mark that other VS is now completed Erasing */
									TI_Fee_u32SectorEraseState[0] = 0x00000000U;
									TI_Fee_u32SectorEraseState[1] = 0xFFFFFFFFU;
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress  =  TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress + 16U;
									/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
									/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8Data  =  (uint8 *)(&TI_Fee_u32SectorEraseState[0]); 			
									/* Wait till FSM is ready to accept new write */
									(void)TI_FeeInternal_PollFlashStatus();
									(void)TI_FeeInternal_WriteDataF021(FALSE,(uint16)8U,u8EEPIndex);
								}	
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress = u32WriteAddressTemp;								
								/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
								/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
								/*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Reason -  u8WriteDataptrTemp is assigned a value and it can't be NULL."*/
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8Data = (uint8 *)u8WriteDataptrTemp;																																
								/* Reset static variables */
								u8VSHeaderWriteCounter[u8EEPIndex] = 0U;
								u32VSWriteAddressTemp[u8EEPIndex] = 0U;
								u8VirtualSectorIndex[u8EEPIndex] = 0U;
								u16Index[u8EEPIndex] = 0U;		
								bEraseCommandIssued[u8EEPIndex]	= FALSE;								
								if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult == JOB_PENDING)
								{
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_OK;
									#if(STD_OFF == TI_FEE_POLLING_MODE)
									TI_FEE_NVM_JOB_END_NOTIFICATION();
									#endif
								}
								/* Set the module state to IDLE */
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = IDLE;
								if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32InternalEraseQueue == 0U)
								{
									TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Erase=0U;	
								}
							}
							else
							{
								/* MISRA C Compliance */
							}	
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorAddress;
						}						
					}							
				}				
			}			
		}
		else
		{
			/* MISRA C Compliance */
		}	
	}	
	return(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus);
}

/**********************************************************************************************************************
 *  TI_FeeInternal_WriteBlockHeader
 *********************************************************************************************************************/
/*! \brief      This API will write the block header 
 *  \param[in]	boolean bWrite  
 *  \param[in]	uint8 u8EEPIndex  
 *  \param[in]	uint16 Fee_BlockSize_u16  
 *  \param[in]	uint16 u16BlockNumber  
 *  \param[out] none 
 *  \return 	none
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
void TI_FeeInternal_WriteBlockHeader(boolean bWrite, uint8 u8EEPIndex, uint16 Fee_BlockSize_u16,uint16 u16BlockNumber)
{
	uint8 u8WriteCount = 0U;	
	BlockStatesType BlockState;

	/* After writing all the data. write the Block Header */
	if(bWrite == TRUE)
	{
		if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8WriteCount == 0U)
		{
			BlockState = Block_Valid;
			TI_FeeInternal_ConfigureBlockHeader(u8EEPIndex, BlockState,Fee_BlockSize_u16,u16BlockNumber);					
		}								
		/*Update 16 bytes of block header. Update block status, Checksum and address of previous block */
		if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8WriteCount < 0x10U)
		{		
			/* Write to the Block Header */
			u8WriteCount  =  TI_FeeInternal_WriteDataF021(FALSE,(uint16)8U,u8EEPIndex);				
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8WriteCount += u8WriteCount;		
		}
		if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8WriteCount == 0x10U)
		{
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWriteBlockHeader = TRUE;
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8WriteCount = 0U;	
		}
	}
	else
	{		
		/* Write Block erase count to Block Header */	
		#if(TI_FEE_FLASH_WRITECOUNTER_SAVE == STD_ON)		
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[(TI_FEE_BLOCK_OVERHEAD >> 2U)-2U]  =  TI_Fee_u32BlockEraseCount;	
		#else
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[(TI_FEE_BLOCK_OVERHEAD >> 2U)-2U]  =  0xFFFFFFFFU;	
		#endif		
		/* Write block number */			
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[(TI_FEE_BLOCK_OVERHEAD >> 2U)-1U]  =  ((uint32)u16BlockNumber & 0x0000FFFFU);
		/* Write block size */	
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[(TI_FEE_BLOCK_OVERHEAD >> 2U)-1U] |= ((uint32)Fee_BlockSize_u16 & 0x0000FFFFU)<<0x10U;								
		/* Blocknumber, Blocksize  and Block Counter are last 8bytes of block header */
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentBlockHeader + 0x10U;						
		/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
		/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8Data=(uint8 *)&TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[4U];		
		/* Write the Block Number and Block Size, Block Erase count */
		(void)TI_FeeInternal_WriteDataF021(FALSE,(uint16)8U,u8EEPIndex);
	}		
}

/**********************************************************************************************************************
 *  TI_FeeInternal_ConfigureBlockHeader
 *********************************************************************************************************************/
/*! \brief      This API will configure the block header 
 *  \param[in]	uint8 u8EEPIndex  
 *  \param[in]	uint8 u8BlockState 
 *  \param[in]	uint16 Fee_BlockSize_u16  
 *  \param[in]	uint16 u16BlockNumber  
 *  \param[out] none 
 *  \return 	none
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
static void TI_FeeInternal_ConfigureBlockHeader(uint8 u8EEPIndex, uint8 u8BlockState,uint16 Fee_BlockSize_u16,
                                                uint16 u16BlockNumber)
{		
	/* To remove remark 880-D*/
	u16BlockNumber = u16BlockNumber;
	Fee_BlockSize_u16 = Fee_BlockSize_u16;

	/* Set the status */	
	switch(u8BlockState)
	{	   
	   case Block_StartProg: 	
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[0] = StartProgramBlockLo;
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[1] = StartProgramBlockHi;
				break;
	   case Block_Valid:
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[0] = ValidBlockLo;
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[1] = ValidBlockHi;
				break;
	   case Block_Invalid:
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[0] = InvalidBlockLo;
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[1] = InvalidBlockHi;
				break;	   
	   default:
				break;	
	}
	
	/* Update address of previous block */
	if(0x00000000U == TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentStartAddress)
	{
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[(TI_FEE_BLOCK_OVERHEAD >> 2U)-4U] = 0xFFFFFFFFU;
	}
	else
	{
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[(TI_FEE_BLOCK_OVERHEAD >> 2U)-4U] = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentStartAddress;
	}

	/* Write Block erase count to Block Header */	
	#if(TI_FEE_FLASH_WRITECOUNTER_SAVE == STD_ON)		
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[(TI_FEE_BLOCK_OVERHEAD >> 2U)-2U]  =  TI_Fee_u32BlockEraseCount;	
	#else
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[(TI_FEE_BLOCK_OVERHEAD >> 2U)-2U]  =  0xFFFFFFFFU;	
	#endif	
	
	/* Write Checksum in to Block Header */	
	#if(TI_FEE_FLASH_CHECKSUM_ENABLE == STD_ON)	
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[(TI_FEE_BLOCK_OVERHEAD >> 2U)-3U]  =  TI_Fee_u32FletcherChecksum;	
	#else
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[(TI_FEE_BLOCK_OVERHEAD >> 2U)-3U]  =  0xFFFFFFFFU;	
	#endif		
}

/**********************************************************************************************************************
 *  TI_FeeInternal_WritePreviousBlockHeader
 *********************************************************************************************************************/
/*! \brief      This API will write the previous block header.
 *  \param[in]	boolean bWrite 
 *  \param[in]	uint8 u8EEPIndex  
 *  \param[out] none 
 *  \return 	none
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
void TI_FeeInternal_WritePreviousBlockHeader(boolean bWrite, uint8 u8EEPIndex)
{
	uint8 u8WriteCount = 0U;
	
	/* Check if the Previous block header in the list needs to be updated  */
 	if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentBlockHeader != TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentStartAddress)
 	{
 		if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8WriteCount == 0U)
		{
 			/* Configure the Previous block header */
 			/* Update the status field in the Block Header as Invalid */		
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[0] = InvalidBlockLo;		
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[1] = InvalidBlockHi;			
			/* Determine the address of the previous block header */
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentStartAddress;
			/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
			/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8Data = (uint8 *)&TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[0];
		}		
	}
	else
	{
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8WriteCount = TI_FEE_BLOCK_OVERHEAD;
	}

	/* Check if the previous Block Header is written. We update only 8 bytes of block status */
	if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8WriteCount < 0x08U)
	{		
		u8WriteCount = TI_FeeInternal_WriteDataF021(FALSE,(uint16)8U,u8EEPIndex);
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8WriteCount += u8WriteCount;			
	}
	if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8WriteCount == 0x08U)
	{
		/* The write operation is complete */
		/* Set the module state, job result and call the job end notification */
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8WriteCount = 0U;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWriteBlockHeader = FALSE;
		/* clear the Status word */
		if(bWrite == TRUE)
		{
			if(TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.WriteAsync == 1U)
			{
				TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.WriteAsync = 0U;				
			}
			else if(TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.WriteSync == 1U)
			{
				TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.WriteSync = 0U;				
			}
			else
			{
				/* MISRA C Compliance */
			}	
		}
		else
		{
			if(TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.EraseImmediate == 1U)
			{
				TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.EraseImmediate = 0U;				
			}
			else
			{
				TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.InvalidateBlock = 0U;				
			}
		}		
		/* If copy was initiated by this write job, do not return the job status as completed */
		if(TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Copy == 1U)
		{
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = BUSY_INTERNAL;
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_PENDING;			
		}
		else
		{			
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult=JOB_OK;
			#if(STD_OFF == TI_FEE_POLLING_MODE)
			TI_FEE_NVM_JOB_END_NOTIFICATION();
			#endif
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = IDLE;
		}				
	}
}

/**********************************************************************************************************************
 *  TI_FeeInternal_InvalidateErase
 *********************************************************************************************************************/
/*! \brief      This function initiates the Invalidate or Erase Immediate commands
 *  \param[in]	uint16 BlockNumber 
 *  \param[out] none 
 *  \return 	Std_ReturnType
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
Std_ReturnType TI_FeeInternal_InvalidateErase(uint16 BlockNumber)
{
	Std_ReturnType oResult;
	uint16 u16BlockNumber = 0U;
	uint16 u16BlockIndex = 0U;
	uint8 u8EEPIndex = 0U;
	uint16 u16DataSetNumber = 0U;	
	uint16 u16ArrayIndex=0U;

	/* Determine the Block number & Block index */
	/* From the block number, remove data selection bits */
	/*SAFETYMCUSW 91 D MR:16.10 <APPROVED> "Reason - Return value is used in following code."*/
	u16BlockNumber = TI_FeeInternal_GetBlockNumber(BlockNumber);
	/* Get the index of the block in Fee_BlockConfiguration array */
	u16BlockIndex = TI_FeeInternal_GetBlockIndex(u16BlockNumber);
	if(u16BlockIndex == 0xFFFFU)
	{
	  TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus = TI_FEE_ERROR;
	  TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error = Error_InvalidBlockIndex;
	  /*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be fixed outside of FEE."*/
	  oResult = (uint8)E_NOT_OK;
	}
	else
	{	
	  /* Read the device index from the block configuration */
	  u8EEPIndex  =  Fee_BlockConfiguration[u16BlockIndex].FeeEEPNumber;	
	  /* Get the DataSet index after removing the Block number */
	  /*SAFETYMCUSW 91 D MR:16.10 <APPROVED> "Reason - Return value is used in following code."*/
	  u16DataSetNumber  =  TI_FeeInternal_GetDataSetIndex(BlockNumber);
	  /* Get the array index for address array */
	  u16ArrayIndex = TI_FeeInternal_GetArrayIndex(u16BlockNumber, u16DataSetNumber, u8EEPIndex, TRUE);
	  TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16ArrayIndex = u16ArrayIndex;
	  /* To avoid MISRA warning */
	  u16DataSetNumber=u16DataSetNumber;
	  oResult = TI_FeeInternal_CheckModuleState(u8EEPIndex);
	}			
	/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be fixed outside of FEE."*/
	if(oResult == (uint8)E_OK)
	{			
		/* Determine the Block Number & Block Index */		
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockIndex = u16BlockIndex;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16DataSetIndex = u16DataSetNumber; 
						
		/* Get the Address for the Current Block */
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentStartAddress = TI_FeeInternal_GetCurrentBlockAddress(u16ArrayIndex,u16DataSetNumber,u8EEPIndex);

		/* Report an error if Block Index or Address is not found */
		if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentStartAddress == 0x0000000U))
		{
			/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be fixed outside of FEE."*/
		    oResult = (uint8)E_NOT_OK;

		}				

		/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be fixed outside of FEE."*/
		if(oResult == (uint8)E_OK)
		{
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = BUSY;
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_PENDING;
			if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult != JOB_FAILED) || (TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus != TI_FEE_ERROR))
			{
				/* If using more than one DataSet, find out the DataSet Index. If Dataset Index is not found, report an error */
				if(Fee_BlockConfiguration[TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockIndex].FeeNumberOfDataSets>1U)
				{					
					if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16DataSetIndex > Fee_BlockConfiguration[TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockIndex].FeeNumberOfDataSets)
					{
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_FAILED;
						/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be fixed outside of FEE."*/
						oResult = (uint8)E_NOT_OK;
					}					
				}				
				
				if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult != JOB_FAILED)
				{										
					TI_FeeInternal_InvlalidateEraseInitialize(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress,u8EEPIndex);
					/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be fixed outside of FEE."*/
					oResult = (uint8)E_OK;
				}				
			}			
		}		
	}			
	return(oResult);
}

/**********************************************************************************************************************
 *  TI_FeeInternal_StartProgramBlock
 *********************************************************************************************************************/
/*! \brief      This function marks the Block Status as StartProgamBlock to indicate
 *				that this block is currently being programmed
 *  \param[in]	uint8 u8EEPIndex
 *  \param[out] none 
 *  \return 	none
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
void TI_FeeInternal_StartProgramBlock(uint8 u8EEPIndex)
{
	uint8 u8WriteCount;
  
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentBlockHeader;	
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[0] = StartProgramBlockLo;
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[1] = StartProgramBlockHi;	
	/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
	/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8Data = (uint8 *)&TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[0];
	/* Status of block is 8 bytes */
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8WriteCount = 8U;
	/* Write complete block status */	
	u8WriteCount = TI_FeeInternal_WriteDataF021(FALSE,(uint16)TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8WriteCount, 
	                                            u8EEPIndex);			
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8WriteCount=0U;
	TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress += u8WriteCount;
}

/**********************************************************************************************************************
 *  TI_Fee_GetStatus
 *********************************************************************************************************************/
/*! \brief      This function is pre-compile time configurable by the parameter FlsGetStatusApi
 *  \param[in]	uint8 u8EEPIndex
 *  \param[out] none 
 *  \return 	TI_FeeModuleStatusType
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
/* SourceId : HL_Fee_SourceId_9 */
/* DesignId : HL_FEE_DesignId_25 */
/* Requirements : HL_FEE_SR35, HL_FEE_SR36, HL_FEE_SR37, HL_FEE_SR38, HL_FEE_SR39 */
/*SAFETYMCUSW 61 D MR:8.10,8.11 <APPROVED> "Reason -  This API will be called by application."*/
TI_FeeModuleStatusType TI_Fee_GetStatus(uint8 u8EEPIndex)
{

	TI_FeeModuleStatusType ModuleState = UNINIT;

	#if((TI_FEE_NUMBER_OF_EEPS == 2U) && (TI_FEE_DRIVER == 1U))
	if((TI_Fee_GlobalVariables[0].Fee_ModuleState == UNINIT)
		&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == UNINIT))
	{
		ModuleState = UNINIT;
	}
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == UNINIT)
			&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == IDLE))
	{
		ModuleState = IDLE;
	}
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == UNINIT)
			&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == BUSY))
	{
		ModuleState = BUSY;
	}
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == UNINIT)
			&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == BUSY_INTERNAL))
	{
		ModuleState =BUSY_INTERNAL;
	}


	if((TI_Fee_GlobalVariables[0].Fee_ModuleState == IDLE)
	   &&(TI_Fee_GlobalVariables[1].Fee_ModuleState == UNINIT))
	{
		ModuleState = IDLE;
	}
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == IDLE)
			&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == IDLE))
	{
		ModuleState =IDLE;
	}
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == IDLE)
			&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == BUSY))
	{
		ModuleState = BUSY;
	}
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == IDLE)
			&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == BUSY_INTERNAL))
	{
		ModuleState = BUSY_INTERNAL;
	}

	if((TI_Fee_GlobalVariables[0].Fee_ModuleState == BUSY)
		&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == UNINIT))
	{
		ModuleState = BUSY;
	}
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == BUSY)
			&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == IDLE))
	{
		ModuleState = BUSY;
	}
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == BUSY)
			&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == BUSY))
	{
		ModuleState = BUSY;
	}
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == BUSY)
			&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == BUSY_INTERNAL))
	{
		ModuleState = BUSY;
	}


	if((TI_Fee_GlobalVariables[0].Fee_ModuleState == BUSY_INTERNAL)
		&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == UNINIT))
	{
		ModuleState = BUSY_INTERNAL;
	}
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == BUSY_INTERNAL)
			&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == IDLE))
	{
		ModuleState = BUSY_INTERNAL;
	}
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == BUSY_INTERNAL)
			&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == BUSY))
	{
		ModuleState = BUSY;
	}
	else if((TI_Fee_GlobalVariables[0].Fee_ModuleState == BUSY_INTERNAL)
			&&(TI_Fee_GlobalVariables[1].Fee_ModuleState == BUSY_INTERNAL))
	{
		ModuleState = BUSY_INTERNAL;
	}

	if((TI_Fee_oStatusWord[0].Fee_StatusWordType_ST.Erase != 0U) ||
	   (TI_Fee_oStatusWord[0].Fee_StatusWordType_ST.Copy != 0U)  ||
	   (TI_Fee_oStatusWord[1].Fee_StatusWordType_ST.Erase != 0U) ||
	   (TI_Fee_oStatusWord[1].Fee_StatusWordType_ST.Copy != 0U))
	{
		ModuleState = BUSY;
	}
	#elif(TI_FEE_NUMBER_OF_EEPS == 1U)
	if((TI_Fee_oStatusWord[0].Fee_StatusWordType_ST.Erase != 0U) ||
	    (TI_Fee_oStatusWord[0].Fee_StatusWordType_ST.Copy != 0U))
	{
		ModuleState = BUSY;
	}
	else
	{
		ModuleState = TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState;
	}
	#endif

	return(ModuleState);
}

/**********************************************************************************************************************
 *  TI_FeeInternal_CheckForError
 *********************************************************************************************************************/
/*! \brief      This function checks if the error is severe error.
 *  \param[in]	uint8 u8EEPIndex
 *  \param[out] none 
 *  \return 	TI_FeeModuleStatusType
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
void TI_FeeInternal_CheckForError(uint8 u8EEPIndex)
{	
	if((Error_BlockInvalid == TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error) ||
	   (Error_NullDataPtr == TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error) ||
	   (Error_InvalidVirtualSectorParameter == TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error) ||	   
	   (Error_BlockOffsetGtBlockSize == TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error) ||
	   (Error_LengthParam == TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error) ||
	   (Error_FeeUninit == TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error) ||
	   (Error_Suspend == TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error) ||
	   (Error_InvalidBlockIndex == TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error) ||
	   (Error_NoErase == TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error) ||
	   (Error_CurrentAddress == TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error) ||
	   (Error_Exceed_No_Of_DataSets == TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error) ||
	   (Error_EraseVS == TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error)
	  )
	{
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error = Error_Nil;
	}		
}

/**********************************************************************************************************************
 *  TI_FeeInternal_Fletcher16
 *********************************************************************************************************************/
/*! \brief      This function calculates Checksum.
 *  \param[in]	uint8 *pu8data
 *  \param[in]	uint16 u16Length
 *  \param[out] none 
 *  \return 	16bit checksum
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
 #if(TI_FEE_FLASH_CHECKSUM_ENABLE == STD_ON)
uint32 TI_FeeInternal_Fletcher16( uint8 const *pu8data, uint16 u16Length)
{
	uint16 u16sum1 = 0xFFU;
	uint16 u16sum2 = 0xFFU;	
	uint16 u16len;		
	 
	while(u16Length > 0U) 
	{
		u16len = u16Length > 20U ? 20U : u16Length;
		u16Length -= u16len;
		do 
		{
			if(pu8data != 0U)
			{
				u16sum1 += *pu8data;
				pu8data += 1U;
			}	
			u16sum2 += u16sum1;
			u16len -= 1U;
			
		}while(u16len > 0U);
		u16sum1 = (u16sum1 & 0xFFU) + (u16sum1 >> 8U);
		u16sum2 = (u16sum2 & 0xFFU) + (u16sum2 >> 8U);
	}
	/* Second reduction step to reduce sums to 8 bits */
	u16sum1 = (u16sum1 & 0xFFU) + (u16sum1 >> 8U);
	u16sum2 = (u16sum2 & 0xFFU) + (u16sum2 >> 8U);
	return ((u16sum2 << 8U) | u16sum1);
}
#endif
/**********************************************************************************************************************
 *  TI_Fee_ErrorRecovery
 *********************************************************************************************************************/
/*! \brief      This function checks if the error is severe error.
 *  \param[in]	ErrorCode, u8VirtualSector
 *  \param[out] none 
 *  \return 	TI_FeeModuleStatusType
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 *********************************************************************************************************************/
/* SourceId : HL_Fee_SourceId_32 */
/* Requirements : HL_FEE_SR96 */
/* DesignId : HL_FEE_DesignId_32 */
/*SAFETYMCUSW 61 D MR:8.10,8.11 <APPROVED> "Reason -  This API will be called by application."*/
void TI_Fee_ErrorRecovery(TI_Fee_ErrorCodeType ErrorCode, uint8 u8VirtualSector)
{
	uint8 u8EEPIndex = 0U;
	TI_Fee_AddressType u32VirtualSectorStartAddress = 0U;
	TI_Fee_AddressType u32VirtualSectorEndAddress = 0U;
	boolean bFlashStatus;
	uint16 u16LoopIndex=0U;	
	Fapi_FlashSectorType oSectorStart = Fapi_FlashSector63;

	for(u16LoopIndex=0U;u16LoopIndex<TI_FEE_NUMBER_OF_VIRTUAL_SECTORS;u16LoopIndex++)	
	{			
		/* Determine the Start & End Address for the Virtual Sector */						
		if(u8VirtualSector == Fee_VirtualSectorConfiguration[u16LoopIndex].FeeVirtualSectorNumber)		
		{	
			oSectorStart=Fee_VirtualSectorConfiguration[u16LoopIndex].FeeStartSector;			
			break;
		}	
	}		
	#if(TI_FEE_NUMBER_OF_EEPS==2U)
	/* If the Virtual Sector index is greater than the virtual sectors configured for EEP1, then the VS is 
	   configured for EEP2. */
	if(u8VirtualSector > TI_FEE_NUMBER_OF_VIRTUAL_SECTORS_EEP1)
	{	
		u8EEPIndex = 1U;
	}
	else
	{	
		u8EEPIndex = 0U;
	}	
	#endif
	
	/* Call F021 to set up EEPROM banks since INIT did not do it for errors */
	/*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/	  
	/*SAFETYMCUSW 433 S MR:6.1,6.2,10.1,10.2,10.3,10.4 <APPROVED> "Macro comes from compiler files."*/	  
	if(FALSE == TI_Fee_FapiInitCalled)
	{
		if((Fapi_initializeFlashBanks((uint32)TI_FEE_OPERATING_FREQUENCY))==Fapi_Status_Success)
		{
			TI_Fee_FapiInitCalled = TRUE;				
			(void)Fapi_setActiveFlashBank(Device_FlashDevice.Device_BankInfo[0].Device_Core); 
			(void)Fapi_enableEepromBankSectors(FEE_ENABLE_SECTORS_31_00, FEE_ENABLE_SECTORS_63_32);	
		}	
	}
	
	switch(ErrorCode)
	{
		/* Mark one of the Active/Copy VS as Ready for Erase. It will be erased in background.*/
		case Error_TwoActiveVS:			
		case Error_TwoCopyVS:
			/* Update the start address for writing */
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress  =  TI_FeeInternal_GetVirtualSectorParameter((Fapi_FlashSectorType)u8VirtualSector,
																				  (uint16)FEE_BANK,
									                                              /*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/
																				  TRUE, u8EEPIndex);
			TI_FeeInternal_WriteVirtualSectorHeader(u8VirtualSector,VsState_ReadyForErase, u8EEPIndex);			
			TI_Fee_u32ActCpyVS = 0U;
			(void)TI_FeeInternal_PollFlashStatus();
			TI_Fee_Init();
			break;		
		
		case Error_SetupStateMachine:
		case Error_NoActiveVS:		
			TI_Fee_Init();
			break; 	
			
		/* Mark the copy VS as Active VS. */
		case Error_CopyButNoActiveVS:			
			TI_FeeInternal_WriteVirtualSectorHeader(u8VirtualSector,VsState_Active, u8EEPIndex);
			TI_Fee_u32ActCpyVS = 0U;
			(void)TI_FeeInternal_PollFlashStatus();
			/* Call Init to capture the address of blocks, next write address etc.*/
			TI_Fee_Init();
			break;
			
		/* There are no free VS's for copying. Erase one of the VS */
		case Error_NoFreeVS:			
			u32VirtualSectorStartAddress = TI_FeeInternal_GetVirtualSectorParameter(oSectorStart,
			                          /*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/
									  (uint16)FEE_BANK,TRUE, u8EEPIndex);
			u32VirtualSectorEndAddress = u32VirtualSectorStartAddress+TI_FeeInternal_GetVirtualSectorParameter(
			            /*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/
						oSectorStart,(uint16)FEE_BANK,FALSE, u8EEPIndex);
			/* Errata : Enable only required sector to erase. */
			TI_FeeInternal_EnableRequiredFlashSector(u32VirtualSectorStartAddress);		
			/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason - Casting is required here."*/
			if((Fapi_issueAsyncCommandWithAddress(Fapi_EraseSector,
												  (uint32_t *)u32VirtualSectorStartAddress
												  ))==Fapi_Status_Success)
			 {
				/* Nothing to be done inside */
			 }			
			/*SAFETYMCUSW 91 D MR:16.10 <APPROVED> "Reason - Return value is used in following code."*/
			(void)TI_FeeInternal_PollFlashStatus();
			(void)Fapi_enableEepromBankSectors(FEE_ENABLE_SECTORS_31_00, FEE_ENABLE_SECTORS_63_32);
			/* Check if it is Blank */
			bFlashStatus = TI_FeeInternal_BlankCheck(u32VirtualSectorStartAddress,u32VirtualSectorEndAddress,
			                                       (uint16)FEE_BANK,u8EEPIndex);
			/* If it is not Blank, report an Error */
			if(bFlashStatus == FALSE)
			{
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error = Error_EraseVS;
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_FAILED;
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus = TI_FEE_ERROR;				
			}			
			break;	
		
		case Error_EraseVS:
			u32VirtualSectorStartAddress = TI_FeeInternal_GetVirtualSectorParameter(oSectorStart,
			                          /*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/
									  (uint16)FEE_BANK,TRUE, u8EEPIndex);
			/* Errata : Enable only required sector to erase. */
			TI_FeeInternal_EnableRequiredFlashSector(u32VirtualSectorStartAddress);		
			/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason - Casting is required here."*/
			if((Fapi_issueAsyncCommandWithAddress(Fapi_EraseSector,
												 (uint32_t *)u32VirtualSectorStartAddress
												  ))==Fapi_Status_Success)
			 {
				/* Nothing to be done inside */				
			 }
			 (void)TI_FeeInternal_PollFlashStatus();
			 (void)Fapi_enableEepromBankSectors(FEE_ENABLE_SECTORS_31_00, FEE_ENABLE_SECTORS_63_32);			 
			 break;
		default:
			break;
	}
}

#if(TI_FEE_FLASH_ERROR_CORRECTION_HANDLING == TI_Fee_Fix) 
/***********************************************************************************************************************
 *  TI_Fee_ErrorHookSingleBitError
 **********************************************************************************************************************/
/*! \brief      This hook should be called in ESM notification function.
 *  \param[in]	none
 *  \param[out] none 
 *  \return 	none
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 **********************************************************************************************************************/
void TI_Fee_ErrorHookSingleBitError(void)
{ 	
	Fee_bSingleBitError = TRUE;
}

/***********************************************************************************************************************
 *  TI_Fee_ErrorHookDoubleBitError
 **********************************************************************************************************************/
/*! \brief      This hook should be called in ESM notification function.
 *  \param[in]	none
 *  \param[out] none 
 *  \return 	none
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 **********************************************************************************************************************/
void TI_Fee_ErrorHookDoubleBitError(void)
{ 
	Fee_bDoubleBitError = TRUE;		
}
#endif

/***********************************************************************************************************************
 *  TI_Fee_SuspendResumeErase
 **********************************************************************************************************************/
/*! \brief      This API should be called in by application.
 *  \param[in]	Command
 *  \param[out] none 
 *  \return 	none
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 **********************************************************************************************************************/
/*SAFETYMCUSW 61 D MR:8.10,8.11 <APPROVED> "Reason -  Cannot be static since it is used application."*/
void TI_Fee_SuspendResumeErase(TI_Fee_EraseCommandType Command)
{
	uint8 u8EEPIndex = 0U;
	static TI_FeeJobResultType static_u16JobResult;
	static TI_FeeModuleStatusType static_ModuleState;
	static uint8 static_u8EraseSuspended[TI_FEE_NUMBER_OF_EEPS];

	while(u8EEPIndex<TI_FEE_NUMBER_OF_EEPS)
	{
		if(Suspend_Erase == Command)
		{
			if(TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Erase != 0U)
			{
			    /* Suspend Erase */
				/* Suspending Erase when erase was not started has no effect */
				FAPI_SUSPEND_FSM;
				/* Wait until Flash is not BUSY. It will take approximately
				  43usec for the FSM state machine to come out of BUSY state, if ERASE was started */
				(void)TI_FeeInternal_PollFlashStatus();
				TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Erase = 0U;
				static_u8EraseSuspended[u8EEPIndex] = 1u;
				static_u16JobResult = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult;
				static_ModuleState = TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState;
	            TI_Fee_bEraseSuspended = TRUE;
	            if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult == JOB_PENDING)
	            {
	                TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_OK;
	                #if(STD_OFF == TI_FEE_POLLING_MODE)
	                TI_FEE_NVM_JOB_END_NOTIFICATION();
	                #endif
	            }
	            /* Set the module state to IDLE */
	            TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = IDLE;
			}
			else
			{
			    static_u8EraseSuspended[u8EEPIndex] = 0u;
			}
		}
		else
		{
		    if(1u == static_u8EraseSuspended[u8EEPIndex])
		    {
	            TI_Fee_bEraseSuspended = FALSE;
	            /*Resuming Erase when it was not suspended has no effect */
	            (void)Fapi_issueAsyncCommand(Fapi_EraseResume);
	            static_u8EraseSuspended[u8EEPIndex] = 0u;
                TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = static_u16JobResult;
                TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = static_ModuleState;
                TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Erase = 1U;
		    }
		}
		u8EEPIndex++;
	}
}
/***********************************************************************************************************************
 *  TI_FeeInternal_EnableRequiredFlashSector
 **********************************************************************************************************************/
/*! \brief      This API should be called in by application.
 *  \param[in]	u32VirtualSectorStartAddress
 *  \param[out] none 
 *  \return 	none
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 **********************************************************************************************************************/
/*SAFETYMCUSW 61 D MR:8.10,8.11 <APPROVED> "Reason -  Cannot be static since it is used in format API."*/
 void TI_FeeInternal_EnableRequiredFlashSector(uint32 u32VirtualSectorStartAddress)
{
	uint32 u32SectorsEnables_31_00 = 0U;
	uint32 u32SectorsEnables_63_32 = 0U;
	uint8 u8LoopIndex = 0U;
	uint32 u32SectorRequired = 0U; 
		
	/* Disable all the sectors */
	u32SectorsEnables_31_00 = FEE_DISABLE_SECTORS_31_00;
	u32SectorsEnables_63_32 = FEE_DISABLE_SECTORS_63_32;
	
	/* Loop through all the sectors */
	#if (TI_FEE_GENERATE_DEVICEANDVIRTUALSECTORSTRUC == STD_ON)
	for(u8LoopIndex = 0U ; u8LoopIndex<TI_Fee_MaxSectors ; u8LoopIndex++)
	#else
	for( u8LoopIndex = 0U ; u8LoopIndex<DEVICE_BANK_MAX_NUMBER_OF_SECTORS ; u8LoopIndex++)
	#endif	
	{				
		/* Check if the sector address matched with the sector to be erased */
		if((Device_FlashDevice.Device_BankInfo[FEE_BANK].Device_SectorInfo[u8LoopIndex].Device_SectorStartAddress) == u32VirtualSectorStartAddress)
		{			
			break;	
		}		
	}	
	/* Set required bit position */
	u32SectorRequired |= (1U << u8LoopIndex);
	
	if(u8LoopIndex < 32U)
	{
		u32SectorsEnables_31_00 = u32SectorRequired;
	}
	else
	{
		u32SectorsEnables_63_32 = u32SectorRequired;
	}	
	(void)Fapi_enableEepromBankSectors(u32SectorsEnables_31_00, u32SectorsEnables_63_32);
}
/***********************************************************************************************************************
 *  TI_FeeInternal_PopulateStructures
 **********************************************************************************************************************/
/*! \brief      This API is called by FEE INIT API.
 *  \param[in]	DeviceType
 *  \param[out] none 
 *  \return 	none
 *  \context    Internal Function.
 *  \note       TI FEE Internal API.
 **********************************************************************************************************************/
#if (TI_FEE_GENERATE_DEVICEANDVIRTUALSECTORSTRUC == STD_ON)
void TI_FeeInternal_PopulateStructures(TI_Fee_DeviceType DeviceType)
{
	uint32 u32FeeSectStartAddr = 0xF0200000U;
	uint32 u32FeeSectSize = 0U;
	uint32 u32FeeECCSectStartAddr = 0xF0100000U;
	uint32 u32FeeECCSectSize = 0U;
	uint8 u8LoopIndex = 0U;
	uint8 u8NumberOfPhysicalSectors = 0U;
	uint8 u8EndSector = 0U;
	uint8 u8PSToFormVS = 0U;

	Device_FlashDevice.Device_BankInfo[0].Device_ControlRegister = F021_CPU0_BASE_ADDRESS;
	Device_FlashDevice.Device_BankInfo[0].Device_Core = Fapi_FlashBank7;
	if(DeviceType == ARCHER)
	{
		u32FeeSectSize = 0x00001000U;	/* Each Sector is 4KB in size */
		u32FeeECCSectSize = 0x00000200U;/* ECC Size for 4KB FEE sector size */
		u8NumberOfPhysicalSectors = 16U;
		/* Calculate number of physical sectors required to form required virtual sector */
		u8PSToFormVS = TI_FEE_VIRTUALSECTOR_SIZE / 4U; /* Each Physical Sector is 4KB in Size */
	}
	else
	{
		u32FeeSectSize = 0x00004000U;	/* Each Sector is 16KB in size */
		u32FeeECCSectSize = 0x00000800U;/* ECC Size for 16KB FEE sector size */
		u8NumberOfPhysicalSectors = 4U;
		/* Calculate number of physical sectors required to form required virtual sector */
		u8PSToFormVS = TI_FEE_VIRTUALSECTOR_SIZE / 16U;	/* Each Physical Sector is 16KB in Size */
	}
	
	/* Fill in Device Specific Structure */
	for(u8LoopIndex = 0U; u8LoopIndex < u8NumberOfPhysicalSectors; u8LoopIndex++)
	{
		Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[u8LoopIndex].Device_Sector = (Fapi_FlashSectorType) u8LoopIndex;
		Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[u8LoopIndex].Device_SectorStartAddress = (u32FeeSectStartAddr + ((uint32)u8LoopIndex*u32FeeSectSize));
		Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[u8LoopIndex].Device_SectorLength = u32FeeSectSize;
		Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[u8LoopIndex].Device_EccAddress = (u32FeeECCSectStartAddr + ((uint32)u8LoopIndex*u32FeeECCSectSize));
		Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[u8LoopIndex].Device_EccLength = u32FeeECCSectSize;
	}
	
	/* Fill in Virtual Sector Configuration Structure */
	for(u8LoopIndex = 0U; u8LoopIndex < TI_FEE_NUMBER_OF_VIRTUAL_SECTORS; u8LoopIndex++)
	{
		Fee_VirtualSectorConfiguration[u8LoopIndex].FeeVirtualSectorNumber = u8LoopIndex+1U; /* Virtual Sector starts with 1U */
		Fee_VirtualSectorConfiguration[u8LoopIndex].FeeFlashBank = 7U;
		Fee_VirtualSectorConfiguration[u8LoopIndex].FeeStartSector = (Fapi_FlashSectorType) (u8EndSector);
		Fee_VirtualSectorConfiguration[u8LoopIndex].FeeEndSector = (Fapi_FlashSectorType)(Fee_VirtualSectorConfiguration[u8LoopIndex].FeeStartSector + 
		                                                            (u8PSToFormVS-1U));
		u8EndSector = Fee_VirtualSectorConfiguration[u8LoopIndex].FeeEndSector + 1U;
	}	
}
#endif
/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_STOP_SEC_CODE
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"
/**********************************************************************************************************************
 *  END OF FILE: ti_fee_util.c
 *********************************************************************************************************************/

