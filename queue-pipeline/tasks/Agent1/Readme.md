# Agent Task
This task is in charge of reading a GPIO pin and outputting the data to a queue to be processed by the Actor. The beauty of this architecture is that each task is simple, and has a well-defined interface. 

The code below can be easily separated into its hardware and software parts. Those working on hardware can develop a single function to read the signals and then integrate their code into a task by adding the boilerplate queue code at the bottom.

For those unfamiliar with freeRTOS, the ```vTaskDelay``` function will essentially yield execution of this task for 100ms to allow other tasks to run. This means that the data is more or less sampled at 10Hz.
```
void vTaskAgent1(void* pvParams){

    static AgentMessage_t data = {0};
    static AgentMessage_t* data_ptr = &data;
    data_ptr->id = AGENT_ONE;

    while(true){

        // read inputs from pin
        data_ptr->msg = gioGetBit(gioPORTB, 1);

        // send data to actor
        xQueueSend(

            &q.tx,
            ( void * ) data_ptr,
            ( TickType_t ) 10

        );

        vTaskDelay(pdMS_TO_TICKS(100));

    }
}
```