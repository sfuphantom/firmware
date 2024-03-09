/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  ti_fee_main.c
 *      Project:  Tms570_TIFEEDriver
 *       Module:  TIFEEDriver
 *    Generator:  None
 *
 *  Description:  This file implements the TI FEE Api TI_Fee_MainFunction.
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
 * 00.01.04		  12Feb2012	   Vishwanath Reddy     SDOCM00099152    Integration issues fix. 
 * 00.01.05		  04Mar2013	   Vishwanath Reddy     SDOCM00099152    Added Deleting a block feature, bug fixes.
 * 00.01.07		  15Mar2013	   Vishwanath Reddy     SDOCM00099152    Added feature : Number of 8 bytes writes, fixed
																	 issue with copy blocks. 
 * 00.01.08		  05Apr2013	   Vishwanath Reddy     SDOCM00099152    Added feature : CRC check for unconfigured blocks,
																	 Main function modified to complete writes as fast
																	 as possible, Added Non polling mode support.
 * 00.01.09		  19Apr2013	   Vishwanath Reddy     SDOCM00099152    Warning removal, Added feature comparision of data
																	 during write.
 * 00.01.10       11Jun2013	   Vishwanath Reddy     SDOCM00101845    Fixed job result issue with TI_Fee_Fix.
                                                                     Moved block writing by 16 bytes after VS Header.
 * 00.01.11       05Jul2013	   Vishwanath Reddy     SDOCM00101643	 Fixed issue with SYNC write.Fee_Manager was not
                                                                     getting called for SYNC writes.
 * 01.12.00		  13Dec2013    Vishwanath Reddy     SDOCM00105412    Traceability tags added. 
 *                                                                   MISRA C fixes.
 * 01.13.00       30Dec2013	   Vishwanath Reddy     SDOCM00107976	 Check for Multi Bit error.
 *                                                  SDOCM00105795	 Limit access of FEE to EEPROM bank.
 * 01.13.01       19May2014	   Vishwanath Reddy     SDOCM00107622    Changes for Unexpected Job Result. Set Job result
 *                                                                   before changing module state.
 * 01.13.02       12Jun2014	   Vishwanath Reddy     SDOCM00108238	 Remove the check for IDLE state during the write
 *                                                                   of valid and invalid blocks.
 * 01.14.00		  26Mar2014    Vishwanath Reddy 	SDOCM00107161    Update jobresult before updaing module state. 
 * 01.15.00		  06Jun2014    Vishwanath Reddy 	                 Support for TMS570LCx.
 * 01.16.00		  15Jul2014    Vishwanath Reddy 	SDOCM00112141    Remove  MISRA warnings.
 * 01.17.00		  15Oct2014    Vishwanath Reddy     SDOCM00113379    RAM Optimization changes.
 * 01.17.02		  26Dec2014    Vishwanath Reddy     SDOCM00114423    Changes for unification of Champion/Archer.
 * 01.18.00		  12Oct2015    Vishwanath Reddy     SDOCM00119455    Update version history.
 * 01.18.01		  17Nov2015    Vishwanath Reddy     SDOCM00120161    Update version history.
 * 01.18.02		  05Feb2016    Vishwanath Reddy     SDOCM00121158    Update version history.
 * 01.18.03       30June2016   Vishwanath Reddy     SDOCM00122388    Update version history.
 * 01.19.00       08Augu2016   Vishwanath Reddy     SDOCM00122592    Bugfix for FEE reading from unimplemented memory
 *                                                                   space.
 * 01.19.01       12Augu2016   Vishwanath Reddy     SDOCM00122543    Bugfix for FEE reading from unimplemented memory
 *                                                                   space.
 * 01.19.02       25Janu2017   Vishwanath Reddy     SDOCM00122832    Update version history.
 * 01.19.03       15May2017    Prathap Srinivasan   SDOCM00122917    Removed Block Size interpretation for Blocks that 
 *                                                                   are not Valid, Invalid or Empty. 
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
#define FEE_START_SEC_VAR_INIT_UNSPECIFIED  
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"

#if(TI_FEE_FLASH_ERROR_CORRECTION_HANDLING == TI_Fee_Fix)
boolean Fee_bDoubleBitError;
boolean Fee_bSingleBitError;
#endif

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_STOP_SEC_VAR_INIT_UNSPECIFIED  
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_START_SEC_CODE
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"
/***********************************************************************************************************************
 *  TI_Fee_MainFunction
 **********************************************************************************************************************/
