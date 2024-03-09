/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  ti_fee_cfg.h
 *      Project:  Tms570_TIFEEDriver
 *       Module:  TIFEEDriver
 *    Generator:  HALCoGen
 *
 *  Description:  This file implements the TI FEE Api.
 *---------------------------------------------------------------------------------------------------------------------
 * Author:  Vishwanath Reddy
 *---------------------------------------------------------------------------------------------------------------------
 * Revision History
 *---------------------------------------------------------------------------------------------------------------------
 * Version        Date         Author               Change ID        Description
 *---------------------------------------------------------------------------------------------------------------------
 * 00.00.01       31Aug2012    Vishwanath Reddy     0000000000000    Initial Version
 * 01.19.04		  05Dec2017    Prathap Srinivasan   HERCULES_SW-5082 Update version history.
 *
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

 
 #ifndef TI_FEE_CFG_H
 #define TI_FEE_CFG_H



/** @def TI_FEE_DRIVER
*   @brief Alias name for FEE Device 
*/
#define TI_FEE_DRIVER                                      1U

/* TI FEE General Configuration */
/** @def FEE_DEV_ERROR_DETECT
*   @brief Alias name for FEE Device Error
*/
/* SourceId : HL_Fee_SourceId_21 */
/* DesignId : None */
/* Requirements : HL_FEE_SR74 */
#define TI_FEE_DEV_ERROR_DETECT                            STD_ON

/** @def FEE_POLLING_MODE
*   @brief Alias name for FEE Polling Mode
*/
/* SourceId : HL_Fee_SourceId_30 */
/* DesignId : None */
/* Requirements : HL_FEE_SR88 */
#define TI_FEE_POLLING_MODE                                STD_ON

/** @def FEE_OPERATING_FREQUENCY
*   @brief Alias name for FEE Operating Frequency
*/
/* SourceId : HL_Fee_SourceId_31 */
/* DesignId : HL_FEE_DesignId_4 */
/* Requirements : HL_FEE_SR84 */
#define TI_FEE_OPERATING_FREQUENCY                         160.000F

/** @def FEE_FLASH_ERROR_CORRECTION_ENABLE
*   @brief Alias name for FEE Error Correction Enable
*/
#define TI_FEE_FLASH_ERROR_CORRECTION_ENABLE               STD_ON 

/** @def FEE_FLASH_ERROR_CORRECTION_HANDLING
*   @brief Alias name for FEE Error Correction Handle
*/
#define TI_FEE_FLASH_ERROR_CORRECTION_HANDLING             TI_Fee_None 

/** @def TI_FEE_FLASH_CHECKSUM_ENABLE
*   @brief Alias name for FEE Checksum Enable
*/
/* SourceId : HL_Fee_SourceId_23 */
/* DesignId : HL_FEE_DesignId_14 */
/* Requirements : HL_FEE_SR76 */
#define TI_FEE_FLASH_CHECKSUM_ENABLE                       STD_ON

/** @def TI_FEE_CHECK_BANK7_ACCESS
*   @brief Alias name for FEE BANK7 Access
*/
#define TI_FEE_CHECK_BANK7_ACCESS                          STD_ON

/** @def FEE_FLASH_WRITECOUNTER_SAVE
*   @brief Alias name for FEE Flash Write Counter
*/
/* SourceId : HL_Fee_SourceId_24 */
/* DesignId : HL_FEE_DesignId_15 */
/* Requirements : HL_FEE_SR77 */
#define TI_FEE_FLASH_WRITECOUNTER_SAVE                        STD_ON 

/** @def FEE_NUMBER_OF_EEPS
*   @brief Alias name for FEE EEPS
*/
/* SourceId : HL_Fee_SourceId_28 */
/* DesignId : HL_FEE_DesignId_2 */
/* Requirements : HL_FEE_SR92 */
#define TI_FEE_NUMBER_OF_EEPS                                 1U

/** @def TI_FEE_DATASELECT_BITS
*   @brief Alias name for FEE Data Select
*/
/* SourceId : HL_Fee_SourceId_29 */
/* DesignId : None */
/* Requirements : HL_FEE_SR85 */
#define TI_FEE_DATASELECT_BITS                             0U

/** @def FEE_INDEX
*   @brief Alias name for FEE Index
*/
/* SourceId : HL_Fee_SourceId_22 */
/* DesignId : HL_FEE_DesignId_13 */
/* Requirements : HL_FEE_SR72 */
#define TI_FEE_INDEX                                       0U

/** @def FEE_PAGE_OVERHEAD
*   @brief Alias name for FEE Page Overhead
*/
/* SourceId : HL_Fee_SourceId_20 */
/* DesignId : HL_FEE_DesignId_9*/
/* Requirements : HL_FEE_SR75 */
#define TI_FEE_PAGE_OVERHEAD                               0U

