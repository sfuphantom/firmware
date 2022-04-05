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


#include "FreeRTOS.h"
#include "os_task.h"
#include "os_queue.h"
#include "gio.h"
# include <stdlib.h>

/* USER CODE END */

/* Include Files */

#include "sys_common.h"

/* USER CODE BEGIN (1) */

#include "string.h"
#include "sci.h"
#include "stdio.h"



void delayms(uint16_t ms) {
      volatile unsigned int delayval;
      delayval = ms * 8400;   // 8400 are about 1ms
      while(delayval--);
}
#define PC_UART scilinREG
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

void UARTprintf(char data[])
{
   UARTSend(PC_UART, data);
}

void split(char* str, const char* delimeter, char* buffer, int buffer_size);
#define TEST_MODE 
#define SIM_TASK 2
enum{
    DIRECTOR=0,
    ACTOR,
    AGENT_ONE,
    AGENT_TWO
};

enum{
    RAW_QUEUE=0,
    FILTERED_QUEUE

};


typedef struct GlobalData{

    TaskHandle_t task_handle_arr[4];
    QueueHandle_t queue_handle_arr[2];

}GlobalData_t;

typedef struct AgentMessage{
    uint8_t id;
    uint8_t msg;
}AgentMessage_t;

static GlobalData_t global;

static GlobalData_t* global_ptr = &global;
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */

void vTaskDirector(void* pvParams){

    static uint8_t rx_data = 0;
    static BaseType_t rx_success = pdFALSE;
    while(true){


        rx_success = xQueueReceive(
            global_ptr->queue_handle_arr[FILTERED_QUEUE],
            &rx_data,
            ( TickType_t ) 6000 // block for 1000 ticks
        );


//        if(rx_data == 1){
//
//            vTaskSuspend(global_ptr->task_handle_arr[ACTOR]);
//
//        }
//
//        if(rx_success == pdFALSE){
//            xQueueReset(global_ptr->queue_handle_arr[RAW_QUEUE]);
//            vTaskResume(global_ptr->task_handle_arr[ACTOR]);
//        }


        vTaskDelay(pdMS_TO_TICKS(1000));

    }



}

void vTaskActor(void* pvParams){

    static AgentMessage_t data = {0};
    static AgentMessage_t* data_ptr = &data;
    static uint8_t tx_data = 0;
    static uint8_t output = 0;
    static BaseType_t rx_success = pdFALSE;
    static uint8_t agent1_msg = 0;
    static uint8_t agent2_msg = 0;


    while(true){

        rx_success = xQueueReceive(
            global_ptr->queue_handle_arr[RAW_QUEUE],
            data_ptr,
            ( TickType_t ) portMAX_DELAY  // block for ~50 days
        );


        if(rx_success == pdFALSE){
            continue;
        }

        switch(data_ptr->id){

            case AGENT_ONE:
                agent1_msg = data_ptr->msg;
                gioSetBit(gioPORTB, 1, agent1_msg);
                break;

            case AGENT_TWO:
                agent2_msg =  data_ptr->msg;
                gioSetBit(gioPORTB, 2, agent2_msg);
                break;

            default:
                output = 0;
        }

        tx_data = agent2_msg && agent1_msg;
        xQueueSend(

            global_ptr->queue_handle_arr[FILTERED_QUEUE],
            &tx_data,
            ( TickType_t ) 1

        );



    }



}


void vTaskAgent1(void* pvParams){


    static AgentMessage_t data = {0};
    static AgentMessage_t* data_ptr = &data;
    data_ptr->id = AGENT_ONE;

    while(true){


        // read inputs

        data_ptr->msg = gioGetBit(gioPORTB, 1);



        xQueueSend(

            global_ptr->queue_handle_arr[RAW_QUEUE],
            ( void * ) data_ptr,
            ( TickType_t ) 10

        );

        vTaskDelay(pdMS_TO_TICKS(100));


    }



}

void vTaskAgent2(void* pvParams){

    static AgentMessage_t data = {0};
    static AgentMessage_t* data_ptr = &data;
    data_ptr->id = AGENT_TWO;

    while(true){


        // read inputs
        data_ptr->msg = gioGetBit(gioPORTB, 2);


        xQueueSend(

            global_ptr->queue_handle_arr[RAW_QUEUE],
            ( void * ) data_ptr,
            ( TickType_t ) 10

        );

        vTaskDelay(pdMS_TO_TICKS(100));


    }





}

