/*
 * RTD.c
 *
 *  Created on: Jan 20, 2022
 *      Author: Adam Tinaburri
 *
 * To do check-list
 *      - (DONE) Initialize gio, vim, gio notification
 *      - (DONE) Get Interrupt working
 *      - Integrate with TSAL and brake sensors
 *      -
 */

#include "RTD.h"


void main(void)
{
    RTDInit();

    while(1);
}

void RTDInit(){
    gioInit();

    vimInit();

    gioEnableNotification(gioPORTA, 1);

    _enable_IRQ();
}

bool isBreakPressed() // checks if the break is being pressed
{
    // jay's code, look at his function, can call it so see if the brake sensor is active
    // Check if past a certain threshold to see if active
    return 1;
    return bse_pedal_percent > 30
}

bool TSALstatus() // checks if tractive system is active
{
    // actual function is just a 1 or a 0 for active or not
    return 1; // GIO getBit, 1 - TSAL active, 0 - TSAL not active

    gioGetBit(gioPORTA,)
}

void gioNotification(gioPORT_t *port, uint32 bit)
{
    if(port == gioPORTA && bit == 1){

        if(isBreakPressed() == 1 && TSALstatus() == 1){
            gioToggleBit(gioPORTA, 5); // this would be enabling the throttle and making sound for 2 seconds
            switch_flipped = true
        }
    }else if(stodnw)
    shfe
}

// 1. Ready to drive logic 
// 2.Queue for communicating
// 3. Buzzer logic (Timers)  


void InterruptTask3(){

    while (true)
    {
        yield until any(int_flags are set)

        if(RTD){

            RTD_loigc
        } else if (another_flag){

            another-logic()
        }

        // /executre 

        // start timer
        // yield for 2000ms


        jkdss


        /* code */
    }


}



//reading the throttle
void task1(){

    while(true){

..



        yield 1ms

    }

}

// setting the state of the car
void task2(){

    while(true){

        //

    }

}


