/*
 * temperature_yash.c
 *
 *  Created on: Feb 18, 2020
 *      Author: JASKANWAL SINGH
 */
#include <temperature_yash.h>

/*int getTemperature(struct temperatureConverter aTempConvertertest);
int getResistance(struct temperatureConverter aTempConvertertest);
float getResistanceFromVoltage(float voltage);
*/

int getTemperature(struct temperatureConverter aTempConvertertest)
{
    return aTempConvertertest.temperature;
}

int getResistance(struct temperatureConverter aTempConvertertest)
{
    return aTempConvertertest.resistance;
}

float getResistanceFromVoltage(float voltage)
{
    float resistance = (voltage *7500)/(3.3 - voltage);
    return resistance;
}

void InitializeTemperature()
{
    int i = 0;
    //struct temperatureConverter test[MAX_ELEMENTS];
      int temperature[MAX_ELEMENTS] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,
                                        22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
                                        41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,
                                        60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80};

        float resistance[] = {29490, 28160, 26890,25690, 24540, 23460, 22430, 21440,
                                        20510, 19620, 18780, 17980, 17210, 16480, 15790, 15130,
                                        14500, 13900, 13330, 12780, 12260, 11770, 11290, 10840,
                                        10410, 10000, 9602, 9226, 8866, 8522, 8194, 7879, 7579,
                                        7291, 7016, 6752, 6500, 6258, 6027, 5805, 5592, 5389,
                                        5194, 5007, 4827, 4655, 4490, 4331, 4179, 4033, 3893,
                                        3758, 3629, 3505, 3385, 3271, 3160, 3054, 2952, 2854,
                                        2760, 2669, 2582, 2498, 2417, 2339, 2264, 2191, 2122,
                                        2055, 1990, 1928, 1868, 1810, 1754, 1700, 1648, 1598,
                                        1550, 1503, 1458};

        for(i = 0; i < MAX_ELEMENTS; i++)
        {
                test[i].temperature = temperature[i];
                test[i].resistance  = resistance[i];
        }

}
int DoCalculation(float inputVoltage){
    int i = 0;
    float inputResistance = 0.0;


//    for(i = 0; i < MAX_ELEMENTS; i++)
//    {
//         printf("%d",test[i].temperature);
//         printf(":");
//         printf("%f",test[i].resistance);
//         printf("\n");
//    }

    // Find the temperature
    while(inputVoltage != - 1 )
    {
        bool loop = false;
        // printf("\nEnter resistance:\t");
        // scanf("%d", &inputResistance);

//        printf("\nEnter voltage:\t");
//        scanf("%f", &inputVoltage);

        inputResistance = getResistanceFromVoltage(inputVoltage);
//        printf("resistance: ");
//        printf("%f\n", inputResistance);

        if(inputResistance > test[0].resistance)            // temperature is below zero degrees
           return -1;

        else if(inputResistance < test[MAX_ELEMENTS-1].resistance) // temperature is above 81 degrees
            return 82;

        else{
            for(i = 0; i < MAX_ELEMENTS; i++)
            {
                if(test[i].resistance == inputResistance){
                    loop =  true;
                    return test[i].temperature;
                }
            }

            for(i = 0; i < MAX_ELEMENTS; i++)
            {

                    if(loop == false){
                        if(i+1 != MAX_ELEMENTS){
                            if(test[i].resistance > inputResistance && test[i+1].resistance < inputResistance){
                                loop =  true;
                                return test[i+1].temperature;

                            }
                        }
                }
            }
        }
    }

}