void vTaskSim(void* pvParams){

    static AgentMessage_t agent1 = {0};
    static AgentMessage_t* agent1_ptr = &agent1;
    agent1_ptr->id = AGENT_ONE;    
    static AgentMessage_t agent2 = {0};
    static AgentMessage_t* agent2_ptr = &agent2;
    agent2_ptr->id = AGENT_TWO;
    static char py_msg[1];
    static char command[2];
    static char cmp_str[1];
    

    while(true){


        // read inputs
        sciReceive(PC_UART, 3, py_msg);

        split(py_msg, ",", command, 2);

        cmp_str[0] = command[0];
        agent1_ptr->msg = (int)strtol(cmp_str, (char **)NULL, 10);
        cmp_str[0] = command[1];
        agent2_ptr->msg = (int)strtol(cmp_str, (char **)NULL, 10);
        
        xQueueSend(

            global_ptr->queue_handle_arr[RAW_QUEUE],
            ( void * ) agent1_ptr,
            ( TickType_t ) 10

        );
        xQueueSend(

            global_ptr->queue_handle_arr[RAW_QUEUE],
            ( void * ) agent2_ptr,
            ( TickType_t ) 10

        );

        vTaskDelay(pdMS_TO_TICKS(1));


    }
}


void createTasks(GlobalData_t* data);
void createQueues(GlobalData_t* data);
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    UARTInit(PC_UART, 9600);

//    while (true)
//    {
//        /* code */
//        UARTprintf("Hello");
//        delayms(1000);
//    }

    UARTprintf("Starting program...\r\n");

    gioInit();


    createTasks(global_ptr);

    createQueues(global_ptr);

    vTaskStartScheduler();

    while(true);

//

/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */

void split(char* str, const char* delimeter, char* buffer, int buffer_size){


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

void createQueues(GlobalData_t* data){

    data->queue_handle_arr[RAW_QUEUE] = xQueueCreate( 100, sizeof( AgentMessage_t ) );
    data->queue_handle_arr[FILTERED_QUEUE] = xQueueCreate( 100, sizeof( uint8_t ) );

    if(data->queue_handle_arr[FILTERED_QUEUE] == NULL|| data->queue_handle_arr[RAW_QUEUE] == NULL ){
        UARTprintf("Failed to create queues\r\n");
    }else{
        UARTprintf("Created queues successfully!\r\n");
    }





}

void createTasks(GlobalData_t* data)
{
    BaseType_t xReturned;

    xReturned = xTaskCreate(
                    vTaskDirector,       /* Function that implements the task. */
                    "Director",          /* Text name for the task. */
                    64,      /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    3,/* Priority at which the task is created. */
                    &data->task_handle_arr[DIRECTOR]

    );      /* Used to pass out the created task's handle. */

    if(xReturned == pdFALSE){
        UARTprintf("Failed to create Director\r\n");
    }else{
        UARTprintf("Succcessfully created Director!\r\n");
    }
//
    xReturned = xTaskCreate(
                    vTaskActor,       /* Function that implements the task. */
                    "Actor",          /* Text name for the task. */
                    64,      /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    2,/* Priority at which the task is created. */
                    &data->task_handle_arr[ACTOR]

    );



    if(xReturned == pdFALSE){
        UARTprintf("Failed to create Actor\r\n");
    }else{
        UARTprintf("Succcessfully created Actor!\r\n");
    }

    #ifndef TEST_MODE
    xReturned = xTaskCreate(
                    vTaskAgent1,       /* Function that implements the task. */
                    "Agent1",          /* Text name for the task. */
                    64,      /* Stack size in words, not bytes. */
                    ( void * ) 1,    /* Parameter passed into the task. */
                    1,/* Priority at which the task is created. */
                    &data->task_handle_arr[AGENT_ONE]

    );

    if(xReturned == pdFALSE){
        UARTprintf("Failed to create Agent1\r\n");
    }else{
        UARTprintf("Succcessfully created Agent1!\r\n");
    }

    xReturned = xTaskCreate(
                vTaskAgent2,       /* Function that implements the task. */
                "Agent2",          /* Text name for the task. */
                64,      /* Stack size in words, not bytes. */
                ( void * ) 1,    /* Parameter passed into the task. */
                1,/* Priority at which the task is created. */
                &data->task_handle_arr[AGENT_TWO]

    );
    
    if(xReturned == pdFALSE){
        UARTprintf("Failed to create Agent2\r\n");
    }else{
        UARTprintf("Succcessfully created Agent2!\r\n");
    }

    #else

    xReturned = xTaskCreate(
                vTaskSim,       /* Function that implements the task. */
                "Sim",          /* Text name for the task. */
                64,      /* Stack size in words, not bytes. */
                ( void * ) 1,    /* Parameter passed into the task. */
                1,/* Priority at which the task is created. */
                &data->task_handle_arr[AGENT_ONE]

    );
    
    if(xReturned == pdFALSE){
        UARTprintf("Failed to create sim agent!\r\n");
    }else{
        UARTprintf("Succcessfully created sim agent!!\r\n");
    }


    #endif

}
/* USER CODE END */
