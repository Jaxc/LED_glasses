/*
 * pattern_generate.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */
#include "main.h"
#include "pattern_generate.h"
#include "spi.h"

#include "colours.h"

uint8_t spi_buffer[2][FRAME_SIZE];
uint8_t active_buffer = 0;
#ifdef COMPILE_TESTS
pattern current_effect = 0x4;
#else
pattern current_effect = CYCLE_COLOURS_BEATS;
#endif

struct Presets presets[] = {
#ifdef COMPILE_TESTS
    {
        /* LED_OFF */
        .light_new_frame    = &do_nothing,
        .light_gen_data     = &lights_led_off_gen_data,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,
        .colour_new_frame   = &do_nothing,
        .colour_gen_data    = &colour_white_gen_data,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,
    },
    {
        /* test_1 */
        .light_new_frame    = &do_nothing,
        .light_gen_data     = &test_1_gen_data,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,
        .colour_new_frame   = &do_nothing,
        .colour_gen_data    = &colour_white_gen_data,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,
    },
    {
        /* test_2 */
        .light_new_frame    = &test_2_new_frame,
        .light_gen_data     = &test_2_gen_data,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,
        .colour_new_frame   = &do_nothing,
        .colour_gen_data    = &colour_white_gen_data,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,
    },
    {
        /* test_3 */
        .light_new_frame    = &test_3_new_frame,
        .light_gen_data     = &test_3_gen_data,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,
        .colour_new_frame   = &do_nothing,
        .colour_gen_data    = &colour_white_gen_data,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,
    },
    {
        /* test_4 */
        .light_new_frame    = &test_4_new_frame,
        .light_gen_data     = &test_4_gen_data,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,
        .colour_new_frame   = &do_nothing,
        .colour_gen_data    = &colour_white_gen_data,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,
    },
    {
        /* test_5 */
        .light_new_frame    = &do_nothing,
        .light_gen_data     = &lights_led_on_gen_data,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,
        .colour_new_frame   = &test_5_new_frame,
        .colour_gen_data    = &test_5_gen_data,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,
    },
    {
        /* test_6 */
        .light_new_frame    = &do_nothing,
        .light_gen_data     = &lights_led_on_gen_data,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,
        .colour_new_frame   = &test_6_new_frame,
        .colour_gen_data    = &test_6_gen_data,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,
    },
    {
        /* test_7 */
        .light_new_frame    = &do_nothing,
        .light_gen_data     = &lights_led_on_gen_data,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,
        .colour_new_frame   = &test_7_new_frame,
        .colour_gen_data    = &test_7_gen_data,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,
    },
    {
        /* test_8 */
        .light_new_frame    = &do_nothing,
        .light_gen_data     = &test_8_gen_data,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,
        .colour_new_frame   = &do_nothing,
        .colour_gen_data    = &colour_white_gen_data,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,
    },
    {
        /* test_9 */
        .light_new_frame    = &do_nothing,
        .light_gen_data     = &lights_led_on_gen_data,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,
        .colour_new_frame   = &do_nothing,
        .colour_gen_data    = &test_9_gen_data,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,
    },
#else
    {
        /* LED_OFF */
        .light_new_frame    = &do_nothing,
        .light_gen_data     = &lights_led_off_gen_data,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,
        .colour_new_frame   = &do_nothing,
        .colour_gen_data    = &colour_white_gen_data,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,
    },
    {
        /* FLASH_WHITE */
        .light_new_frame    = &lights_flash_new_frame,
        .light_gen_data     = &lights_flash_gen_data,
        .light_beat_start   = &lights_flash_beat_start,
        .light_beat_stop    = &lights_flash_beat_stop,
        .colour_new_frame   = &colour_white_new_frame,
        .colour_gen_data    = &colour_white_gen_data,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,
    },
    {
        /* CYCLE_COLOURS */
        .ligh    buffer[i]   = 0xff;
        buffer[i+1] = 0xff;
        buffer[i+2] = 0xff;
        buffer[i+3] = 0xff;t_new_frame    = &do_nothing,
        .light_gen_data     = &lights_led_on_gen_data,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,
        .colour_new_frame   = &colour_cycle_new_frame,
        .colour_gen_data    = &colour_cycle_gen_data,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,
    },
    {    buffer[i]   = 0xff;
    buffer[i+1] = 0xff;
    buffer[i+2] = 0xff;
    buffer[i+3] = 0xff;
        /* FLASH_COLOURS */
        .light_new_frame    = &lights_flash_new_frame,
        .light_gen_data     = &lights_flash_gen_data,
        .light_beat_start   = &lights_flash_beat_start,
        .light_beat_stop    = &lights_flash_beat_stop,
        .colour_new_frame   = &colour_cycle_new_frame,
        .colour_gen_data    = &colour_cycle_gen_data,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,
    },
    {
        /* STROBE */
        .light_new_frame    = &lights_strobe_new_frame,
        .light_gen_data     = &lights_strobe_gen_data,
        .light_beat_start   = &lights_strobe_beat_start,
        .light_beat_stop    = &lights_strobe_beat_stop,
        .colour_new_frame   = &colour_white_new_frame,
        .colour_gen_data    = &colour_white_gen_data,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,
    },
    {
        /* SINGLE_FLOW */
        .light_new_frame    = &lights_single_flow_new_frame,
        .light_gen_data     = &lights_single_flow_gen_data,
        .light_beat_start   = &lights_single_flow_beat_start,
        .light_beat_stop    = &lights_single_flow_beat_stop,
        .colour_new_frame   = &colour_flowing_hue_new_frame,
        .colour_gen_data    = &colour_flowing_hue_gen_data,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,
    },
    {
        /* CYCLE_COLOURS_BEATS */
        .light_new_frame    = &do_nothing,
        .light_gen_data     = &lights_led_on_gen_data,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,
        .colour_new_frame   = &colour_cycle_beats_new_frame,
        .colour_gen_data    = &colour_cycle_beats_gen_data,
        .colour_beat_start  = &colour_cycle_beats_beat_start,
        .colour_beat_stop   = &do_nothing,
    },
    {
        /* FLOWING_HUE */
        .light_new_frame    = &do_nothing,
        .light_gen_data     = &lights_led_on_gen_data,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,
        .colour_new_frame   = &colour_flowing_hue_new_frame,
        .colour_gen_data    = &colour_flowing_hue_gen_data,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,
    },
    {
        /* RANDOM_OFFSET_HUE */
        .light_new_frame    = &do_nothing,
        .light_gen_data     = &lights_led_on_gen_data,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,
        .colour_new_frame   = &colour_random_offset_hue_new_frame,
        .colour_gen_data    = &colour_random_offset_hue_gen_data,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,
    },
#endif
};

