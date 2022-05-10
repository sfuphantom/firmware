# Simulation Task

```
void vTaskSim(void* pvParams){

    static char py_msg[1];
    static char command[2];
    static char cmp_str[1];

    while(true){

        // read inputs from PC
        sciReceive(PC_UART, 3, py_msg);

        // parse serial command
        split(py_msg, ",", command, 2);

        // distribute values to appropriate pointers
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

        vTaskDelay(pdMS_TO_TICKS(1));
    }
}
```