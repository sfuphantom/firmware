# Actor Task

This task is in charge of handling and processing the data received by the Agents. It sends the output to the Director task as well as outputs a signal to an led on the development board.

An important note to discuss is the use of a struct for this module to wrap all relevant data together. Any random, irrelevant and/or intermediate variables can be declared within the scope of the task itself. This makes the code easier to read (all relevant data in the module can be seen in the header file), and harder to misuse.
```
typedef struct Actor_t
{
    /* Queue Handles */
    QueueArr_t queue;

    /* Input Data */ 
    AgentMessage_t data;
    uint8_t agent1_state;
    uint8_t agent2_state;
    
    /* Output Data */
    uint8_t tx_data;

}Actor_t;
```

Here, there is no explicit delay or 'yielding' of execution to the scheduler. Instead, this task is part of the pipeline that begins at the Agents. The task will block for 1ms when no data is being sent to the queue. If the Agent tasks never fail, then in theory this task can be assumed to run at the same frequency as the tasks it is receiving from.

If receiving times out, ```xQueueReceive``` will return ``pdFALSE``. This event can be acted upon and the queue used as a type of software heartbeat to ensure its child task is operating as expected.

The software logic for this module is sandwiched between boilerplate calls to the queue api.
```

void vTaskActor(void* pvParams){
    
    /* Initialize intermediate variables */
    static BaseType_t rx_success = pdFALSE;

    while(true){

        /* receive data from agents (suspended until available data) */
        rx_success = xQueueReceive(
            this->queue.rx,
            &this->data,
            ( TickType_t ) pdMS_TO_TICKS(1)  // block for 1 tick
        );

        /* failed to receive data; do smt!! */
        if(rx_success == pdFALSE){
            continue;
        }

        /* act on agent data */
        this->tx_data = actor_logic(this->data, this->agent1_state, this->agent2_state);

        /* transmit data */
        xQueueSend(
            this->queue.tx,
            &this->tx_data,
            ( TickType_t ) 1
        );

    } // superloop
}
```
The actor_logic function processes the data and acts upon it. Here, it parses the message as either agent1 or 2 data, sends the values to the debug actor, and returns the ```and``` of both values. Because the struct is static, this function already has access to all of the data without needing them to be passed in. The parameters were still specified though, to be explicit and more unit testable. This decision may be a little overdone.
```
uint8_t actor_logic(AgentMessage_t data, uint8_t agent1_state, uint8_t agent2_state){

    switch(data.id){

        case AGENT_ONE:
            agent1_state = data.msg;
            gioSetBit(gioPORTB, 1, agent1_state);
            log_valuef(data.msg);
            break;

        case AGENT_TWO:
            agent2_state =  data.msg;
            gioSetBit(gioPORTB, 2, agent2_state);
            break;
    } // switchcase
    return agent2_state && agent1_state;
}
```