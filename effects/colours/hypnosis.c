/*
 * hypnosis.c
 *
 *  Created on: Dec 29, 2019
 *      Author: jaxc
 */

#include "colours.h"
#include "led_position.h"

uint32_t hypnosis_flow_hue = 0;

void colour_hypnosis_new_frame (void) {
    hypnosis_flow_hue = (hypnosis_flow_hue + 10 ) % 1024;
}

void colour_hypnosis_gen_data(struct colours *buffer, uint16_t buffer_index) {
    get_colour(buffer, (hypnosis_flow_hue + (led_pos_pol_rad[buffer_index] >> 22 )) % 1024, 0xff);
}


