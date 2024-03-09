/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  ti_fee_readSync.c
 *      Project:  Tms570_TIFEEDriver
 *       Module:  TIFEEDriver
 *    Generator:  None
 *
 *  Description:  This file implements the TI FEE Api TI_Fee_ReadSync.
 *---------------------------------------------------------------------------------------------------------------------
 * Author:  Vishwanath Reddy
 *---------------------------------------------------------------------------------------------------------------------
 * Revision History
 *---------------------------------------------------------------------------------------------------------------------
 * Version        Date         Author               Change ID        Description
 *---------------------------------------------------------------------------------------------------------------------
 * 01.12.00       13Dec2013	   Vishwanath Reddy     SDOCM00104076	 New API to read data synchronously.		
 * 01.13.00       30Dec2013	   Vishwanath Reddy     SDOCM00107976	 Check for Multi Bit error.
 *                                                  SDOCM00105795	 Limit access of FEE to EEPROM bank.
 * 01.15.00		  06Jun2014    Vishwanath Reddy 	                 Support for TMS570LCx.
 * 01.16.00		  15Jul2014    Vishwanath Reddy 	SDOCM00112141    Remove  MISRA warnings.
 * 01.17.00		  15Oct2014    Vishwanath Reddy     SDOCM00113379    RAM Optimization changes.
 * 01.18.00		  12Oct2015    Vishwanath Reddy     SDOCM00119455    Update version history.
 * 01.18.01		  17Nov2015    Vishwanath Reddy     SDOCM00120161    Update version history.
 * 01.18.02		  05Feb2016    Vishwanath Reddy     SDOCM00121158    Update version history.
 *                                                                   Add a call of TI_FeeInternal_PollFlashStatus()
 *                                                                   before reading data from FEE bank. 
 * 01.18.03       30June2016   Vishwanath Reddy     SDOCM00122388    Update version history. 
 * 01.19.00       08Augu2016   Vishwanath Reddy     SDOCM00122592    Update version history. 
 * 01.19.01       12Augu2016   Vishwanath Reddy     SDOCM00122543    Changes to avoid FEE reading from unimplemented 
 *                                                                   memory space. 
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
 *  TI_Fee_ReadSync
 *********************************************************************************************************************/
/*! \brief      This function performs the Synchronous Read operation on the Block. 
 *  \param[in]  uint16 BlockNumber
 *  \param[in]	uint16 BlockOffset
 *  \param[in]	uint8* DataBufferPtr
 *  \param[in]	uint16 Length
 *  \param[out] none
 *  \return     E_OK
 *  \return     E_NOT_OK
 *  \context    Function could be called from task level
 *  \note       TI FEE API.
 *********************************************************************************************************************/
/* SourceId : HL_Fee_SourceId_7 */
/* DesignId : HL_FEE_DesignId_20 */
/* Requirements : HL_FEE_SR25, HL_FEE_SR26, HL_FEE_SR27, HL_FEE_SR28, HL_FEE_SR29, HL_FEE_SR30 */
 #if(TI_FEE_DRIVER == 1U)
 /*SAFETYMCUSW 61 D MR:8.10,8.11 <APPROVED> "Reason -  This API will be called by application."*/
