/*
 * led_on.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */

#include "pattern_generate.h"


void lights_led_on_gen_frame (uint8_t buffer[FRAME_SIZE])  {
    for (uint16_t current_led = 0; current_led < N_LEDS; current_led += 1) {
        buffer[current_led] = 255; /* Full light */
    }
}

