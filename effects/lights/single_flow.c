/*
 * single_flow.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */

#include "pattern_generate.h"

uint32_t single_flow_pattern_counter __attribute__ ((section(".ccmram")));
uint16_t single_flow_active_led __attribute__ ((section(".ccmram")));

#define SNAKE_LEN 7

void lights_single_flow_gen_frame(uint8_t buffer[N_LEDS]) {
    for (uint16_t current_led = 0; current_led < N_LEDS; current_led += 1) {

        buffer[current_led] = 0x00;
        for (uint16_t i = 0; i < SNAKE_LEN; ++i) {
            if ((current_led + i) % (N_LEDS >> 1) == single_flow_active_led) {
                buffer[current_led] = 0xff;
            }
        }

    }
}


void lights_single_flow_beat_start(void) {
    single_flow_active_led = (single_flow_active_led + 1) % (N_LEDS >> 1);
}
