/*
 * temperature_yash.h
 *
 *  Created on: Feb 18, 2020
 *      Author: JASKANWAL SINGH
 */

#ifndef INCLUDE_TEMPERATURE_YASH_H_
#define INCLUDE_TEMPERATURE_YASH_H_

#include<stdio.h>
#include<stdbool.h>
#define MAX_ELEMENTS 81

struct temperatureConverter
{
    int temperature;
    float resistance;
};
struct temperatureConverter test[MAX_ELEMENTS];
int getTemperature(struct temperatureConverter aTempConvertertest);     //shouldn't these be floats
int getResistance(struct temperatureConverter aTempConvertertest);      //shouldn't these be floats
float getResistanceFromVoltage(float voltage);
int DoCalculation(float inputVoltage);
void InitializeTemperature();


#endif /* INCLUDE_TEMPERATURE_YASH_H_ */
