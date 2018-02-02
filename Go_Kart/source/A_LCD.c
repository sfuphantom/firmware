
/*  PIN MUX
 * RS           0
 * RW           1
 * EN           2
 * BACK_LIGHT   3
 * D4           4
 * D5           5
 * D6           6
 * D7           7
 */


#include "A_LCD.h"
#include "utilities.h"
#include <stdio.h>


uint8 curr_device = LCD_ADDR_1;



uint8 lcdInit(){

    //Useful testing code, only for debugging
    /*i2cSetSlaveAdd(i2cREG1, LCD_ADDR_1);
    i2cSetDirection(i2cREG1, I2C_TRANSMITTER);
    i2cSetCount(i2cREG1, 2);

    i2cSetMode(i2cREG1, I2C_MASTER);
    i2cSetStop(i2cREG1);

    delay(1000);
    i2cSetStart(i2cREG1);

    //delay(10000);
    i2cSendByte(i2cREG1, 0xFF );
    //delay(100000);
    i2cSendByte(i2cREG1, 0xF0 );
    i2cSendByte(i2cREG1, 0xF8 );*/
    //delay(10000);
    //lcdStop();
    //delay(100000);

    //i2cREG1 -> MDR &= ~(1 << 5);

    setDevice(1);

    if(enable_4bit() != 0){

    }

    if( enableDisplay() != 0){

    }

    if( clearScreen() != 0){

    }

    if ( returnHome() != 0){

    }

    if(writeString("LET'S RACE!",11) != 0){

    }


    setDevice(2);

    if(enable_4bit() != 0){

    }

    if( enableDisplay() != 0){

    }

    if( clearScreen() != 0){

    }

    if ( returnHome() != 0){

    }

    if(writeString("Powered By",10) != 0){

    }

    if( setPos(2, 0) != 0){

    }

    if(writeString("SFU PHANTOM", 11) != 0){

    }


    fxTimerDelay(3);

    lcd_en = 1;

    return 0;


}



void setDevice(uint8 val){

    curr_device = (val == 1) ? LCD_ADDR_1 : LCD_ADDR_2;

}



uint8 detectRelease(){

    uint32 max_loop = 20;

    uint32 cnt = max_loop;

    //MAX_LOOP_STOP

    while(i2cIsBusBusy(i2cREG1) == true){
        if (--cnt  == 3){
            return 1;
        }

    }

    cnt = max_loop;

    while(i2cIsStopDetected(i2cREG1) == 0){
        if (--cnt  == 3){
            return 1;
        }
    }

    i2cClearSCD(i2cREG1);

    return 0;
}






/*
i2cSetSlaveAdd(i2cREG1, addr);
i2cSetDirection(i2cREG1, I2C_TRANSMITTER);
i2cSetMode(i2cREG1, I2C_MASTER);*/



uint8 writeString(char *str, uint8 num){

    i2cSetSlaveAdd(i2cREG1, curr_device );
    i2cSetDirection(i2cREG1, I2C_TRANSMITTER);
    i2cSetMode(i2cREG1, I2C_MASTER);

    i2cSetCount(i2cREG1, num * 4);
    i2cSetStop(i2cREG1);

    delay(500);
    i2cSetStart(i2cREG1);

    int i;
    for(i = 0; i < num; ++i){

        if( writeChar(str[i]) != 0 ){
            return 1;
        }


    }


    delay(DELAY_CMD);
    delay(DELAY_CMD);

    if(detectRelease() != 0 ){
        return 1;
    }



    return 0;

}



uint8 enable_4bit(){

    i2cSetSlaveAdd(i2cREG1, curr_device );
    i2cSetDirection(i2cREG1, I2C_TRANSMITTER);
    i2cSetMode(i2cREG1, I2C_MASTER);

    i2cSetCount(i2cREG1, 5);
    i2cSetStop(i2cREG1);

    delay(500);

    i2cSetStart(i2cREG1);

    if( m_i2cSendByte(i2cREG1, 0x3C ) != 0 ){
        return 1;
    }
    delay(DELAY_CMD);
    if( m_i2cSendByte(i2cREG1, 0x3C ) != 0 ){
        return 1;
    }
    delay(DELAY_CMD);
    if ( m_i2cSendByte(i2cREG1, 0x3C ) != 0 ){
        return 1;
    }
    delay(DELAY_CMD);

    if ( m_i2cSendByte(i2cREG1, 0x2C ) != 0 ){
        return 1;
    }
    delay(DELAY_CMD);
    if ( m_i2cSendByte(i2cREG1, RESET ) != 0 ){
        return 1;
    }

    delay(DELAY_CMD);
    delay(DELAY_CMD);

    if(detectRelease() != 0 ){
        return 1;
    }

    return 0;
}







uint8 enableDisplay(){

    writeCommand(0x0C);
    writeCommand(0x2C);

    return 0;
    //return  writeCommand(0x0C) || writeCommand(0x2C);

}


uint8 clearScreen(){

    return writeCommand(0x01);

}
uint8 returnHome(){

    return writeCommand(0x02);

}



uint8 setPos(uint8 line, uint8 pos){

    uint8 data = (line == 1) ? (ADDR_LINE1 + pos) : (ADDR_LINE2 + pos);

    return writeCommand( 0x80 | (data & 0x7F) );

}











static void delay(uint32 val){
    for( ; val >= 2; --val);
}


static uint8 writeChar(uint8 c){


    uint8 data1 = (c & 0xF0) | 0x0D;
    uint8 data2 = ((c & 0x0F)<< 4U) | 0x0D;


    if ( m_i2cSendByte(i2cREG1, data1 ) != 0){
        return 1;
    }
    delay(DELAY_DATA);

    if( m_i2cSendByte(i2cREG1, RESET ) != 0 ){
        return 1;
    }
    delay(DELAY_DATA);

    if(m_i2cSendByte(i2cREG1, data2 ) != 0){
        return 1;
    }
    delay(DELAY_DATA);

    if (m_i2cSendByte(i2cREG1, RESET ) != 0){
        return 1;
    }
    delay(DELAY_DATA);

    return 0;

}

static uint8 writeCommand(uint8 cmd){

    i2cSetSlaveAdd(i2cREG1, curr_device );
    i2cSetDirection(i2cREG1, I2C_TRANSMITTER);
    i2cSetMode(i2cREG1, I2C_MASTER);

    i2cSetCount(i2cREG1, 4);
    i2cSetStop(i2cREG1);

    delay(5000);

    i2cSetStart(i2cREG1);


    uint8 data1 = (cmd & 0xF0) | 0x0C;
    uint8 data2 = ((cmd & 0x0F)<< 4U) | 0x0C;

    if( m_i2cSendByte(i2cREG1, data1 ) != 0){
        return 1;
    }
    delay(DELAY_CMD);
    if ( m_i2cSendByte(i2cREG1, RESET ) != 0){
        return 1;
    }
    delay(DELAY_CMD);
    if ( m_i2cSendByte(i2cREG1, data2 ) != 0 ){
        return 1;
    }
    delay(DELAY_CMD);
    if( m_i2cSendByte(i2cREG1, RESET ) != 0){
        return 1;
    }
    delay(DELAY_CMD);
    delay(DELAY_CMD);

    if(detectRelease() != 0 ){
        return 1;
    }

    return 0;

}














