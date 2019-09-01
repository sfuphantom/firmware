/*
 * temperature_buff.c
 *
 *  Created on: Aug 31, 2019
 *      Author: junaidkhan
 */


/*
 * Change later : w = written to the buffer i.e. processed
 *                r = read but not written to the buffer i.e. unprocessed
 *
 */
#include <temperature_buff.h>

#define BUF_MIN(x, y)                   ((x) < (y) ? (x) : (y))

// Make sure size is multiplied by 2 - because size_t is in One-Byte; We have 16 bits so Two-bytes
uint16_t
buff_init(temperature_buff_t *temperature_buff, void* buffdata, uint16_t buff_size){


    if (buff_size == 0) {
                return 0;
            }

            temperature_buff->size = buff_size;
            temperature_buff->RxData_Buff = buffdata;


            return 1;
}

uint16_t buff_get_free(temperature_buff_t* buff){
            uint16_t size, w, r;

            if (buff->size == 0) {
                return 0;
            }

            /* Use temporary values in case they are changed during operations */
            w = buff->processed;
            r = buff->unprocessed;
            if (w == r) {
                size = buff->size;
            } else if (r > w) {
                size = r - w;
            } else {
                size = buff->size - (w - r);
            }

            /* Buffer free size */
            return size;
}

uint16_t
buff_write(temperature_buff_t* buff, const void* buffdata, uint16_t buff_size){

            uint16_t tocopy, free;
            const uint16_t* d = buffdata;

            if (buff_size == 0) {
                      return 0;
             }


            /* Calculate maximum number of bytes available to write */
            free = buff_get_free(buff);
            buff_size = BUF_MIN(free, buff_size);
            if (buff_size == 0) {
                return 0;
            }

            /* Step 1: Write data to linear part of buffer */
            tocopy = BUF_MIN(buff->size - buff->processed, buff_size);
            uint16_t i;
            uint16_t startIndex =  buff->processed;
            for(i=0; i<tocopy;i++)
            {
                buff->RxData_Buff[startIndex++] = d[i];
            }

            buff->processed += tocopy;
            buff_size -= tocopy;

            /* Step 2: Write data to beginning of buffer (overflow part) */
            if (buff_size > 0) {
                uint16_t j;
                startIndex = 0;
                for (j=0; j<buff_size; j++)
                {
                    buff->RxData_Buff[startIndex++] = d[tocopy++];
                }
                buff->processed = buff_size;
            }

            if (buff->processed >= buff->size) {
                buff->processed = 0;
            }
            return tocopy + buff_size;
}



uint16_t
buff_get_full(temperature_buff_t* buff){
           uint16_t w, r, size;

           if (buff->size == 0) {
                         return 0;
            }
           /* Use temporary values in case they are changed during operations */
           w = buff->processed;
           r = buff->unprocessed;
           if (w == r) {
               size = 0;
           } else if (w > r) {
               size = w - r;
           } else {
               size = buff->size - (r - w);
           }
           return size;
}


uint16_t
buff_read(temperature_buff_t* buff, void* buffdata, uint16_t itr) {         //itr = #of indexes to read

           uint16_t tocopy, full;
           uint8_t *d = buffdata;

           if (buff->size == 0) {
               return 0;
           }

           /* Calculate maximum number of bytes available to read */
           full = buff_get_full(buff);
           itr = BUF_MIN(full, itr);
           if (itr == 0) {
               return 0;
           }

           /* Step 1: Read data from linear part of buffer */
           tocopy = BUF_MIN(buff->size - buff->unprocessed, itr);

           uint16_t i;
           uint16_t startIndex =  buff->unprocessed;
           for(i=0; i<tocopy;i++)
           {
              d[i] = buff->RxData_Buff[startIndex++];
           }
           buff->unprocessed += tocopy;
           itr -= tocopy;


           /* Step 2: Read data from beginning of buffer (overflow part) */
           if (itr > 0) {

               uint16_t j;
               for (j=0; j<itr; j++)
               {
                   d[tocopy++] = buff->RxData_Buff[j];
               }
               buff->unprocessed = itr;
           }

           /* Step 3: Check end of buffer */
           if (buff->unprocessed >= buff->size) {
               buff->unprocessed = 0;
           }
           return tocopy + itr;
}

