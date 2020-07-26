/*
 * flowing_hue.c
 *
 *  Created on: Mar 10, 2019
 *  Author: jaxc
 */
#include "../../Inc/colours_palette.h"
#include "main.h"
#include "led_position.h"

uint32_t flow_hue = 0;

void colour_flowing_hue_new_frame (void) {
    flow_hue = (flow_hue + 10) % 1024;
}

void colour_flowing_hue_gen_data(struct colours *buffer, uint16_t buffer_index) {
    if(led_pos_eye(buffer_index)){
        get_colour(buffer, (flow_hue - (((16 - led_pos_cart_x[buffer_index]) - led_pos_cart_y[buffer_index] ) << 7)) % 1024, 0xff);
    } else {
        get_colour(buffer, (flow_hue + ((led_pos_cart_x[buffer_index] + led_pos_cart_y[buffer_index]) << 7)) % 1024, 0xff);
    }

}
