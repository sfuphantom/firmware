/*
 * launchpadhw.h
 *
 *  Created on: Jul 13, 2020
 *      Author: Mahmoud Ahmed
 */

#ifndef PHANTOM_DRIVERS_INCLUDE_HWCONFIG_H_
#define PHANTOM_DRIVERS_INCLUDE_HWCONFIG_H_



/***************  VCU PINS  *********************/

/*********   SHUTDOWN/RTD GPIO   ****************/ //(gioGetBit)
#define SHUTDOWN_CIRCUIT_PORT gioPORTA //configure in halcogen
#define BMS_FAULT_PIN         7 
#define IMD_FAULT_PIN         6 

#define BSPD_PORT             hetPORT1 //configure in halcogen
#define BSPD_FAULT_PIN        9 

#define RESET_PORT            hetPORT1 //configure in halcogen
#define RESET_PIN             26

#define READY_TO_DRIVE_PORT   gioPORTA //configure in halcogen
#define READY_TO_DRIVE_PIN    2

/****************** BRAKE LIGHT *************************/
#define BRAKE_LIGHT_PORT      hetPORT1 //configure in halcogen
#define BRAKE_LIGHT_PIN       22

/********* READY TO DRIVE PIEZO PWM ****************/
#define BUZZER_PORT           hetRAM1 //configure in halcogen
#define READY_TO_DRIVE_BUZZER pwm0    //configure in halcogen (output on pin 7)

/***************  TSAL GPIO  *********************/
#define TSAL_PORT             gioPORTA //configure in halcogen
#define TSAL_ACTIVE_PIN       5 


///*********   HV CURRENT/VOLTAGE   ****************/
#define HV_VOLTAGE_SPI        spiREG3 //configure in halcogen


///*********   HV CURRENT APPS/BSE   ****************/
#define DAC_SPI_PORT          mibspiREG1 // APPS1/2, BSE, HVCURRENT //configure in halcogen
#define INVERTER_PORT         adcREG1
#define INVERTER_PIN          adcGROUP1 //configure in halcogen (input/output? on pin 15)

/***************  IMD  *********************/
#define IMD_PORT              hetRAM1   //configure in halcogen
#define IMD_PIN               pwm1      //configure to output on pin 4 in halcogen




///*********   LV MONITOR   ****************/
//#define LV_MONITOR_I2C_PORT   i2cREG1 //configure in halcogen






///*********   UART PORTS   ****************/
//#define PC_UART               sciREG //configure in halcogen
//#define BMS_UART              scilinREG




















///*********   VCU/BMS CAN   ****************/












/***************  BMS PINS  *********************/

#define BMS_UART                sciREG //configure in halcogen
#define WAKEUP_PORT             gioPORTA //configure in halcogen
#define WAKEUP_PIN              0 //configure in halcogen
#define FAULT_PORT              gioPORTA //configure in halcogen
#define FAULT_PIN               1 //configure in halcogen

// Debug UART
#define PC_UART                 scilinREG

// Thermistor Board Pins
#define THERMISTOR_SPI                  mibspiREG3 //configure in halcogen
#define THERMISTOR_INIT_TRANSFER_GROUP  TransferGroup0 //configure in halcogen
#define THERMISTOR_COMM_TRANSFER_GROUP  TransferGroup1 //configure in halcogen
#define THERMISTOR_MUX_PORT             gioPORTA //configure in halcogen
#define THERMISTOR_MUX_PIN_A            5 //configure in halcogen
#define THERMISTOR_MUX_PIN_B            6 //configure in halcogen
#define THERMISTOR_MUX_PIN_C            7 //configure in halcogen


#endif /* PHANTOM_DRIVERS_INCLUDE_HWCONFIG_H_ */
