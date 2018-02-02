

#include "A_exception_handler.h"
#include "mainStateMachine.h"

#include "A_LCD.h"
#include "alarmLogic.h"
#include "utilities.h"

uint8 LCD_EN_2 = 0;

static uint32 lcd_cnt = 0;

void setError(uint8 val){

        char s[20];
        char stateString[20];

        switch(val){

            case ERR_VT_HIGH:
                sprintf(s, "A2_1"); //ERR VT_HIGH
                break;
            case ERR_VT_LOW:
                sprintf(s, "A2_2"); //ERR VT_LOW
                break;
            case ERR_CT_HIGH:
                sprintf(s, "A2_3"); //ERR CT_HIGH
                break;
            case ERR_CT_LOW:
                sprintf(s, "A2_4"); //ERR CT_LOW
                break;

            default:
                sprintf(s, "OK"); //No Active Alarms
              return;
        }

        switch(state){

            case UNLOCKED:
                sprintf(stateString, "UNLOCKED"); //WARN VT_HIGH
                break;
            case STANDBY:
                sprintf(stateString, "STANDBY"); //WARN VT_LOW
                break;
            case PRECHARGE:
                sprintf(stateString, "PRECHARGE"); //WARN CT_HIGH
                break;
            case HIGH_VOLTAGE:
                sprintf(stateString,"HV"); //WARN CT_LOW
                break;
            case RUNNING:
                sprintf(stateString,"RUNNING");
                break;
            case SHUTDOWN:
                sprintf(stateString,"SD");
                break;
            default:
                return;
        }

        if( (((++lcd_cnt) % 10) == 0) ){
        lcdUpdate_2(stateString, s);
        }

    }


void setWarnning(uint8 val){

    char s[20];
    char stateString[20];

           switch(val){

            case WARN_VT_HIGH:
                sprintf(s, "A1_1"); //WARN VT_HIGH
                break;
            case WARN_VT_LOW:
                sprintf(s, "A1_2"); //WARN VT_LOW
                break;
            case WARN_CT_HIGH:
                sprintf(s, "A1_3"); //WARN CT_HIGH
                break;
            case WARN_CT_LOW:
                sprintf(s, "A1_4"); //WARN CT_LOW
                break;

            default:
                sprintf(s, "OK"); //No active warnings
                return; }

        switch(state){

            case UNLOCKED:
                sprintf(stateString, "UNLOCKED"); //WARN VT_HIGH
                break;
            case STANDBY:
                sprintf(stateString, "STANDBY"); //WARN VT_LOW
                break;
            case PRECHARGE:
                sprintf(stateString, "PRECHARGE"); //WARN CT_HIGH
                break;
            case HIGH_VOLTAGE:
                sprintf(stateString,"HV"); //WARN CT_LOW
                break;
            case RUNNING:
                sprintf(stateString,"RUNNIG");
                break;
            default:
                return; }


      if( (((++lcd_cnt) % 10) == 0)){
        lcdUpdate_2(stateString, s);
      }
}
