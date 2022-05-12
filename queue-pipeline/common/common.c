/*
 * common.c
 *
 *  Created on: Apr 11, 2022
 *      Author: Rafael
 */

#include "common.h"

static QueueHandle_t debug_q;

void split(char* str, const char* delimeter, char* buffer, int buffer_size){
    /*
    Args: 
        str: original string to split 
        delimeter: delimeter
        buffer: string to copy contents to 
        buffer_size: size of buffer 
    Return:
        No explicit returns. Output of function is copied to buffer

    */

    // Returns first token
    char *token = strtok(str, delimeter);

    // Keep printing tokens while one of the
    // delimiters present in str[].
    int index = 0;
    while (token != NULL && index < buffer_size)
    {
        buffer[index] = *token;
        token = strtok(NULL, delimeter);
        index++;
    }
}


void delayms(uint16_t ms) {
      volatile unsigned int delayval;
      delayval = ms * 8400;   // 8400 are about 1ms
      while(delayval--);
}

void UARTSend(sciBASE_t *sci, char data[])
{
    char *first = &data[0];
    sciSend(sci, strlen(data),(uint8 *)first);
}

void UARTInit(sciBASE_t *sci, uint32 baud)
{
    sciInit();
    sciSetBaudrate(sci, baud);
}

void UARTprintf(char msg[])
{
   UARTSend(PC_UART, msg);
}

void debug_init(QueueHandle_t q){
    debug_q = q;
}

uint8_t log_messagef(uint32_t index){

    #if SIM_MODE == 1
    DebugStruct_t data = {
        .print_val = 0,
        .data = index
    };

    BaseType_t tx_success =  xQueueSend(
        debug_q,
        &data,
        (TickType_t) pdMS_TO_TICKS(1)

    );

    return tx_success == pdTRUE;
    #else
    return 0;
    #endif
}

uint8_t log_valuef(uint32_t value){

    #if SIM_MODE == 1
    DebugStruct_t data = {
        .print_val = 1,
        .data = value
    };

    BaseType_t tx_success =  xQueueSend(
        debug_q,
        &data,
        (TickType_t) pdMS_TO_TICKS(1)

    );

    return tx_success == pdTRUE;
    
    #else
    return 0;
    #endif
}
