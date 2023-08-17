/*
 * led_off.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */

#include "colours_palette.h"
#include "pattern_generate.h"

uint16_t hue_beats = 0;

void colour_cycle_beats_gen_frame(uint8_t buffer[FRAME_SIZE]) {

    for (uint16_t i = 0; i < FRAME_SIZE; i += 3) {
        struct colours pixel_hue;
        get_colour(&pixel_hue, hue_beats, 0xff);

        buffer[i] = pixel_hue.green; /* Green value */
        buffer[i+1] = pixel_hue.red; /* Red value */
        buffer[i+2] = pixel_hue.blue; /* Blue value */

    }
}

void colour_cycle_beats_beat_start (void) {
    hue_beats = (hue_beats + 128) % 1024;
}
