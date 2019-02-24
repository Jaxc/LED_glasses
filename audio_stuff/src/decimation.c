/*
 * decimation.c
 *
 *  Created on: Feb 24, 2019
 *      Author: jaxc
 */

#include "main.h"
#include "i2s.h"
#include "filter.h"

int16_t pre_filtered_buffer[WINDOWSIZE/64] = {0};
int16_t filtered_buffer[WINDOWSIZE/64] = {0};
uint32_t decimated_buffer[WINDOWSIZE/32] = {0};

void handle_samples ( uint16_t *i2s_buffer[WINDOWSIZE]) {

    for(uint16_t i; i < WINDOWSIZE; i++) {
        uint32_t count = 0;
        for(uint16_t j = 0; j < 4; j++) {
            int32_t current_word = *i2s_buffer[(i << 2) + j];
            while (current_word)
            {
              current_word &= (current_word - 1) ;
              count++;
            }
        }
        pre_filtered_buffer[i] = count;
    }
    decimation_filter(&pre_filtered_buffer[0], &filtered_buffer[0], WINDOWSIZE/64);
    for (uint16_t i = 0; i < WINDOWSIZE / 32; i ++) {
        decimated_buffer[i] = filtered_buffer[ i << 5 ];
    }

}

uint32_t get_decimated_signal (uint16_t i) {
    return (uint16_t)decimated_buffer[i];
}
