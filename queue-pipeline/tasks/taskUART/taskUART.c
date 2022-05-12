/*
 * taskUART.c
 *
 *  Created on: Apr 19, 2022
 *      Author: Rafael
 */


#include "taskUART.h"

static QueueHandle_t rx;


static const char* MESSAGES[] = {
    
    "foo", // MSG_ONE
    
    "bar" // ...

     
};

static const MSG_BUFFER_SIZE = sizeof(MESSAGES) / sizeof(char*);

void debugger_init(QueueHandle_t debug_queue){
    rx = debug_queue;
}

void vTaskDebugger(void* pvParams){

    static DebugStruct_t data;

    uint32_t prev_data;
//    static uint8_t delay;
    static BaseType_t rx_success = pdFALSE;
    while(1){

        // receieve messages from uart with an id
        rx_success = xQueueReceive(
            rx,
            &data,
            (TickType_t) pdMS_TO_TICKS(10000)

        );



       /* failed to receive data; do smt!! */
       if(rx_success == pdFALSE){
           continue;
       }

        if(data.print_val == 1){

            // (int)((ceil(log10(2^32))+1)*sizeof(char)) -stack overflow 
            char number_str[11];
            
            ltoa(data.data, number_str);
            UARTprintf(number_str);
            UARTprintf("\n");
        } else{

            if(data.data >= MSG_BUFFER_SIZE ){
                continue;
            }
            // print whatever value to the console
            UARTprintf(MESSAGES[data.data]);
            UARTprintf("\n");
            
        }


        prev_data = data.data;
//        uint16_t to_process = uxQueueMessagesWaiting(rx);
//
//        // speed up processing for lots of messages
//        if(to_process > 10){
//            delay = 1;
//        }else{
//            delay = 100;
//        }
//
//        vTaskDelay(pdMS_TO_TICKS(delay));
//

    }

}
