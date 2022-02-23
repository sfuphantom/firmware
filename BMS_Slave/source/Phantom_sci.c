
#include "sci.h"
#include "string.h"
#include "stdio.h"
#include "hwConfig.h"

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

void UARTprintf(const char *_format, ...)
{
   char str[128];
   int8_t length = -1;

   va_list argList;
   va_start( argList, _format );

   length = vsnprintf(str, sizeof(str), _format, argList);

   va_end( argList );

   if (length > 0)
   {
      sciSend(PC_UART, (unsigned)length, (unsigned char*)str);
   }
}
