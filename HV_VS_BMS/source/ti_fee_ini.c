/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  ti_fee_ini.c
 *      Project:  Tms570_TIFEEDriver
 *       Module:  TIFEEDriver
 *    Generator:  None
 *
 *  Description:  This file implements the TI FEE Api TI_Fee_Init.
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
 * 00.01.06		  11Mar2013	   Vishwanath Reddy     SDOCM00099152    Added feature : copying of unconfigured blocks. 
 * 00.01.07		  15Mar2013	   Vishwanath Reddy     SDOCM00099152    Added feature : Number of 8 bytes writes, fixed 
																	 issue with copy blocks. 
 * 00.01.08		  05Apr2013	   Vishwanath Reddy     SDOCM00099152    Added feature : CRC check for unconfigured blocks,
																	 Main function modified to complete writes as fast 
																	 as possible, Added Non polling mode support.															 
 * 00.01.09		  19Apr2013	   Vishwanath Reddy     SDOCM00099152    Warning removal, Added feature comparision of data
																	 during write.		
 * 00.01.10       11Jun2013	   Vishwanath Reddy     SDOCM00101845	 Updated version info.
                                                                     Enabled SECDED.                
                                                                     Updated logic to know if erase was started in 
                                                                     previous cycle.
                                                                     Moved block writing by 16 bytes after VS Header.
 * 00.01.11       05Jul2013	   Vishwanath Reddy     SDOCM00101643	 Updated version information.
 * 01.12.00		  13Dec2013    Vishwanath Reddy     SDOCM00105412    Traceability tags added. 
 *                                                                   version info updated. MISRA C fixes. 
 *                                                                   Version Info corected. 
 * 01.13.00       30Dec2013	   Vishwanath Reddy     0000000000000	 Undated version info for SDOCM00107976
 *                                                                   and SDOCM00105795.     
 * 01.13.01       19May2014	   Vishwanath Reddy     0000000000000	 Updated version info for SDOCM00107913
 *                                                                   and SDOCM00107622.     
 * 01.13.02       12Jun2014	   Vishwanath Reddy     0000000000000	 Updated version info for SDOCM00108238
 * 01.14.00		  26Mar2014    Vishwanath Reddy 	                 Update version info for SDOCM00107161.
 * 01.15.00		  06Jun2014    Vishwanath Reddy 	                 Support for TMS570LCx.
 * 01.16.00		  15Jul2014    Vishwanath Reddy 	SDOCM00112141    Remove  MISRA warnings.
 * 01.16.01		  12Sep2014	   Vishwanath Reddy     SDOCM00112930    Updated version information.
 *                                                                   New global variable TI_Fee_bEraseSuspended added.  
 * 01.17.00		  15Oct2014    Vishwanath Reddy     SDOCM00113379    RAM Optimization changes.
 * 01.17.01		  30Oct2014    Vishwanath Reddy     SDOCM00113536    Support for TMS570LS07xx,TMS570LS09xx,
 *                                                                   TMS570LS05xx, RM44Lx.
 * 01.17.02		  26Dec2014    Vishwanath Reddy     SDOCM00114102    FLEE Errata Fix.
 *                                                  SDOCM00114104    Change ALL 1's OK check condition.
 *                                                  SDOCM00114423	 Add new variable TI_Fee_MaxSectors and 
 *                                                                   changes for unification of Archer/Champion.
 * 01.18.00		  12Oct2015    Vishwanath Reddy     SDOCM00119455    Update version history. 
 * 01.18.01		  17Nov2015    Vishwanath Reddy     SDOCM00120161    Update version history.
 * 01.18.02		  05Feb2016    Vishwanath Reddy     SDOCM00121158    Update version history.
 * 01.18.03       30June2016   Vishwanath Reddy     SDOCM00122388    Update patch version TI_FEE_SW_PATCH_VERSION.
 *                                                                   Changes related to supporting of configuring
 *                                                                   data set numbers instead of block numbers.
 *                                                                   TI_FEE_FLASH_CRC_ENABLE is renamed to 
 *                                                                   TI_FEE_FLASH_CHECKSUM_ENABLE.    
 * 01.19.00       08Augu2016   Vishwanath Reddy     SDOCM00122592    Update patch version TI_FEE_MINOR_VERSION.
 * 01.19.01       12Augu2016   Vishwanath Reddy     SDOCM00122543    Update patch version TI_FEE_MINOR_VERSION.
 * 01.19.02       25Janu2017   Vishwanath Reddy     SDOCM00122832    Update patch version TI_FEE_MINOR_VERSION.
 * 01.19.03       15May2017    Prathap Srinivasan   SDOCM00122917    Removed Block Size interpretation for Blocks that 
 *                                                                   are not Valid, Invalid or Empty.
 * 01.19.04		  05Dec2017    Prathap Srinivasan   HERCULES_SW-5082 Update version history.
 *********************************************************************************************************************/
