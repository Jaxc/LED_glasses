/*
 * tests.c
 *
 *  Created on: Dec 28, 2019
 *      Author: jaxc
 */
#include "stdint.h"
#include "pattern_generate.h"

#define UNUSED(X) (void)X

uint32_t pattern_counter;
uint8_t white_level;

/* This test is used to determine if the first LED is affected by the
 * transmission.*/
void test_1_gen_frame(uint8_t *buffer) {
    for (uint16_t current_led = 0; current_led < N_LEDS; current_led += 1) {
        if (current_led == 0) {
            buffer[current_led] = 0x00;
        } else {
            buffer[current_led] = 0xff;
        }
    }
}


/* This test is used to verify that the transmission delay is not
 * large enough to be visable to the eye*/
uint8_t test_2_status = 0;

void test_2_gen_frame (uint8_t *buffer) {
    test_2_status = !test_2_status;

    for (uint16_t current_led = 0; current_led < N_LEDS; current_led += 1) {
        if (0 == test_2_status) {
            buffer[current_led] = 0x00;
        } else {
            buffer[current_led] = 0xff;
        }
    }
}

/* This test is used to verify that the columns are working correctly*/
uint8_t active_col = 0;
uint8_t frame_cnt_col = 0;
void test_3_gen_frame (uint8_t buffer[N_LEDS]) {
    if (1 == frame_cnt_col) {
        frame_cnt_col = 0;
        if ((N_COLS - 1) == active_col ) {
            active_col = 0;
        } else {
            active_col++;
        }
    } else {
        frame_cnt_col++;
    }

    for (uint16_t current_led = 0; current_led < N_LEDS; current_led += 1) {
        if (active_col == led_pos_cart_x[current_led]) {
            buffer[current_led] = 0xff;
        } else {
            buffer[current_led] = 0x00;
        }
    }
}

/* This test is used to verify that the rows are working correctly*/
uint8_t active_row = 0;
uint8_t frame_cnt_row = 0;
void test_4_gen_frame (uint8_t buffer[N_LEDS]) {
    if (1 == frame_cnt_row) {
        frame_cnt_row = 0;
        if ((N_ROWS - 1) == active_row ) {
            active_row = 0;
        } else {
            active_row++;
        }
    } else {
        frame_cnt_row++;
    }

    for (uint16_t current_led = 0; current_led < N_LEDS; current_led += 1) {
        if (active_row == led_pos_cart_y[current_led]) {
            buffer[current_led] = 0xff;
        } else {
            buffer[current_led] = 0x00;
        }
    }
}

/* radius test */
uint32_t test_flow_hue = 0;
void test_5_gen_frame (uint8_t buffer[FRAME_SIZE]) {
    test_flow_hue = (test_flow_hue + 20) % 1024;

    uint16_t current_led = 0;
    for (uint16_t i = 0; i < FRAME_SIZE; i += 3) {
        struct colours pixel_hue;
        get_colour(&pixel_hue, (test_flow_hue + (led_pos_pol_rad[current_led] >> 6 )) % 1024, 0xff);

        buffer[i] = pixel_hue.green; /* Green value */
        buffer[i+1] = pixel_hue.red; /* Red value */
        buffer[i+2] = pixel_hue.blue; /* Blue value */

        current_led++;
    }
}


/* angle test */
void test_6_gen_frame (uint8_t buffer[FRAME_SIZE]) {
    test_flow_hue = (test_flow_hue + 20) % 1024;


        uint16_t current_led = 0;
    for (uint16_t i = 0; i < FRAME_SIZE; i += 3) {
        struct colours pixel_hue;
        get_colour(&pixel_hue, (test_flow_hue + (led_pos_pol_ang[current_led] >> 6 )) % 1024, 0xff);

        buffer[i] = pixel_hue.green; /* Green value */
        buffer[i+1] = pixel_hue.red; /* Red value */
        buffer[i+2] = pixel_hue.blue; /* Blue value */

        current_led++;
    }
}

/* colour test */
uint8_t active_colour = 0;
uint8_t frame_cnt_colour = 0;
void test_7_gen_frame (uint8_t buffer[FRAME_SIZE]) {

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

    for (uint16_t i = 0; i < FRAME_SIZE; i += 3) {

        buffer[i] = 0x00;
        buffer[i+1] = 0x00;
        buffer[i+2] = 0x00;

        if (0 == active_colour ) {
            buffer[i+1] = 0xff;
        } else if (1 == active_colour ) {
            buffer[i] = 0xff;
        } else {
            buffer[i+2] = 0xff;
        }
    }

}

/* Checkerboard pattern */
void test_8_gen_frame(uint8_t buffer[N_LEDS]) {

    uint16_t current_led = 0;
    for (uint16_t i = 0; i < N_LEDS; i += 1) {


        if (0 == ((led_pos_cart_x[current_led] % 2) ^ ((led_pos_cart_y[current_led] % 2)))) {
            buffer[i] = 0x00;
        } else {
            buffer[i] = 0xff;
        }

        current_led++;
    }
}

/* Colour gradient */

void test_9_gen_frame(uint8_t *buffer) {
    uint16_t current_led = 0;
    for (uint16_t i = 0; i < FRAME_SIZE; i += 3) {
        struct colours pixel_hue;
        get_colour(&pixel_hue, (current_led * 12) % 1024, 0xff);

        buffer[i] = pixel_hue.green; /* Green value */
        buffer[i+1] = pixel_hue.red; /* Red value */
        buffer[i+2] = pixel_hue.blue; /* Blue value */

        current_led++;
    }

}

/* Microphone test */

uint32_t current_power = 0;
void test_10_gen_frame (void) {
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
void test_11_gen_frame (void) {
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

void test_12_gen_frame(uint8_t buffer[N_LEDS]) {

    test_12_current_led = (test_12_current_led + 1) % N_LEDS;

    for (uint16_t current_led = 0; current_led < N_LEDS; current_led += 1) {
        if (test_12_current_led == current_led) {
            buffer[current_led] = 0xff;
        } else {
            buffer[current_led] = 0x00;
        }
    }
}
