#include "LV_monitor.h"






/* USER CODE END */

int main(void)
{

lv_monitorInit();
while(true){

    uint16_t busVoltage = LV_reading(LV_bus_voltage_register);
    uint16_t current = LV_reading(LV_current_register);


    char buffer3[10];
    uint32 numberofChars3;
    numberofChars3 = ltoa(busVoltage,buffer3);   // here 2 means binary
    sciSend(sciREG,12, (unsigned char*) "bus voltage = ");
    sciSend(sciREG,numberofChars3, (unsigned char*) buffer3);
    sciSend(sciREG,2, (unsigned char*) " ,  ");

    char buffer2[10];
    uint32 numberofChars;
    numberofChars = ltoa(current,buffer2);   // here 2 means binary
    sciSend(sciREG,10, (unsigned char*) "current = ");
    sciSend(sciREG,numberofChars, (unsigned char*) buffer2);
    sciSend(sciREG,2, (unsigned char*) "\r\n");


}


    asm(" nop");
    asm(" nop");
    asm(" nop");

    while(1);

/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
void sciNotification(sciBASE_t *sci, uint32 flags)
{
/*  enter user code between the USER CODE BEGIN and USER CODE END. */
/* USER CODE BEGIN (29) */
    /* Echo received character */
    sciSend(sci, 1,(unsigned char *)&command);
    /* Await further character */
    sciReceive(sci, 1,(unsigned char *)&command);
}
/* USER CODE END */
