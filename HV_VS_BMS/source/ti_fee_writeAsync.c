/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  ti_fee_writeAsync.c
 *      Project:  Tms570_TIFEEDriver
 *       Module:  TIFEEDriver
 *    Generator:  None
 *
 *  Description:  This file implements the TI FEE Api, TI_Fee_WriteAsync.
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
 * 00.01.03       14Jan2013    Vishwanath Reddy     SDOCM00098510    Changes as requested by Vector.
 * 00.01.04		  12Feb2013	   Vishwanath Reddy     SDOCM00099152    Integration issues fix. 
 * 00.01.05		  04Mar2013	   Vishwanath Reddy     SDOCM00099152    Added Deleting a block feature, bug fixes. 
 * 00.01.08		  05Apr2013	   Vishwanath Reddy     SDOCM00099152    Added feature : CRC check for unconfigured blocks,
																	 Main function modified to complete writes as fast
																	 as possible, Added Non polling mode support.
 * 00.01.09		  19Apr2013	   Vishwanath Reddy     SDOCM00099152    Warning removal, Added feature comparision of data
																	 during write.								
 * 00.01.10       11Jun2013	   Vishwanath Reddy     SDOCM00101845	 Fixed issue with one EEPROM getting locked because
                                                                     of error in second EEPROM.	
 * 01.12.00		  13Dec2013    Vishwanath Reddy     SDOCM00105412    Traceability tags added. 
 *                                                                   MISRA C fixes.
 * 01.15.00       19Jun2014	   Vishwanath Reddy     SDOCM00108332	 Find new VS if space in active VS is less 
 *                                                                   than 32 bytes.
 * 01.16.00		  15Jul2014    Vishwanath Reddy 	SDOCM00112141    Remove  MISRA warnings.
 * 01.17.00		  15Oct2014    Vishwanath Reddy     SDOCM00113379    RAM Optimization changes.
 * 01.18.00		  12Oct2015    Vishwanath Reddy     SDOCM00119455    Update version history.
 * 01.18.01		  12Oct2015    Vishwanath Reddy     SDOCM00120161    Update version history.
 * 01.18.02		  05Feb2016    Vishwanath Reddy     SDOCM00121158    Update version history.
 *                                                                   Add a call of TI_FeeInternal_PollFlashStatus()
 *                                                                   before reading data from FEE bank. 
 * 01.18.03       30June2016   Vishwanath Reddy     SDOCM00122388    Update version history.
 *                                                                   TI_FEE_FLASH_CRC_ENABLE is renamed to 
 *                                                                   TI_FEE_FLASH_CHECKSUM_ENABLE.  
 * 01.19.00       08Augu2016   Vishwanath Reddy     SDOCM00122592    Update version history.
 * 01.19.01       12Augu2016   Vishwanath Reddy     SDOCM00122543    Update version history.
 * 01.19.02       25Janu2017   Vishwanath Reddy     SDOCM00122832    Update version history.   
 * 01.19.03       15May2017    Prathap Srinivasan   SDOCM00122917    Update version history.
 * 01.19.04		  05Dec2017    Prathap Srinivasan   HERCULES_SW-5082 Update version history.
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
 *  TI_Fee_WriteAsync
 *********************************************************************************************************************/
/*! \brief      This function initiates the Asynchronous Write operation to a Block.
 *  \param[in]  uint16 BlockNumber
 *  \param[in] 	uint8* DataBufferPtr
 *  \param[out] none
 *  \return     E_OK
 *  \return     E_NOT_OK
 *  \context    Function could be called from task level
 *  \note       TI FEE API.
 *********************************************************************************************************************/
