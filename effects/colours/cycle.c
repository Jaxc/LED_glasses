/*
 * led_off.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */

#include "main.h"
#include "colours.h"

uint16_t hue = 0;


void colour_cycle_new_frame (void) {
    hue = (hue + 2) % 1024;
}

void colour_cycle_gen_data(struct colours *buffer, uint16_t buffer_index) {
    get_colour(buffer, hue, 0xff);
}


