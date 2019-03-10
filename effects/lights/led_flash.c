/*
 * whiteflash.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */
#include "main.h"

uint32_t pattern_counter;
uint8_t white_level;

void lights_flash_new_frame (void) {
    if (pattern_counter == 0) {
        pattern_counter = 0;
        white_level = 0;
    } else {
        white_level = pattern_counter;
        pattern_counter += 1;
    }
}

void lights_flash_gen_data(uint8_t *buffer, uint16_t buffer_index) {
    *buffer = white_level;
}

void lights_flash_beat_start (void) {
    pattern_counter = 31;
}

void lights_flash_beat_stop (void) {

}