/* Total Number of Requirements : FEE : 104 */ 

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
 *  VERSION CHECK
 *********************************************************************************************************************/
/* SourceId : HL_Fee_SourceId_5 */
/* Requirements : HL_FEE_SR11 */
 #if (TI_FEE_MAJOR_VERSION != 3U)
    #error TI_FEE_Cfg.c: TI_FEE_MAJOR_VERSION of TI_FEE.h is incompatible.
#endif /* FEE_SW_MAJOR_VERSION */
#if (TI_FEE_MINOR_VERSION != 0U)
    #error TI_FEE_Cfg.c: TI_FEE_MINOR_VERSION of TI_FEE.h is incompatible.
#endif /* FEE_SW_MINOR_VERSION */
#if (TI_FEE_PATCH_VERSION != 2U)
    #error TI_FEE_Cfg.c: TI_FEE_PATCH_VERSION of TI_FEE.h is incompatible.
#endif /* FEE_SW_PATCH_VERSION */
#if (TI_FEE_SW_MAJOR_VERSION != 1U)
    #error TI_FEE_Cfg.c: TI_FEE_SW_MAJOR_VERSION of TI_FEE.h is incompatible.
#endif /* FEE_SW_MAJOR_VERSION */
#if (TI_FEE_SW_MINOR_VERSION != 19U)
    #error TI_FEE_Cfg.c: TI_FEE_SW_MINOR_VERSION of TI_FEE.h is incompatible.
#endif /* FEE_SW_MINOR_VERSION */
#if (TI_FEE_SW_PATCH_VERSION != 4U)
    #error TI_FEE_Cfg.c: TI_FEE_SW_PATCH_VERSION of TI_FEE.h is incompatible.
#endif /* FEE_SW_PATCH_VERSION */

/**********************************************************************************************************************
 *  Configuration CHECK
 *********************************************************************************************************************/
#if ((TI_FEE_NUMBER_OF_EEPS > 2U))
	#error ti_fee_ini.c: Number of EEP's can't be more than 2.Check configuration file.
#endif	
#if ((TI_FEE_DATASELECT_BITS > 8U))
	#error ti_fee_ini.c: Data selection bits cannot be more than 8.Check configuration file.
#endif	
	
/**********************************************************************************************************************
 *  Global Definitions
 *********************************************************************************************************************/
/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_START_SEC_VAR_INIT_UNSPECIFIED  
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"

TI_Fee_GlobalVarsType TI_Fee_GlobalVariables[TI_FEE_NUMBER_OF_EEPS];
#if (TI_FEE_GENERATE_DEVICEANDVIRTUALSECTORSTRUC == STD_ON)
Device_FlashType Device_FlashDevice;
Fee_VirtualSectorConfigType Fee_VirtualSectorConfiguration[TI_FEE_NUMBER_OF_VIRTUAL_SECTORS];
uint8 TI_Fee_MaxSectors;
#endif
uint8 TI_Fee_u8DataSets;
#if(TI_FEE_FLASH_CHECKSUM_ENABLE == STD_ON)						
uint32 TI_Fee_u32FletcherChecksum;
#endif
uint32 TI_Fee_u32BlockEraseCount;
uint8  TI_Fee_u8DeviceIndex;
uint32 TI_Fee_u32ActCpyVS;
uint8  TI_Fee_u8ErrEraseVS;
boolean TI_Fee_bEraseSuspended;
boolean TI_Fee_bIsMainFunctionCalled;
TI_Fee_StatusWordType_UN TI_Fee_oStatusWord[TI_FEE_NUMBER_OF_EEPS];
Fapi_FlashStatusWordType TI_FlashStatusWord;
#if (TI_FEE_NUMBER_OF_UNCONFIGUREDBLOCKSTOCOPY != 0U)
uint16 TI_Fee_u16NumberOfUnconfiguredBlocks[TI_FEE_NUMBER_OF_EEPS];
#endif
#if(TI_FEE_NUMBER_OF_EEPS==2U)
TI_Fee_StatusWordType_UN TI_Fee_oStatusWord_Global;
#endif
boolean TI_Fee_FapiInitCalled; 

#define	TI_FEE_GET_DEVICE_TYPE	(*(volatile uint32*) (0xFFF87400U))

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_STOP_SEC_VAR_INIT_UNSPECIFIED  
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_START_SEC_CODE
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"

/**********************************************************************************************************************
 *  TI_Fee_Init
 *********************************************************************************************************************/