void create_payload(uint8_t buffer[FRAME_SIZE]) {
    uint16_t i = 0;

    buffer[0] = 0x00;
    buffer[1] = 0x00;
    buffer[2] = 0x00;
    buffer[3] = 0x00;

    presets[current_effect].light_new_frame();
    presets[current_effect].colour_new_frame();

    for (i = 4; i < ((N_LEDS * 4) + 4); i += 4) {
        get_current_led(&buffer[i], (i >> 2) - 1);
        //buffer[i] |= 0xe0;
        buffer[i] = 0xe0 | (buffer[i] >> 4);
    }

    buffer[i]   = 0xff;
    buffer[i+1] = 0xff;
    buffer[i+2] = 0xff;
    buffer[i+3] = 0xff;
    buffer[i+4] = 0xff;
    buffer[i+5] = 0xff;
    buffer[i+6] = 0xff;
    buffer[i+7] = 0xff;
}

void tx_led_buffer(void) {
    HAL_SPI_Transmit_DMA(&hspi2, spi_buffer[active_buffer], FRAME_SIZE);
    active_buffer = !active_buffer;
    create_payload(spi_buffer[active_buffer]);
}

void cycle_effects (void) {
    current_effect += 1;
    if (current_effect >= N_EFFECTS) {
        current_effect = LED_OFF;
    }
}

void get_current_led(uint8_t buffer[4], uint16_t current_led) {
    presets[current_effect].light_gen_data(&buffer[0], current_led);
    struct colours colour = {0};
    presets[current_effect].colour_gen_data(&colour, current_led);
    buffer[0] &= 0x1F;
    buffer[1] = colour.blue;
    buffer[2] = colour.green;
    buffer[3] = colour.red;
}

void beat_start(void) {
    presets[current_effect].light_beat_start();
    presets[current_effect].colour_beat_start();
    return;
}

void beat_stop(void) {
    presets[current_effect].light_beat_stop();
    presets[current_effect].colour_beat_stop();
    return;
}
