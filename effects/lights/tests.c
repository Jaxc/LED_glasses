/*
 * tests.c
 *
 *  Created on: Dec 28, 2019
 *      Author: jaxc
 */
#include "main.h"

uint32_t pattern_counter;
uint8_t white_level;

void test_1_new_frame (void) {

}

void test_1_gen_data(uint8_t *buffer, uint16_t buffer_index) {
    if (buffer_index == 0) {
        *buffer = 0x00;
    } else {
        *buffer = 0xff;
    }
}

uint8_t test_2_status = 0;

void test_2_new_frame (void) {
    test_2_status = !test_2_status;
}

void test_2_gen_data(uint8_t *buffer, uint16_t buffer_index) {
    if (0 == test_2_status) {
        *buffer = 0x00;
    } else {
        *buffer = 0xff;
    }
}
