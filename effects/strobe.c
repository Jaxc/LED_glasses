/*
 * strobe.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */

#include "main.h"

uint32_t pattern_counter;
uint8_t white_level;

void strobe_new_frame (void) {
    if (pattern_counter > 4) {
        pattern_counter = 0;
    } else {
        pattern_counter += 1;
    }
}

void strobe_gen_data(uint8_t buffer[4]) {
    if (pattern_counter == 0) {
        buffer[0] = 0xff;
        buffer[1] = 0xff;
        buffer[2] = 0xff;
        buffer[3] = 0xff;
    } else {
        buffer[0] = 0x00;
        buffer[1] = 0x00;
        buffer[2] = 0x00;
        buffer[3] = 0x00;
    }
}



