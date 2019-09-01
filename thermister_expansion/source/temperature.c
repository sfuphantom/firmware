/*
 * temperature.c
 *
 *  Created on: Aug 31, 2019
 *      Author: junaidkhan
 */

#include <temperature.h>

uint16_t
temperature_init(temperature_t* th,uint16_t size){
    th->size = size;
    th->currentIndex =0;
    return 1;

}


uint16_t
parse_address(const uint16_t* data){

    uint16_t copy = (*data);
    (copy)&=~0x0FFF; /* Clear the Lower 12 bits - Temperature value*/
    (copy)= (copy)>>12U; // Shift the channel address to the right.
    return  (copy);

}
uint16_t
parse_temperature(const uint16_t* data){

    uint16_t copy = (*data);
    (copy)&=~0xF000; /* Clear the upper 4 bits - Channel Address*/
    uint16_t resistance = 10000 * ((4095/(copy)-1));
    return resistance;
}
uint16_t calculate_temperature(temperature_t* th, void* data, uint16_t currentIndex){

    const uint16_t *d = data;
    if(currentIndex>0 && currentIndex<(th->size)){
        th->currentIndex = currentIndex;
        th->adc_values[th->currentIndex] = (*d);
        th->channel_address[currentIndex] = parse_address(d);
        th->temperature_value[currentIndex] = parse_temperature(d);
    }else if(currentIndex==(th->size)){
        currentIndex = 0;
        th->adc_values[th->currentIndex]=(*d);
        th->channel_address[currentIndex] = parse_address(d);
        th->temperature_value[currentIndex] = parse_temperature(d);
    }

    return 1;

}





