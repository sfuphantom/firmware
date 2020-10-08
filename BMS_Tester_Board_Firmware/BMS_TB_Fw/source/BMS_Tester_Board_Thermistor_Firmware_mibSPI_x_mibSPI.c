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

//GND       -   BoosterPackSite-1-j3-pin-2
//GND       -   BoosterPackSite-1-j5-pin-1

//MASTER    -   mibspi3
    /*
     * MOSI -   BoosterPackSite-1-j5-pin-6
     * MISO -   BoosterPackSite-1-j5-pin-7
     * CLK  -   BoosterPackSite-1-j2-pin-7
     * CS   -   BoosterPackSite-1-j5-pin-3
     */
//SLAVE     -   mibspi1
    /*
     * MOSI -   BoosterPackSite-2-j9-pin-6
     * MISO -   BoosterPackSite-2-j9-pin-7
     * CLK  -   BoosterPackSite-2-j6-pin-7
     * CS   -   BoosterPackSite-2-j9-pin-8
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

//uint16_t

#define config_words    ((uint8)11)

#define channels        ((uint8)12)

//------------------------------------------------------------------------------------------------------------------------------------------------
//16-bit data words sent by the master for configuring the ADC in Auto-2 mode
uint16
adc_config[config_words]  =   {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3C00, 0x3000, 0x9300};

//16-bit data words sent by the master to keep the ADC operating in Auto-2 mode
uint16
adc_mode[channels]        =   {0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000,0x3000};


//------------------------------------------------------------------------------------------------------------------------------------------------
//16-bit data words sent by the slave (disguised as the ADC) to confirm its readiness to transfer test data
uint16
slave_ready[config_words]   =   {0x0000, 0x0000, 0x0001, 0x0000, 0x0000, 0x0001, 0x0000, 0x0000, 0x0001,0x0000, 0x0000};   //001-001-001-00

//16-bit test-data words sent by the slave (disguised as the ADC)
uint16
slave_test_data_1[channels] =   {0x0001, 0x0001, 0x0000, 0x0001, 0x0001, 0x0000, 0x0001, 0x0001, 0x0000, 0x0001, 0x0001, 0x0000};   //110-110-110-110


//------------------------------------------------------------------------------------------------------------------------------------------------
//16-bit data buffers for the application to process received data
uint16
Rx_config_data_buffer[config_words];

//16-bit data buffers for the application to process received data
uint16
Rx_data_buffer[channels];



/***********************************************************************************************************************************************************/
/*      DATA SHIFT CONFIRMATION VARIABLES        */
/***********************************************************************************************************************************************************/



uint8
adc_configured  =   0;

uint8
slave_connection_verified   =   0;

uint8
received_data   =   0;



/***********************************************************************************************************************************************************/
/*      DATA TRANSMISSION CONTROL       */
/***********************************************************************************************************************************************************/



#define transmission_successful     ((uint8)1)
#define slave_not_recognized        ((uint8)0)
#define slave_recognized            ((uint8)1)


uint8   initialize_mibspi_mibspi_comm(void)
{
    mibspiInit();
    gioInit();

    //mibspiSetConfigData();
    mibspiSetData(mibspiREG3, TransferGroup0_M, adc_config[]);

  //mibspiSetConfigResponseData();
    mibspiSetData(mibspiREG1, TransferGroup0_S, slave_ready[]);

  //enable group notifications
    mibspiEnableGroupNotification(mibspiREG3, TransferGroup0_M, 0);
//  mibspiEnableGroupNotification(mibspiREG1, TransferGroup0_S, 0);           //wouldn't this clash with the preceding group notification

  //send configuration data
    mibspiTransfer(mibspiREG3, TransferGroup0_M)

  //wait until ADC configured
    while   (!adc_configured){};

 /*******************************************************************************************************


  //cross-check if the slave sent the desired data
    verify_slave_connection();
    while   (!slave_connection_verified){};         //Visual Aid - LED

  //mispiSetModeData
    mibspiSetData(mibspiREG3, TransferGroup1_M, adc_mode[]);

  //enable group notification
    mibspiEnableGroupNotification(mibspiREG3, TransferGroup1_M, 0);

  //send mode data
    mibspiTransfer(mibspiREG3, TransferGroup1_M);

  //wait until test data received from the slave
    while   (!received_data){};


 *******************************************************************************************************/


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
            adc_configured  =   1;

            //shift the received data, from the master's transfer group, into the master's receive buffer
            mibspiGetData(mibspiREG3, group, Rx_config_data_buffer[]);

        }

    else if  (group  ==  TransferGroup1_M)
        {
            mibspiDisableGroupNotification(mibspiREG3, group);

        }

}



/***********************************************************************************************************************************************************/
/*      AUXILIARY FUNCTIONS       */
/***********************************************************************************************************************************************************/


uint8   verify_slave_connection()       ////001-001-001-00
{
    if      (Rx_config_data_buffer[0]   !=  0x0000)
    {
        return  slave_not_recognized;
    }
    else if (Rx_config_data_buffer[1]   !=  0x0000)
    {
        return slave_not_recognized;
    }
    else if (Rx_config_data_buffer[2]   !=  0x0001)
        {
            return slave_not_recognized;
        }
    else if (Rx_config_data_buffer[3]   !=  0x0000)
        {
            return slave_not_recognized;
        }
    else if (Rx_config_data_buffer[4]   !=  0x0000)
        {
            return slave_not_recognized;
        }
    else if (Rx_config_data_buffer[5]   !=  0x0001)
        {
            return slave_not_recognized;
        }
    else if (Rx_config_data_buffer[6]   !=  0x0000)
        {
            return slave_not_recognized;
        }
    else if (Rx_config_data_buffer[7]   !=  0x0000)
        {
            return slave_not_recognized;
        }
    else if (Rx_config_data_buffer[8]   !=  0x0001)
        {
            return slave_not_recognized;
        }
    else if (Rx_config_data_buffer[9]   !=  0x0000)
        {
            return slave_not_recognized;
        }
    else if (Rx_config_data_buffer[10]  !=  0x0000)
        {
            return slave_not_recognized;
        }
    return slave_recognized;
}











