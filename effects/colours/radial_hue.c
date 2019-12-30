/*
 * radial_hue.c
 *
 *  Created on: Dec 29, 2019
 *      Author: jaxc
 */

#include "colours.h"
#include "led_position.h"

uint32_t radial_flow_hue = 0;
uint32_t hue_boost = 0;


void colour_radial_hue_new_frame (void) {
    radial_flow_hue = (radial_flow_hue + 20 + hue_boost) % 1024;
    if (0 < hue_boost) {
        hue_boost -= 5;
    }
}

void colour_radial_hue_gen_data(struct colours *buffer, uint16_t buffer_index) {
    get_colour(buffer, (radial_flow_hue + (led_pos_pol_rad[buffer_index] >> 23 )) % 1024, 0xff);
}

void colour_radial_hue_beat_start(void) {
    hue_boost = 20;
    return;
}


