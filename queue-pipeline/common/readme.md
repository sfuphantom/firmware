## phantom_vars.h
This file holds common user-defined types in this project so that all software modules can access their definition. This mostly consists of structs and enums used to identify message types and tasks when transmitting and receiving messages to and from the queue.

A common ```Queue``` pattern highlighted in the Mastering the FreeRTOS™
Real Time Kernel book is defining a struct as follows:
```
typedef struct AgentMessage{
    uint8_t id; // agent identifier
    uint8_t msg; // data from agent
}AgentMessage_t;
```
When multiple senders have access to a common queue, the receiver can identify where the data came from by receiving a type ```AgentMessage_t``` that holds the actual data, as well as an id that the transmitter can use to identify the information source (normally an enum).

Another notable design choice is the user-defined type QueueArr_t:
```
typedef struct QueueArr_t
{
    QueueHandle_t tx;
    QueueHandle_t rx;
}QueueArr_t;
```
Each task is given one instance of this struct, and is limited to one queue for receiving, and one for transmitting. For this prototype, this was a reasonable choice to make but bigger projects may need to relax this restriction. In general, take care not to overwhelm the amount of data accessible to any given section of code ie limit the scope as much as possible. Another benefit to this is that once the QueueHandle_t rx/tx queues are assigned during initialization, it is made explicitly clear in the code that the data is being accessed at a specific side.

## phantom_config.h
This file holds configurations/pre-processor flags for enabling simulation and debug mode.

## common.h/c

This file holds a collection of common underlying functions used by a majority of the tasks.

### [back to root](/queue-pipeline)