/** @file sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
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

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */
#include "sci.h"
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */

#include "MCP48FV_DAC_SPI.h"
uint16_t lookUpSine[]={
                     0,4,9,13,18,22,27,31,36,40,45,49,54,58,63,67,72,76,81,85,89,94,98,103,107,111,116,120,124,129,133,137,142,146,150,154,159,163,167,171,175,179,183,188,192,196,200,204,208,212,216,220,224,227,231,235,239,243,247,250,254,258,261,265,269,272,276,279,283,286,290,293,297,300,303,307,310,313,316,320,323,326,329,332,335,338,341,344,347,350,352,355,358,361,363,366,369,371,374,376,379,381,383,386,388,390,393,395,397,399,401,403,405,407,409,411,413,414,416,418,419,421,423,424,426,427,428,430,431,432,434,435,436,437,438,439,440,441,442,443,443,444,445,446,446,447,447,448,448,449,449,449,449,450,450,450,450,450,450,450,450,450,449,449,449,449,448,448,447,447,446,446,445,444,444,443,442,441,440,439,438,437,436,435,434,433,431,430,429,427,426,424,423,421,420,418,416,415,413,411,409,407,405,403,401,399,397,395,393,391,388,386,384,381,379,377,374,372,369,366,364,361,358,356,353,350,347,344,341,339,336,333,330,326,323,320,317,314,311,307,304,301,297,294,290,287,284,280,276,273,269,266,262,258,255,251,247,243,240,236,232,228,224,220,216,212,208,204,200,196,192,188,184,180,176,172,168,163,159,155,151,146,142,138,134,129,125,121,116,112,108,103,99,95,90,86,81,77,72,68,64,59,55,50,46,41,37,32,28,23,19,14,10,5,1,4,8,13,17,22,26,31,35,40,44,49,53,58,62,67,71,75,80,84,89,93,98,102,106,111,115,119,124,128,132,137,141,145,149,154,158,162,166,170,175,179,183,187,191,195,199,203,207,211,215,219,223,227,231,235,238,242,246,250,253,257,261,265,268,272,275,279,282,286,289,293,296,300,303,306,309,313,316,319,322,325,329,332,335,338,341,343,346,349,352,355,358,360,363,366,368,371,373,376,378,381,383,385,388,390,392,394,397,399,401,403,405,407,409,410,412,414,416,417,419,421,422,424,425,427,428,430,431,432,433,435,436,437,438,439,440,441,442,443,443,444,445,445,446,447,447,448,448,448,449,449,449,450,450,450,450,450,450,450,450,450,449,449,449,449,448,448,447,447,446,446,445,444,444,443,442,441,440,439,438,437,436,435,434,433,432,430,429,427,426,425,423,422,420,418,417,415,413,411,409,408,406,404,402,400,398,395,393,391,389,387,384,382,379,377,375,372,369,367,364,362,359,356,353,351,348,345,342,339,336,333,330,327,324,321,317,314,311,308,304,301,298,294,291,288
   };


/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */


    //using MCP48FV Library
    MCP48FV_Init();
    MCP48FV_Set_Value(500);//500 =5.00V, 250= 2.5V

//demo code for displaying sine wave
    uint32_t i=0;
    uint32_t j=0;
    for (;;){
    for(i=0; i<sizeof(lookUpSine)-1; i++){
       for (  j=0;j<0xffff; j++){
         asm("NOP");
       }

       MCP48FV_Set_Value(lookUpSine[i]);

    }}


/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
/* USER CODE END */
