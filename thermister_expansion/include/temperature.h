/*
 * temperature.h
 *
 *  Created on: Feb 6, 2020
 *  Updated on: Mar 3, 2020
 *      Author: YashBhavnani
 */

#ifndef _TEMPERATURE_H_
#define _TEMPERATURE_H_

#include<stdio.h>
#include<stdbool.h>
#define MAX_ELEMENTS 81

struct TemperatureConverter
{
    int temperature;
    float resistance;
};

struct FaultCheck
{
    bool overtemp;
    bool undertemp;
};

struct TemperatureConverter test[MAX_ELEMENTS];
int getTemperature(struct TemperatureConverter aTempConvertertest);
int getResistance(struct TemperatureConverter aTempConvertertest);
float getResistanceFromVoltage(float voltage);
int DoCalculation(float inputVoltage);
void InitializeTemperature();

#endif /* SOURCE_TEMPERATURE_H_ */
