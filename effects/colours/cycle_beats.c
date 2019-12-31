/*
 * led_off.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */

#include "main.h"
#include "colours.h"

uint16_t hue_beats = 0;

void colour_cycle_beats_gen_data(struct colours *buffer, uint16_t buffer_index) {
    UNUSED(buffer_index);
    get_colour(buffer, hue_beats, 0xff);
}

void colour_cycle_beats_beat_start (void) {
    hue_beats = (hue_beats + 128) % 1024;
}
