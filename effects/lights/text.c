/*
 * text.c
 *
 *  Created on: May 9, 2023
 *      Author: jaxc
 */
#include <stdbool.h>
#include "main.h"
#include "led_position.h"
#include "font_engine.h"

uint8_t display_text[] = "   ZERO AUDIENCE   ";

bool display_matrix[N_COLS][N_ROWS] __attribute__ ((section(".ccmram")));

uint16_t scrolling_char_start = 0;

uint16_t total_length = 0;


void lights_text_new_frame (void) {
    uint16_t current_char = 0;
    uint16_t current_char_col = 0;

    if (total_length == 0) {
        for(uint16_t i = 0; i < sizeof(display_text); i++) {
            total_length += font_data[display_text[i]].length;
        }
    }

    /* I'm not going to figure this out properly, so I'm just counting the already displayed characters.*/
    for(uint16_t i = 0; i < scrolling_char_start; i++) {
        struct font_data_struct active_character = font_data[display_text[current_char]];
        if(active_character.length == current_char_col) {
            current_char++;
            current_char_col = 0;
        } else {
            current_char_col++;
        }
    }


    for(uint16_t i = 0; i < N_COLS; i++) {
        struct font_data_struct active_character = font_data[display_text[current_char]];
        uint16_t current_char_row = 512;
        for(uint16_t j = 0; j < N_ROWS; j++) {
            display_matrix[i][j] = (active_character.data[current_char_col] & current_char_row) != 0;
            current_char_row = current_char_row >> 1;
        }
        if(active_character.length == current_char_col) {
            current_char++;
            current_char_col = 0;
        } else {
            current_char_col++;
        }
    }

}

void lights_text_gen_data(uint8_t *buffer, uint16_t buffer_index){

    if (display_matrix[led_pos_cart_x[buffer_index]][led_pos_cart_y[buffer_index]] == true) {
        *buffer = 0xff;
    } else {
        *buffer = 0x00;
    }
}

void lights_text_beat_start(void) {
    if (total_length == scrolling_char_start) {
        scrolling_char_start = 0;
    } else {
        scrolling_char_start++;
    }

}
