/*
 * flowing_hue.c
 *
 *  Created on: Mar 10, 2019
 *      Author: jaxc
 */



#include "main.h"
#include "colours.h"
#include "pattern_generate.h"

uint32_t random_hue[N_LEDS] = {0};

uint32_t random = 22222;

void colour_random_offset_hue_beat_start (void) {
    for (uint16_t i = 0; i < N_LEDS; ++i) {
        random_hue[i] = random % 1024;
        random = (random * 196314165) + 907633515;
    }

}

void colour_random_offset_hue_gen_data(struct colours *buffer, uint16_t buffer_index) {
 get_colour(buffer, random_hue[buffer_index], 0xff);
}
