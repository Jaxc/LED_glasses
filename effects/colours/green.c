/*
 * green.c
 *
 *  Created on: Jan 10, 2020
 *      Author: jaxc
 */

#include "colours_palette.h"
#include "pattern_generate.h"


void colour_green_gen_frame(uint8_t buffer[FRAME_SIZE]) {
    for (uint16_t i = 0; i < FRAME_SIZE; i += 3) {
        buffer[i] = 0xff; /* Green value */
        buffer[i+1] = 0x00; /* Red value */
        buffer[i+2] = 0x00; /* Blue value */
    }

}
