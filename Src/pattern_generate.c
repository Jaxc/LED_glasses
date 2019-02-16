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
pattern current_effect = FLASH_WHITE;


void (*effect_new_frame)(void) = &strobe_new_frame;
void (*effect_gen_data)(uint8_t buffer[4]) = &strobe_gen_data;


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

void cycle_effects (void) {
    if (current_effect == N_EFFECTS) {
        current_effect = LED_OFF;
    } else {
        current_effect += 1;
    }
    switch (current_effect) {
        case LED_OFF:
            effect_new_frame = &led_off_new_frame;
            effect_gen_data = &led_off_gen_data;
            break;

        case FLASH_WHITE:
            effect_new_frame= &white_flash_new_frame;
            effect_gen_data = &white_flash_gen_data;
            break;

        case CYCLE_COLOURS:
            effect_new_frame= &white_flash_new_frame;
            effect_gen_data = &white_flash_gen_data;
            break;

        default:
            effect_new_frame = &cycle_colour_new_frame;
            effect_gen_data = &cycle_colour_gen_data;
            break;

    }
}

void get_current_led(uint8_t buffer[4], uint16_t buffer_index) {
    if (buffer_index == 1) {
        /*i == 1 means that it is the first led of a new frame. */
        (effect_new_frame)();
    }
    (effect_gen_data)(buffer);
}
