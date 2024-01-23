/*
 * flowing_hue.c
 *
 *  Created on: Mar 10, 2019
 *  Author: jaxc
 */
#include "colours_palette.h"
#include "pattern_generate.h"

uint32_t flow_hue  __attribute__ ((section(".ccmram"))) = 0;

void colour_flowing_hue_gen_frame (uint8_t *buffer) {
    flow_hue = (flow_hue + 10) % 1024;


    uint16_t current_led = 0;
    for (uint16_t i = 0; i < FRAME_SIZE; i += 3) {
        struct colours pixel_hue;
        if(led_pos_eye(current_led)){
            get_colour(&pixel_hue, (flow_hue - (((16 - led_pos_cart_x[current_led]) - led_pos_cart_y[current_led] ) << 7)) % 1024, 0xff);
        } else {
            get_colour(&pixel_hue, (flow_hue + ((led_pos_cart_x[current_led] + led_pos_cart_y[current_led]) << 7)) % 1024, 0xff);
        }

        buffer[i] = pixel_hue.green;
        buffer[i+1] = pixel_hue.red;
        buffer[i+2] = pixel_hue.blue;

        current_led++;
    }

}