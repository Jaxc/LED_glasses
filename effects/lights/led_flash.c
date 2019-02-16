/*
 * whiteflash.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */
#include "main.h"

uint32_t pattern_counter;
uint8_t white_level;

void lights_flash_new_frame (void) {
    if (pattern_counter >= 61) {
        pattern_counter = 0;
        white_level = 0;
    } else if (pattern_counter >= 31){
        white_level = 62 - pattern_counter;
        pattern_counter += 1;
    } else {
        white_level = pattern_counter;
        pattern_counter += 1;
    }
}

void lights_flash_gen_data(uint8_t *buffer, uint16_t buffer_index) {
    *buffer = white_level;
}
