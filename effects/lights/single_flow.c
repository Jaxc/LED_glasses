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

#define SNAKE_LEN 7

void lights_single_flow_new_frame (void) {

}

void lights_single_flow_gen_data(uint8_t *buffer, uint16_t buffer_index) {
    *buffer = 0x00;
    for (uint16_t i = 0; i < SNAKE_LEN; ++i) {
        if ((buffer_index + i) % (N_LEDS >> 1) == single_flow_active_led) {
            *buffer = 0xff;
        }
    }
}


void lights_single_flow_beat_start(void) {
    single_flow_active_led = (single_flow_active_led + 1) % (N_LEDS >> 1);
}

void lights_single_flow_beat_stop(void) {

}

