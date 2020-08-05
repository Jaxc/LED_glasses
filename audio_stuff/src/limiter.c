/*
 * limiter.c
 *
 *  Created on: Jan 9, 2020
 *      Author: jaxc
 */


#include "limiter.h"

uint32_t max_power = 0;
uint32_t power_buffer[256] = {0};
uint16_t power_buffer_pointer = 0;

void calculate_max (uint32_t *new_power)
{
    power_buffer[power_buffer_pointer] = *new_power;
    power_buffer_pointer = (power_buffer_pointer + 1) % 256;
    uint32_t max_power = 0;
    for(uint16_t i = 0; i < 256; i++) {
        if (max_power < power_buffer[i]) {
            max_power = power_buffer[i];
        }
    }
    if (0 != max_power) {
        *new_power = (((uint64_t)*new_power) * UINT32_MAX) / max_power;
    }

    return ;
}
