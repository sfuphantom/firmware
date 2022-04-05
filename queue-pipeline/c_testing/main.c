#include <stdio.h>
#include <string.h>
#define true 1
#define false 0
#define BaseType_t int
#define uint8_t unsigned int
#define pdFALSE 0
#define gioPORTB "gioPORTB"
#define gioSetBit(port, num , x) printf("Setting %s%d to %d\n", port,num, x);
#define QueueSend()
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



typedef struct AgentMessage{
    uint8_t id;
    uint8_t msg;
}AgentMessage_t;


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

uint8_t vTaskActor(AgentMessage_t* data_ptr){

    static uint8_t tx_data = 0;
    static uint8_t output = 0;
    static BaseType_t rx_success = pdFALSE;
    static uint8_t agent1_msg = 0;
    static uint8_t agent2_msg = 0;


        /* Queue Receive
        rx_success = xQueueReceive(
            global_ptr->queue_handle_arr[RAW_QUEUE],
            data_ptr,
            ( TickType_t ) 1000 // block for 1000 ticks
        );
        */

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
        
        return tx_data;


}


int main(){

    AgentMessage_t data = {
        .id=AGENT_TWO,
        .msg=0
    };

    uint8_t ret = vTaskActor(&data);
    
    printf("Returned: %d\n", ret);

    // printf("hello");
    // char str[] = "1,2,3,4,5,6,7";
    // char buffer[4];
    // split(str, ",", buffer, 4);

    // printf("%s\n", buffer);
    // int i =0;
    // for(i = 0; i < 6; i++){
        
    //     printf("%c\n", buffer[i]);

    // }

    // static char command[2] = "11";
    // static char str[1];
    // str[0] =  command[1];
    // int result = strcmp(str, "1");
    // printf("strcmp(%s, \"1\") = %d\n", str, result);
    // return 0;

}