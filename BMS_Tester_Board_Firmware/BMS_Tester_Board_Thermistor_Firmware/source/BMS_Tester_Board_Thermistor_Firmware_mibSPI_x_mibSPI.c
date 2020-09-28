/*
 * BMS_Tester_Board_Thermistor_Firmware_mibSPI_x_mibSPI.c
 *
 *  Created on: Sep 24, 2020
 *      Author: Jaskanwal Singh
 */


#include "BMS_Tester_Board_Thermistor_Firmware_mibSPI_x_mibSPI.h""


/***********************************************************************************************************************************************************/
/*      MIBSPI MODULES     */
/***********************************************************************************************************************************************************/


//MASTER    -   mibspi3
    /*
     * MOSI - Pin __ on Booster Pack site - 1
     * MISO -
     * CLK  -
     * CS   -
     */
//SLAVE     -   mibspi1
    /*
     * MOSI -
     * MISO -
     * CLK  -
     * CS   -
     */


/***********************************************************************************************************************************************************/
/*      DATA TRANSFER GROUPS     */
/***********************************************************************************************************************************************************/



#define TransferGroup0_M    0x0     //Transfer Group 0 - Master
#define TransferGroup1_M    0x1     //Transfer Group 1 - Master
#define TransferGroup0_S    0x0     //Transfer Group 0 - Slave
#define TransferGroup1_S    0x1     //Transfer Group 1 - Slave



/***********************************************************************************************************************************************************/
/*      DATA BUFFERS        */
/***********************************************************************************************************************************************************/



#define config_words    11
#define channels        12

//------------------------------------------------------------------------------------------------------------------------------------------------
//16-bit data words sent by the master for configuring the ADC in Auto-2 mode
uint16_t
adc_config[config_words]  =   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3C00, 0x3000, 0x9300};

//16-bit data words sent by the master to keep the ADC operating in Auto-2 mode
uint16_t
adc_mode[channels]        =   {0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000};


//------------------------------------------------------------------------------------------------------------------------------------------------
//16-bit data words sent by the slave (disguised as the ADC) to confirm its readiness to transfer test data
uint16_t
slave_ready[config_words]    =   {0x0000, 0x0000, 0x0001, 0x0000, 0x0000, 0x0001, 0x0000, 0x0000, 0x0001,0x0000, 0x0000};   //001-001-001-00

//16-bit test-data words sent by the slave (disguised as the ADC)
uint16_t
slave_test_data_1[channels]         =   {0x0001, 0x0001, 0x0000, 0x0001, 0x0001, 0x0000, 0x0001, 0x0001, 0x0000, 0x0001, 0x0001, 0x0000};   //110-110-110-110


//------------------------------------------------------------------------------------------------------------------------------------------------
//16-bit data buffers for the application to process received data
uint16_t
Rx_config_data_buffer[config_words];

//16-bit data buffers for the application to process received data
uint16_t
Rx_data_buffer[channels];



/***********************************************************************************************************************************************************/
/*      DATA SHIFT CONFIRMATION VARIABLES        */
/***********************************************************************************************************************************************************/



uint8_t
adc_configured;

uint8_t
received_data;



/***********************************************************************************************************************************************************/
/*      DATA TRANSMISSION CONTROL       */
/***********************************************************************************************************************************************************/



#define transmission_successful     ((uint8)1)


uint8   initialize_mibspi_mibspi_comm()
{
    //mibspiSetConfigData();
    //enable group notification
    //send configuration data
    //wait until ADC configured
    //cross-check if the slave sent the desired data

    //if yes
        //mispiSetModeData
        //enable group notification
        //send mode data
        //wait until test data received from the slave

    //if no
        //

    return  transmission_successful;
}



/***********************************************************************************************************************************************************/
/*      TRANSMISSION NOTIIFCATIONS       */
/***********************************************************************************************************************************************************/

void mibspiGroupNotification(mibspiBASE_t *mibspi, uint32 group)
{
    if  (group  ==  TransferGroup0_M)
        {
            mibspiDisableGroupNotification(mibspiREG3, group);
        }

    else if  (group  ==  TransferGroup1_M)
        {
            mibspiDisableGroupNotification(mibspiREG3, group);

        }

}

















