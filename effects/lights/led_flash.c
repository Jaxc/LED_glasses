/*
 * whiteflash.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */
#include "main.h"
#include "led_position.h"

uint32_t flash_pattern_counter;
uint8_t flash_white_level;

void lights_flash_gen_frame (uint8_t buffer[N_LEDS]) {
    if (flash_pattern_counter == 0) {
        flash_pattern_counter = 0;
        flash_white_level = 0;
    } else {
        flash_white_level = flash_pattern_counter;
        flash_pattern_counter += 1;
    }

    for(uint16_t i = 0; i < N_LEDS; i++) {
        buffer[i] = flash_white_level;
    }
}

void lights_flash_beat_start (void) {
    flash_pattern_counter = 31;
}
