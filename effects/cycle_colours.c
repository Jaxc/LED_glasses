/*
 * led_off.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */

#include "main.h"

typedef enum State {
    YELLOW,
    MAGENTA,
    CYAN
} state;


uint8_t red_level = 0;
uint8_t blue_level = 0;
uint8_t green_level = 0xff;
state colour_state = 0;


void cycle_colour_new_frame (void) {
    switch (colour_state) {
        case YELLOW:
            red_level += 1;
            green_level -= 1;
            blue_level = 0;
            if (red_level == 0xff) {
                colour_state = MAGENTA;
            }
            break;
        case MAGENTA:
            red_level -= 1;
            green_level = 0;
            blue_level += 1;
            if (blue_level == 0xff) {
                colour_state = CYAN;
            }
            break;
        case CYAN:
            red_level = 0;
            blue_level -= 1;
            green_level += 1;
            if (green_level == 0xff) {
                colour_state = YELLOW;
            }
            break;

    }
}

void cycle_colour_gen_data(uint8_t buffer[4]) {
    buffer[0] = 0xff;
    buffer[1] = blue_level;
    buffer[2] = green_level;
    buffer[3] = red_level;
}


