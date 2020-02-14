/*
 * temperature.h
 *
 *  Created on: Feb 6, 2020
 *      Author: yashv
 */

#ifndef _TEMPERATURE_H_
#define _TEMPERATURE_H_

#include<stdio.h>
#include<stdbool.h>
#define MAX_ELEMENTS 81

struct temperatureConverter
{
    int temperature;
    float resistance;
};
struct temperatureConverter test[MAX_ELEMENTS];
int getTemperature(struct temperatureConverter aTempConvertertest);
int getResistance(struct temperatureConverter aTempConvertertest);
float getResistanceFromVoltage(float voltage);
int DoCalculation(float inputVoltage);
void InitializeTemperature();

#endif /* SOURCE_TEMPERATURE_H_ */
