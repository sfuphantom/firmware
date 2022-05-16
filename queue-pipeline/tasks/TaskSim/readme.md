# Simulation Task

Any simulation will have some quirks that push it farther away from reality. Quirks in this simulation include...
* The more Agents a system has, the farther this simulation will be from reality as this task mimics all of them at once
*  This task sends all data serially one after another. The data is not being sent asynchronously

The major difference is that normally, a good design pattern is for freeRTOS tasks to be distributed and divided according to their time domain. For example, sensors that sample at 1Hz and use similar protocols may appear together in one task whereas sensors operating at 50Hz would be in another task. This simulation task would put every Agent under the same time domain. This solution may not be ideal for some signal processing applications where sampling at a particular frequency is quite important. 

First, we read the inputs from the ```PC_UART```. This is exactly the data that is being sent by blinky_sim.py. Once it is received, we split and parse the data, then convert the chars to proper integers, and package them into the correct format agreed upon by the Actor and its Agents. 

```
void vTaskSim(void* pvParams){

    static char py_msg[1];
    static char command[2];
    static char cmp_str[1];

    while(true){

        /* read inputs from PC */
        sciReceive(PC_UART, 3, py_msg);

        /* parse serial command */
        split(py_msg, ",", command, 2);

        /* distribute values to appropriate pointers */
        cmp_str[0] = command[0];
        this->agent1.msg = (int)strtol(cmp_str, (char **)NULL, 10);
        cmp_str[0] = command[1];
        this->agent2.msg = (int)strtol(cmp_str, (char **)NULL, 10);

        /* Send to all actor queues */
        xQueueSend(
            this->agent1_q,
            ( void * ) &this->agent1,
            ( TickType_t ) 1

        );
        xQueueSend(
            this->agent1_q,
            ( void * ) &this->agent2,
            ( TickType_t ) 1

        );

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
```

### [back to root](/README.md) 
