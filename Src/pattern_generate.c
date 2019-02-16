/*
 * pattern_generate.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */
#include "main.h"
#include "pattern_generate.h"
#include "spi.h"

uint8_t spi_buffer[2][FRAME_SIZE];
uint8_t active_buffer = 0;
pattern current_pattern = FLASH_WHITE;

uint8_t red_level;
uint8_t blue_level;
uint8_t green_level;


void create_payload(uint8_t buffer[FRAME_SIZE]) {
    uint16_t i = 0;

    buffer[0] = 0;
    buffer[1] = 0;
    buffer[2] = 0;
    buffer[3] = 0;

    for (i = 4;i < N_LEDS * 4 + 4; i += 4) {
        get_current_led(&buffer[i], i >> 2);
        buffer[i] |= 0xe0;
    }
    buffer[i] = 0xff;
    buffer[i+1] = 0xff;
    buffer[i+2] = 0xff;
    buffer[i+3] = 0xff;
}

void tx_led_buffer(void) {
    HAL_SPI_Transmit_DMA(&hspi2, spi_buffer[active_buffer], FRAME_SIZE);
    active_buffer = !active_buffer;
    create_payload(spi_buffer[active_buffer]);
}


void get_current_led(uint8_t buffer[4], uint16_t buffer_index) {
    if (buffer_index == 1) {
        /*i == 1 means that it is the first led of a new frame. */
        pattern_new_frame();
    }
    pattern_gen_data(buffer);
}
