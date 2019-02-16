/*
 * strobe.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */

#include "main.h"

uint32_t pattern_counter;
uint8_t white_level;

void lights_strobe_new_frame (void) {
    if (pattern_counter > 4) {
        pattern_counter = 0;
    } else {
        pattern_counter += 1;
    }
}

void lights_strobe_gen_data(uint8_t *buffer, uint16_t buffer_index){
    if (pattern_counter == 0) {
        *buffer = 0xff;
    } else {
        *buffer = 0x00;
    }
}



