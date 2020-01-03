
#include "sci.h"
#include "string.h"

void UARTSend(sciBASE_t *sci, char data[])
{
    char *first = &data[0];
    sciSend(sci, strlen(data),(uint8 *)first);
}

void UARTInit(sciBASE_t *sci, uint32 baud)
{
    sciInit();
    sciSetBaudrate(sci, baud);
}
