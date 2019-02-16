/*
 * single_flow.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */

#include "main.h"
#include "pattern_generate.h"

uint32_t single_flow_pattern_counter;
uint16_t single_flow_active_led;

void lights_single_flow_new_frame (void) {
    if (single_flow_pattern_counter > 4) {
        single_flow_pattern_counter = 0;
        single_flow_active_led = (single_flow_active_led + 1) % N_LEDS;

    } else {
        single_flow_pattern_counter += 1;
    }
}

void lights_single_flow_gen_data(uint8_t *buffer, uint16_t buffer_index) {
    if (buffer_index - 1 == single_flow_active_led) {
        *buffer = 0xff;
    } else {
        *buffer = 0x00;
    }
}






