/*
 * flowing_hue.c
 *
 *  Created on: Mar 10, 2019
 *  Author: jaxc
 */
#include "main.h"
#include "colours.h"

uint32_t flow_hue = 0;

void colour_flowing_hue_new_frame (void) {
    flow_hue = (flow_hue + 10) % 1024;
}

void colour_flowing_hue_gen_data(struct colours *buffer, uint16_t buffer_index) {
    get_colour(buffer, (flow_hue + (buffer_index << 7)) % 1024, 0xff);
}
