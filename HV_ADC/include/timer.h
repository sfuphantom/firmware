/*
 * timers.h
 *
 *  Created on: Apr 26, 2021
 *      Author: Rafael Guevara
 */

//Halcogen Setup
// 1. Enable RTI driver
// 2. Enable appropriate VIM channel (ie look for compare block)
// 3. Set period of compare block

#ifndef TIMERS_TIMERS_H_
#define TIMERS_TIMERS_H_

#include "rti.h"

#define NUM_TIMERS 7 //define more timers here...

/* Variables */

// Timer List Enum
// Indexes of all timers in xTimers array
typedef enum{

    TEST_COMPLETE_TIMER,

    //bse timers
    BSE_SWEEP_TIMER,

    //apps timers
    APPS_SHORT_TIMER,
    APPS_OPEN_TIMER,
    APPS_BSE_ACTIVATED_TIMER,
    APPS_SWEEP_TIMER,

    //hv_vs timers
    HV_VS_SWEEP_TIMER

    //more timers here...

} Timer;

typedef void (*Callbackfunc)(Timer, int); //callback function signature; MUST return void and take Timer and int as parameters

// TimerHandle Struct
typedef struct{

    char* name;

    Callbackfunc callback; //function that executes when timer expires

    int ID; //timer ID; can be used to count cycles

    int period; //timer period in ms

    bool stop; //boolean to start/stop timer

} TimerHandle;

static unsigned long long int ticks; //number of times RTI has expired in ms

static TimerHandle xTimers[NUM_TIMERS]; //array of all timers

/* Function Declarations */

void timerInit();

/* Getters */

int getTimerID(Timer);

int getTimerPeriod(Timer);

uint8_t isBlocked(Timer);

/* Setters */

void xTimerSet(char*, Timer, Callbackfunc, int, int);

void startGlobalTimer();

void stopGlobalTimer();

//test functions
void startAllTimers();

void stopAllTimers();

void startTimer(Timer);

void stopTimer(Timer);

void setTimerID(Timer, int);

void setTimerPeriod(Timer, int);

#endif /* TIMERS_TIMERS_H_ */
