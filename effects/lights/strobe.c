/*
 * strobe.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */

#include "main.h"

uint32_t pattern_counter;
uint8_t white_level;
uint8_t strobe_active = 0;

void lights_strobe_new_frame (void) {
    if (strobe_active > 0) {
        --strobe_active;
    }
}

void lights_strobe_gen_data(uint8_t *buffer, uint16_t buffer_index){
    UNUSED(buffer_index);
    if ( (strobe_active % 2) != 0) {
        *buffer = 0xff;
    } else {
        *buffer = 0x00;
    }
}

void lights_strobe_beat_start(void) {
    strobe_active = 5;
    return;
}

void lights_strobe_beat_stop(void) {
    return;
}
