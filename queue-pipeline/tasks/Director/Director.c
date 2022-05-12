#include "Director.h"

static QueueArr_t q;
static QueueArr_t* q_ptr = &q;

static Control_t control;
static Control_t* ctrl = &control;

void directorInit(QueueArr_t other, Control_t octrl){

    /* Deep copy elements */
    q_ptr->rx = other.rx;

    ctrl->agent1 = octrl.agent1;
    ctrl->agent2 = octrl.agent2;
    ctrl->actor = octrl.actor;
}

void vTaskDirector(void* pvParams){

    uint8_t rx_data = 0;
    BaseType_t rx_success = pdFALSE;
    while(1){

        rx_success = xQueueReceive(
            q_ptr->rx,
            &rx_data,
            ( TickType_t ) pdMS_TO_TICKS(1000) // block for x ticks
        );

        if(rx_success == pdFALSE){
            continue;
        }

        // control signals        
        if(rx_data == 1){
//            vTaskSuspend(some-task);
        }else{

//            vTaskResume(some-task);
        }

    } // superloop

}

