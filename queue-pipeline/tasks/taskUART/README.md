# Debugger Task

This task is responsible for processing message requests from other tasks. There are two modes. One mode prints the provided value and the other prints the message at a given index in the following buffer.

It is much more complicated to send strings of variable length through freeRTOS queues while also unifying this mode with  printing a value. This buffer was chosen to simplify the design and make it easier to keep track of the possible messages the system can output. 
```
static const char* MESSAGES[] = {
    
    "foo", // MSG_ONE  
    "bar" // ... 
};
```
```
void vTaskDebugger(void* pvParams){

    static DebugStruct_t data;
    static BaseType_t rx_success = pdFALSE;
    while(1){

        // receieve messages from uart with an id
        rx_success = xQueueReceive(
            rx,
            &data,
            (TickType_t) pdMS_TO_TICKS(10000)

        );
    
       /* failed to receive data; do smt!! */
       if(rx_success == pdFALSE){
           continue;
       }

        if(data.print_val == 1){

            // (int)((ceil(log10(2^32))+1)*sizeof(char)) -stack overflow 
            char number_str[11];
            ltoa(data.data, number_str);

            UARTprintf(number_str);
            UARTprintf("\n");

        } else{

            if(data.data >= MSG_BUFFER_SIZE ){
                continue;
            }
            // print whatever value to the console
            UARTprintf(MESSAGES[data.data]);
            UARTprintf("\n");
        }
    } // superloop
}
```