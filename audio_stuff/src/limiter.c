/*
 * limiter.c
 *
 *  Created on: Jan 9, 2020
 *      Author: jaxc
 */


#include "limiter.h"

uint32_t max_power = 0;

uint32_t calculate_max (uint32_t *new_power)
{
    //uint32_t max_power = 0;
    if (*new_power > max_power) {
        max_power = *new_power;
    } else {
        *new_power = (((uint64_t)*new_power) * UINT32_MAX) / max_power;
        max_power = max_power - 0X80;
    }

    //max_power_div = 1/max_power;

    return max_power;
}
