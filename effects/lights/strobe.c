/*
 * strobe.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */

#include "main.h"
#include "led_position.h"

uint8_t strobe_active = 0;

void lights_strobe_gen_frame (uint8_t *buffer) {
    if (strobe_active > 0) {
        --strobe_active;
    }

    for (uint16_t current_led = 0; current_led < N_LEDS; current_led += 1) {
        if ( (strobe_active % 2) != 0) {
            buffer[current_led] = 0xff;
        } else {
            buffer[current_led] = 0x00;
        }
    }
}

void lights_strobe_beat_start(void) {
    strobe_active = 4;
    return;
}

void lights_strobe_beat_stop(void) {
    return;
}
