/*
 * flash_colours.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */

#include "stdint.h"

typedef enum State {
    YELLOW,
    RED,
    MAGENTA,
    BLUE,
    CYAN,
    GREEN
} state;

uint32_t colours_pattern_counter __attribute__ ((section(".ccmram")));
uint8_t colours_white_level __attribute__ ((section(".ccmram")));
uint8_t flash_red_level __attribute__ ((section(".ccmram"))) = 0;
uint8_t flash_blue_level __attribute__ ((section(".ccmram"))) = 0;
uint8_t flash_green_level __attribute__ ((section(".ccmram"))) = 0xff;
state flash_colour_state = YELLOW;

void flash_colour_new_frame (void) {
    if (colours_pattern_counter >= 61) {
        colours_pattern_counter = 0;
        colours_white_level = 0;
        flash_red_level = 0;
        flash_blue_level = 0;
        flash_green_level = 0;
        switch (flash_colour_state) {
            case YELLOW:
                flash_red_level = 0xff;
                flash_green_level = 0xff;
                flash_colour_state = RED;
                break;
            case RED:
                flash_red_level = 0xff;
                flash_colour_state = MAGENTA;
                break;
            case MAGENTA:
                flash_red_level = 0xff;
                flash_blue_level = 0xff;
                flash_colour_state = BLUE;
                break;
            case BLUE:
                flash_blue_level = 0xff;
                flash_colour_state = CYAN;
                break;
            case CYAN:
                flash_blue_level = 0xff;
                flash_green_level = 0xff;
                flash_colour_state = GREEN;
                break;
            case GREEN:
                flash_green_level = 0xff;
                flash_colour_state = YELLOW;
                break;
            default:
                break;
            }
    } else if (colours_pattern_counter >= 31){
        colours_white_level = 62 - colours_pattern_counter;
        colours_pattern_counter += 2;
    } else {
        colours_white_level = colours_pattern_counter;
        colours_pattern_counter += 1;
    }
}

void flash_colour_gen_data(uint8_t buffer[4]) {
    buffer[0] = colours_white_level;
    buffer[1] = flash_blue_level << 3;
    buffer[2] = flash_green_level << 3;
    buffer[3] = flash_red_level << 3;
}