/*! \brief      This function is a cyclic function. It will Write data, Read Data, Invalidate Block, Erase Block,
 *				Copy blocks, Erase Sectors. 
 *  \param[in]  none
 *  \param[out] none
 *  \return     None 
 *  \context    Function could be called from task level
 *  \note       TI FEE API.
 **********************************************************************************************************************/
/* SourceId : HL_Fee_SourceId_4 */
/* DesignId : HL_FEE_DesignId_28 */
/* Requirements : HL_FEE_SR9, HL_FEE_SR10, HL_FEE_SR23, HL_FEE_SR68, HL_FEE_SR69, HL_FEE_SR70 */
/*SAFETYMCUSW 61 D MR:8.10,8.11 <APPROVED> "Reason -  This API will be called by application."*/
 void TI_Fee_MainFunction(void)
{
	uint8 u8EEPIndex = 0U;
	uint8 u8WriteCount=0U;	
	uint8 * DataBufferPtr;
	boolean bVSError=FALSE;		
	static uint8 Fee_u8WriteCounter=0U;
	#if(TI_FEE_FLASH_ERROR_CORRECTION_HANDLING == TI_Fee_Fix)
	TI_Fee_AddressType oBlockAddress=0U;
	uint32 **ppu32ReadHeader=0U;
	uint32 u32BlockAddressTemp=0U;	
	#endif
	uint32 u32WriteAddressTemp=0U;
	uint8 * u8WriteDataptrTemp=0U;
	uint8 u8loopindex = 0U;

	TI_Fee_bIsMainFunctionCalled = TRUE;
	while(u8EEPIndex<TI_FEE_NUMBER_OF_EEPS)
	{
		/* Write the remaining of the VS header */
		/*SAFETYMCUSW 114 S MR:21.1 <APPROVED> "Reason -  Eventhough expression is not boolean, we check for the 
		  function return value."*/
		/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/	
		/*SAFETYMCUSW 114 S MR:12.6,13.2 <APPROVED> "Reason -  LDRA does not understand macro 
		  FAPI_CHECK_FSM_READY_BUSY."*/
		/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  ( pFapi_FmcRegistersType ) ( 0xFFF87000U ) ) casting 
		 is done in F021 library.*/ 		  
		if((TRUE == TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWriteVSHeader) &&
			(FAPI_CHECK_FSM_READY_BUSY == Fapi_Status_FsmReady))
		{
			u32WriteAddressTemp = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress;			
			/*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Reason -  Null pointer check is done for 
			  TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8Data."*/
			u8WriteDataptrTemp = TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8Data;			
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress  =  TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress + 8U;
			/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/									 
			/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8Data  =  (uint8 *)(&TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorStateValue[2]); 	
			(void)TI_FeeInternal_WriteDataF021((boolean)FALSE,(uint16)8U, u8EEPIndex);	
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWriteVSHeader = FALSE;
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress = u32WriteAddressTemp;			
			/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/									 
			/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/									 
			/*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Reason -  Null pointer check is done for 
			  TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8Data."*/
			TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8Data = (uint8 *)u8WriteDataptrTemp;			
		}
		
		/* Check if the FEE is in Busy State, else handle the internal operations */		
		if((TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.WriteAsync==1U) 	  || 
		   (TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.InvalidateBlock==1U) ||
		   (TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.EraseImmediate==1U)  ||
		   (TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Read==1U)		
		  )
		{
			/* check if the Flash State machine is Busy */
			/*SAFETYMCUSW 114 S MR:21.1 <APPROVED> "Reason -  Eventhough expression is not boolean, 
			  we check for the function return value."*/
			/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/	
			/*SAFETYMCUSW 114 S MR:12.6,13.2 <APPROVED> "Reason -  LDRA does not understand macro 
		      FAPI_CHECK_FSM_READY_BUSY."*/
			/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  ( pFapi_FmcRegistersType ) ( 0xFFF87000U ) ) casting 
		      is done in F021 library.*/ 		  
			if(FAPI_CHECK_FSM_READY_BUSY == Fapi_Status_FsmReady)
			{
				/* program, erase, or suspend operation is not being processed*/
				/* check the current job in progress & execute it */
				if(TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.WriteAsync==1U)
				{					
					if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_bFindNextVirtualSector == TRUE)
					{
						/* Find the next Virtual Sector to write to */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8CopyVirtualSector = TI_FeeInternal_FindNextVirtualSector(u8EEPIndex);
							
						/* Configure it as a Copy Virtual Sector */
						if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8CopyVirtualSector!=0U) && 
						   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error == Error_Nil))
						{
							/* Immediately Update the VS state to COPY */
							TI_FeeInternal_WriteVirtualSectorHeader(
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8CopyVirtualSector,
							 VsState_Copy, u8EEPIndex);														
						}						
						else
						{
							/* If no Virtual Sector found, update an Error. Global error is already updated. */
							bVSError=TRUE;	
							/* Writing is not possible since no VS is found free */							
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult= JOB_FAILED;
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = IDLE;
							TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.WriteAsync = 0U;
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_bFindNextVirtualSector = FALSE;
							#if(STD_OFF == TI_FEE_POLLING_MODE)
							TI_FEE_NVM_JOB_END_NOTIFICATION();
							#endif
						}
						if(bVSError==FALSE)
						{
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyVirtualSectorAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress;
							/* Next data write happens after VS Header */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextCopyVSwriteaddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress+TI_FEE_VIRTUAL_SECTOR_OVERHEAD+16U;
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress  =  TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextCopyVSwriteaddress;
							/* Clear the block copy status of all blocks. All blocks need to be copied in background */
							/*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/
							TI_FeeInternal_SetClearCopyBlockState(u8EEPIndex,(boolean)FALSE);
							/* update the block copy status for current block to copied. */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8BlockCopyStatus[TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16ArrayIndex]= 0x01U;
							/* Update Next write address */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextCopyVSwriteaddress;									
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress = TI_FeeInternal_AlignAddressForECC(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress);																	
							/* Update the status to COPY. This will enable copying of all blocks from Active VS to Copy VS in background*/
							TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Copy = 1U;									
						
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
							  TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize-=TI_FEE_BLOCK_OVERHEAD;						
							}
							else
							{
							
							}						
							/* Update block offset array */							
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_au16BlockOffset[TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16ArrayIndex]=(uint16)(((TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress) - (TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyVirtualSectorAddress))& 0x0000FFFFU);
							/* update address for current block. This will be used in fee_main for writing block header */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentBlockHeader = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress;
							/* Initialize the write address for block header */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress  =  TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress;	
							/* Wait till FSM is ready to accept new write */
							(void)TI_FeeInternal_PollFlashStatus();
							/* Mark the Block header to indicate start of programming to the Block*/						
							TI_FeeInternal_StartProgramBlock(u8EEPIndex);
							DataBufferPtr = TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8DataStart;
							/* initialize Write */
							/*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Reason -  Null pointer check is done for 
							  TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8DataStart."*/		
							TI_FeeInternal_WriteInitialize(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress,DataBufferPtr, u8EEPIndex);													
							/* Make the write flag as TRUE. This flag will be used in main function to write data */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWriteData = TRUE;
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_bFindNextVirtualSector = FALSE;
							/* Make the partial block status write flag as TRUE to indicate partial block write needs to happen.*/
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWritePartialBlockHeader	= TRUE;
						}	
					}
					/*SAFETYMCUSW 28 D <APPROVED> "Reason -  Fee_bWriteStartProgram is made FALSE after writing */  
					while(TRUE == TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWriteStartProgram)
					{						
						/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/	
						/*SAFETYMCUSW 114 S MR:12.6,13.2 <APPROVED> "Reason -  LDRA does not understand macro 
		                 FAPI_CHECK_FSM_READY_BUSY."*/
						/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  ( pFapi_FmcRegistersType ) ( 0xFFF87000U ) ) casting 
		                  is done in F021 library.*/ 		  
						if(FAPI_CHECK_FSM_READY_BUSY == Fapi_Status_FsmReady)
						{
							/* Mark the Block header to indicate start of programming to the Block*/						
							TI_FeeInternal_StartProgramBlock(u8EEPIndex);						
							/* Make the block status write flag as FALSE to indicate status write complete.*/
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWriteStartProgram = FALSE;
							/* Make the partial block status write flag as TRUE to indicate partial block write needs to happen.*/
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWritePartialBlockHeader	= TRUE;	
						}
					}					
					/*SAFETYMCUSW 28 D <APPROVED> "Reason -  Fee_bWritePartialBlockHeader is made FALSE after writing */  
					while(TRUE == TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWritePartialBlockHeader)
					{
						/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/	
						/*SAFETYMCUSW 114 S MR:12.6,13.2 <APPROVED> "Reason -  LDRA does not understand macro 
		                  FAPI_CHECK_FSM_READY_BUSY."*/
						/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  ( pFapi_FmcRegistersType ) ( 0xFFF87000U ) ) casting 
		                  is done in F021 library.*/ 		    
						if(FAPI_CHECK_FSM_READY_BUSY == Fapi_Status_FsmReady)
						{
							/* Write Block number, Block Size and Block counter into Block Header */
							TI_FeeInternal_WriteBlockHeader((boolean)FALSE,u8EEPIndex,
							              (uint16)TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSizeinBlockHeader,
							              (uint16)TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockNumberinBlockHeader);
							/* Initialize Write */
							TI_FeeInternal_WriteInitialize(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oFlashNextAddress,
							                       TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8DataStart, u8EEPIndex);
							/* Make the partial block status write flag as FALSE to indicate status write complete.*/
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWritePartialBlockHeader	= FALSE;	
						}	
					}										
					/* Write the data of the Block */
					while((u8loopindex<TI_FEE_NUMBER_OF_EIGHTBYTEWRITES) && 
					      (TRUE == TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWriteData))
					{						
						/* Write job in progress */
						/* Write the next data to the Block */
						/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/	
						/*SAFETYMCUSW 114 S MR:12.6,13.2 <APPROVED> "Reason -  LDRA does not understand macro 
		                  FAPI_CHECK_FSM_READY_BUSY."*/
						/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  ( pFapi_FmcRegistersType ) ( 0xFFF87000U ) ) casting 
		                  is done in F021 library.*/ 		    
						if(FAPI_CHECK_FSM_READY_BUSY == Fapi_Status_FsmReady)
						{
							/*SAFETYMCUSW 91 D MR:16.10 <APPROVED> "Reason - Return value is used in following code."*/
							u8WriteCount=TI_FeeInternal_WriteDataF021(FALSE,
							             (uint16)TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize, u8EEPIndex);
							/* To avoid MISRA warning */
							u8WriteCount=u8WriteCount;				
							if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize <= 0x08U)
							{
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize = 0x0U;
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWriteData=FALSE;
								break;
							}  
							else
							{
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize-=u8WriteCount;							
							}
							u8loopindex++;
						}												
					}						
					/* After writing the block, mark the block as valid */
					while((TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize==0U)&&
					       (TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWriteData==FALSE))
					{
						/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/	
						/*SAFETYMCUSW 114 S MR:12.6,13.2 <APPROVED> "Reason -  LDRA does not understand macro 
		                  FAPI_CHECK_FSM_READY_BUSY."*/
						/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  ( pFapi_FmcRegistersType ) ( 0xFFF87000U ) ) casting 
		                  is done in F021 library.*/ 		    
						if(FAPI_CHECK_FSM_READY_BUSY == Fapi_Status_FsmReady)
						{
							/* Mark Current Block Header as VALID */
							if(0U == TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8WriteCount)
							{
								/* First update Checksum and Address of previous block */
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentBlockHeader + 8U;
								/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
								/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8Data=(uint8 *)&TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[2];
								TI_FeeInternal_WriteBlockHeader((boolean)TRUE,u8EEPIndex,
								     (uint16)TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSizeinBlockHeader,
								     (uint16)TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockNumberinBlockHeader);
							}
							else
							{
								/* Update the block status as Valid */
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_oWriteAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentBlockHeader;
								/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
								/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8Data=(uint8 *)&TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32BlockHeader[0];
								TI_FeeInternal_WriteBlockHeader((boolean)TRUE,u8EEPIndex,
								        (uint16)TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSizeinBlockHeader,
								    	(uint16)TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockNumberinBlockHeader);
								break;
							}							 							
						}	
					}
					/* Mark the previous block as invalid */
					/*SAFETYMCUSW 28 D <APPROVED> "Reason -  Fee_bWriteBlockHeader is made FALSE after writing */  
					while(TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWriteBlockHeader==TRUE)
					{
						/*SAFETYMCUSW 184 S LDRA adding spaces causes this rule to fail."*/	
						/*SAFETYMCUSW 114 S MR:12.6,13.2 <APPROVED> "Reason -  LDRA does not understand macro 
		                  FAPI_CHECK_FSM_READY_BUSY."*/
						/*SAFETYMCUSW 440 S MR:11.3 <APPROVED> "Reason -  ( pFapi_FmcRegistersType ) ( 0xFFF87000U ) ) casting 
		                  is done in F021 library.*/ 		    
						if(FAPI_CHECK_FSM_READY_BUSY == Fapi_Status_FsmReady)
						{
							if(TI_Fee_GlobalVariables[u8EEPIndex].bWriteFirstTime!=TRUE)
							{
								/* Previous block shd be configured as notvalid */
								TI_FeeInternal_WritePreviousBlockHeader((boolean)TRUE, u8EEPIndex);						
							}
							else
							{
								TI_Fee_GlobalVariables[u8EEPIndex].bWriteFirstTime = FALSE;
								TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.WriteAsync = 0U;							
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWriteBlockHeader = FALSE;							
								/* If copy was initiated by this write job, do not return the job status as completed*/
								if(TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Copy == 1U)
								{
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult=JOB_PENDING;
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = BUSY_INTERNAL;
								}
								else
								{									
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult=JOB_OK;
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = IDLE;
									#if(STD_OFF == TI_FEE_POLLING_MODE)
									TI_FEE_NVM_JOB_END_NOTIFICATION();
									#endif
								}
							}
						}	
					}	
				}
				else if((TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.InvalidateBlock==1U) ||
				        (TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.EraseImmediate==1U))
				{					
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8WriteCount = 0U;					
					TI_FeeInternal_WritePreviousBlockHeader(FALSE, u8EEPIndex);
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentBlockHeader = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentStartAddress;
					TI_Fee_GlobalVariables[u8EEPIndex].bWriteFirstTime=FALSE;		
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_au16BlockOffset[TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16ArrayIndex]= 0xABCDU;										
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8BlockCopyStatus[TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16ArrayIndex]=2U;
				}
				else if (TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Read==1U)
				{					
					while(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize>0U)
					{						
						/*SAFETYMCUSW 45 D MR:21.1 <APPROVED> "Reason -  Null pointer check is done in ti_fee_read."*/
						*TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8ReadDataBuffer=*TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8ReadAddress;								
						
						/*For every eight bytes of data, there is 1 byte of ECC. We need to check for errors only
                          during first byte read of eight bytes */
						if(8U==Fee_u8WriteCounter) 	
						{	
							Fee_u8WriteCounter=0U;	
						}	
						#if(TI_FEE_FLASH_ERROR_CORRECTION_HANDLING == TI_Fee_Fix)	
						/* If there is corectable error, continue reading the data, initiate write to new location */
						if((Fee_bSingleBitError == TRUE) && (0U==Fee_u8WriteCounter))						
						{
							Device_FlashDevice.Device_BankInfo[0].Device_ControlRegister->EeCorErrAdd.EE_COR_ERR_ADD_BITS.COR_ERR_ADD;
							TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.SingleBitError = 1U;
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8BlockCopyStatus[TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16ArrayIndex]=3U;	
							Fee_bSingleBitError = FALSE;
						}									
						if((Fee_bDoubleBitError == TRUE) && (0U==Fee_u8WriteCounter))
						{
							oBlockAddress = TI_FeeInternal_GetCurrentBlockAddress(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16ArrayIndex,
							                      TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16DataSetIndex,u8EEPIndex);
							Device_FlashDevice.Device_BankInfo[0].Device_ControlRegister->EeUncErrAdd.EE_UNC_ERR_ADD_BITS.UNC_ERR_ADD;								
							/* If there is uncorectable error, read the data from previous block */	
							/* Address of previous block is present after block status.*/		
							/* If block header is 24 bytes(0-23), 8-11 bytes are previous block address */
							oBlockAddress += (((TI_FEE_BLOCK_OVERHEAD >> 2U)-4U) << 2U);	
							/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
							ppu32ReadHeader = (uint32 **)&oBlockAddress;
							u32BlockAddressTemp = **ppu32ReadHeader;
							if((u32BlockAddressTemp<TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorStartAddress) || 
							   (u32BlockAddressTemp>TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorEndAddress))
							{	
								/* Previous Block Address is not valid. Stop reading data */
								TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Read=0U;																
								/* Set the module state to IDLE */
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState=IDLE;
								#if(STD_OFF == TI_FEE_POLLING_MODE)
								TI_FEE_NVM_JOB_ERROR_NOTIFICATION();
								#endif
							}
							else 
							{								
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8ReadAddress = (uint8 *)u32BlockAddressTemp;										
								*TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8ReadDataBuffer=*TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8ReadAddress;								
							}														
						}						
						#endif	
						
						Fee_u8WriteCounter++;
						
						/*SAFETYMCUSW 567 S MR:17.1,17.4 <APPROVED> "Reason -  Pointer Arithmatic is necessary here."*/
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8ReadDataBuffer++;
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8ReadAddress++;
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize--;

						if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize > 0U)
						{
							#if(TI_FEE_CHECK_BANK7_ACCESS == STD_ON)
							if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8ReadAddress > (uint8 *)Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[0].Device_SectorStartAddress) &&
									#if (TI_FEE_GENERATE_DEVICEANDVIRTUALSECTORSTRUC == STD_ON)
									(TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8ReadAddress < (uint8 *) Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[TI_Fee_MaxSectors-1U].Device_SectorStartAddress+
									Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[TI_Fee_MaxSectors-1U].Device_SectorLength))
									#else
									(TI_Fee_GlobalVariables[u8EEPIndex].Fee_pu8ReadAddress < (uint8 *)Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[DEVICE_BANK_MAX_NUMBER_OF_SECTORS-1U].Device_SectorStartAddress+
									Device_FlashDevice.Device_BankInfo[0].Device_SectorInfo[DEVICE_BANK_MAX_NUMBER_OF_SECTORS-1U].Device_SectorLength))
									#endif
							{
								/* MISRA C Compliance */
							}
							else
							{
								/* Address is out of bank7 range. Reset block size so that no furthur read's happen */
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize = 0U;
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_FAILED;
							}
							#endif
						}
					}
					if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize == 0U)
					{
						#if(TI_FEE_FLASH_ERROR_CORRECTION_HANDLING == TI_Fee_Fix)
						if((Fee_bDoubleBitError == TRUE))
						{
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult=BLOCK_INCONSISTENT;
							Fee_bDoubleBitError = FALSE;	
						}
						/* Finished reading */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult=JOB_OK;	
						#else
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
						#endif							
						TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Read=0U;
						Fee_u8WriteCounter = 0U;
						/* Set the module state to IDLE since the Read command has been completed */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState=IDLE;
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
					}
					TI_Fee_GlobalVariables[u8EEPIndex].bWriteFirstTime=FALSE;
				}
				else
				{					
					TI_Fee_GlobalVariables[u8EEPIndex].bWriteFirstTime=FALSE;					
					#if(STD_OFF == TI_FEE_POLLING_MODE)
					TI_FEE_NVM_JOB_END_NOTIFICATION();
					#endif
					if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult==JOB_PENDING)
					{
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult=JOB_OK;
					}
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState=IDLE;
				}
			}			
		}		
		else if((TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.WriteAsync==0U) 	   && 
		        (TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.InvalidateBlock==0U) &&
		        (TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.EraseImmediate==0U)  &&
		        (TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Read==0U)			   &&
				(TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.ReadSync==0U)		   &&
				(TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.WriteSync==0U)		
		  )
		{
			/* program, erase, or suspend operation is being processed*/
			/* Perform the internal operations like copying data blocks, erasing VS */
			(void)TI_FeeInternal_FeeManager(u8EEPIndex);	
			TI_Fee_GlobalVariables[u8EEPIndex].bWriteFirstTime=FALSE;	
		}
		else
		{
			/* MISRA C Compliance */
		}	
		u8EEPIndex++;
	}	
	#if(TI_FEE_NUMBER_OF_EEPS==2U)
	TI_Fee_oStatusWord_Global.Fee_u16StatusWord = ((TI_Fee_oStatusWord[0].Fee_u16StatusWord) |
			 									   (TI_Fee_oStatusWord[1].Fee_u16StatusWord));
	#endif	
	TI_Fee_bIsMainFunctionCalled = FALSE;
}
/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_STOP_SEC_CODE
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"
/**********************************************************************************************************************
 *  END OF FILE: ti_fee_main.c
 *********************************************************************************************************************/
