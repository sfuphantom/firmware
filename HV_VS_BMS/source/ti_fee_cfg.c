/** @file ti_fee_cfg.c 
*   @brief FEE Driver Implementation File
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This is the FEE configuration parameter file.
*/

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


/* USER CODE BEGIN (0) */
/* USER CODE END */

/* Include Files                                                              */

#include "ti_fee.h"



/*----------------------------------------------------------------------------*/
/* Fee Version Check                                                          */

 #if (TI_FEE_MAJOR_VERSION != 3U)
     #error TI_FEE_Cfg.c: TI_FEE_SW_MAJOR_VERSION of TI_FEE.h is incompatible.
 #endif /* FEE_SW_MAJOR_VERSION */
 #if (TI_FEE_MINOR_VERSION != 0U)
     #error TI_FEE_Cfg.c: TI_FEE_SW_MINOR_VERSION of TI_FEE.h is incompatible.
 #endif /* FEE_SW_MINOR_VERSION */
 #if (TI_FEE_PATCH_VERSION != 2U)
     #error TI_FEE_Cfg.c: TI_FEE_SW_PATCH_VERSION of TI_FEE.h is incompatible.
 #endif /* FEE_SW_PATCH_VERSION */

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
 #define FEE_START_SEC_CONST_UNSPECIFIED
 /*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h" 

/*----------------------------------------------------------------------------*/
/* TI Fee Configurations                                                     */

/** @struct Fee_VirtualSectorConfigType 	*/
/*  @brief Virtual Sector Configuration 	*/
const Fee_VirtualSectorConfigType Fee_VirtualSectorConfiguration[TI_FEE_NUMBER_OF_VIRTUAL_SECTORS] =
{

    /* Virtual Sector 1 */
    {
       /* Virtual sector number */      1U,
       /* Bank                  */      7U,      
       /* Start Sector          */      (Fapi_FlashSectorType)0U,
       /* End Sector            */      (Fapi_FlashSectorType)0U
    },
    /* Virtual Sector 2 */
    {
        /* Virtual sector number */     2U,
        /* Bank                  */     7U,
        /* Start Sector          */     (Fapi_FlashSectorType)1U,            
		/* End Sector            */     (Fapi_FlashSectorType)1U
    }
  
};


/* Block Configurations         */
/* SourceId : HL_Fee_SourceId_2 */
/* DesignId : HL_FEE_DesignId_3, HL_FEE_DesignId_8 */
/* Requirements : HL_FEE_SR2, HL_FEE_SR3, HL_FEE_SR4, HL_FEE_SR6, HL_FEE_SR85, HL_FEE_SR86
                  HL_FEE_SR87, HL_FEE_SR88, HL_FEE_SR89, HL_FEE_SR90, HL_FEE_SR91 */
const Fee_BlockConfigType Fee_BlockConfiguration[TI_FEE_NUMBER_OF_BLOCKS] =
{
        /*      Block 1 */
        {
               /* Block number                          */     1U, 
               /* Block size                            */     8U,
               /* Block immediate data used             */     TRUE,			   
               /* Number of write cycles                */     0x8U,
               /* Device Index                          */     0x00000000U,
               /* Number of DataSets                    */     1U,			   
               /* EEP number                            */     0U			   
        }

		,
		/* If project needs more than 16 blocks, add additional blocks here and also 
           modify TI_FEE_TOTAL_BLOCKS_DATASETS and TI_FEE_NUMBER_OF_BLOCKS in ti_fee_cfg.h 	*/
/* USER CODE BEGIN (1) */
/* USER CODE END */
 
};

/*SAFETYMCUSW 580 S MR:1.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#define FEE_STOP_SEC_CONST_UNSPECIFIED
/*SAFETYMCUSW 338 S MR:19.1 <APPROVED> "Reason - This is the format to use for specifying memorysections."*/
#include "MemMap.h"

/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN (2) */
/* USER CODE END */
