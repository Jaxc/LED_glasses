/*
 * radial_hue.c
 *
 *  Created on: Dec 29, 2019
 *      Author: jaxc
 */

#include "colours_palette.h"
#include "pattern_generate.h"

uint32_t radial_flow_hue __attribute__ ((section(".ccmram"))) = 0;
uint32_t hue_boost __attribute__ ((section(".ccmram"))) = 0;


void colour_radial_hue_gen_frame (uint8_t *buffer) {
    radial_flow_hue = (radial_flow_hue + 20 + hue_boost) % 1024;
    if (0 < hue_boost) {
        hue_boost -= 5;
    }
    uint16_t current_led = 0;
    for (uint16_t i = 0; i < FRAME_SIZE; i += 3) {
        struct colours pixel_hue;
        get_colour(&pixel_hue, (radial_flow_hue + (led_pos_pol_rad[current_led] >> 7 )) % 1024, 0xff);

        buffer[i] = pixel_hue.green; /* Green value */
        buffer[i+1] = pixel_hue.red; /* Red value */
        buffer[i+2] = pixel_hue.blue; /* Blue value */

        current_led++;
    }
}

void colour_radial_hue_beat_start(void) {
    hue_boost = 20;
    return;
}


