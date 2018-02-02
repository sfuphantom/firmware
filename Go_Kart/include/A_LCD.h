

#ifndef A_LCD
#define A_LCD


#include "sys_common.h"
#include "i2c.h"


#define LCD_ADDR_1      0x3F
#define LCD_ADDR_2      0x3B    //A2 to GND, A0,A1 to high

#define ADDR_LINE1      0x00
#define ADDR_LINE2      0x40


#define MAX_CMD         65530
#define DELAY_DATA      5000
#define DELAY_CMD       5000
#define RESET           0x08

#define MAX_LOOP_STOP   10000;







//Function Signature Declaration ------------------------------------
uint8 lcdInit();
void setDevice(uint8 val);
uint8 detectRelease();



uint8 writeString(char *str, uint8 num);


uint8 enable_4bit();
uint8 enableDisplay();
uint8 clearScreen();
uint8 returnHome();
uint8 setPos(uint8 line, uint8 pos);


static void delay(uint32 val);
static uint8 writeChar(uint8 c);
static uint8 writeCommand(uint8 cmd);


#endif
