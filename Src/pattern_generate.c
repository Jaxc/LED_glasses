/*
 * pattern_generate.c
 *
 *  Created on: Feb 16, 2019
 *      Author: jaxc
 */

#include "pattern_generate.h"
#include "colour.h"
#include "lights.h"

#define GLOBAL_POWER_RANGE_REDUCTION 2
#define COLOUR_POWER_RANGE_REDUCTION 0

uint8_t light_buffer[N_LEDS] __attribute__ ((section(".ccmram")));
uint8_t led_buffer[FRAME_SIZE];

#ifdef COMPILE_TESTS
pattern current_effect __attribute__ ((section(".ccmram"))) = test_3;
#include "tests.h"
#else
pattern current_effect __attribute__ ((section(".ccmram"))) = RANDOM_OFFSET_HUE;
#endif

const struct Presets presets[N_EFFECTS] = {
#ifdef COMPILE_TESTS
    {
        /* LED_OFF */
        LIGHTS_LED_OFF,
        COLOUR_WHITE
    },
    {
        /* test_1 */
        {.light_gen_frame    = &test_1_gen_frame,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,},
        {.colour_gen_frame   = &colour_white_gen_frame,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,}
    },
    {
        /* test_2 */
        {.light_gen_frame    = &test_2_gen_frame,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,},
        {.colour_gen_frame   = &colour_white_gen_frame,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,}
    },
    {
        /* test_3 */
        {.light_gen_frame    = &test_3_gen_frame,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,},
        {.colour_gen_frame   = &colour_white_gen_frame,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,}
    },
    {
        /* test_4 */
        {.light_gen_frame    = &test_4_gen_frame,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,},
        {.colour_gen_frame   = &colour_white_gen_frame,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,}
    },
    {
        /* test_5 */
        {.light_gen_frame    = &lights_led_on_gen_frame,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,},
        {.colour_gen_frame   = &test_5_gen_frame,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,}
    },
    {
        /* test_6 */
        {.light_gen_frame    = &lights_led_on_gen_frame,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,},
        {.colour_gen_frame   = &test_6_gen_frame,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,}
    },
    {
        /* test_7 */
        {.light_gen_frame    = &lights_led_on_gen_frame,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,},
        {.colour_gen_frame   = &test_7_gen_frame,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,}
    },
    {
        /* test_8 */
        {.light_gen_frame    = &test_8_gen_frame,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,},
        {.colour_gen_frame   = &colour_white_gen_frame,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,}
    },
    {
        /* test_9 */
        {.light_gen_frame    = &lights_led_on_gen_frame,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,},
        {.colour_gen_frame   = &test_9_gen_frame,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,}
    },
# ifdef USE_ADC
    {
        /* test_10 */
        {.light_gen_frame    = &test_10_gen_frame,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,},
        {.colour_gen_frame   = &colour_white_gen_frame,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,}
    },
    {
        /* test_11 */
        {.light_gen_frame    = &test_11_gen_frame,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,},
        {.colour_gen_frame   = &colour_white_gen_frame,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,}
    },
# endif
    {
        /* test_12 */
        {.light_gen_frame    = &test_12_gen_frame,
        .light_beat_start   = &do_nothing,
        .light_beat_stop    = &do_nothing,},
        {.colour_gen_frame   = &colour_white_gen_frame,
        .colour_beat_start  = &do_nothing,
        .colour_beat_stop   = &do_nothing,}
    },
#else
    {
        /* LED_OFF */
        LIGHTS_STROBE,
        COLOUR_FLOWING_HUE
    },
    {
        /* HYPNOSIS */
        LIGHTS_LED_ON,
        COLOUR_HYPNOSIS
    },
    {
        /* CYCLE_COLOURS */
        LIGHTS_LED_ON,
        COLOUR_CYCLE
    },
    {
        /* FLASH_COLOURS */
        LIGHTS_FLASH,
        COLOUR_CYCLE
    },
    {
        /* BEAT_RADIAL_HUE */
        LIGHTS_LED_ON,
        COLOUR_BEAT_RADIAL_HUE
    },  
    {
        /* BEAT_HYPNOSIS */
        LIGHTS_FLASH,
        COLOUR_HYPNOSIS
    },     
    //{
        /* STROBE */
    //    LIGHTS_STROBE,
  //      COLOUR_WHITE
//    },
    {
        /* CYCLE_COLOURS_BEATS */
        LIGHTS_LED_ON,
        COLOUR_CYCLE_BEATS
    },
    {
        /* FLOWING_HUE */
        LIGHTS_LED_ON,
        COLOUR_FLOWING_HUE
    },
    {
        /* RANDOM_OFFSET_HUE */
        LIGHTS_LED_ON,
        COLOUR_RANDOM_OFFSET
    },
    {
        /* RADIAL_HUE */
        LIGHTS_FLASH,
        COLOUR_RADIAL_HUE
    },
    {
        /* MATRIX */
        LIGHTS_RAIN,
        COLOUR_GREEN
    },
    {
        /* TEXT */
        LIGHTS_TEXT,
        COLOUR_CYCLE
    },
#endif
};

void create_payload(uint8_t buffer[FRAME_SIZE]) {

    /* buffer is reused to save RAM */
    presets[current_effect].light.light_gen_frame(&light_buffer);
    presets[current_effect].colour.colour_gen_frame(buffer);

    uint16_t j = 0;
    for (uint16_t i = 0; i < FRAME_SIZE; i += 3) {
        uint16_t light_damping = ((uint16_t)0xFF - light_buffer[j]);

        if((buffer[i] - light_damping) <= 0) {
            buffer[i] = 0;
        } else {
            buffer[i] = ((buffer[i] - light_damping) >> COLOUR_POWER_RANGE_REDUCTION);
        }
        if((buffer[i+1] - light_damping) <= 0) {
            buffer[i+1] = 0;
        } else {
            buffer[i+1] = ((buffer[i+1] - light_damping) >> COLOUR_POWER_RANGE_REDUCTION);
        }
        if((buffer[i+2]- light_damping) <= 0) {
            buffer[i+2] = 0;
        } else {
            buffer[i+2] = ((buffer[i+2] - light_damping) >> COLOUR_POWER_RANGE_REDUCTION);
        }
        j++;
    }
}

void tx_led_buffer(void) {
    create_payload(&led_buffer);
    transmit_led(led_buffer, FRAME_SIZE);

}

void cycle_effects (void) {
    set_effect(current_effect + 1);
    if (current_effect >= N_EFFECTS) {
        current_effect = LED_OFF;
    }
}

void set_effect(pattern new_pattern) {
    current_effect = new_pattern;
}

void beat_start(void) {
    static uint8_t switch_effect = 1;
    presets[current_effect].light.light_beat_start();
    presets[current_effect].colour.colour_beat_start();

    if ((switch_effect % 16) == 0) {
        //cycle_effects();

    }

    switch_effect++;

    return;
}

void beat_stop(void) {
    presets[current_effect].light.light_beat_stop();
    presets[current_effect].colour.colour_beat_stop();
    return;
}
