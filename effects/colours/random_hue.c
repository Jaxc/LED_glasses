/*
 * flowing_hue.c
 *
 *  Created on: Mar 10, 2019
 *      Author: jaxc
 */



#include "colours_palette.h"
#include "pattern_generate.h"

uint32_t random_seed __attribute__ ((section(".ccmram"))) = 22222;

void colour_random_offset_hue_gen_frame(uint8_t buffer[FRAME_SIZE]) {

    uint16_t current_led = 0;
    for (uint16_t i = 0; i < FRAME_SIZE; i += 3) {
        struct colours pixel_hue;
        uint32_t random_hue = random_seed % 1024;
        random_seed = (random_seed * 196314165) + 907633515;
        get_colour(&pixel_hue, random_hue, 0xff);

        buffer[i] = pixel_hue.green; /* Green value */
        
        buffer[i+1] = pixel_hue.red; /* Red value */
        buffer[i+2] = pixel_hue.blue; /* Blue value */

        current_led++;
    }
}



void colour_random_offset_hue_beat_start (void) {
    for (uint16_t i = 0; i < N_LEDS; ++i) {

    }

}

