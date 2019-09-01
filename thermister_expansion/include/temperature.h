/*
 * temperature.h
 *
 *  Created on: Aug 31, 2019
 *      Author: junaidkhan
 */

#ifndef INCLUDE_TEMPERATURE_H_
#define INCLUDE_TEMPERATURE_H_

#include <stdint.h>
#include <stddef.h>

typedef struct{
    uint16_t size;
    uint16_t adc_values[12];
    uint16_t currentIndex;
    uint16_t channel_address[12];
    uint16_t temperature_value[12];
}temperature_t;


uint16_t    temperature_init(temperature_t* th, uint16_t size);
uint16_t    calculate_temperature(temperature_t* th, void* data, uint16_t len);
uint32_t    parsed_data(uint16_t adc_value, uint16_t* channel_address, uint16_t* );
uint16_t    parse_address(const uint16_t* data);
uint16_t    parse_temperature(const uint16_t* data);

#endif /* INCLUDE_TEMPERATURE_H_ */
