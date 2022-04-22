#include "Director.h"

static QueueArr_t q;

// void directorInit(QueueArr_t other){

//     /* Deep copy elements */
//     q.rx = other.rx;
//     q.tx = other.tx; 
// }

void vTaskDirector(void* pvParams){

    static uint8_t rx_data = 0;
    static BaseType_t rx_success = pdFALSE;
    while(1){


        // rx_success = xQueueReceive(
        //     global_ptr->queue_handle_arr[FILTERED_QUEUE],
        //     &rx_data,
        //     ( TickType_t ) 6000 // block for 1000 ticks
        // );


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

