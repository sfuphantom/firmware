# Director Task

This task's internal logic would be most likely to implement the system's state machine. Here, it simply acts upon a single arbitrary condition. Because only one task module exists and that task module determines the suspension of the task, it would not make sense for it to suspend itself since it cannot get itself out of suspension. 

In a bigger project with more than one task, for example an electric race vehicle, you can imagine one module reporting an error in one of the sensors and having the Director suspend the throttleActor, preventing the driver from moving during a fault scenario. Once the fault is cleared, the Director can resume the task.    
```
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
```

### [back to root](/README.md) 