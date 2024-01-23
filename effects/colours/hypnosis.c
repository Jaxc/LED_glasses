/*
 * hypnosis.c
 *
 *  Created on: Dec 29, 2019
 *      Author: jaxc
 */

#include "colours_palette.h"
#include "pattern_generate.h"

uint32_t hypnosis_flow_hue __attribute__ ((section(".ccmram"))) = 0;

void colour_hypnosis_gen_frame (uint8_t buffer[FRAME_SIZE]) {
    hypnosis_flow_hue = (hypnosis_flow_hue + 10 ) % 1024;

    uint16_t current_led = 0;
    for (uint16_t i = 0; i < FRAME_SIZE; i += 3) {
        struct colours pixel_hue;
        get_colour(&pixel_hue, (hypnosis_flow_hue + (led_pos_pol_rad[current_led] >> 6 )) % 1024, 0xff);
        /* example */
        buffer[i] = pixel_hue.green; /* Green value */
        buffer[i+1] = pixel_hue.red; /* Red value */
        buffer[i+2] = pixel_hue.blue; /* Blue value */

        current_led++;
    }
}