Std_ReturnType TI_Fee_ReadSync(uint16 BlockNumber,uint16 BlockOffset,uint8* DataBufferPtr,uint16 Length)
{
	uint32 u32BlockSize = 0U,au32BlockAddress[2],au32BlockStatus[2];
	TI_Fee_AddressType oBlockAddress=0U;
	uint16 u16BlockIndex=0U;	
	uint32 **ppu32ReadHeader=0U;	
	/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be fixed outside
      of FEE."*/
	Std_ReturnType oResult=E_OK;
	uint16 u16DataSetNumber=0U;
	uint8 u8EEPIndex=0U;
	uint16 u16BlockNumber=0U;	
	uint16 u16ArrayIndex = 0U;	
	TI_FeeModuleStatusType ModuleState=IDLE;		
	
	TI_Fee_u8DeviceIndex = 0U;		

	/* Determine the Block number & Block index */
	/* From the block number, remove data selection bits */
	u16BlockNumber = TI_FeeInternal_GetBlockNumber(BlockNumber);
	/* Get the index of the block in Fee_BlockConfiguration array */
	u16BlockIndex = TI_FeeInternal_GetBlockIndex(u16BlockNumber);	
	/* If block index is not found, report an error */
	if(u16BlockIndex == 0xFFFFU)
	{
	  TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus = TI_FEE_ERROR;
	  TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_FAILED;
	  TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error = Error_InvalidBlockIndex;
	}
	else
	{	
		/* Read the device index from the block configuration */
		u8EEPIndex = Fee_BlockConfiguration[u16BlockIndex].FeeEEPNumber;	
		ModuleState=TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState;
		if(UNINIT == ModuleState)
		{
			/* Module is Not Initialized */
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus=TI_FEE_ERROR;
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error=Error_FeeUninit;
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult=JOB_FAILED;
			/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be fixed
  			 outside of FEE"*/
			oResult=E_NOT_OK;
		}
		else
		{
			TI_Fee_u8DeviceIndex = u8EEPIndex;
			/* Get the DataSet index after removing the Block number */
			/*SAFETYMCUSW 91 D MR:16.10 <APPROVED> "Reason - Return value is used in following code."*/
			u16DataSetNumber = TI_FeeInternal_GetDataSetIndex(BlockNumber);
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
		/* Read current state*/
		/* If the module state is BUSY_INTERNAL, change it to IDLE */
		oResult = TI_FeeInternal_CheckModuleState(u8EEPIndex);
		/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be fixed
 		outside of FEE"*/
		if((oResult == (uint8)E_OK) && 
		   (TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Read != 1U) && 
		   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult != JOB_PENDING))
		{		
			/* Initialize the DataSetIndex */
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16DataSetIndex = 0U;			
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockIndex = u16BlockIndex;
			/* Report error if Block index cannot be found */
			if(u16BlockIndex == 0xFFFFU)
			{
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_FAILED;
				/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be 
				  fixed outside of FEE"*/
				oResult = E_NOT_OK;					
			}
			else
			{
				/* Determine the Block Size */
				u32BlockSize = Fee_BlockConfiguration[u16BlockIndex].FeeBlockSize;
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_PENDING;
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = BUSY;				
				/* Check if the parameters used for Fee_Read are proper or not */
				oResult = TI_FeeInternal_CheckReadParameters(u32BlockSize,BlockOffset,DataBufferPtr,Length,u8EEPIndex);
				/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be 
				  fixed outside of FEE"*/
				if(oResult == (uint8)E_OK)
				{
					/* If using more than one DataSet, find out the DataSet Index. If Dataset Index is not found, 
					   report an error */
					if(Fee_BlockConfiguration[u16BlockIndex].FeeNumberOfDataSets > 1U)
					{
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16DataSetIndex = u16DataSetNumber;
						if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16DataSetIndex > 
						   Fee_BlockConfiguration[u16BlockIndex].FeeNumberOfDataSets)
						{
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_FAILED;
							/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.
							  This should be fixed outside of FEE."*/
							oResult = E_NOT_OK;								
						}						
					}

					if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult != JOB_FAILED)
					{
						/* Get the Current Block Address for this Block */
						oBlockAddress = TI_FeeInternal_GetCurrentBlockAddress(u16ArrayIndex,
						                                        u16DataSetNumber,u8EEPIndex);
						if(oBlockAddress == 0x00000000U)
						{
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = BLOCK_INVALID;
							/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.
							   This should be fixed outside of FEE."*/
							oResult = E_OK;								
						}	
					}

					if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult != JOB_FAILED) && 
					   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult != BLOCK_INVALID))
					{
						/* Wait till FSM is READY */
						(void)TI_FeeInternal_PollFlashStatus();
						/* Read the Block Header and check if it is valid */						
						/* If invalid, report an Error else continue reading the block */				
						au32BlockAddress[0] = oBlockAddress;						
						au32BlockAddress[1] = au32BlockAddress[0]+4U;
						/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
						/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
						ppu32ReadHeader = (uint32 **)&au32BlockAddress[0];							
						au32BlockStatus[0] = **ppu32ReadHeader;
						/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
						/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
						ppu32ReadHeader = (uint32 **)&au32BlockAddress[1];
						au32BlockStatus[1] = **ppu32ReadHeader;

						if((au32BlockStatus[0]==ValidBlockLo) && (au32BlockStatus[1] == ValidBlockHi))
						{								
							#ifndef _L2FMC
							#if (STD_ON == TI_FEE_FLASH_ERROR_CORRECTION_ENABLE)
							/* Clear multi bit error's before initiating read */
							if(1U == Device_FlashDevice.Device_BankInfo[0].Device_ControlRegister->EeStatus.EE_STATUS_BITS.EE_UNC_ERR)
							{
								Device_FlashDevice.Device_BankInfo[0].Device_ControlRegister->EeStatus.EE_STATUS_BITS.EE_UNC_ERR = 1U;
							}
							#endif
							#endif
							/* Read the Data */
							/* Determine the start address for the Read command */
							/* Start Address of data  = Current Address + Block Header Size + offset in the data */															
							/*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Reason -  Null pointer check is done for 
							  oBlockAddress."*/
							/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  Casting is required here."*/
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8ReadAddress = (uint8 *)oBlockAddress ;								
							/*SAFETYMCUSW 567 S MR:17.1,17.4 <APPROVED> "Reason -  Pointer Arithmatic is necessary here."*/
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8ReadAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8ReadAddress+(uint32)TI_FEE_BLOCK_OVERHEAD+(uint32)BlockOffset;								
							/* If the length of the block to read is 0xffff, then the length of the block is read 
							   from the block header */
							if(Length == 0xFFFFU)
							{								
								/* Length of the block is present in 2 bytes of last 4 bytes*/		
								/* If block header is 24 bytes(0-23), 20-21 bytes are block size */
								oBlockAddress += (((TI_FEE_BLOCK_OVERHEAD >> 2U)-1U) << 2U);
								/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
								/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
								ppu32ReadHeader = (uint32 **)&oBlockAddress;
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize = (uint16)(((**ppu32ReadHeader)&0xFFFF0000U)>>16U);
								oBlockAddress -= (((TI_FEE_BLOCK_OVERHEAD >> 2U)-1U) << 2U);
							} 
							else
							{
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize = Length;
							}	
							/* Update the pointer. */							
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8ReadDataBuffer = DataBufferPtr;							
							/* Update the status */
							TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.ReadSync = 1U;	
							
							/* Read complete data of the block */
							while((TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize>0U))								   
							{							
								/*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Reason -  Null pointer check is done in ti_fee_read."*/
								*TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8ReadDataBuffer=*TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8ReadAddress;
								
								if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8ReadDataBuffer != NULL_PTR)
								{
									/*SAFETYMCUSW 567 S MR:17.1,17.4 <APPROVED> "Reason -  Pointer Arithmatic is necessary here."*/
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8ReadDataBuffer++;						
								}									
								#if(TI_FEE_CHECK_BANK7_ACCESS == STD_ON)
								if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8ReadAddress > (uint8 *)Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[0].Device_SectorStartAddress)
							       && (TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8ReadAddress < (uint8 *) Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[DEVICE_BANK_MAX_NUMBER_OF_SECTORS-1U].Device_SectorStartAddress+
			                           Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[DEVICE_BANK_MAX_NUMBER_OF_SECTORS-1U].Device_SectorLength))
								{
									if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8ReadAddress != NULL_PTR)
									{
										/*SAFETYMCUSW 567 S MR:17.1,17.4 <APPROVED> "Reason -  Pointer Arithmatic is necessary here."*/
										TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8ReadAddress++;						
									}
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize--;	
								}
								else
								{
									/* Address is out of bank7 range. Reset block size so that no furthur read's happen */
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize = 0U;
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_FAILED;
								}
								#else
								if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8ReadAddress != NULL_PTR)
								{
									/*SAFETYMCUSW 567 S MR:17.1,17.4 <APPROVED> "Reason -  Pointer Arithmatic is necessary here."*/
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8ReadAddress++;						
								}	
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize--;
								#endif
							}
							if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize == 0U)
							{						
								/* Finished reading */
								TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.ReadSync=0U;
								#ifndef _L2FMC
								#if (STD_ON == TI_FEE_FLASH_ERROR_CORRECTION_ENABLE)
								/* Check if there is multi bit error/uncorectable error, update job result*/
								if(1U == Device_FlashDevice.Device_BankInfo[0].Device_ControlRegister->EeStatus.EE_STATUS_BITS.EE_UNC_ERR)
								{
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult=BLOCK_INCONSISTENT;
								}
								else
								#endif
								#endif
								{
									/* Finished reading correctly */
									if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult != JOB_FAILED)
									{
										TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult=JOB_OK;
									}	
								}								
								/* Set the module state to IDLE since the Read command has been completed */
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState=IDLE;								
								#ifndef _L2FMC
								#if(STD_OFF == TI_FEE_POLLING_MODE)
								if(1U == Device_FlashDevice.Device_BankInfo[0].Device_ControlRegister->EeStatus.EE_STATUS_BITS.EE_UNC_ERR)
								{
									TI_FEE_NVM_JOB_ERROR_NOTIFICATION();
								}
								else
								{
									TI_FEE_NVM_JOB_END_NOTIFICATION();
								}
								#endif
								#endif
							}							
							/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.
							  This should be fixed outside of FEE"*/
							oResult = (uint8)E_OK;								
						}
						else
						{
							/* Invalid Block */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = BLOCK_INVALID;
							/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.
							  This should be fixed outside of FEE"*/
							oResult = E_OK;								
						}																		
					}
				}
			}
			if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult == JOB_FAILED)	
			{
				TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.ReadSync = 0U;
				TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = IDLE;					
			}
		}
	}

	if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error!=Error_Nil)
	{
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_FAILED;
		/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be fixed
 		outside of FEE"*/
		oResult = E_NOT_OK;
	}
	/*SAFETYMCUSW 331 S MR:10.1 <APPROVED> "Reason - Std_ReturnType is not part of FEE.This should be fixed 
	  outside of FEE"*/
	if((oResult == (uint8)E_NOT_OK)||
	   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult == BLOCK_INVALID)||
	   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult == JOB_FAILED))
	{
		/* no other operations are in progress, change the module state if it is initialized */
		if((TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.EraseImmediate == 0U) &&
		   (TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.InvalidateBlock == 0U) &&
		   (TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.WriteAsync == 0U)&&
		   (TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.WriteSync == 0U)&&
		   (TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Read == 0U)&&
		   (TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.ReadSync == 0U)
		  )
		{			
			/* Restore the module state */
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = ModuleState;
			TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.ReadSync = 0U;	
			#if(STD_OFF == TI_FEE_POLLING_MODE)
			TI_FEE_NVM_JOB_ERROR_NOTIFICATION();				
			#endif
		}
	}
	#if(TI_FEE_NUMBER_OF_EEPS==2U)
	TI_Fee_oStatusWord_Global.Fee_u16StatusWord = ((TI_Fee_oStatusWord[0].Fee_u16StatusWord) |
												   (TI_Fee_oStatusWord[1].Fee_u16StatusWord));
	#endif
	
    return(oResult);
}
#endif

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_STOP_SEC_CODE
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"
/**********************************************************************************************************************
 *  END OF FILE: ti_fee_readSync.c
 *********************************************************************************************************************/