/** @def FEE_BLOCK_OVERHEAD
*   @brief Alias name for FEE Block Overhead
*/
/* SourceId : HL_Fee_SourceId_18 */
/* DesignId : HL_FEE_DesignId_9*/
/* Requirements : HL_FEE_SR74 */
#define TI_FEE_BLOCK_OVERHEAD                              24U

/** @def FEE_VIRTUAL_PAGE_SIZE
*   @brief Alias name for FEE Virtual Page Size
*/
/* SourceId : HL_Fee_SourceId_1 */
/* DesignId : HL_FEE_DesignId_12*/
/* Requirements : HL_FEE_SR1, HL_FEE_SR73 */
#define TI_FEE_VIRTUAL_PAGE_SIZE                           8U

/** @def FEE_VIRTUAL_SECTOR_OVERHEAD
*   @brief Alias name for FEE Virtual Sector Overhead
*/
/* SourceId : HL_Fee_SourceId_33 */
/* DesignId : HL_FEE_DesignId_11*/
/* Requirements : HL_FEE_SR97 */
#define TI_FEE_VIRTUAL_SECTOR_OVERHEAD                     16U

/** @def FEE_MAXIMUM_BLOCKING_TIME
*   @brief Alias name for FEE Maximum Blocking Time
*/
/* SourceId : HL_Fee_SourceId_19 */
/* DesignId : None */
/* Requirements : HL_FEE_SR72 */
#define TI_FEE_MAXIMUM_BLOCKING_TIME                       600U

/* TI FEE Virtual Sector Configuration */

/** @def FEE_NUMBER_OF_VIRTUAL_SECTORS
*   @brief Alias name for FEE Number Of Virtual Sectors
*/
/* SourceId : HL_Fee_SourceId_27 */
/* DesignId : HL_FEE_DesignId_6*/
/* Requirements : HL_FEE_SR80 */
#define TI_FEE_NUMBER_OF_VIRTUAL_SECTORS                   2U  

/** @def FEE_NUMBER_OF_VIRTUAL_SECTORS
*   @brief Alias name for FEE Number Of Virtual Sectors for EEP1
*/
/* SourceId : HL_Fee_SourceId_34 */
/* DesignId : HL_FEE_DesignId_7*/
/* Requirements : HL_FEE_SR96 */
#define TI_FEE_NUMBER_OF_VIRTUAL_SECTORS_EEP1               0U

/* TI FEE Block Configuration */

/** @def FEE_NUMBER_OF_BLOCKS
*   @brief Alias name for FEE Number Of Blocks
*/
/* SourceId : HL_Fee_SourceId_35 */
/* DesignId : HL_FEE_DesignId_5*/
/* Requirements : HL_FEE_SR95  */
#define TI_FEE_NUMBER_OF_BLOCKS                             1U

/** @def TI_FEE_NUMBER_OF_UNCONFIGUREDBLOCKSTOCOPY
*   @brief Alias name for Fee Number Of Unconfigured Blocks To Copy
*/
/* SourceId : HL_Fee_SourceId_26 */
/* DesignId : None */
/* Requirements : HL_FEE_SR82 */
#define TI_FEE_NUMBER_OF_UNCONFIGUREDBLOCKSTOCOPY           0U

/** @def TI_FEE_NUMBER_OF_EIGHTBYTEWRITES
*   @brief Alias name for Fee Number Of eight byte writes
*/
/* SourceId : HL_Fee_SourceId_25 */
/* DesignId : None */
/* Requirements : HL_FEE_SR81 */
#define TI_FEE_NUMBER_OF_EIGHTBYTEWRITES                    1U

/** @def TI_FEE_TOTAL_BLOCKS_DATASETS
*   @brief Alias name for total number of blocks and datasets
*/
#define TI_FEE_TOTAL_BLOCKS_DATASETS                        1U

/** @def TI_FEE_GENERATE_DEVICEANDVIRTUALSECTORSTRUC
*   @brief Alias name for Generate Device Specific Structure and Virtual sector Configuration Structure during runtime
*/
#define TI_FEE_GENERATE_DEVICEANDVIRTUALSECTORSTRUC         STD_OFF

/** @def TI_FEE_USEPARTIALERASEDSECTOR 
*   @brief Alias name for Use Partial Erased Sector
*/
#define TI_FEE_USEPARTIALERASEDSECTOR                       STD_OFF

/** @def TI_FEE_VARIABLE_DATASETS 
*   @brief Alias name Variable data sets
*/
#define TI_FEE_VARIABLE_DATASETS                            STD_ON

 #endif /* TI_FEE_CFG_H */

 /**********************************************************************************************************************
 *  END OF FILE: ti_fee_cfg.h
 *********************************************************************************************************************/
