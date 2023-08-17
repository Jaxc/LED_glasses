/*
 * white.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */

#include "colours_palette.h"
#include "pattern_generate.h"

void colour_white_gen_frame(uint8_t buffer[FRAME_SIZE]) {
    struct colours pixel_hue;
    get_colour(&pixel_hue, 0, 0);
    for (uint16_t i = 0; i < FRAME_SIZE; i += 3) {
        buffer[i] = pixel_hue.green; /* Green value */
        buffer[i+1] = pixel_hue.red; /* Red value */
        buffer[i+2] = pixel_hue.blue; /* Blue value */
    }
}
