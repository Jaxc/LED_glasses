/*
 * flash_colours.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */


#include "main.h"

typedef enum State {
    YELLOW,
    RED,
    MAGENTA,
    BLUE,
    CYAN,
    GREEN
} state;

uint32_t pattern_counter;
uint8_t flash_white_level;
uint8_t flash_red_level = 0;
uint8_t flash_blue_level = 0;
uint8_t flash_green_level = 0xff;
state flash_colour_state = YELLOW;

void flash_colour_new_frame (void) {
    if (pattern_counter >= 61) {
        pattern_counter = 0;
        flash_white_level = 0;
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
            }
    } else if (pattern_counter >= 31){
        flash_white_level = 62 - pattern_counter;
        pattern_counter += 2;
    } else {
        flash_white_level = pattern_counter;
        pattern_counter += 1;
    }
}

void flash_colour_gen_data(uint8_t buffer[4]) {
    buffer[0] = flash_white_level;
    buffer[1] = flash_blue_level << 3;
    buffer[2] = flash_green_level << 3;
    buffer[3] = flash_red_level << 3;
}

