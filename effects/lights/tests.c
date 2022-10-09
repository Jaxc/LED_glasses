/*
 * tests.c
 *
 *  Created on: Dec 28, 2019
 *      Author: jaxc
 */
#include "stdint.h"
#include "adc.h"
#include "pattern_generate.h"

#define UNUSED(X) (void)X

uint32_t pattern_counter;
uint8_t white_level;

/* This test is used to determine if the first LED is affected by the
 * transmission.*/
void test_1_gen_data(uint8_t *buffer, uint16_t buffer_index) {
    if (buffer_index == 0) {
        *buffer = 0x00;
    } else {
        *buffer = 0xff;
    }
}


/* This test is used to verify that the transmission delay is not
 * large enough to be visable to the eye*/
uint8_t test_2_status = 0;

void test_2_new_frame (void) {
    test_2_status = !test_2_status;
}

void test_2_gen_data(uint8_t *buffer, uint16_t buffer_index) {
    UNUSED(buffer_index);
    if (0 == test_2_status) {
        *buffer = 0x00;
    } else {
        *buffer = 0xff;
    }
}

/* This test is used to verify that the columns are working correctly*/
uint8_t active_col = 0;
uint8_t frame_cnt_col = 0;
void test_3_new_frame (void) {
    if (10 == frame_cnt_col) {
        frame_cnt_col = 0;
        if ((N_COLS - 1) == active_col ) {
            active_col = 0;
        } else {
            active_col++;
        }
    } else {
        frame_cnt_col++;
    }
}

void test_3_gen_data(uint8_t *buffer, uint16_t buffer_index) {
    if (active_col == led_pos_cart_x[buffer_index]) {
        *buffer = 0xff;
    } else {
        *buffer = 0x00;
    }
}

/* This test is used to verify that the rows are working correctly*/
uint8_t active_row = 0;
uint8_t frame_cnt_row = 0;
void test_4_new_frame (void) {
    if (10 == frame_cnt_row) {
        frame_cnt_row = 0;
        if ((N_ROWS - 1) == active_row ) {
            active_row = 0;
        } else {
            active_row++;
        }
    } else {
        frame_cnt_row++;
    }
}

void test_4_gen_data(uint8_t *buffer, uint16_t buffer_index) {
    if (active_row == led_pos_cart_y[buffer_index]) {
        *buffer = 0xff;
    } else {
        *buffer = 0x00;
    }
}

/* radius test */
uint32_t test_flow_hue = 0;
void test_5_new_frame (void) {
    test_flow_hue = (test_flow_hue + 20) % 1024;
}

void test_5_gen_data(struct colours *buffer, uint16_t buffer_index) {
    get_colour(buffer, (test_flow_hue + (led_pos_pol_rad[buffer_index] >> 22 )) % 1024, 0xff);
}

/* angle test */
void test_6_new_frame (void) {
    test_flow_hue = (test_flow_hue + 20) % 1024;
}

void test_6_gen_data(struct colours *buffer, uint16_t buffer_index) {
    get_colour(buffer, (test_flow_hue + (led_pos_pol_ang[buffer_index] >> 22 )) % 1024, 0xff);
}

/* colour test */
uint8_t active_colour = 0;
uint8_t frame_cnt_colour = 0;
void test_7_new_frame (void) {

    if (10 == frame_cnt_colour) {
        frame_cnt_colour = 0;
        if ((3 - 1) == active_colour ) {
            active_colour = 0;
        } else {
            active_colour++;
        }
    } else {
        frame_cnt_colour++;
    }

}

void test_7_gen_data(struct colours *buffer, uint16_t buffer_index) {

    UNUSED(buffer_index);

    buffer->red = 0x00;
    buffer->green = 0x00;
    buffer->blue = 0x00;

    if (0 == active_colour ) {
        buffer->red = 0xff;
    } else if (1 == active_colour ) {
        buffer->green = 0xff;
    } else {
        buffer->blue = 0xff;
    }
}

/* Checkerboard pattern */
void test_8_gen_data(uint8_t *buffer, uint16_t buffer_index) {
    if (0 == ((led_pos_cart_x[buffer_index] % 2) ^ ((led_pos_cart_y[buffer_index] % 2)))) {
        *buffer = 0x00;
    } else {
        *buffer = 0xff;
    }
}

/* Colour gradient */

void test_9_gen_data(struct colours *buffer, uint16_t buffer_index) {

    get_colour(buffer, (buffer_index * 12) % 1024, 0xff);
}

/* Microphone test */
uint32_t current_power = 0;
void test_10_new_frame (void) {
    current_power = get_audio_power();

}

void test_10_gen_data(uint8_t *buffer, uint16_t buffer_index) {

    if((current_power >> 15) > buffer_index) {
        *buffer = 0xff;
    } else {
        *buffer = 0x00;
    }
}

/* Microphone test 2 */
uint16_t vu_power = 0;
void test_11_new_frame (void) {
    current_power = get_audio_power();

    vu_power = (current_power >> 28);

}

void test_11_gen_data(uint8_t *buffer, uint16_t buffer_index) {

    if (0 == led_pos_eye(buffer_index)) {
        if(vu_power > led_pos_cart_x[buffer_index]) {
            *buffer = 0xff;
        } else {
            *buffer = 0x00;
        }
    } else {
        if((vu_power >> 3) > (7 - led_pos_cart_x[buffer_index])) {
            *buffer = 0xff;
        } else {
            *buffer = 0x00;
        }
    }
}

/* Order test: test which order LEDs are addressed */

static uint32_t test_12_current_led = 0;
void test_12_new_frame (void) {
    test_12_current_led = (test_12_current_led + 1) % N_LEDS;
}


void test_12_gen_data(uint8_t *buffer, uint16_t buffer_index) {
    

    if (test_12_current_led == buffer_index) {
        *buffer = 0xff;
    } else {
        *buffer = 0x00;
    }
}
