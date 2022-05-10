## phantom_vars.h
This file holds all user-defined types in this project so that all software modules can access their types. This mostly consists of structs and enums used to identify message types and tasks from transmitting and receiving messages to and from the queue.

A common pattern to highlight, mentioned in freeRTOS book is defining a struct as follows:
```
typedef struct AgentMessage{
    uint8_t id; // agent identifier
    uint8_t msg; // data from agent
}AgentMessage_t;
```
When multiple senders access a single queue, the receiver can identify where the data came from by receiving a type ```AgentMessage_t``` that holds the actual data, as well as an id to that the transmitter and receiver can agree upon (normally an enum).

Another notable design choice is the user-defined type QueueArr_t:
```
typedef struct QueueArr_t
{
    QueueHandle_t tx;
    QueueHandle_t rx;
}QueueArr_t;
```
Each task is given one instance of this struct, and is limited to one queue for receiving, and one for transmitting. For this prototype, this was a reasonable choice to make but bigger projects may need to relax this restriction. In general, take care not to overwhelm the amount of data. Another benefit to this is that once the QueueHandle_t rx/tx queues are assigned during initialization, it is made explicitly clear in the code that the data being accessed at a specific side.

## phantom_config.h
This file holds configurations/pre-processor flags for enabling simulation and debug mode.

## common.h/c

This file holds a collection of common underlying functions used by a majority of the tasks. The two most important functions here are integral for simulation and debug mode.

```
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
```
```
uint8_t log_messagef(uint32_t index){

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
}

uint8_t log_valuef(uint32_t value){


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
}
```

