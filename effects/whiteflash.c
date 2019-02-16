/*
 * whiteflash.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */
#include "main.h"

uint32_t pattern_counter;
uint8_t white_level;

void white_flash_new_frame (void) {
    if (pattern_counter > 64) {
        pattern_counter = 0;
        white_level = 0;
    } else if (pattern_counter > 32){
        white_level = 64 - pattern_counter;
        pattern_counter += 1;
    } else {
        white_level = pattern_counter;
        pattern_counter += 1;
    }
}

void white_flash_gen_data(uint8_t buffer[4]) {
    buffer[0] = 0xff;
    buffer[1] = white_level << 3;
    buffer[2] = white_level << 3;
    buffer[3] = white_level << 3;
}