/*! \brief      This function is used to initialize the TI Fee module.
 *				It determines which Virtual Sector to use, sets up the Flash state machine.
 *  \param[in]  none
 *  \param[out] none
 *  \return     none
 *  \return     none
 *  \context    Function could be called from task level
 *  \note       TI FEE API.
 *********************************************************************************************************************/
/* SourceId : HL_Fee_SourceId_3 */
/* DesignId : HL_FEE_DesignId_16 */
/* Requirements : HL_FEE_SR5, HL_FEE_SR7, HL_FEE_SR8, HL_FEE_SR16, HL_FEE_SR17, HL_FEE_SR99 */
void TI_Fee_Init(void)
{
	uint32 au32VirtualSectorHeader[6];
	uint32 au32VirtualSectorAddress[6];
	uint32 u32VirtualSectorStartAddress = 0U;
	uint32 u32VirtualSectorEndAddress=0U;
	uint16 u16Index=0U;
	uint16 u16Index1=0U;
	Fapi_FlashSectorType oSectorStart,oSectorEnd;
	uint32 **ppu32ReadHeader = 0U;	
	TI_Fee_AddressType oCopyVirtualSectorStartAddress = 0U;
	uint8 u8EEPIndex=0U;
	boolean bActiveVSScanned[TI_FEE_NUMBER_OF_EEPS];
	boolean bFoundActiveVS[TI_FEE_NUMBER_OF_EEPS];	
	boolean bFoundCopyVS[TI_FEE_NUMBER_OF_EEPS];	
	boolean bFoundReadyForEraseVS[TI_FEE_NUMBER_OF_EEPS];
	boolean	bFoundActiveVirtualSector[TI_FEE_NUMBER_OF_EEPS];
	boolean bFoundReadyforEraseVirtualSector[TI_FEE_NUMBER_OF_EEPS];
	boolean bDoNotIncrement=FALSE;
	TI_Fee_u32BlockEraseCount = 0xFFFFFFFFU;
	#if(TI_FEE_FLASH_CHECKSUM_ENABLE == STD_ON)						
	TI_Fee_u32FletcherChecksum = 0xFFFFFFFFU;
	#endif
	TI_Fee_bEraseSuspended = FALSE;
	TI_Fee_bIsMainFunctionCalled = FALSE;
	
	#if (TI_FEE_GENERATE_DEVICEANDVIRTUALSECTORSTRUC == STD_ON)	
	if((((TI_FEE_GET_DEVICE_TYPE) & 0xFFF00000U) >> 20U) > 73U)
	{	
		TI_FeeInternal_PopulateStructures(CHAMPION);
		TI_Fee_MaxSectors = 4U;
	}	
	else
	{		
		TI_FeeInternal_PopulateStructures(ARCHER);
		TI_Fee_MaxSectors = 16U;		
	}	
	#endif

	while(u8EEPIndex<TI_FEE_NUMBER_OF_EEPS)
	{	
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress=0xFFFFFFFFU;		
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockIndex=0U;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockCopyIndex=0xFFFFU;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16DataSetIndex=0U;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16BlockSize=0U;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector=0U;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8CopyVirtualSector=0U;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState=UNINIT;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentStartAddress=0U;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentBlockHeader=0U;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorEndAddress=0U;		
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_bInvalidWriteBit=FALSE;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWriteData=FALSE;		
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8WriteCount=0U;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8WriteCopyVSHeader=0U;		
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWriteBlockHeader=FALSE;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16CopyBlockNumber=0U;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error=Error_Nil;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus=TI_FEE_OK;				
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32InternalEraseQueue=0U;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8InternalVirtualSectorEnd=0U;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8InternalVirtualSectorStart=0U;
		TI_Fee_GlobalVariables[u8EEPIndex].bWriteFirstTime=FALSE;
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_bFindNextVirtualSector=FALSE;		
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWriteVSHeader = FALSE;	
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWriteStartProgram = FALSE;	
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_bWritePartialBlockHeader	= FALSE;	
		TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCurrentStartAddress = 0xFFFFFFFFU;
		
		bActiveVSScanned[u8EEPIndex] = FALSE;
		bFoundActiveVS[u8EEPIndex] = FALSE;
		bFoundCopyVS[u8EEPIndex] = FALSE;
		bFoundReadyForEraseVS[u8EEPIndex] = FALSE;
		bFoundActiveVirtualSector[u8EEPIndex] = FALSE;
		bFoundReadyforEraseVirtualSector[u8EEPIndex] = FALSE;
		TI_Fee_FapiInitCalled = FALSE;
		
		if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus == TI_FEE_OK) && 
		   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error == Error_Nil))
		{
			/* Determine how many DataSets are being used */
			/* Update total number of data sets in to global variable. If TI_FEE_DATASELECT_BITS=3, total data sets per block would be 2 power 3 = 8 */
			TI_Fee_u8DataSets = (1U<<TI_FEE_DATASELECT_BITS)-1U;

			if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error == Error_Nil)
			{
				/* Initialize the Status word */
				TI_Fee_oStatusWord[u8EEPIndex].Fee_u16StatusWord=0U;
				
				/* Initialize the copy status of all the Blocks */
				/* Initialize the block offset address of all the Blocks */
				for(u16Index=0U;u16Index<TI_FEE_TOTAL_BLOCKS_DATASETS;u16Index++)	
				{					
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8BlockCopyStatus[u16Index]=2U;
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_au16BlockOffset[u16Index]= 0x0BADU;					
				}
				#if (TI_FEE_NUMBER_OF_UNCONFIGUREDBLOCKSTOCOPY != 0U)
				for(u16Index=0U;u16Index<TI_FEE_NUMBER_OF_UNCONFIGUREDBLOCKSTOCOPY;u16Index++)	
				{					
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_au16UnConfiguredBlockAddress[u16Index] = 0x0BADU;
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8UnConfiguredBlockCopyStatus[u16Index]= 2U;																
				}
				#endif
				/* Find the Active Virtual Sector */
				/* Read the virtual sector header and find if it matches 0x000000000000FFFF for active */
				/* If Active, calculate the next flash address */
				/* If not, parse the next Virutal Sector */
				/* Else create a new active Virtual Sector header */
				if(0U == u8EEPIndex)
				{
					u16Index=0U;
					u16Index1= (uint16)(TI_FEE_NUMBER_OF_VIRTUAL_SECTORS - TI_FEE_NUMBER_OF_VIRTUAL_SECTORS_EEP1);	
				}
				else
				{
					u16Index = TI_FEE_NUMBER_OF_VIRTUAL_SECTORS_EEP1;
					u16Index1 = TI_FEE_NUMBER_OF_VIRTUAL_SECTORS;
				}	
				/* Enable Reading of all 1's as OK. Else device may generate errors. */
				#ifdef _L2FMC
				Device_FlashDevice.Device_BankInfo[FEE_BANK].Device_ControlRegister->FedAcCtrl1.FEDACCTRL1_BITS.EOCV = 0x01U;
				#else
				/* Enable Reading of all 1's as OK. */
				Device_FlashDevice.Device_BankInfo[FEE_BANK].Device_ControlRegister->EeCtrl1.EE_CTRL1_BITS.EE_ALL1_OK = 0x01U;
				/* Enable SECDED */
				Device_FlashDevice.Device_BankInfo[FEE_BANK].Device_ControlRegister->EeCtrl1.EE_CTRL1_BITS.EE_EDACEN = 0xAU;
				/* Enable Single bit error correction */
				Device_FlashDevice.Device_BankInfo[FEE_BANK].Device_ControlRegister->EeCtrl1.EE_CTRL1_BITS.EE_EDACMODE = 0xAU;						
				#endif

				/*SAFETYMCUSW 28 D <APPROVED> "Reason - u16Index1 is not more than TI_FEE_NUMBER_OF_VIRTUAL_SECTORS."*/
				while(u16Index < u16Index1)				
				{
					/* Initialize the state of all the Virtual Sectors */	
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16Index]=0U;	
					
					u32VirtualSectorStartAddress=0xFFFFFFFFU;									
					oSectorStart=Fee_VirtualSectorConfiguration[u16Index].FeeStartSector;										
					/* Get the starting address of the VS */
					/*SAFETYMCUSW 91 D 0 MR:16.10 <APPROVED> "Reason -  Return value is used in next lines if there is no error."*/
					u32VirtualSectorStartAddress = TI_FeeInternal_GetVirtualSectorParameter(oSectorStart,(uint16)FEE_BANK,(boolean)TRUE,u8EEPIndex);                          
					/* To avoid MISRA warning */	
					u32VirtualSectorStartAddress=u32VirtualSectorStartAddress;
					if(Error_Nil==TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error)
					{						
						if((u32VirtualSectorStartAddress)!=0xFFFFFFFFU)
						{
							/* Read this address and find whether it is Active or not */
							au32VirtualSectorAddress[0]=u32VirtualSectorStartAddress;
							au32VirtualSectorAddress[1]=u32VirtualSectorStartAddress+4U;
							au32VirtualSectorAddress[2]=u32VirtualSectorStartAddress+8U;
							au32VirtualSectorAddress[3]=u32VirtualSectorStartAddress+12U;
							au32VirtualSectorAddress[4]=u32VirtualSectorStartAddress+16U;
							au32VirtualSectorAddress[5]=u32VirtualSectorStartAddress+20U;
							/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
							/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
							ppu32ReadHeader=(uint32 **)&au32VirtualSectorAddress[0];
							au32VirtualSectorHeader[0] = **ppu32ReadHeader;
							/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
							/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
							ppu32ReadHeader=(uint32 **)&au32VirtualSectorAddress[1];
							au32VirtualSectorHeader[1] = **ppu32ReadHeader;
							/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
							/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
							ppu32ReadHeader=(uint32 **)&au32VirtualSectorAddress[2];
							au32VirtualSectorHeader[2] = **ppu32ReadHeader;
							/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
							/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
							ppu32ReadHeader=(uint32 **)&au32VirtualSectorAddress[3];
							au32VirtualSectorHeader[3] = **ppu32ReadHeader;
							/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
							/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
							ppu32ReadHeader=(uint32 **)&au32VirtualSectorAddress[4];
							au32VirtualSectorHeader[4] = **ppu32ReadHeader;
							/*SAFETYMCUSW 94 S MR:11.1,11.2,11.4 <APPROVED> "Reason -  Casting is required here."*/
							/*SAFETYMCUSW 95 S MR:11.1,11.4 <APPROVED> "Reason -  Casting is required here."*/
							ppu32ReadHeader=(uint32 **)&au32VirtualSectorAddress[5];
							au32VirtualSectorHeader[5] = **ppu32ReadHeader;
							
							/* Get the erase count of the VS */							
							if((au32VirtualSectorHeader[3] & 0x00FFFFF0U)!=0x00FFFFF0U)
							{							
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorEraseCount[u16Index]=((au32VirtualSectorHeader[3] & 0x00FFFFF0U) >> 0x4U) ;						
							}
							else
							{
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_au32VirtualSectorEraseCount[u16Index]=0U;
							}		
							
							/* Check if the sector is active VS */
							/*SAFETYMCUSW 433 S MR:6.1,6.2,10.1,10.2,10.3,10.4  <APPROVED> "Reason - LDRA Version
                              problem. Latest version do not have this warning."*/
							if(((au32VirtualSectorHeader[0]==ActiveVSLo) && 
							    (au32VirtualSectorHeader[1]==ActiveVSHi)) ||							     
							   /*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/
							   (TRUE == bFoundActiveVS[u8EEPIndex])
							  )	
							{								
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16Index]=VsState_Active;								
								
								if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector!=0U)
								{
									/* Two or more Active Virtual sectors found */
									/* Report Error */
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error = Error_TwoActiveVS;
									/* Update which of the VS's are Active */
									TI_Fee_u32ActCpyVS = 0x1U << (TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector-1U);
									TI_Fee_u32ActCpyVS |= 0x1U << u16Index;
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus = TI_FEE_ERROR;
									bFoundActiveVirtualSector[u8EEPIndex]=FALSE;
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector=0U;
								}
								else
								{
									/* Active virtual sector. Get the VS index */									
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector=Fee_VirtualSectorConfiguration[u16Index].FeeVirtualSectorNumber; 									
									bFoundActiveVirtualSector[u8EEPIndex]=TRUE;
									bFoundActiveVS[u8EEPIndex] = FALSE;
									bDoNotIncrement = FALSE;
									if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8CopyVirtualSector==0U)
									{
										/* Determine the Start & End address of the Active virtual sector */
										TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress=u32VirtualSectorStartAddress;									
										TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorStartAddress=u32VirtualSectorStartAddress;										
										oSectorEnd=Fee_VirtualSectorConfiguration[u16Index].FeeEndSector; 																			
										/* Get the start address of the end VS */
										/* To remove MISRA warning 72 D MR 12.2, get the return value from the API and assign to local variable */
										u32VirtualSectorEndAddress = TI_FeeInternal_GetVirtualSectorParameter(oSectorEnd,(uint16)FEE_BANK,(boolean)TRUE, u8EEPIndex);
										TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorEndAddress = u32VirtualSectorEndAddress;
										if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorEndAddress==0xFFFFFFFFU)
										{
											TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus=TI_FEE_ERROR;
										}
										/* Get the length of VS and add to start address of the end VS. Now we have VS end address */
										/*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/
										/* To remove MISRA warning 72 D MR 12.2, get the return value from the API and assign to local variable */
										u32VirtualSectorEndAddress = TI_FeeInternal_GetVirtualSectorParameter(oSectorEnd,(uint16)FEE_BANK,FALSE, u8EEPIndex); 
										TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorEndAddress += u32VirtualSectorEndAddress;
										TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorEndAddress=TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorEndAddress;
										if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error != Error_Nil)
										{
											TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus = TI_FEE_ERROR;
										}
									}
									/* Memorize the start address of VS as start address of active VS */
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorAddress=u32VirtualSectorStartAddress;
								}
							}							
							/*SAFETYMCUSW 433 S MR:6.1,6.2,10.1,10.2,10.3,10.4  <APPROVED> "Reason - LDRA 
						      Version problem. Latest version do not have this warning."*/
							else if(((au32VirtualSectorHeader[0] == CopyVSLo) && 
							         (au32VirtualSectorHeader[1] == CopyVSHi)) ||							        
									/*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/
									(TRUE == bFoundCopyVS[u8EEPIndex])
							        )
							{	
								/* Check if the sector is copy VS */								
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16Index]=VsState_Copy;								
										
								if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8CopyVirtualSector!=0U)
								{
									/* Two or more Copy Virtual Sectors found */
									/* Report Error */
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error=Error_TwoCopyVS;
									/* Update which of the VS's are Copy */
									TI_Fee_u32ActCpyVS = 0x1U << (TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8CopyVirtualSector-1U);
									TI_Fee_u32ActCpyVS |= 0x1U << u16Index;
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus=TI_FEE_ERROR;
								}
								else
								{
									/* Copy Virtual Sector found */
									/* Determine the Start & End address of the Copy Virtual Sector */									
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8CopyVirtualSector = Fee_VirtualSectorConfiguration[u16Index].FeeVirtualSectorNumber;
									bFoundCopyVS[u8EEPIndex] = FALSE;
									bDoNotIncrement = FALSE;								
									oCopyVirtualSectorStartAddress=u32VirtualSectorStartAddress;	
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyVirtualSectorStartAddress = u32VirtualSectorStartAddress;
									oSectorEnd = Fee_VirtualSectorConfiguration[u16Index].FeeEndSector;
									/* To remove MISRA warning 72 D MR 12.2, get the return value from the API and assign to local variable */
									u32VirtualSectorEndAddress = TI_FeeInternal_GetVirtualSectorParameter(oSectorEnd,(uint16)FEE_BANK,(boolean)TRUE, u8EEPIndex);	
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorEndAddress = u32VirtualSectorEndAddress; 
									if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorEndAddress == 0xFFFFFFFFU)
									{
										TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus=TI_FEE_ERROR;
									}									
									/*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/
									/* To remove MISRA warning 72 D MR 12.2, get the return value from the API and assign to local variable */
									u32VirtualSectorEndAddress=TI_FeeInternal_GetVirtualSectorParameter(oSectorEnd,(uint16)FEE_BANK,FALSE, u8EEPIndex);
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorEndAddress += u32VirtualSectorEndAddress;
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyVirtualSectorEndAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorEndAddress;
									if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error != Error_Nil)
									{
										TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus=TI_FEE_ERROR;
									}									
								}
							}							
							else if((au32VirtualSectorHeader[0] == EmptyVSLo) && 
							        (au32VirtualSectorHeader[1] == EmptyVSHi))
							{
								/* Check if the sector is Empty VS */								
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16Index]=VsState_Empty;									
							}							
							else if((au32VirtualSectorHeader[0] == InvalidVSLo) && 
							        (au32VirtualSectorHeader[1] == InvalidVSHi))
							{
								/* Check if the sector is Invalid VS */
								/* If it is invalid, add to internal erase queue. Erasing will happen in background */																
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16Index]=VsState_Invalid;								
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32InternalEraseQueue|=0x1U<<u16Index;	
							}							
							/*SAFETYMCUSW 433 S MR:6.1,6.2,10.1,10.2,10.3,10.4  <APPROVED> "Reason - LDRA 
						      Version problem. Latest version do not have this warning."*/
							else if(((au32VirtualSectorHeader[0] == ReadyforEraseVSLo) && 
							         (au32VirtualSectorHeader[1] == ReadyforEraseVSHi)) ||									 
									 /*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/
									 (TRUE == bFoundReadyForEraseVS[u8EEPIndex]))
							{
								/* Check if the sector is Ready for Erase VS */
								/* If it is ready for erase, add to internal erase queue. Erasing will happen in background */								
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16Index] = VsState_ReadyForErase;
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32InternalEraseQueue |= 0x1U<<u16Index; 																	
								bFoundReadyforEraseVirtualSector[u8EEPIndex] = TRUE;
								bDoNotIncrement = FALSE;
								bFoundReadyForEraseVS[u8EEPIndex] = FALSE;
							}
							else
							{
								if((au32VirtualSectorHeader[2]==0x00000000U) && 
								   (((au32VirtualSectorHeader[4] == 0x0000FFFFU) && 
								    (au32VirtualSectorHeader[5] == 0xFFFFFFFFU)) ||
								   ((au32VirtualSectorHeader[4] == 0x00000000U) && 
									 (au32VirtualSectorHeader[5] == 0xFFFFFFFFU))
								    ))
								{
									bFoundActiveVS[u8EEPIndex] = TRUE;
									bDoNotIncrement = TRUE;									
								}
								else if((au32VirtualSectorHeader[2]==0x0000FFFFU))
								{
									bFoundCopyVS[u8EEPIndex] = TRUE;
									/* If erase was started/completed, it means there is a VS ready for erase */
									if(((au32VirtualSectorHeader[4] == 0x0000FFFFU) && 
									    (au32VirtualSectorHeader[5] == 0xFFFFFFFFU)) ||
									    ((au32VirtualSectorHeader[4] == 0x00000000U) && 
										(au32VirtualSectorHeader[5] == 0xFFFFFFFFU)))
									{
										bFoundReadyforEraseVirtualSector[u8EEPIndex]=TRUE;	
									}
									bDoNotIncrement = TRUE;									
								}
								else if((au32VirtualSectorHeader[2]==0x00000000U) && 
								        ((au32VirtualSectorHeader[4] == 0x00000000U) && 
										 (au32VirtualSectorHeader[5] == 0x0000FFFFU)))
								{
									bFoundReadyForEraseVS[u8EEPIndex] = TRUE;		
									bDoNotIncrement = TRUE;									
								}
								else								   
								{	
									/* Report Invalid Virtual Sector State */																
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_au8VirtualSectorState[u16Index]=VsState_ReadyForErase;
									TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32InternalEraseQueue|=0x1U<<u16Index;																
								}
							}
						}						
					}
					else
					{
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus=TI_FEE_ERROR;
					}
					if(bDoNotIncrement == FALSE)
					{
						u16Index++;
					}	
				} /* While for sectors loop ends here */
				
				/* If there is no error in above, continue with setting up FLASH.*/
				if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus==TI_FEE_OK)&& 
				   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error==Error_Nil))
				{	
					/* Set up the State machine, only if it is not already initialized */ 					
					/*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/
					/*SAFETYMCUSW 433 S MR:6.1,6.2,10.1,10.2,10.3,10.4 <APPROVED> "Reason -  FALSE is a macro."*/
					if(FALSE == TI_Fee_FapiInitCalled)
					{					
						TI_Fee_FapiInitCalled = TRUE;						
						if((Fapi_initializeFlashBanks((uint32)TI_FEE_OPERATING_FREQUENCY))==Fapi_Status_Success)
						{						
						}
						else
						{
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error = Error_SetupStateMachine;
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus = TI_FEE_ERROR;
						}														
					}					
					
					if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus != TI_FEE_ERROR)
					{
						/* Select which Sectors to enable...all the sectors for the particular Bank are enabled*/					
						(void)Fapi_setActiveFlashBank(Device_FlashDevice.Device_BankInfo[FEE_BANK].Device_Core); 
						(void)Fapi_enableEepromBankSectors(FEE_ENABLE_SECTORS_31_00, FEE_ENABLE_SECTORS_63_32);

						/* If Ready for Erase and Copy VS found, then mark Copy as Active */
						if((bFoundReadyforEraseVirtualSector[u8EEPIndex]==TRUE) && 
						   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8CopyVirtualSector!=0U) && 
						   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector == 0U))
						{							
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector=TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8CopyVirtualSector;
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8CopyVirtualSector=0U;
							bFoundActiveVirtualSector[u8EEPIndex]=TRUE;
							
							/* Determine the Start & End address of the Active virtual sector */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress = oCopyVirtualSectorStartAddress;
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorAddress = oCopyVirtualSectorStartAddress;
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorStartAddress = oCopyVirtualSectorStartAddress;
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorEndAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyVirtualSectorEndAddress;
							/* Mark the VS Header as Active*/
							TI_FeeInternal_WriteVirtualSectorHeader(
							                     TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector,
							                     VsState_Active, u8EEPIndex);
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextActiveVSwriteaddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorAddress+TI_FEE_VIRTUAL_SECTOR_OVERHEAD+16U;
						}

						/* If there is one Copy VS and no Active VS and no ready for erase VS, there may be some error */
						if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8CopyVirtualSector!=0U)
						{
							if((bFoundReadyforEraseVirtualSector[u8EEPIndex]==FALSE) && 
							    (TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector==0U))
							{
								/* Update which of the VS's are Copy */
								TI_Fee_u32ActCpyVS = 0x1U << (TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8CopyVirtualSector-1U);
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error=Error_CopyButNoActiveVS;								
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus=TI_FEE_ERROR;
							}
						}						
						
						if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector!=0U) && 
						   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8CopyVirtualSector!=0U))
						{	
							/* One active VS and one copy VS found */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8WriteCopyVSHeader = TI_FEE_VIRTUAL_SECTOR_OVERHEAD;
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oCopyVirtualSectorAddress = oCopyVirtualSectorStartAddress;
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress = oCopyVirtualSectorStartAddress;
							/* Update Block offset array. Also update block copy stauus */
							/* Scan Active VS */
							TI_FeeInternal_UpdateBlockOffsetArray(u8EEPIndex, 
							              (boolean)TRUE,TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector);
							bActiveVSScanned[u8EEPIndex] = TRUE;
							/* Scan Copy VS */
							TI_FeeInternal_UpdateBlockOffsetArray(u8EEPIndex, 
							               (boolean)FALSE,TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8CopyVirtualSector);
							TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Copy=1U;
							/* Complete copy operation and only then accept new jobs.*/
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_PENDING;
						}
						/* No Active Virtual Sector found */
						else if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector==0U) 
						{
							 /* Create a new Active Virtual Sector */
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector = TI_FeeInternal_FindNextVirtualSector(u8EEPIndex);
							if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector!=0U) &&
							   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error==Error_Nil))
							{
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress;
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorStartAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress;
								TI_FeeInternal_WriteVirtualSectorHeader(
								                 TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector,
								                 VsState_Active,u8EEPIndex);
								TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextActiveVSwriteaddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorAddress +
												   TI_FEE_VIRTUAL_SECTOR_OVERHEAD+16U;
								bFoundActiveVirtualSector[u8EEPIndex]=TRUE;
							}							
						}
						else
						{
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress;
							TI_Fee_GlobalVariables[u8EEPIndex].Fee_oActiveVirtualSectorStartAddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_oVirtualSectorStartAddress;
						}
					}
				}				
				/* If Active virtual sector found */
				/*SAFETYMCUSW 433 S MR:6.1,6.2,10.1,10.2,10.3,10.4  <APPROVED> "Reason - LDRA Version
                  problem. Latest version do not have this warning."*/
				if(bFoundActiveVirtualSector[u8EEPIndex]==TRUE)				
				{				
					/* Scan Active VS, if it is not already scanned. */
					/*SAFETYMCUSW 96 S MR:6.2,10.1,10.2,12.6 <APPROVED> "Macro comes from compiler files."*/
					if(FALSE == bActiveVSScanned[u8EEPIndex])
					{
						/* Wait till FSM has completed write */
						(void)TI_FeeInternal_PollFlashStatus();
						TI_FeeInternal_UpdateBlockOffsetArray(u8EEPIndex, (boolean)TRUE,
						                                TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector);
					}	
					/* Update the next free address */
					if(TI_Fee_oStatusWord[u8EEPIndex].Fee_StatusWordType_ST.Copy==1U)
					{
						/* Copying is in progress. Next data should be written in to copy VS */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextCopyVSwriteaddress;
					}
					else
					{
						/* Copying is not in progress. Next data should be written in to Active VS */
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress = TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextActiveVSwriteaddress;
					}					
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress=TI_FeeInternal_AlignAddressForECC(
					                                  TI_Fee_GlobalVariables[u8EEPIndex].Fee_u32nextwriteaddress);
				}				

				if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8CopyVirtualSector!=0U) &&
				   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error != Error_TwoCopyVS))
				{
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState = BUSY_INTERNAL;
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult = JOB_PENDING;
				}
				else if(TI_Fee_GlobalVariables[u8EEPIndex].Fee_u8ActiveVirtualSector!=0U)
				{
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState=IDLE;
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult=JOB_OK;
					#if((TI_FEE_FLASH_ERROR_CORRECTION_HANDLING == TI_Fee_Fix))									
					Fee_bSingleBitError = FALSE;
					Fee_bDoubleBitError = FALSE;
					#endif
				}
				else
				{					
					if((TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error != Error_TwoActiveVS) &&
					   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error != Error_TwoCopyVS) &&
					   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error != Error_CopyButNoActiveVS) &&
					   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error != Error_SetupStateMachine) &&
					   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error != Error_EraseVS) &&
					   (TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error != Error_NoFreeVS))
					{	
						TI_Fee_GlobalVariables[u8EEPIndex].Fee_Error=Error_NoActiveVS;
					}	
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_oStatus=TI_FEE_ERROR;
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_ModuleState=UNINIT;
					TI_Fee_GlobalVariables[u8EEPIndex].Fee_u16JobResult=JOB_FAILED;
				}				
			}		
		}		
		u8EEPIndex++;
	}
}

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_STOP_SEC_CODE
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"
/**********************************************************************************************************************
 *  END OF FILE: ti_fee_ini.c
 *********************************************************************************************************************/
