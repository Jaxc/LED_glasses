/*
 * decimation.c
 *
 *  Created on: Feb 24, 2019
 *      Author: jaxc
 */

#include "main.h"

uint32_t filtered_buffer[WINDOWSIZE] = {0};
uint32_t decimated_buffer[WINDOWSIZE/32] = {0};

void handle_samples ( uint32_t *i2s_buffer[WINDOWSIZE]) {
    uint32_t count = 0;
    for(uint16_t i; i < WINDOWSIZE; i++) {
        current_word = i2s_buffer[i];
        while (current_word)
        {
          current_word &= (current_word - 1) ;
          count++;
        }
    }
    decimation_filter(i2s_buffer, &filtered_buffer);
    for (uint16_i = 0; i < WINDOWSIZE / 32; i ++) {
        decimated_buffer[i] = filtered_buffer[ i << 5 ];
    }
}
