# Actor Task

This task is in charge of handling and processing the data received by the Agents. It sends the output to the Director task as well as outputs a signal to an led on the development board.

An important note to discuss is the use of a struct for this module to wrap all relevant data together. Any random, irrelevant and/or intermediate variables can be declared within the scope of the task itself. This makes the code easier to read (all relevant data in the module can be seen in the header file), and harder to misuse.
```
typedef struct Actor_t
{
    /* Input Data */ 
    AgentMessage_t data;
    uint8_t agent1_state;
    uint8_t agent2_state;
    
    /* Output Data */
    uint8_t tx_data;

}Actor_t;
```

In the following code below, there is no explicit delay or 'yielding' of execution to the scheduler. Instead, this task is part of the pipeline that begins at the Agents; once data is made available through them, the Actor will be allowed to run again. When no data is being sent to the queue, the task will block until the timeout of 1ms has been reached. If the Agent tasks never fail, this task can be assumed to run at the same frequency as the tasks it is receiving from.

If receiving times out, ```xQueueReceive``` will return ``pdFALSE``. This event can be acted upon and the queue could used as a form of software heartbeats to ensure its agents are operating as expected.

The software logic for this module is sandwiched between boilerplate calls to the queue api.
```
void vTaskActor(void* pvParams){
    
    /* Initialize struct */
    static Actor_t actor_data = {
        .data = {0},
        .tx_data = 0,
        .agent1_state = 0,
        .agent2_state = 0,
    };
    static Actor_t* self = &actor_data;

    /* Initialize intermediate variables */
    static BaseType_t rx_success = pdFALSE;
    uint8_t debug_success = 1;

    while(true){

        /* receive data from agents (suspend until data available) */
        rx_success = xQueueReceive(
            q_ptr->rx,
            &self->data,
            ( TickType_t ) pdMS_TO_TICKS(500)  // block for 500ms
        );

        /* failed to receive data; do smt!! */
        if(rx_success == pdFALSE){
            continue;
        }

        /* act on agent data */
        actor_logic(self);
        debug_success = log_valuef(self->tx_data);

        /* transmit data */
        xQueueSend(
            q_ptr->tx,
            &self->tx_data,
            ( TickType_t ) 1
        );

    } // superloop
}
```
The actor_logic function processes the data and acts upon it.
```
void actor_logic(Actor_t* inst){

    switch(inst->data.id){

        case AGENT_ONE:
            inst->agent1_state = inst->data.msg;
            gioSetBit(gioPORTB, 1, inst->agent1_state);
            break;

        case AGENT_TWO:
            inst->agent2_state = inst->data.msg;
            gioSetBit(gioPORTB, 2, inst->agent2_state);
            break;
    } // switchcase
    inst->tx_data = inst->agent2_state && inst->agent1_state;
}
```

### [back to root](/queue-pipeline)