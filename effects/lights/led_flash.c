/*
 * whiteflash.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */
#include "main.h"

uint32_t flash_pattern_counter;
uint8_t flash_white_level;

void lights_flash_new_frame (void) {
    if (flash_pattern_counter == 0) {
        flash_pattern_counter = 0;
        flash_white_level = 0;
    } else {
        flash_white_level = flash_pattern_counter;
        flash_pattern_counter += 1;
    }
}

void lights_flash_gen_data(uint8_t *buffer, uint16_t buffer_index) {
    UNUSED(buffer_index);
    *buffer = flash_white_level;
}

void lights_flash_beat_start (void) {
    flash_pattern_counter = 31;
}
