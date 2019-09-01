/*
 * temperature.h
 *
 *  Created on: Aug 31, 2019
 *      Author: junaidkhan
 */

#ifndef INCLUDE_TEMPERATURE_BUFF_H_
#define INCLUDE_TEMPERATURE_BUFF_H_

#include <stdint.h>
#include <stddef.h>
#include <string.h>

typedef struct{

    uint16_t *RxData_Buff;          /*!< Pointer to buffer data.
                                            Buffer is considered initialized when `buff != NULL` and `size > 0` */
    uint16_t size;                    /*!< Size of buffer data. Size of actual buffer is `1` byte less than value holds */
    uint16_t processed;               /*!< Next read pointer. Buffer is considered empty when `r == w` and full when `w == r - 1` */
    uint16_t unprocessed;             /*!< Next write pointer. Buffer is considered empty when `r == w` and full when `w == r - 1` */

}temperature_buff_t;

uint16_t buff_init(temperature_buff_t *temperature_buff, void* buffdata, uint16_t buff_size);

uint16_t buff_write(temperature_buff_t* buff, const void* buffdata, uint16_t buff_size);

uint16_t buff_get_free(temperature_buff_t* buff);

uint16_t buff_get_full(temperature_buff_t* buff);

uint16_t buff_read(temperature_buff_t* buff, void* buffdata, uint16_t itr); // itr = #of indexes to read


#endif /* INCLUDE_TEMPERATURE_BUFF_H_ */
