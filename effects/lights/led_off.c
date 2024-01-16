/*
 * led_off.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */

#include "pattern_generate.h"

#define UNUSED(X) (void)X

void lights_led_off_gen_frame(uint8_t *buffer, uint16_t buffer_index) {
    for (uint16_t current_led = 0; current_led < N_LEDS; current_led += 1) {
        buffer[current_led] = 0; /* Full light */
    }
}

