/*
 * flowing_hue.c
 *
 *  Created on: Mar 10, 2019
 *      Author: jaxc
 */



#include "main.h"
#include "colours.h"
#include "pattern_generate.h"

uint32_t random_hue[N_LEDS] = {0, 43, 85, 128, 171, 213, 256, 299, 341, 384,
        427, 469, 512, 555, 597, 640, 683, 725, 768, 811, 853, 896, 939, 981,
        1024, 1067, 1109, 1152, 1195, 1237, 1280, 1323, 1365, 1408, 1451,
        1493};

void colour_random_offset_hue_new_frame (void) {
    for (uint16_t i = 0; i < N_LEDS; ++i) {
        random_hue[i] = (random_hue[i] + 10) % 1024;
    }

}

void colour_random_offset_hue_gen_data(struct colours *buffer, uint16_t buffer_index) {
 get_colour(buffer, random_hue[buffer_index], 0xff);
}