/* SourceId : HL_Fee_SourceId_14 */
/* DesignId : HL_FEE_DesignId_17 */
/* Requirements : HL_FEE_SR58, HL_FEE_SR59, HL_FEE_SR60, HL_FEE_SR61 */
Std_ReturnType TI_Fee_WriteAsync(uint16 BlockNumber,uint8* DataBufferPtr)
{
	Std_ReturnType oResult=E_OK;
	uint16 u16BlockNumber = 0U;
	uint16 u16DataSetNumber = 0U;
	uint16 u16BlockIndex = 0U;
	uint16 u16ArrayIndex = 0U;
	#if(TI_FEE_FLASH_CHECKSUM_ENABLE == STD_ON)	
	uint32 u32CheckSum = 0U;
	#else
	uint8 * pu8ReadData;
	uint8 * pu8ReadSourceData;
	uint16 u16LoopIndex;
	#endif
	uint8 u8EEPIndex = 0U;
	boolean bDoNotWrite = FALSE;
	#if((TI_FEE_FLASH_WRITECOUNTER_SAVE == STD_ON) || (TI_FEE_FLASH_CHECKSUM_ENABLE == STD_ON))
	uint32 **ppu32ReadHeader = 0U;
	#endif	
	TI_FeeModuleStatusType ModuleState=IDLE;	
	boolean bError=FALSE;
	
	TI_Fee_u8DeviceIndex = 0U;	
	
	/* Check if the DataBufferPtr is a Null pointer */
	if(DataBufferPtr == 0U)
	{				
		bError = TRUE;
		/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be fixed 
		  outside of FEE."*/
		oResult = E_NOT_OK;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_FAILED;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus=TI_FEE_ERROR;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error=Error_NullDataPtr;
		#if(TI_FEE_NUMBER_OF_EEPS==2U)
		TI_Fee_GlobalVariables[u8EEPIndex+1U].Fee_oStatus=TI_FEE_ERROR;
		TI_Fee_GlobalVariables[u8EEPIndex+1U].Fee_Error=Error_NullDataPtr;
		TI_Fee_GlobalVariables[u8EEPIndex+1U].Fee_u16JobResult=JOB_FAILED;
		#endif
	}	
	/*SAFETYMCUSW 139 S MR:13.7 <APPROVED> "Reason - bError is set to TRUE in above lines."*/	
	/*SAFETYMCUSW 433 S MR:6.1,6.2,10.1,10.2,10.3,10.4  <APPROVED> "Reason - LDRA Version
      problem. Latest version do not have this warning."*/
	/*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/
	if(FALSE == bError) 
	{
		/* Determine the Block number & Block index */
		/* From the block number, remove data selection bits */
		/*SAFETYMCUSW 91 D MR:16.10 <APPROVED> "Reason - Return value is used in following code."*/
		u16BlockNumber = TI_FeeInternal_GetBlockNumber(BlockNumber);
		/* Get the index of the block in Fee_BlockConfiguration array */
		u16BlockIndex = TI_FeeInternal_GetBlockIndex(u16BlockNumber);
		/* If block index is not found, report an error */
		if(u16BlockIndex == 0xFFFFU)
		{
		  TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus = TI_FEE_ERROR;
		  TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error = Error_InvalidBlockIndex;
		  #if(TI_FEE_NUMBER_OF_EEPS==2U)
		  TI_Fee_GlobalVariables[u8EEPIndex+1U].Fee_oStatus=TI_FEE_ERROR;
		  TI_Fee_GlobalVariables[u8EEPIndex+1U].Fee_Error=Error_InvalidBlockIndex;
		  #endif
		}
		else
		{	
			/* Read the device index from the block configuration */
			u8EEPIndex = Fee_BlockConfiguration[u16BlockIndex].FeeEEPNumber;
			/* Check the module state */
			ModuleState = TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState;	
			if(UNINIT == ModuleState)
			{
				/* Module is Not Initialized */
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus=TI_FEE_ERROR;
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error=Error_FeeUninit;
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult=JOB_FAILED;
				/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be 
				  fixed outside of FEE."*/
				oResult=E_NOT_OK;
			}
			else
			{
				TI_Fee_u8DeviceIndex = u8EEPIndex;
				/* Get the DataSet index after removing the Block number */
				/*SAFETYMCUSW 91 D MR:16.10 <APPROVED> "Reason - Return value is used in following code."*/
				u16DataSetNumber  =  TI_FeeInternal_GetDataSetIndex(BlockNumber);
				/* Get the array index for address array */
				u16ArrayIndex = TI_FeeInternal_GetArrayIndex(u16BlockNumber, u16DataSetNumber, u8EEPIndex, TRUE);
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16ArrayIndex = u16ArrayIndex;
				/* To avoid MISRA warning */
				u16DataSetNumber = u16DataSetNumber;
				/* Check for any non severe errors */		
				TI_FeeInternal_CheckForError(u8EEPIndex);	
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus = TI_FEE_OK;		
			}
		}
		if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error == Error_Nil)
		{
			/* Store the module state */
			ModuleState = TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState;

			/* If the module state is BUSY_INTERNAL, change it to IDLE */
			oResult  =  TI_FeeInternal_CheckModuleState(u8EEPIndex);
			/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be fixed 
			  outside of FEE."*/
			if((oResult == (uint8)E_OK) && 
			               (TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.WriteAsync != 1U) && 
						   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult != JOB_PENDING))
			{
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = BUSY;
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_PENDING;
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16DataSetIndex = 0U;						
				/* Update Block Index in to array */				
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockIndex = u16BlockIndex;
				/* Update the data set number */
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16DataSetIndex = u16DataSetNumber;
				/* Report an error if Block Index is not found */
				if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockIndex == 0xFFFFU)
				{
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_FAILED;
					/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should 
					  be fixed outside of FEE."*/
					oResult = (uint8)E_NOT_OK;					
				}
				else
				{
					/* Get the Address for the Current Block */
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentStartAddress =TI_FeeInternal_GetCurrentBlockAddress(
					                                                        u16ArrayIndex,u16DataSetNumber,u8EEPIndex);
										
					if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentStartAddress == 0x00000000U)
					{
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error = Error_CurrentAddress;
						TI_Fee_GlobalVariables[u8EEPIndex].bWriteFirstTime = TRUE;
					}
					else
					{
						#if(TI_FEE_FLASH_WRITECOUNTER_SAVE == STD_ON)
						/* Get the block erase count */
						/* If block header is 24 bytes(0-23), 16-19 bytes are erase count */						
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentStartAddress += (((TI_FEE_BLOCK_OVERHEAD >> 2U)-2U) << 2U);
						/* Wait till FSM is READY */
						(void)TI_FeeInternal_PollFlashStatus();
						/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/									 
						/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
						/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here."*/
						ppu32ReadHeader = (uint32 **)&TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentStartAddress;
						TI_Fee_u32BlockEraseCount = **ppu32ReadHeader;
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentStartAddress -= (((TI_FEE_BLOCK_OVERHEAD >> 2U)-2U) << 2U);
						TI_Fee_u32BlockEraseCount++;
						#endif
					}
					if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult != JOB_FAILED)
					{							
						/* Get the Block Size. Function will return Block size+BlockHeader size */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize = TI_FeeInternal_GetBlockSize(
						                                 (uint16)TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockIndex);
						/* Update correct block size in to global variable. This will be written into Block Header.*/
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSizeinBlockHeader = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize-TI_FEE_BLOCK_OVERHEAD;																		
												
						/*If Checksum check if enabled, perform Checksum on the data to be written and check if Checksum matches in EEP */
						#if(TI_FEE_FLASH_CHECKSUM_ENABLE == STD_ON)						
						TI_Fee_u32FletcherChecksum = TI_FeeInternal_Fletcher16(DataBufferPtr, 
						                    TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize-TI_FEE_BLOCK_OVERHEAD);
						TI_Fee_u32FletcherChecksum |= (0xFFFF0000U) ;
						if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error != Error_CurrentAddress)
						{							
							/* Read the Checksum */
							/* If block header is 24 bytes(0-23), 12-15 bytes are Checksum */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentStartAddress += (((TI_FEE_BLOCK_OVERHEAD >> 2U)-3U) << 2U);
							/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/	
							/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here.*/
							/*SAFETYMCUSW 95 S MR:11.1,11.2<APPROVED> "Reason -  Casting is required here."*/
							ppu32ReadHeader = (uint32 **)&TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentStartAddress;
							u32CheckSum = **ppu32ReadHeader;
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentStartAddress -= (((TI_FEE_BLOCK_OVERHEAD >> 2U)-3U) << 2U);
							if(TI_Fee_u32FletcherChecksum == u32CheckSum)
							{
								bDoNotWrite = TRUE;
								/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This 
								  should be fixed outside of FEE."*/
								oResult = (uint8)E_OK;
								/* Restore the status since no writing will happen */
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = IDLE;
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_OK;
								#if(STD_OFF == TI_FEE_POLLING_MODE)
								TI_FEE_NVM_JOB_END_NOTIFICATION();	
								#endif
							}
						}
						else if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error == Error_CurrentAddress)
						{
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error = Error_Nil;
						}
						else
						{
							/* MISRA C Compliance */
						}	
						#else						
						/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here.*/
						pu8ReadData = (uint8 *)(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentStartAddress + TI_FEE_BLOCK_OVERHEAD);
						pu8ReadSourceData = DataBufferPtr;
						bDoNotWrite = TRUE;
						for(u16LoopIndex = 0U; u16LoopIndex < (TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize-TI_FEE_BLOCK_OVERHEAD); u16LoopIndex++)
						{
							if(*pu8ReadData != *pu8ReadSourceData)
							{
								bDoNotWrite = FALSE;
								break;
							}
							else
							{
								/*SAFETYMCUSW 567 S MR:17.1,17.4 <APPROVED> "Reason -  Pointer Arithmatic is necessary here."*/
								pu8ReadData++;
								/*SAFETYMCUSW 567 S MR:17.1,17.4 <APPROVED> "Reason -  Pointer Arithmatic is necessary here."*/
								pu8ReadSourceData++;
							}							
						}
						/*SAFETYMCUSW 433 S MR:6.1,6.2,10.1,10.2,10.3,10.4  <APPROVED> "Reason - LDRA Version
                          problem. Latest version do not have this warning."*/
						/*SAFETYMCUSW 96 S MR:6.1,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/	  
						if(TRUE == bDoNotWrite)	
						{
							/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This 
							  should be fixed outside of FEE."*/
							oResult = (uint8)E_OK;
							/* Restore the status since no writing will happen */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = IDLE;
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_OK;
							#if(STD_OFF == TI_FEE_POLLING_MODE)
							TI_FEE_NVM_JOB_END_NOTIFICATION();	
							#endif
						}
						#endif	
						
						if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error == Error_CurrentAddress)
						{
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error = Error_Nil;
						}	
							
						/* If using more than one DataSet, find out the DataSet Index. If Dataset Index is not 
						   found, report an error */
						if(Fee_BlockConfiguration[TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockIndex].FeeNumberOfDataSets > 1U)
						{							
							if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16DataSetIndex >= 
							   Fee_BlockConfiguration[TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockIndex].FeeNumberOfDataSets)
							{
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_FAILED;
								/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.
								  This should be fixed outside of FEE."*/
								oResult = (uint8)E_NOT_OK;								
							}						
						}							
					}
					if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult!=JOB_FAILED) && (bDoNotWrite == FALSE))
					{
						/* Get the Next Flash Address for this Block */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress = TI_FeeInternal_GetNextFlashAddress(u8EEPIndex);
						if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult!=JOB_FAILED) && (bDoNotWrite == FALSE))
						{
							/* Check if the memory space to write this block is free */
							TI_FeeInternal_SanityCheck((uint16)TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize,u8EEPIndex);
							/* If the Virtual Sector size is exceeded by this Write operation */
							/* Find out the next Virtual Sector to write to, mark that as Copy */
							if(((TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress+TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize) > TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorEndAddress)
							   || ((TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorEndAddress - TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress) <= 0x1FU))
							{									
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_bFindNextVirtualSector = TRUE;
								TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.WriteAsync = 1U;									
								
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockNumberinBlockHeader  =  BlockNumber;	
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8DataStart = DataBufferPtr;
							}								
						}
					}
					if(((TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult!=JOB_FAILED) || 
					   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus!=TI_FEE_ERROR)) && 
					   (bDoNotWrite == FALSE) && 
					   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_bFindNextVirtualSector == FALSE))
					{
						if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress>=TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress)				   			
						{						 					  
						  /* Update the next free write address */			
						  TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress+TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize;						  
						  TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress = TI_FeeInternal_AlignAddressForECC(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress);													  
						  
						  /* Update the next free write address in COPY or ACTIVE VS */
						  if(TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Copy == 1U)
						  {
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextCopyVSwriteaddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress;
						  }
						  else
						  {
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextActiveVSwriteaddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress;
						  }
						}						
						/* Subtract Block Header from block size since sanity check and VS size is already checked */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize-=TI_FEE_BLOCK_OVERHEAD;						
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockNumberinBlockHeader  =  BlockNumber;
						/* Update block offset array */							
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_au16BlockOffset[u16ArrayIndex]= (uint16)(((TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress) -(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorAddress)) & 0x0000FFFFU);
						/* Update the block copy status */						
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8BlockCopyStatus[u16ArrayIndex] = 0U;												
						/* update address for current block. This will be used in fee_main for writing block header */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentBlockHeader = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress;
						/* Initialize the write address for block header */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress  =  TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress;	
						/* Make the block status write flag as TRUE. This flag will be used in main function to write 
						   start program block status data */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWriteStartProgram = TRUE;
						/* Memorize the source pointer address */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8DataStart = DataBufferPtr;
						/* Make the write flag as TRUE. This flag will be used in main function to write data */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWriteData = TRUE;
						/* Write Job in Progress */
						TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.WriteAsync = 1U;
						oResult = (uint8)E_OK;
					}
				}				
			}
		}

		if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error!=Error_Nil)
		{
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_FAILED;
			/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be 
			  fixed outside of FEE."*/
			oResult = (uint8)E_NOT_OK;			
		}
		/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be fixed 
		  outside of FEE."*/
		if((oResult == (uint8)E_NOT_OK) || (TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult == JOB_FAILED))
		{
			/* If any other operation is in progress, don't change the module state */
			if((TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.EraseImmediate == 0U) &&
			   (TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.InvalidateBlock == 0U) &&
			   (TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.WriteAsync == 0U) &&
			   (TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.WriteSync == 0U) &&
			   (TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Read == 0U)
			  )		  
			{			
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_FAILED;
				#if(STD_OFF == TI_FEE_POLLING_MODE)
				TI_FEE_NVM_JOB_ERROR_NOTIFICATION();
				#endif
				TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.WriteAsync = 0U;			
				/* Restore the module state */
				if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error != Error_InvalidBlockIndex)
				{
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = ModuleState;
				}						
			}
		}
		#if(TI_FEE_NUMBER_OF_EEPS==2U)	
		TI_Fee_oStatusWord_Global.Fee_u16StatusWord = ((TI_Fee_oStatusWord[0].Fee_u16StatusWord) |
													   (TI_Fee_oStatusWord[1].Fee_u16StatusWord));
		#endif	
  }
  return(oResult);
}
/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_STOP_SEC_CODE
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"
/**********************************************************************************************************************
 *  END OF FILE: ti_fee_writeAsync.c
 *********************************************************************************************************************/
